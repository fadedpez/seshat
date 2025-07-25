package services

import (
	"context"
	"sync"
	"time"

	pb "github.com/seshat/server/generated/seshat"
)

// EventsService implements the gRPC EventService interface
type EventsService struct {
	pb.UnimplementedEventServiceServer
	subscribers map[string]chan *pb.GameEvent // subscription_id -> channel
	subMutex    sync.RWMutex
	history     []*pb.GameEvent
	histMutex   sync.RWMutex
}

// NewEventsService creates a new events service instance
func NewEventsService() *EventsService {
	return &EventsService{
		subscribers: make(map[string]chan *pb.GameEvent),
		history:     []*pb.GameEvent{},
	}
}

// PublishEvent handles event publishing
func (e *EventsService) PublishEvent(ctx context.Context, req *pb.PublishEventRequest) (*pb.PublishEventResponse, error) {
	if req.Event == nil {
		return &pb.PublishEventResponse{
			Status: &pb.Result{
				Success: false,
				Error: &pb.ErrorDetails{
					Code:    "MISSING_EVENT",
					Message: "Event is required",
				},
			},
		}, nil
	}

	// Set timestamp if not provided
	if req.Event.Timestamp == 0 {
		req.Event.Timestamp = time.Now().Unix()
	}

	// Generate ID if not provided
	if req.Event.Id == "" {
		req.Event.Id = e.generateEventID()
	}

	// Add to history
	e.histMutex.Lock()
	e.history = append(e.history, req.Event)
	// Keep only last 10000 events to prevent memory bloat
	if len(e.history) > 10000 {
		e.history = e.history[len(e.history)-10000:]
	}
	e.histMutex.Unlock()

	// Send to all subscribers
	e.subMutex.RLock()
	for _, ch := range e.subscribers {
		select {
		case ch <- req.Event:
		default:
			// Channel full, skip this subscriber
		}
	}
	e.subMutex.RUnlock()

	return &pb.PublishEventResponse{
		Status: &pb.Result{
			Success: true,
		},
		EventId:   req.Event.Id,
		Timestamp: req.Event.Timestamp,
	}, nil
}

// SubscribeToEvents handles event subscriptions with streaming
func (e *EventsService) SubscribeToEvents(req *pb.SubscribeRequest, stream pb.EventService_SubscribeToEventsServer) error {
	// Create subscription channel
	ch := make(chan *pb.GameEvent, 100) // Buffer for 100 events
	subscriptionID := e.generateSubscriptionID()
	
	e.subMutex.Lock()
	e.subscribers[subscriptionID] = ch
	e.subMutex.Unlock()

	// Cleanup on disconnect
	defer func() {
		e.subMutex.Lock()
		close(ch)
		delete(e.subscribers, subscriptionID)
		e.subMutex.Unlock()
	}()

	// Send historical events if requested
	if req.IncludeHistory {
		e.histMutex.RLock()
		for _, event := range e.history {
			if e.eventMatchesSubscription(event, req.EventTypes) {
				if err := stream.Send(event); err != nil {
					e.histMutex.RUnlock()
					return err
				}
			}
		}
		e.histMutex.RUnlock()
	}

	// Stream live events
	for {
		select {
		case event := <-ch:
			if e.eventMatchesSubscription(event, req.EventTypes) {
				if err := stream.Send(event); err != nil {
					return err
				}
			}
		case <-stream.Context().Done():
			return stream.Context().Err()
		}
	}
}

// SubscribeToAllEvents handles subscription to all events
func (e *EventsService) SubscribeToAllEvents(req *pb.SubscribeAllRequest, stream pb.EventService_SubscribeToAllEventsServer) error {
	// Create subscription channel
	ch := make(chan *pb.GameEvent, 100)
	subscriptionID := e.generateSubscriptionID()
	
	e.subMutex.Lock()
	e.subscribers[subscriptionID] = ch
	e.subMutex.Unlock()

	// Cleanup on disconnect
	defer func() {
		e.subMutex.Lock()
		close(ch)
		delete(e.subscribers, subscriptionID)
		e.subMutex.Unlock()
	}()

	// Send historical events if requested
	if req.IncludeHistory {
		e.histMutex.RLock()
		for _, event := range e.history {
			if err := stream.Send(event); err != nil {
				e.histMutex.RUnlock()
				return err
			}
		}
		e.histMutex.RUnlock()
	}

	// Stream all live events
	for {
		select {
		case event := <-ch:
			if err := stream.Send(event); err != nil {
				return err
			}
		case <-stream.Context().Done():
			return stream.Context().Err()
		}
	}
}

