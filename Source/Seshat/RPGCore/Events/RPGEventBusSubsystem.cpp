#include "RPGEventBusSubsystem.h"
#include "HAL/PlatformProcess.h"
#include "Misc/Paths.h"
#include "Engine/World.h"
#include "TimerManager.h"

void URPGEventBusSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
    
    UE_LOG(LogTemp, Warning, TEXT("URPGEventBusSubsystem: Initializing"));
    
    // Initialize state
    bToolkitLoaded = false;
    ToolkitDLLHandle = nullptr;
    EventStatistics.Reset();
    
    // Clear collections
    EventSubscriptions.Empty();
    FilteredEventTypes.Empty();
    DeferredEvents.Empty();
    
    // Load DLL functions for event system
    LoadToolkitDLL();
    LoadEventDLLFunctions();
    
    if (bToolkitLoaded)
    {
        InitializeEventSystem();
        UE_LOG(LogTemp, Warning, TEXT("URPGEventBusSubsystem: Event system initialized successfully"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("URPGEventBusSubsystem: Event system initialized without toolkit integration"));
    }
    
    // Set up periodic cleanup timer (every 30 seconds)
    if (UWorld* World = GetWorld())
    {
        World->GetTimerManager().SetTimer(CleanupTimerHandle, this, 
            &URPGEventBusSubsystem::PerformPeriodicCleanup, 30.0f, true);
    }
}

void URPGEventBusSubsystem::Deinitialize()
{
    UE_LOG(LogTemp, Warning, TEXT("URPGEventBusSubsystem: Deinitializing"));
    
    // Clear cleanup timer
    if (UWorld* World = GetWorld())
    {
        World->GetTimerManager().ClearTimer(CleanupTimerHandle);
    }
    
    // Clear all subscriptions
    FScopeLock Lock(&EventBusLock);
    EventSubscriptions.Empty();
    FilteredEventTypes.Empty();
    DeferredEvents.Empty();
    
    // Clear function pointers to prevent shutdown crashes
    bToolkitLoaded = false;
    PublishEventFuncPtr = nullptr;
    SubscribeEventFuncPtr = nullptr;
    UnsubscribeEventFuncPtr = nullptr;
    GetEventDataFuncPtr = nullptr;
    ToolkitDLLHandle = nullptr;
    
    // Don't unload DLL - let Windows handle cleanup on process exit
    // Following same pattern as RPGDiceSubsystem
    
    Super::Deinitialize();
}

bool URPGEventBusSubsystem::PublishEvent(const FRPGEventContext& EventContext)
{
    if (!EventContext.IsValid())
    {
        UE_LOG(LogTemp, Warning, TEXT("URPGEventBusSubsystem::PublishEvent: Invalid event context"));
        return false;
    }
    
    // Check if event type is filtered
    if (IsEventFiltered(EventContext.EventType))
    {
        UE_LOG(LogTemp, VeryVerbose, TEXT("URPGEventBusSubsystem::PublishEvent: Event type %s is filtered"), 
               *RPGEventTypes::EventTypeToString(EventContext.EventType));
        return false;
    }
    
    double StartTime = FPlatformTime::Seconds();
    
    // Process the event
    ERPGEventResult Result = ProcessEventInternal(EventContext);
    
    double ProcessingTime = FPlatformTime::Seconds() - StartTime;
    
    // Update statistics
    UpdateEventStatistics(EventContext.EventType, ProcessingTime, Result);
    
    // Broadcast event published
    OnEventPublished.Broadcast(EventContext);
    
    // Sync with toolkit if available
    if (bToolkitLoaded)
    {
        SyncEventWithToolkit(EventContext);
    }
    
    UE_LOG(LogTemp, VeryVerbose, TEXT("URPGEventBusSubsystem::PublishEvent: Published %s event in %.4f seconds"), 
           *RPGEventTypes::EventTypeToString(EventContext.EventType), ProcessingTime);
    
    return Result != ERPGEventResult::Error;
}

