#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "RPGEventTypes.h"
#include "RPGEventContext.h"
#include "../Entity/RPGEntity.h"
#include "RPGEvent.generated.h"

// Forward declarations
class URPGEventBusSubsystem;

/**
 * Delegate types for event handling
 */
DECLARE_DYNAMIC_DELEGATE_TwoParams(FRPGEventHandler, const FRPGEventContext&, EventContext, ERPGEventResult&, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FRPGEventDelegate, const FRPGEventContext&, EventContext, ERPGEventResult&, Result);

/**
 * Interface for objects that can handle RPG events
 * Implement this interface to receive and process events from the event bus
 */
UINTERFACE(MinimalAPI, Blueprintable)
class URPGEventInterface : public UInterface
{
    GENERATED_BODY()
};

class SESHAT_API IRPGEventInterface
{
    GENERATED_BODY()

public:
    /**
     * Handle an RPG event
     * @param EventContext The context data for the event
     * @return The result of handling this event
     */
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "RPG Event")
    ERPGEventResult HandleRPGEvent(const FRPGEventContext& EventContext);

    // C++ interface for direct handling
    virtual ERPGEventResult HandleEvent(const FRPGEventContext& EventContext) = 0;

    /**
     * Get the priority for handling specific event types
     * Higher priority handlers are called first
     */
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "RPG Event")
    ERPGEventPriority GetEventHandlingPriority(ERPGEventType EventType);

    // C++ interface for priority
    virtual ERPGEventPriority GetHandlingPriority(ERPGEventType EventType) const { return ERPGEventPriority::Normal; }

    /**
     * Check if this handler should process a specific event type
     */
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "RPG Event")
    bool ShouldHandleEventType(ERPGEventType EventType);

    // C++ interface for filtering
    virtual bool ShouldHandle(ERPGEventType EventType) const { return true; }
};

/**
 * Base class for RPG events that provides common functionality
 * Use this as a base for creating specific event types
 */
UCLASS(Abstract, BlueprintType, Blueprintable)
class SESHAT_API URPGEvent : public UObject, public IRPGEventInterface
{
    GENERATED_BODY()

public:
    URPGEvent();

    // IRPGEventInterface implementation
    virtual ERPGEventResult HandleEvent(const FRPGEventContext& EventContext) override;
    virtual ERPGEventPriority GetHandlingPriority(ERPGEventType EventType) const override;
    virtual bool ShouldHandle(ERPGEventType EventType) const override;

    // Blueprint-accessible versions
    UFUNCTION(BlueprintCallable, Category = "RPG Event")
    ERPGEventResult HandleRPGEvent_Implementation(const FRPGEventContext& EventContext);

    UFUNCTION(BlueprintCallable, Category = "RPG Event")
    ERPGEventPriority GetEventHandlingPriority_Implementation(ERPGEventType EventType);

    UFUNCTION(BlueprintCallable, Category = "RPG Event")
    bool ShouldHandleEventType_Implementation(ERPGEventType EventType);

    // Event creation helpers
    UFUNCTION(BlueprintCallable, Category = "RPG Event", CallInEditor)
    static FRPGEventContext CreateEventContext(ERPGEventType EventType, 
                                              TScriptInterface<IRPGEntityInterface> SourceEntity,
                                              TScriptInterface<IRPGEntityInterface> TargetEntity);

    // C++ convenience overloads (not exposed to Blueprint)
    static FRPGEventContext CreateEventContext(ERPGEventType EventType);
    static FRPGEventContext CreateEventContext(ERPGEventType EventType, TScriptInterface<IRPGEntityInterface> SourceEntity);

    // Event publishing helpers  
    UFUNCTION(BlueprintCallable, Category = "RPG Event")
    static bool PublishEvent(const FRPGEventContext& EventContext);

    UFUNCTION(BlueprintCallable, Category = "RPG Event")
    static bool PublishEventToSubsystem(URPGEventBusSubsystem* EventBus, const FRPGEventContext& EventContext);

