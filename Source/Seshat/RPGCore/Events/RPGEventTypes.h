#pragma once

#include "CoreMinimal.h"
#include "Engine/Engine.h"
#include "RPGEventTypes.generated.h"

/**
 * Core event types matching rpg-toolkit's event system
 * Represents different categories of game events that can occur
 */
UENUM(BlueprintType)
enum class ERPGEventType : uint8
{
    // Core Events
    Unknown             UMETA(DisplayName = "Unknown Event"),
    
    // Entity Lifecycle Events
    EntityCreated       UMETA(DisplayName = "Entity Created"),
    EntityDestroyed     UMETA(DisplayName = "Entity Destroyed"),
    EntityModified      UMETA(DisplayName = "Entity Modified"),
    
    // Dice and Random Events
    DiceRolled          UMETA(DisplayName = "Dice Rolled"),
    RandomSelection     UMETA(DisplayName = "Random Selection"),
    
    // Spatial Events
    EntityMoved         UMETA(DisplayName = "Entity Moved"),
    EntityPositioned    UMETA(DisplayName = "Entity Positioned"),
    AreaEntered         UMETA(DisplayName = "Area Entered"),
    AreaExited          UMETA(DisplayName = "Area Exited"),
    
    // Combat Events
    AttackInitiated     UMETA(DisplayName = "Attack Initiated"),
    AttackResolved      UMETA(DisplayName = "Attack Resolved"),
    DamageDealt         UMETA(DisplayName = "Damage Dealt"),
    DamageReceived      UMETA(DisplayName = "Damage Received"),
    
    // Condition Events
    ConditionApplied    UMETA(DisplayName = "Condition Applied"),
    ConditionRemoved    UMETA(DisplayName = "Condition Removed"),
    ConditionTriggered  UMETA(DisplayName = "Condition Triggered"),
    
    // Resource Events
    ResourceChanged     UMETA(DisplayName = "Resource Changed"),
    ResourceDepleted    UMETA(DisplayName = "Resource Depleted"),
    ResourceRestored    UMETA(DisplayName = "Resource Restored"),
    
    // Game State Events
    TurnStarted         UMETA(DisplayName = "Turn Started"),
    TurnEnded           UMETA(DisplayName = "Turn Ended"),
    RoundStarted        UMETA(DisplayName = "Round Started"),
    RoundEnded          UMETA(DisplayName = "Round Ended"),
    
    // Custom Events (extensible)
    Custom              UMETA(DisplayName = "Custom Event")
};

/**
 * Event modifier types for altering event behavior
 * These can modify event outcomes, add conditions, or change event flow
 */
UENUM(BlueprintType)
enum class ERPGEventModifier : uint8
{
    None                UMETA(DisplayName = "No Modifier"),
    
    // Advantage/Disadvantage Modifiers
    Advantage           UMETA(DisplayName = "Advantage"),
    Disadvantage        UMETA(DisplayName = "Disadvantage"),
    
    // Numeric Modifiers
    Bonus               UMETA(DisplayName = "Bonus"),
    Penalty             UMETA(DisplayName = "Penalty"),
    Multiplier          UMETA(DisplayName = "Multiplier"),
    
    // Conditional Modifiers
    Conditional         UMETA(DisplayName = "Conditional"),
    Temporary           UMETA(DisplayName = "Temporary"),
    Persistent          UMETA(DisplayName = "Persistent"),
    
    // Priority Modifiers
    HighPriority        UMETA(DisplayName = "High Priority"),
    LowPriority         UMETA(DisplayName = "Low Priority"),
    
    // State Modifiers
    Cancelled           UMETA(DisplayName = "Cancelled"),
    Delayed             UMETA(DisplayName = "Delayed"),
    Repeated            UMETA(DisplayName = "Repeated"),
    
    // Custom Modifiers
    Custom              UMETA(DisplayName = "Custom Modifier")
};

/**
 * Event processing priority levels
 * Determines the order in which event handlers are executed
 */
UENUM(BlueprintType)
enum class ERPGEventPriority : uint8
{
    Lowest      = 0     UMETA(DisplayName = "Lowest Priority"),
    Low         = 25    UMETA(DisplayName = "Low Priority"),
    Normal      = 50    UMETA(DisplayName = "Normal Priority"),
    High        = 75    UMETA(DisplayName = "High Priority"),
    Highest     = 100   UMETA(DisplayName = "Highest Priority"),
    Critical    = 255   UMETA(DisplayName = "Critical Priority")
};

/**
 * Event handling result types
 * Indicates how an event handler processed the event
 */
UENUM(BlueprintType)
enum class ERPGEventResult : uint8
{
    Unhandled           UMETA(DisplayName = "Unhandled"),
    Handled             UMETA(DisplayName = "Handled"),
    HandledStopProcessing UMETA(DisplayName = "Handled - Stop Processing"),
    Error               UMETA(DisplayName = "Error"),
    Cancelled           UMETA(DisplayName = "Cancelled")
};

/**
 * Event subscription types
 * Defines how long an event subscription should remain active
 */
UENUM(BlueprintType)
enum class ERPGEventSubscriptionType : uint8
{
    Persistent          UMETA(DisplayName = "Persistent"),
    OneTime             UMETA(DisplayName = "One Time"),
    Conditional         UMETA(DisplayName = "Conditional"),
    TimeLimited         UMETA(DisplayName = "Time Limited")
};

// Event type utility functions
namespace RPGEventTypes
{
    // Common event type constants as strings
    const FString EntityCreated = TEXT("EntityCreated");
    const FString EntityDestroyed = TEXT("EntityDestroyed");
    const FString DiceRolled = TEXT("DiceRolled");
    const FString AttackInitiated = TEXT("AttackInitiated");
    const FString AttackResolved = TEXT("AttackResolved");
    const FString ConditionApplied = TEXT("ConditionApplied");
    const FString TurnStarted = TEXT("TurnStarted");
    const FString TurnEnded = TEXT("TurnEnded");
    
    // Utility functions for type conversion
    SESHAT_API FString EventTypeToString(ERPGEventType EventType);
    SESHAT_API ERPGEventType StringToEventType(const FString& TypeString);
    SESHAT_API FString ModifierTypeToString(ERPGEventModifier ModifierType);
    SESHAT_API ERPGEventModifier StringToModifierType(const FString& ModifierString);
}