bool URPGEventBusSubsystem::PublishEventDeferred(const FRPGEventContext& EventContext, float DelaySeconds)
{
    if (!EventContext.IsValid())
    {
        return false;
    }
    
    double ScheduledTime = FApp::GetCurrentTime() + DelaySeconds;
    
    FScopeLock Lock(&EventBusLock);
    DeferredEvents.Add(FDeferredEvent(EventContext, ScheduledTime));
    
    UE_LOG(LogTemp, VeryVerbose, TEXT("URPGEventBusSubsystem::PublishEventDeferred: Scheduled %s event for %.2f seconds"), 
           *RPGEventTypes::EventTypeToString(EventContext.EventType), DelaySeconds);
    
    return true;
}

bool URPGEventBusSubsystem::PublishEventToEntity(const FRPGEventContext& EventContext, 
                                               TScriptInterface<IRPGEntityInterface> TargetEntity)
{
    if (!TargetEntity.GetInterface())
    {
        return PublishEvent(EventContext);
    }
    
    // Create a modified context with the target entity
    FRPGEventContext ModifiedContext = EventContext;
    ModifiedContext.TargetEntity = TargetEntity;
    
    return PublishEvent(ModifiedContext);
}

FString URPGEventBusSubsystem::Subscribe(ERPGEventType EventType, TScriptInterface<IRPGEventInterface> Handler, 
                                        ERPGEventPriority Priority)
{
    if (!Handler.GetInterface())
    {
        UE_LOG(LogTemp, Warning, TEXT("URPGEventBusSubsystem::Subscribe: Invalid handler for event type %s"), 
               *RPGEventTypes::EventTypeToString(EventType));
        return FString();
    }
    
    FScopeLock Lock(&EventBusLock);
    
    // Create subscription
    FRPGEventSubscription Subscription(Handler, Priority);
    
    // Add to subscriptions
    if (!EventSubscriptions.Contains(EventType))
    {
        EventSubscriptions.Add(EventType, TArray<FRPGEventSubscription>());
    }
    
    EventSubscriptions[EventType].Add(Subscription);
    
    // Sort by priority (higher priority first)
    SortSubscriptionsByPriority(EventSubscriptions[EventType]);
    
    // Broadcast subscription change
    OnSubscriptionChanged.Broadcast(EventType, true);
    
    UE_LOG(LogTemp, VeryVerbose, TEXT("URPGEventBusSubsystem::Subscribe: Subscribed handler to %s events with priority %d"), 
           *RPGEventTypes::EventTypeToString(EventType), static_cast<int32>(Priority));
    
    return Subscription.SubscriptionID;
}

bool URPGEventBusSubsystem::Unsubscribe(ERPGEventType EventType, TScriptInterface<IRPGEventInterface> Handler)
{
    if (!Handler.GetInterface())
    {
        return false;
    }
    
    FScopeLock Lock(&EventBusLock);
    
    if (!EventSubscriptions.Contains(EventType))
    {
        return false;
    }
    
    TArray<FRPGEventSubscription>& Subscriptions = EventSubscriptions[EventType];
    
    // Remove subscriptions for this handler
    int32 RemovedCount = Subscriptions.RemoveAll([Handler](const FRPGEventSubscription& Sub)
    {
        return Sub.Handler.GetInterface() == Handler.GetInterface();
    });
    
    if (RemovedCount > 0)
    {
        // Broadcast subscription change
        OnSubscriptionChanged.Broadcast(EventType, false);
        
        UE_LOG(LogTemp, VeryVerbose, TEXT("URPGEventBusSubsystem::Unsubscribe: Removed %d subscriptions for %s events"), 
               RemovedCount, *RPGEventTypes::EventTypeToString(EventType));
        
        return true;
    }
    
    return false;
}

