package services

import (
	"context"
	"crypto/rand"
	"fmt"
	"math/big"
	"time"

	pb "github.com/seshat/server/generated/seshat"
)

// DiceService implements the gRPC DiceService interface
type DiceService struct {
	pb.UnimplementedDiceServiceServer
	history map[string][]*pb.RollRecord // entity_id -> roll history
}

// NewDiceService creates a new dice service instance
func NewDiceService() *DiceService {
	return &DiceService{
		history: make(map[string][]*pb.RollRecord),
	}
}

// SimpleDiceRoller provides basic dice rolling functionality
func (d *DiceService) roll(sides int) (int, error) {
	if sides <= 0 {
		return 0, fmt.Errorf("invalid die size: %d", sides)
	}
	
	n, err := rand.Int(rand.Reader, big.NewInt(int64(sides)))
	if err != nil {
		return 0, fmt.Errorf("crypto/rand error: %w", err)
	}
	
	return int(n.Int64()) + 1, nil
}

func (d *DiceService) rollN(count, sides int) ([]int, error) {
	if count <= 0 || sides <= 0 {
		return nil, fmt.Errorf("invalid parameters: count=%d, sides=%d", count, sides)
	}
	
	results := make([]int, count)
	for i := 0; i < count; i++ {
		roll, err := d.roll(sides)
		if err != nil {
			return nil, err
		}
		results[i] = roll
	}
	
	return results, nil
}

// Roll handles basic single die rolls
func (d *DiceService) Roll(ctx context.Context, req *pb.RollRequest) (*pb.RollResponse, error) {
	// Validate input
	if req.Sides <= 0 {
		return &pb.RollResponse{
			Status: &pb.Result{
				Success: false,
				Error: &pb.ErrorDetails{
					Code:    "INVALID_SIDES",
					Message: fmt.Sprintf("Invalid die size: %d", req.Sides),
				},
			},
		}, nil
	}

	// Roll the die
	result, err := d.roll(int(req.Sides))
	if err != nil {
		return &pb.RollResponse{
			Status: &pb.Result{
				Success: false,
				Error: &pb.ErrorDetails{
					Code:    "ROLL_FAILED",
					Message: err.Error(),
				},
			},
		}, nil
	}

	timestamp := time.Now().Unix()

	// Store in history
	d.addToHistory(req.EntityId, &pb.RollRecord{
		Formula:          fmt.Sprintf("1d%d", req.Sides),
		Result:           int32(result),
		Context:          req.Context,
		EntityId:         req.EntityId,
		Timestamp:        timestamp,
		IndividualRolls:  []int32{int32(result)},
	})

	return &pb.RollResponse{
		Result:    int32(result),
		Context:   req.Context,
		EntityId:  req.EntityId,
		Timestamp: timestamp,
		Status: &pb.Result{
			Success: true,
		},
	}, nil
}

