#include "RPGEvent.h"
#include "RPGEventBusSubsystem.h"
#include "Engine/World.h"

URPGEvent::URPGEvent()
    : DefaultPriority(ERPGEventPriority::Normal)
    , bHandleAllEventTypes(false)
    , bIsProcessingEvent(false)
{
    // Set up default handled event types - derived classes should override
    HandledEventTypes.Empty();
}

ERPGEventResult URPGEvent::HandleEvent(const FRPGEventContext& EventContext)
{
    // Prevent recursive event handling
    if (bIsProcessingEvent)
    {
        UE_LOG(LogTemp, Warning, TEXT("URPGEvent::HandleEvent: Recursive event handling prevented for event type %s"), 
               *RPGEventTypes::EventTypeToString(EventContext.EventType));
        return ERPGEventResult::Error;
    }

    // Check if we should handle this event
    if (!CanHandleEvent(EventContext))
    {
        return ERPGEventResult::Unhandled;
    }

    bIsProcessingEvent = true;
    
    ERPGEventResult Result = ProcessRPGEvent(EventContext);
    
    bIsProcessingEvent = false;
    
    // Notify derived classes that event was handled
    OnEventHandled(EventContext, Result);
    
    return Result;
}

ERPGEventPriority URPGEvent::GetHandlingPriority(ERPGEventType EventType) const
{
    // Derived classes can override this for event-specific priorities
    return DefaultPriority;
}

bool URPGEvent::ShouldHandle(ERPGEventType EventType) const
{
    if (bHandleAllEventTypes)
    {
        return true;
    }
    
    return HandledEventTypes.Contains(EventType);
}

ERPGEventResult URPGEvent::HandleRPGEvent_Implementation(const FRPGEventContext& EventContext)
{
    return HandleEvent(EventContext);
}

ERPGEventPriority URPGEvent::GetEventHandlingPriority_Implementation(ERPGEventType EventType)
{
    return GetHandlingPriority(EventType);
}

bool URPGEvent::ShouldHandleEventType_Implementation(ERPGEventType EventType)
{
    return ShouldHandle(EventType);
}

FRPGEventContext URPGEvent::CreateEventContext(ERPGEventType EventType, 
                                              TScriptInterface<IRPGEntityInterface> SourceEntity,
                                              TScriptInterface<IRPGEntityInterface> TargetEntity)
{
    FRPGEventContext Context(EventType, SourceEntity);
    Context.TargetEntity = TargetEntity;
    return Context;
}

FRPGEventContext URPGEvent::CreateEventContext(ERPGEventType EventType)
{
    return FRPGEventContext(EventType);
}

FRPGEventContext URPGEvent::CreateEventContext(ERPGEventType EventType, TScriptInterface<IRPGEntityInterface> SourceEntity)
{
    return FRPGEventContext(EventType, SourceEntity);
}