bool URPGEventBusSubsystem::UnsubscribeByID(const FString& SubscriptionID)
{
    if (SubscriptionID.IsEmpty())
    {
        return false;
    }
    
    FScopeLock Lock(&EventBusLock);
    
    // Search through all event types
    for (auto& Pair : EventSubscriptions)
    {
        TArray<FRPGEventSubscription>& Subscriptions = Pair.Value;
        
        int32 RemovedCount = Subscriptions.RemoveAll([SubscriptionID](const FRPGEventSubscription& Sub)
        {
            return Sub.SubscriptionID == SubscriptionID;
        });
        
        if (RemovedCount > 0)
        {
            OnSubscriptionChanged.Broadcast(Pair.Key, false);
            return true;
        }
    }
    
    return false;
}

void URPGEventBusSubsystem::UnsubscribeAll(TScriptInterface<IRPGEventInterface> Handler)
{
    if (!Handler.GetInterface())
    {
        return;
    }
    
    FScopeLock Lock(&EventBusLock);
    
    // Remove from all event types
    for (auto& Pair : EventSubscriptions)
    {
        TArray<FRPGEventSubscription>& Subscriptions = Pair.Value;
        
        int32 RemovedCount = Subscriptions.RemoveAll([Handler](const FRPGEventSubscription& Sub)
        {
            return Sub.Handler.GetInterface() == Handler.GetInterface();
        });
        
        if (RemovedCount > 0)
        {
            OnSubscriptionChanged.Broadcast(Pair.Key, false);
        }
    }
    
    UE_LOG(LogTemp, VeryVerbose, TEXT("URPGEventBusSubsystem::UnsubscribeAll: Removed all subscriptions for handler"));
}

int32 URPGEventBusSubsystem::GetSubscriptionCount(ERPGEventType EventType) const
{
    FScopeLock Lock(&EventBusLock);
    
    if (const TArray<FRPGEventSubscription>* Subscriptions = EventSubscriptions.Find(EventType))
    {
        return Subscriptions->Num();
    }
    
    return 0;
}

bool URPGEventBusSubsystem::IsSubscribed(ERPGEventType EventType, TScriptInterface<IRPGEventInterface> Handler) const
{
    if (!Handler.GetInterface())
    {
        return false;
    }
    
    FScopeLock Lock(&EventBusLock);
    
    if (const TArray<FRPGEventSubscription>* Subscriptions = EventSubscriptions.Find(EventType))
    {
        for (const FRPGEventSubscription& Sub : *Subscriptions)
        {
            if (Sub.Handler.GetInterface() == Handler.GetInterface())
            {
                return true;
            }
        }
    }
    
    return false;
}

ERPGEventResult URPGEventBusSubsystem::ProcessEventInternal(const FRPGEventContext& EventContext)
{
    FScopeLock Lock(&EventBusLock);
    
    // Get subscriptions for this event type
    const TArray<FRPGEventSubscription>* Subscriptions = EventSubscriptions.Find(EventContext.EventType);
    
    if (!Subscriptions || Subscriptions->Num() == 0)
    {
        UE_LOG(LogTemp, VeryVerbose, TEXT("URPGEventBusSubsystem::ProcessEventInternal: No handlers for event type %s"), 
               *RPGEventTypes::EventTypeToString(EventContext.EventType));
        return ERPGEventResult::Unhandled;
    }
    
    // Process handlers
    NotifyHandlers(EventContext, *Subscriptions);
    
    return ERPGEventResult::Handled;
}

void URPGEventBusSubsystem::NotifyHandlers(const FRPGEventContext& EventContext, 
                                         const TArray<FRPGEventSubscription>& Handlers)
{
    FRPGEventContext MutableContext = EventContext;
    
    for (const FRPGEventSubscription& Subscription : Handlers)
    {
        if (!Subscription.IsValid() || Subscription.IsExpired())
        {
            continue;
        }
        
        if (MutableContext.bCancelled)
        {
            UE_LOG(LogTemp, VeryVerbose, TEXT("URPGEventBusSubsystem::NotifyHandlers: Event cancelled, stopping processing"));
            break;
        }
        
        ERPGEventResult Result = ERPGEventResult::Unhandled;
        
        // Call the handler
        if (Subscription.Handler.GetInterface())
        {
            Result = Subscription.Handler->HandleEvent(MutableContext);
        }
        
        // Broadcast that event was handled
        OnEventHandled.Broadcast(MutableContext, Result);
        
        // Stop processing if handler requests it
        if (Result == ERPGEventResult::HandledStopProcessing)
        {
            UE_LOG(LogTemp, VeryVerbose, TEXT("URPGEventBusSubsystem::NotifyHandlers: Handler requested to stop processing"));
            break;
        }
        
        // Mark as handled if a handler processed it
        if (Result == ERPGEventResult::Handled || Result == ERPGEventResult::HandledStopProcessing)
        {
            MutableContext.bHandled = true;
        }
    }
}

