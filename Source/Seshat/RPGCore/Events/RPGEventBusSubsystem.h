#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "RPGEventTypes.h"
#include "RPGEventContext.h"
#include "RPGEvent.h"
#include "../Entity/RPGEntity.h"
#include "RPGEventBusSubsystem.generated.h"

// Forward declarations
class IRPGEventInterface;

/**
 * Delegates for event bus lifecycle events
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRPGEventPublished, const FRPGEventContext&, EventContext);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnRPGEventHandled, const FRPGEventContext&, EventContext, ERPGEventResult, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnRPGEventSubscription, ERPGEventType, EventType, bool, bSubscribed);

/**
 * Deferred event structure for delayed event processing
 */
USTRUCT()
struct FDeferredEvent
{
    GENERATED_BODY()

    FRPGEventContext EventContext;
    double ScheduledTime;

    FDeferredEvent()
        : ScheduledTime(0.0)
    {
    }

    FDeferredEvent(const FRPGEventContext& InContext, double InScheduledTime)
        : EventContext(InContext)
        , ScheduledTime(InScheduledTime)
    {
    }
};

/**
 * Event statistics structure for tracking event bus performance
 */
USTRUCT()
struct FRPGEventStatistics
{
    GENERATED_BODY()

    int32 TotalEventsPublished = 0;
    int32 TotalEventsHandled = 0;
    int32 TotalEventsCancelled = 0;
    TMap<ERPGEventType, int32> EventTypeCounts;
    TMap<ERPGEventType, float> EventProcessingTimes;
    double LastResetTime = 0.0;

    void Reset()
    {
        TotalEventsPublished = 0;
        TotalEventsHandled = 0;
        TotalEventsCancelled = 0;
        EventTypeCounts.Empty();
        EventProcessingTimes.Empty();
        LastResetTime = FApp::GetCurrentTime();
    }
};

/**
 * Central event bus system for RPG events
 * Manages event publishing, subscription, and routing throughout the game
 * Integrates with rpg-toolkit event system via Go bindings
 */
UCLASS()
class SESHAT_API URPGEventBusSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    // USubsystem interface
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;

    // Event publishing
    UFUNCTION(BlueprintCallable, Category = "RPG Event Bus")
    bool PublishEvent(const FRPGEventContext& EventContext);

    UFUNCTION(BlueprintCallable, Category = "RPG Event Bus")
    bool PublishEventDeferred(const FRPGEventContext& EventContext, float DelaySeconds = 0.0f);

    UFUNCTION(BlueprintCallable, Category = "RPG Event Bus")
    bool PublishEventToEntity(const FRPGEventContext& EventContext, TScriptInterface<IRPGEntityInterface> TargetEntity);

    // Event subscription management
    UFUNCTION(BlueprintCallable, Category = "RPG Event Bus")
    FString Subscribe(ERPGEventType EventType, TScriptInterface<IRPGEventInterface> Handler, 
                      ERPGEventPriority Priority = ERPGEventPriority::Normal);

    UFUNCTION(BlueprintCallable, Category = "RPG Event Bus")
    bool Unsubscribe(ERPGEventType EventType, TScriptInterface<IRPGEventInterface> Handler);

    UFUNCTION(BlueprintCallable, Category = "RPG Event Bus")
    bool UnsubscribeByID(const FString& SubscriptionID);

    UFUNCTION(BlueprintCallable, Category = "RPG Event Bus")
    void UnsubscribeAll(TScriptInterface<IRPGEventInterface> Handler);

    // Subscription queries
    UFUNCTION(BlueprintCallable, Category = "RPG Event Bus")
    int32 GetSubscriptionCount(ERPGEventType EventType) const;

    UFUNCTION(BlueprintCallable, Category = "RPG Event Bus")
    TArray<FString> GetSubscriptionIDs(ERPGEventType EventType) const;

    UFUNCTION(BlueprintCallable, Category = "RPG Event Bus")
    bool IsSubscribed(ERPGEventType EventType, TScriptInterface<IRPGEventInterface> Handler) const;

    // Event filtering and routing
    UFUNCTION(BlueprintCallable, Category = "RPG Event Bus")
    void SetEventFilter(ERPGEventType EventType, bool bAllowEvent);

    UFUNCTION(BlueprintCallable, Category = "RPG Event Bus")
    bool IsEventFiltered(ERPGEventType EventType) const;

    UFUNCTION(BlueprintCallable, Category = "RPG Event Bus")
    void ClearEventFilters();

    // Event statistics and monitoring
    UFUNCTION(BlueprintCallable, Category = "RPG Event Bus")
    int32 GetTotalEventCount() const { return EventStatistics.TotalEventsPublished; }

    UFUNCTION(BlueprintCallable, Category = "RPG Event Bus")
    int32 GetEventTypeCount(ERPGEventType EventType) const;

    UFUNCTION(BlueprintCallable, Category = "RPG Event Bus")
    float GetEventProcessingTime(ERPGEventType EventType) const;

    // Event queue management
    UFUNCTION(BlueprintCallable, Category = "RPG Event Bus")
    int32 GetQueuedEventCount() const { return DeferredEvents.Num(); }

    UFUNCTION(BlueprintCallable, Category = "RPG Event Bus")
    void ProcessDeferredEvents();

    UFUNCTION(BlueprintCallable, Category = "RPG Event Bus")
    void ClearEventQueue();

    // Debug and utilities
    UFUNCTION(BlueprintCallable, Category = "RPG Event Bus", CallInEditor)
    void DumpEventStatistics() const;

    UFUNCTION(BlueprintCallable, Category = "RPG Event Bus", CallInEditor)
    void DumpSubscriptions() const;

    UFUNCTION(BlueprintCallable, Category = "RPG Event Bus")
    void ResetEventStatistics();

    // Toolkit integration
    UFUNCTION(BlueprintCallable, Category = "RPG Event Bus")
    bool IsToolkitLoaded() const { return bToolkitLoaded; }

    UFUNCTION(BlueprintCallable, Category = "RPG Event Bus")
    bool SyncEventWithToolkit(const FRPGEventContext& EventContext);

    // Event bus lifecycle delegates
    UPROPERTY(BlueprintAssignable, Category = "RPG Event Bus")
    FOnRPGEventPublished OnEventPublished;

    UPROPERTY(BlueprintAssignable, Category = "RPG Event Bus")
    FOnRPGEventHandled OnEventHandled;

    UPROPERTY(BlueprintAssignable, Category = "RPG Event Bus")
    FOnRPGEventSubscription OnSubscriptionChanged;