bool URPGEvent::PublishEvent(const FRPGEventContext& EventContext)
{
    // Try to get the event bus from the current world
    if (GEngine && GEngine->GetCurrentPlayWorld())
    {
        if (UGameInstance* GameInstance = GEngine->GetCurrentPlayWorld()->GetGameInstance())
        {
            if (URPGEventBusSubsystem* EventBus = GameInstance->GetSubsystem<URPGEventBusSubsystem>())
            {
                return PublishEventToSubsystem(EventBus, EventContext);
            }
            else
            {
                UE_LOG(LogTemp, Warning, TEXT("URPGEvent::PublishEvent: Event bus subsystem not found"));
            }
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("URPGEvent::PublishEvent: Game instance not found"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("URPGEvent::PublishEvent: No current play world"));
    }
    
    return false;
}

bool URPGEvent::PublishEventToSubsystem(URPGEventBusSubsystem* EventBus, const FRPGEventContext& EventContext)
{
    if (!EventBus)
    {
        UE_LOG(LogTemp, Error, TEXT("URPGEvent::PublishEventToSubsystem: Event bus is null"));
        return false;
    }
    
    // Forward declaration - implementation will be in URPGEventBusSubsystem
    return EventBus->PublishEvent(EventContext);
}

bool URPGEvent::SubscribeToEventType(ERPGEventType EventType, TScriptInterface<IRPGEventInterface> Handler)
{
    if (GEngine && GEngine->GetCurrentPlayWorld())
    {
        if (UGameInstance* GameInstance = GEngine->GetCurrentPlayWorld()->GetGameInstance())
        {
            if (URPGEventBusSubsystem* EventBus = GameInstance->GetSubsystem<URPGEventBusSubsystem>())
            {
                FString SubscriptionID = EventBus->Subscribe(EventType, Handler);
                return !SubscriptionID.IsEmpty();
            }
        }
    }
    
    return false;
}

bool URPGEvent::UnsubscribeFromEventType(ERPGEventType EventType, TScriptInterface<IRPGEventInterface> Handler)
{
    if (GEngine && GEngine->GetCurrentPlayWorld())
    {
        if (UGameInstance* GameInstance = GEngine->GetCurrentPlayWorld()->GetGameInstance())
        {
            if (URPGEventBusSubsystem* EventBus = GameInstance->GetSubsystem<URPGEventBusSubsystem>())
            {
                return EventBus->Unsubscribe(EventType, Handler);
            }
        }
    }
    
    return false;
}

FRPGEventContext URPGEvent::CreateEntityEvent(ERPGEventType EventType, TScriptInterface<IRPGEntityInterface> Entity)
{
    FRPGEventContext Context(EventType, Entity);
    
    if (Entity.GetInterface())
    {
        Context.SetStringData(TEXT("EntityID"), Entity->GetID());
        Context.SetStringData(TEXT("EntityType"), Entity->GetType());
    }
    
    return Context;
}

FRPGEventContext URPGEvent::CreateDiceRollEvent(TScriptInterface<IRPGEntityInterface> RollerEntity, 
                                               int32 Sides, int32 Result)
{
    FRPGEventContext Context(ERPGEventType::DiceRolled, RollerEntity);
    
    Context.SetIntData(TEXT("Sides"), Sides);
    Context.SetIntData(TEXT("Result"), Result);
    Context.EventName = FString::Printf(TEXT("d%d Roll"), Sides);
    
    return Context;
}

FRPGEventContext URPGEvent::CreateCombatEvent(ERPGEventType EventType,
                                             TScriptInterface<IRPGEntityInterface> Attacker,
                                             TScriptInterface<IRPGEntityInterface> Defender)
{
    FRPGEventContext Context(EventType, Attacker);
    Context.TargetEntity = Defender;
    
    if (Attacker.GetInterface())
    {
        Context.SetStringData(TEXT("AttackerID"), Attacker->GetID());
        Context.SetStringData(TEXT("AttackerType"), Attacker->GetType());
    }
    
    if (Defender.GetInterface())
    {
        Context.SetStringData(TEXT("DefenderID"), Defender->GetID());
        Context.SetStringData(TEXT("DefenderType"), Defender->GetType());
    }
    
    return Context;
}

ERPGEventResult URPGEvent::ProcessRPGEvent(const FRPGEventContext& EventContext)
{
    // Default implementation - derived classes should override this
    UE_LOG(LogTemp, Log, TEXT("URPGEvent::ProcessEvent: Processing event %s"), 
           *RPGEventTypes::EventTypeToString(EventContext.EventType));
    
    return ERPGEventResult::Handled;
}

bool URPGEvent::CanHandleEvent(const FRPGEventContext& EventContext) const
{
    // Check if event is valid
    if (!EventContext.IsValid())
    {
        return false;
    }
    
    // Check if event is cancelled
    if (EventContext.bCancelled)
    {
        return false;
    }
    
    // Check if we handle this event type
    if (!ShouldHandle(EventContext.EventType))
    {
        return false;
    }
    
    return true;
}

void URPGEvent::OnEventHandled(const FRPGEventContext& EventContext, ERPGEventResult Result)
{
    // Default implementation - derived classes can override for post-processing
    UE_LOG(LogTemp, VeryVerbose, TEXT("URPGEvent::OnEventHandled: Event %s handled with result %d"), 
           *EventContext.EventID, static_cast<int32>(Result));
}