void URPGEventBusSubsystem::ProcessDeferredEvents()
{
    FScopeLock Lock(&EventBusLock);
    
    double CurrentTime = FApp::GetCurrentTime();
    TArray<FDeferredEvent> EventsToProcess;
    
    // Find events ready to process
    for (int32 i = DeferredEvents.Num() - 1; i >= 0; i--)
    {
        const FDeferredEvent& DeferredEvent = DeferredEvents[i];
        
        if (CurrentTime >= DeferredEvent.ScheduledTime)
        {
            EventsToProcess.Add(DeferredEvent);
            DeferredEvents.RemoveAt(i);
        }
    }
    
    // Process events (unlock while processing)
    EventBusLock.Unlock();
    
    for (const FDeferredEvent& Event : EventsToProcess)
    {
        PublishEvent(Event.EventContext);
    }
    
    EventBusLock.Lock();
    
    if (EventsToProcess.Num() > 0)
    {
        UE_LOG(LogTemp, VeryVerbose, TEXT("URPGEventBusSubsystem::ProcessDeferredEvents: Processed %d deferred events"), 
               EventsToProcess.Num());
    }
}

void URPGEventBusSubsystem::LoadToolkitDLL()
{
    // Use same DLL loading pattern as RPGDiceSubsystem
    // Construct the path to our DLL in the proper binary directory
    FString BinariesDir = FPaths::Combine(FPaths::ProjectDir(), TEXT("Binaries"), FPlatformProcess::GetBinariesSubdirectory());
    FString LibraryPath = FPaths::Combine(BinariesDir, TEXT("rpg_toolkit.dll"));
    LibraryPath = FPaths::ConvertRelativePathToFull(LibraryPath);

    if (!FPaths::FileExists(LibraryPath))
    {
        UE_LOG(LogTemp, Warning, TEXT("URPGEventBusSubsystem: Toolkit DLL not found, event system will work without toolkit integration"));
        return;
    }

    ToolkitDLLHandle = FPlatformProcess::GetDllHandle(*LibraryPath);
    if (ToolkitDLLHandle)
    {
        UE_LOG(LogTemp, Warning, TEXT("URPGEventBusSubsystem: Toolkit DLL loaded successfully"));
    }
}

void URPGEventBusSubsystem::LoadEventDLLFunctions()
{
    if (!ToolkitDLLHandle)
    {
        return;
    }
    
    // For now, we'll use placeholder function loading since event bindings don't exist yet
    // In the future, this will load actual event-specific functions from the DLL
    
    bToolkitLoaded = false; // Set to true when actual event functions are available
    
    UE_LOG(LogTemp, Warning, TEXT("URPGEventBusSubsystem: Event DLL functions not yet implemented in toolkit"));
}

bool URPGEventBusSubsystem::InitializeEventSystem()
{
    // Initialize event system state
    EventStatistics.Reset();
    
    UE_LOG(LogTemp, Warning, TEXT("URPGEventBusSubsystem: Event system initialized"));
    return true;
}

void URPGEventBusSubsystem::UpdateEventStatistics(ERPGEventType EventType, float ProcessingTime, ERPGEventResult Result)
{
    EventStatistics.TotalEventsPublished++;
    
    if (Result == ERPGEventResult::Handled || Result == ERPGEventResult::HandledStopProcessing)
    {
        EventStatistics.TotalEventsHandled++;
    }
    
    // Update per-type statistics
    int32& TypeCount = EventStatistics.EventTypeCounts.FindOrAdd(EventType, 0);
    TypeCount++;
    
    float& AvgTime = EventStatistics.EventProcessingTimes.FindOrAdd(EventType, 0.0f);
    AvgTime = (AvgTime * (TypeCount - 1) + ProcessingTime) / TypeCount;
}