// RollMultiple handles rolling multiple dice of the same type
func (d *DiceService) RollMultiple(ctx context.Context, req *pb.RollMultipleRequest) (*pb.RollMultipleResponse, error) {
	// Validate input
	if req.Sides <= 0 {
		return &pb.RollMultipleResponse{
			Status: &pb.Result{
				Success: false,
				Error: &pb.ErrorDetails{
					Code:    "INVALID_SIDES",
					Message: fmt.Sprintf("Invalid die size: %d", req.Sides),
				},
			},
		}, nil
	}

	if req.Count <= 0 {
		return &pb.RollMultipleResponse{
			Status: &pb.Result{
				Success: false,
				Error: &pb.ErrorDetails{
					Code:    "INVALID_COUNT",
					Message: fmt.Sprintf("Invalid roll count: %d", req.Count),
				},
			},
		}, nil
	}

	// Roll multiple dice
	rolls, err := d.rollN(int(req.Count), int(req.Sides))
	if err != nil {
		return &pb.RollMultipleResponse{
			Status: &pb.Result{
				Success: false,
				Error: &pb.ErrorDetails{
					Code:    "ROLL_FAILED",
					Message: err.Error(),
				},
			},
		}, nil
	}

	// Convert to int32 slice
	rollsInt32 := make([]int32, len(rolls))
	total := int32(0)
	for i, roll := range rolls {
		rollsInt32[i] = int32(roll)
		total += int32(roll)
	}

	// Handle drop lowest/highest logic
	keptRolls := rollsInt32
	droppedRolls := []int32{}

	if req.DropLowest && len(rollsInt32) > 1 {
		keptRolls, droppedRolls = d.dropLowest(rollsInt32, 1)
	} else if req.DropHighest && len(rollsInt32) > 1 {
		keptRolls, droppedRolls = d.dropHighest(rollsInt32, 1)
	} else if req.KeepCount > 0 && req.KeepCount < int32(len(rollsInt32)) {
		// Keep highest N rolls
		keptRolls, droppedRolls = d.keepHighest(rollsInt32, int(req.KeepCount))
	}

	// Recalculate total from kept rolls
	keptTotal := int32(0)
	for _, roll := range keptRolls {
		keptTotal += roll
	}

	timestamp := time.Now().Unix()

	// Store in history
	d.addToHistory(req.EntityId, &pb.RollRecord{
		Formula:          fmt.Sprintf("%dd%d", req.Count, req.Sides),
		Result:           keptTotal,
		Context:          req.Context,
		EntityId:         req.EntityId,
		Timestamp:        timestamp,
		IndividualRolls:  rollsInt32,
	})

	return &pb.RollMultipleResponse{
		Rolls:        rollsInt32,
		Total:        total,
		KeptRolls:    keptRolls,
		DroppedRolls: droppedRolls,
		Context:      req.Context,
		EntityId:     req.EntityId,
		Timestamp:    timestamp,
		Status: &pb.Result{
			Success: true,
		},
	}, nil
}

// RollFormula handles dice formulas like "2d6+3"
func (d *DiceService) RollFormula(ctx context.Context, req *pb.RollFormulaRequest) (*pb.RollFormulaResponse, error) {
	// For now, implement a simple parser for basic formulas
	// This is a learning exercise, so we'll start simple and expand
	
	// TODO: Implement full dice formula parser
	// For now, return an error to indicate this needs implementation
	return &pb.RollFormulaResponse{
		Status: &pb.Result{
			Success: false,
			Error: &pb.ErrorDetails{
				Code:    "NOT_IMPLEMENTED",
				Message: "Formula parsing not yet implemented - this is a learning exercise!",
			},
		},
	}, nil
}

// StreamRolls handles streaming dice rolls
func (d *DiceService) StreamRolls(stream pb.DiceService_StreamRollsServer) error {
	for {
		req, err := stream.Recv()
		if err != nil {
			return err
		}

		// Process the roll request
		resp, err := d.Roll(stream.Context(), req)
		if err != nil {
			return err
		}

		// Send response back
		if err := stream.Send(resp); err != nil {
			return err
		}
	}
}

// GetRollHistory returns roll history for an entity
func (d *DiceService) GetRollHistory(ctx context.Context, req *pb.RollHistoryRequest) (*pb.RollHistoryResponse, error) {
	entityHistory, exists := d.history[req.EntityId]
	if !exists {
		return &pb.RollHistoryResponse{
			Rolls:      []*pb.RollRecord{},
			TotalCount: 0,
			Status: &pb.Result{
				Success: true,
			},
		}, nil
	}

	// Filter by context if specified
	filteredRolls := entityHistory
	if req.Context != "" {
		filteredRolls = []*pb.RollRecord{}
		for _, roll := range entityHistory {
			if roll.Context == req.Context {
				filteredRolls = append(filteredRolls, roll)
			}
		}
	}

	// Filter by timestamp if specified
	if req.SinceTimestamp > 0 {
		timeFilteredRolls := []*pb.RollRecord{}
		for _, roll := range filteredRolls {
			if roll.Timestamp >= req.SinceTimestamp {
				timeFilteredRolls = append(timeFilteredRolls, roll)
			}
		}
		filteredRolls = timeFilteredRolls
	}

	// Apply limit
	if req.Limit > 0 && int32(len(filteredRolls)) > req.Limit {
		filteredRolls = filteredRolls[len(filteredRolls)-int(req.Limit):]
	}

	return &pb.RollHistoryResponse{
		Rolls:      filteredRolls,
		TotalCount: int32(len(filteredRolls)),
		Status: &pb.Result{
			Success: true,
		},
	}, nil
}