// GetEventHistory returns historical events
func (e *EventsService) GetEventHistory(ctx context.Context, req *pb.EventHistoryRequest) (*pb.EventHistoryResponse, error) {
	e.histMutex.RLock()
	defer e.histMutex.RUnlock()

	filteredEvents := []*pb.GameEvent{}
	
	for _, event := range e.history {
		// Filter by event types
		if len(req.EventTypes) > 0 && !e.eventMatchesSubscription(event, req.EventTypes) {
			continue
		}

		// Filter by entity
		if req.EntityId != "" && event.Context != nil && event.Context.SourceEntityId != req.EntityId {
			continue
		}

		// Filter by timestamp
		if req.SinceTimestamp > 0 && event.Timestamp < req.SinceTimestamp {
			continue
		}
		if req.UntilTimestamp > 0 && event.Timestamp > req.UntilTimestamp {
			continue
		}

		filteredEvents = append(filteredEvents, event)
	}

	// Apply limit
	if req.Limit > 0 && int32(len(filteredEvents)) > req.Limit {
		filteredEvents = filteredEvents[len(filteredEvents)-int(req.Limit):]
	}

	return &pb.EventHistoryResponse{
		Events:     filteredEvents,
		TotalCount: int32(len(filteredEvents)),
		Status: &pb.Result{
			Success: true,
		},
	}, nil
}

// ClearEventHistory clears event history
func (e *EventsService) ClearEventHistory(ctx context.Context, req *pb.ClearEventHistoryRequest) (*pb.ClearEventHistoryResponse, error) {
	e.histMutex.Lock()
	defer e.histMutex.Unlock()

	clearedCount := int32(0)

	if len(req.EventTypes) == 0 && req.EntityId == "" {
		// Clear all history
		clearedCount = int32(len(e.history))
		e.history = []*pb.GameEvent{}
	} else {
		// Selective clearing
		newHistory := []*pb.GameEvent{}
		for _, event := range e.history {
			shouldRemove := false

			// Check event type filter
			if len(req.EventTypes) > 0 {
				for _, eventType := range req.EventTypes {
					if event.Type == eventType {
						shouldRemove = true
						break
					}
				}
			}

			// Check entity filter
			if req.EntityId != "" && event.Context != nil && event.Context.SourceEntityId == req.EntityId {
				shouldRemove = true
			}

			if shouldRemove {
				clearedCount++
			} else {
				newHistory = append(newHistory, event)
			}
		}
		e.history = newHistory
	}

	return &pb.ClearEventHistoryResponse{
		ClearedCount: clearedCount,
		Status: &pb.Result{
			Success: true,
		},
	}, nil
}

// GetSubscriptions returns active subscriptions
func (e *EventsService) GetSubscriptions(ctx context.Context, req *pb.GetSubscriptionsRequest) (*pb.GetSubscriptionsResponse, error) {
	e.subMutex.RLock()
	defer e.subMutex.RUnlock()

	subscriptions := []*pb.Subscription{}
	for subID := range e.subscribers {
		// In a real implementation, we'd store more subscription metadata
		subscriptions = append(subscriptions, &pb.Subscription{
			Id:           subID,
			SubscriberId: req.SubscriberId, // This is a simplification
			EventTypes:   []string{"*"},    // This is a simplification
			Priority:     0,
			CreatedTimestamp: time.Now().Unix(),
			EventsReceived:   0, // Would need to track this
		})
	}

	return &pb.GetSubscriptionsResponse{
		Subscriptions: subscriptions,
		Status: &pb.Result{
			Success: true,
		},
	}, nil
}

// Unsubscribe removes a subscription
func (e *EventsService) Unsubscribe(ctx context.Context, req *pb.UnsubscribeRequest) (*pb.UnsubscribeResponse, error) {
	e.subMutex.Lock()
	defer e.subMutex.Unlock()

	if ch, exists := e.subscribers[req.SubscriptionId]; exists {
		close(ch)
		delete(e.subscribers, req.SubscriptionId)
		return &pb.UnsubscribeResponse{
			Status: &pb.Result{
				Success: true,
			},
		}, nil
	}

	return &pb.UnsubscribeResponse{
		Status: &pb.Result{
			Success: false,
			Error: &pb.ErrorDetails{
				Code:    "SUBSCRIPTION_NOT_FOUND",
				Message: "Subscription ID not found",
			},
		},
	}, nil
}

// Helper functions

func (e *EventsService) generateEventID() string {
	return "evt_" + e.generateID()
}

func (e *EventsService) generateSubscriptionID() string {
	return "sub_" + e.generateID()
}

func (e *EventsService) generateID() string {
	// Simple ID generation - in production, use UUID or similar
	return time.Now().Format("20060102150405") + "_" + string(rune(time.Now().Nanosecond()%1000000))
}

func (e *EventsService) eventMatchesSubscription(event *pb.GameEvent, subscriptionTypes []string) bool {
	if len(subscriptionTypes) == 0 {
		return true // No filter means match all
	}

	for _, subType := range subscriptionTypes {
		if subType == "*" || subType == event.Type {
			return true
		}
	}
	return false
}