void URPGEventBusSubsystem::PerformPeriodicCleanup()
{
    FScopeLock Lock(&EventBusLock);
    CleanupExpiredSubscriptions();
}

void URPGEventBusSubsystem::CleanupExpiredSubscriptions()
{
    for (auto& Pair : EventSubscriptions)
    {
        TArray<FRPGEventSubscription>& Subscriptions = Pair.Value;
        
        int32 RemovedCount = Subscriptions.RemoveAll([](const FRPGEventSubscription& Sub)
        {
            return !Sub.IsValid() || Sub.IsExpired();
        });
        
        if (RemovedCount > 0)
        {
            UE_LOG(LogTemp, VeryVerbose, TEXT("URPGEventBusSubsystem::CleanupExpiredSubscriptions: Removed %d expired subscriptions for %s"), 
                   RemovedCount, *RPGEventTypes::EventTypeToString(Pair.Key));
        }
    }
}

void URPGEventBusSubsystem::SortSubscriptionsByPriority(TArray<FRPGEventSubscription>& Subscriptions)
{
    Subscriptions.Sort([](const FRPGEventSubscription& A, const FRPGEventSubscription& B)
    {
        return static_cast<uint8>(A.Priority) > static_cast<uint8>(B.Priority);
    });
}

bool URPGEventBusSubsystem::SyncEventWithToolkit(const FRPGEventContext& EventContext)
{
    // Placeholder for toolkit synchronization
    // Will be implemented when toolkit event bindings are available
    return true;
}

void URPGEventBusSubsystem::SetEventFilter(ERPGEventType EventType, bool bAllowEvent)
{
    FScopeLock Lock(&EventBusLock);
    
    if (bAllowEvent)
    {
        FilteredEventTypes.Remove(EventType);
        UE_LOG(LogTemp, VeryVerbose, TEXT("URPGEventBusSubsystem::SetEventFilter: Removed filter for %s events"), 
               *RPGEventTypes::EventTypeToString(EventType));
    }
    else
    {
        FilteredEventTypes.Add(EventType);
        UE_LOG(LogTemp, VeryVerbose, TEXT("URPGEventBusSubsystem::SetEventFilter: Added filter for %s events"), 
               *RPGEventTypes::EventTypeToString(EventType));
    }
}

bool URPGEventBusSubsystem::IsEventFiltered(ERPGEventType EventType) const
{
    FScopeLock Lock(&EventBusLock);
    return FilteredEventTypes.Contains(EventType);
}

void URPGEventBusSubsystem::ClearEventFilters()
{
    FScopeLock Lock(&EventBusLock);
    FilteredEventTypes.Empty();
    UE_LOG(LogTemp, VeryVerbose, TEXT("URPGEventBusSubsystem::ClearEventFilters: Cleared all event filters"));
}

int32 URPGEventBusSubsystem::GetEventTypeCount(ERPGEventType EventType) const
{
    if (const int32* Count = EventStatistics.EventTypeCounts.Find(EventType))
    {
        return *Count;
    }
    return 0;
}

float URPGEventBusSubsystem::GetEventProcessingTime(ERPGEventType EventType) const
{
    if (const float* Time = EventStatistics.EventProcessingTimes.Find(EventType))
    {
        return *Time;
    }
    return 0.0f;
}

TArray<FString> URPGEventBusSubsystem::GetSubscriptionIDs(ERPGEventType EventType) const
{
    TArray<FString> SubscriptionIDs;
    
    FScopeLock Lock(&EventBusLock);
    
    if (const TArray<FRPGEventSubscription>* Subscriptions = EventSubscriptions.Find(EventType))
    {
        for (const FRPGEventSubscription& Sub : *Subscriptions)
        {
            SubscriptionIDs.Add(Sub.SubscriptionID);
        }
    }
    
    return SubscriptionIDs;
}