protected:
    // Internal event processing
    ERPGEventResult ProcessEventInternal(const FRPGEventContext& EventContext);
    void NotifyHandlers(const FRPGEventContext& EventContext, const TArray<FRPGEventSubscription>& Handlers);
    void UpdateEventStatistics(ERPGEventType EventType, float ProcessingTime, ERPGEventResult Result);

    // Subscription management
    void CleanupExpiredSubscriptions();
    void SortSubscriptionsByPriority(TArray<FRPGEventSubscription>& Subscriptions);

    // Toolkit integration
    void LoadToolkitDLL();
    void LoadEventDLLFunctions();
    bool InitializeEventSystem();

private:
    // Event subscriptions: EventType -> Array of Subscriptions
    TMap<ERPGEventType, TArray<FRPGEventSubscription>> EventSubscriptions;

    // Event filtering
    TSet<ERPGEventType> FilteredEventTypes;

    // Deferred event processing
    TArray<FDeferredEvent> DeferredEvents;

    // Event statistics
    FRPGEventStatistics EventStatistics;

    // Toolkit DLL integration
    void* ToolkitDLLHandle = nullptr;
    bool bToolkitLoaded = false;

    // DLL function pointers for event system
    typedef int32(*PublishEventFunc)(const char* eventType, const char* eventData);
    typedef int32(*SubscribeEventFunc)(const char* eventType);
    typedef int32(*UnsubscribeEventFunc)(const char* eventType);
    typedef char*(*GetEventDataFunc)(int32 eventHandle);

    PublishEventFunc PublishEventFuncPtr = nullptr;
    SubscribeEventFunc SubscribeEventFuncPtr = nullptr;
    UnsubscribeEventFunc UnsubscribeEventFuncPtr = nullptr;
    GetEventDataFunc GetEventDataFuncPtr = nullptr;

    // Event handle mapping (UE Event <-> Go toolkit handle)
    TMap<FString, int32> EventToHandleMap; // "EventType:EventID" -> toolkit handle
    TMap<int32, FString> HandleToEventMap; // toolkit handle -> "EventType:EventID"
    int32 NextEventHandle = 1;

    // Thread safety
    mutable FCriticalSection EventBusLock;

    // Cleanup timer
    FTimerHandle CleanupTimerHandle;
    void PerformPeriodicCleanup();
};