// TestFairness performs statistical analysis of die fairness
func (d *DiceService) TestFairness(ctx context.Context, req *pb.FairnessTestRequest) (*pb.FairnessTestResponse, error) {
	if req.Sides <= 0 || req.SampleSize <= 0 {
		return &pb.FairnessTestResponse{
			Status: &pb.Result{
				Success: false,
				Error: &pb.ErrorDetails{
					Code:    "INVALID_PARAMETERS",
					Message: "Sides and sample size must be positive",
				},
			},
		}, nil
	}

	// Perform the test rolls
	distribution := make([]int32, req.Sides)
	for i := 0; i < int(req.SampleSize); i++ {
		roll, err := d.roll(int(req.Sides))
		if err != nil {
			return &pb.FairnessTestResponse{
				Status: &pb.Result{
					Success: false,
					Error: &pb.ErrorDetails{
						Code:    "ROLL_FAILED",
						Message: err.Error(),
					},
				},
			}, nil
		}
		distribution[roll-1]++ // Convert to 0-based index
	}

	// Calculate chi-squared test
	expected := float64(req.SampleSize) / float64(req.Sides)
	chiSquared := 0.0
	for _, observed := range distribution {
		diff := float64(observed) - expected
		chiSquared += (diff * diff) / expected
	}

	// Very simple fairness assessment (would need proper statistical tables for real use)
	degreesOfFreedom := req.Sides - 1
	criticalValue := float64(degreesOfFreedom) * 2.0 // Rough approximation
	isFair := chiSquared < criticalValue

	return &pb.FairnessTestResponse{
		Distribution: distribution,
		ChiSquared:   chiSquared,
		PValue:       0.0, // Would need proper calculation
		IsFair:       isFair,
		SampleSize:   req.SampleSize,
		Status: &pb.Result{
			Success: true,
		},
	}, nil
}

// Helper functions

func (d *DiceService) addToHistory(entityId string, record *pb.RollRecord) {
	if d.history[entityId] == nil {
		d.history[entityId] = []*pb.RollRecord{}
	}
	d.history[entityId] = append(d.history[entityId], record)
	
	// Keep only last 1000 rolls per entity to prevent memory bloat
	if len(d.history[entityId]) > 1000 {
		d.history[entityId] = d.history[entityId][len(d.history[entityId])-1000:]
	}
}

func (d *DiceService) dropLowest(rolls []int32, count int) (kept []int32, dropped []int32) {
	// Simple implementation - find and remove lowest values
	remaining := make([]int32, len(rolls))
	copy(remaining, rolls)
	
	for i := 0; i < count && len(remaining) > 1; i++ {
		minIdx := 0
		for j, roll := range remaining {
			if roll < remaining[minIdx] {
				minIdx = j
			}
		}
		dropped = append(dropped, remaining[minIdx])
		remaining = append(remaining[:minIdx], remaining[minIdx+1:]...)
	}
	
	return remaining, dropped
}

func (d *DiceService) dropHighest(rolls []int32, count int) (kept []int32, dropped []int32) {
	// Simple implementation - find and remove highest values
	remaining := make([]int32, len(rolls))
	copy(remaining, rolls)
	
	for i := 0; i < count && len(remaining) > 1; i++ {
		maxIdx := 0
		for j, roll := range remaining {
			if roll > remaining[maxIdx] {
				maxIdx = j
			}
		}
		dropped = append(dropped, remaining[maxIdx])
		remaining = append(remaining[:maxIdx], remaining[maxIdx+1:]...)
	}
	
	return remaining, dropped
}

func (d *DiceService) keepHighest(rolls []int32, keepCount int) (kept []int32, dropped []int32) {
	if keepCount >= len(rolls) {
		return rolls, []int32{}
	}
	
	// Sort rolls to find highest
	sorted := make([]int32, len(rolls))
	copy(sorted, rolls)
	
	// Simple bubble sort (good enough for dice rolls)
	for i := 0; i < len(sorted); i++ {
		for j := 0; j < len(sorted)-1-i; j++ {
			if sorted[j] < sorted[j+1] {
				sorted[j], sorted[j+1] = sorted[j+1], sorted[j]
			}
		}
	}
	
	return sorted[:keepCount], sorted[keepCount:]
}