void URPGEventBusSubsystem::ClearEventQueue()
{
    FScopeLock Lock(&EventBusLock);
    DeferredEvents.Empty();
    UE_LOG(LogTemp, VeryVerbose, TEXT("URPGEventBusSubsystem::ClearEventQueue: Cleared event queue"));
}

void URPGEventBusSubsystem::DumpEventStatistics() const
{
    UE_LOG(LogTemp, Warning, TEXT("=== RPG Event Bus Statistics ==="));
    UE_LOG(LogTemp, Warning, TEXT("Total Events Published: %d"), EventStatistics.TotalEventsPublished);
    UE_LOG(LogTemp, Warning, TEXT("Total Events Handled: %d"), EventStatistics.TotalEventsHandled);
    UE_LOG(LogTemp, Warning, TEXT("Total Events Cancelled: %d"), EventStatistics.TotalEventsCancelled);
    UE_LOG(LogTemp, Warning, TEXT("Queued Events: %d"), DeferredEvents.Num());
    
    UE_LOG(LogTemp, Warning, TEXT("Event Type Breakdown:"));
    for (const auto& Pair : EventStatistics.EventTypeCounts)
    {
        FString EventTypeName = RPGEventTypes::EventTypeToString(Pair.Key);
        float AvgTime = EventStatistics.EventProcessingTimes.FindRef(Pair.Key);
        UE_LOG(LogTemp, Warning, TEXT("  %s: %d events (avg: %.4f ms)"), 
               *EventTypeName, Pair.Value, AvgTime * 1000.0f);
    }
    
    UE_LOG(LogTemp, Warning, TEXT("Subscription Counts:"));
    for (const auto& Pair : EventSubscriptions)
    {
        FString EventTypeName = RPGEventTypes::EventTypeToString(Pair.Key);
        UE_LOG(LogTemp, Warning, TEXT("  %s: %d subscriptions"), *EventTypeName, Pair.Value.Num());
    }
    
    UE_LOG(LogTemp, Warning, TEXT("Filtered Event Types: %d"), FilteredEventTypes.Num());
    for (ERPGEventType FilteredType : FilteredEventTypes)
    {
        UE_LOG(LogTemp, Warning, TEXT("  %s (filtered)"), *RPGEventTypes::EventTypeToString(FilteredType));
    }
    
    UE_LOG(LogTemp, Warning, TEXT("==============================="));
}

void URPGEventBusSubsystem::DumpSubscriptions() const
{
    FScopeLock Lock(&EventBusLock);
    
    UE_LOG(LogTemp, Warning, TEXT("=== RPG Event Bus Subscriptions ==="));
    
    for (const auto& Pair : EventSubscriptions)
    {
        FString EventTypeName = RPGEventTypes::EventTypeToString(Pair.Key);
        const TArray<FRPGEventSubscription>& Subscriptions = Pair.Value;
        
        UE_LOG(LogTemp, Warning, TEXT("%s (%d subscriptions):"), *EventTypeName, Subscriptions.Num());
        
        for (int32 i = 0; i < Subscriptions.Num(); i++)
        {
            const FRPGEventSubscription& Sub = Subscriptions[i];
            FString Status = Sub.IsValid() ? TEXT("Active") : TEXT("Invalid");
            if (Sub.IsExpired())
            {
                Status = TEXT("Expired");
            }
            
            UE_LOG(LogTemp, Warning, TEXT("  [%d] ID:%s Priority:%d Status:%s"), 
                   i, *Sub.SubscriptionID, static_cast<int32>(Sub.Priority), *Status);
        }
    }
    
    UE_LOG(LogTemp, Warning, TEXT("==================================="));
}

void URPGEventBusSubsystem::ResetEventStatistics()
{
    EventStatistics.Reset();
    UE_LOG(LogTemp, Warning, TEXT("URPGEventBusSubsystem::ResetEventStatistics: Event statistics reset"));
}