    // Event subscription helpers
    UFUNCTION(BlueprintCallable, Category = "RPG Event")
    static bool SubscribeToEventType(ERPGEventType EventType, TScriptInterface<IRPGEventInterface> Handler);

    UFUNCTION(BlueprintCallable, Category = "RPG Event")
    static bool UnsubscribeFromEventType(ERPGEventType EventType, TScriptInterface<IRPGEventInterface> Handler);

    // Convenience methods for common events
    UFUNCTION(BlueprintCallable, Category = "RPG Event")
    static FRPGEventContext CreateEntityEvent(ERPGEventType EventType, TScriptInterface<IRPGEntityInterface> Entity);

    UFUNCTION(BlueprintCallable, Category = "RPG Event")
    static FRPGEventContext CreateDiceRollEvent(TScriptInterface<IRPGEntityInterface> RollerEntity, 
                                               int32 Sides, int32 Result);

    UFUNCTION(BlueprintCallable, Category = "RPG Event")
    static FRPGEventContext CreateCombatEvent(ERPGEventType EventType,
                                             TScriptInterface<IRPGEntityInterface> Attacker,
                                             TScriptInterface<IRPGEntityInterface> Defender);

protected:
    // Override these in derived classes for specific event handling
    virtual ERPGEventResult ProcessRPGEvent(const FRPGEventContext& EventContext);
    virtual bool CanHandleEvent(const FRPGEventContext& EventContext) const;
    virtual void OnEventHandled(const FRPGEventContext& EventContext, ERPGEventResult Result);

    // Event type filtering
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RPG Event Configuration")
    TArray<ERPGEventType> HandledEventTypes;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RPG Event Configuration")
    ERPGEventPriority DefaultPriority;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RPG Event Configuration")
    bool bHandleAllEventTypes;

private:
    // Internal state
    bool bIsProcessingEvent;
};

/**
 * Event handler subscription information
 * Used internally by the event bus to manage subscriptions
 */
USTRUCT(BlueprintType)
struct SESHAT_API FRPGEventSubscription
{
    GENERATED_BODY()

    FRPGEventSubscription()
        : Priority(ERPGEventPriority::Normal)
        , SubscriptionType(ERPGEventSubscriptionType::Persistent)
        , ExpirationTime(0.0)
        , bIsActive(true)
    {
    }

    FRPGEventSubscription(TScriptInterface<IRPGEventInterface> InHandler, 
                         ERPGEventPriority InPriority = ERPGEventPriority::Normal,
                         ERPGEventSubscriptionType InType = ERPGEventSubscriptionType::Persistent)
        : Handler(InHandler)
        , Priority(InPriority)
        , SubscriptionType(InType)
        , ExpirationTime(0.0)
        , bIsActive(true)
    {
        SubscriptionID = FGuid::NewGuid().ToString();
    }

    UPROPERTY(BlueprintReadOnly, Category = "RPG Event Subscription")
    FString SubscriptionID;

    UPROPERTY(BlueprintReadOnly, Category = "RPG Event Subscription")
    TScriptInterface<IRPGEventInterface> Handler;

    UPROPERTY(BlueprintReadOnly, Category = "RPG Event Subscription")
    ERPGEventPriority Priority;

    UPROPERTY(BlueprintReadOnly, Category = "RPG Event Subscription")
    ERPGEventSubscriptionType SubscriptionType;

    UPROPERTY(BlueprintReadOnly, Category = "RPG Event Subscription")
    double ExpirationTime;

    UPROPERTY(BlueprintReadWrite, Category = "RPG Event Subscription")
    bool bIsActive;

    // Utility methods (regular C++ methods only in USTRUCT)
    bool IsValid() const
    {
        return Handler.GetInterface() != nullptr && bIsActive;
    }

    bool IsExpired() const
    {
        if (SubscriptionType != ERPGEventSubscriptionType::TimeLimited)
        {
            return false;
        }
        return FApp::GetCurrentTime() > ExpirationTime;
    }

    // For sorting by priority (higher priority first)
    bool operator<(const FRPGEventSubscription& Other) const
    {
        return static_cast<uint8>(Priority) > static_cast<uint8>(Other.Priority);
    }
};