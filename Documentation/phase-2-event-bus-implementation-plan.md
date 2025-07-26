# Phase 2: RPG-Toolkit Event Bus Integration Implementation Plan

*July 25, 2025*

## Overview

With the universal Entity foundation established in Phase 1, Phase 2 focuses on integrating the rpg-toolkit's sophisticated event bus system with Unreal Engine. This will enable event-driven gameplay mechanics, modifier systems, and the foundation for advanced RPG features like combat, conditions, and complex entity interactions.

## Phase 1 Foundation Recap

**What we established:**
- `IRPGEntityInterface` - Universal entity contract
- `ARPGEntity` / `URPGEntityObject` - Entity implementations
- `URPGEntitySubsystem` - Thread-safe entity management
- Entity-to-toolkit handle mapping system
- Go bindings with 7 core entity functions
- **Result**: Universal building block that all other systems can reference

## Event Bus Research Summary

Based on our comprehensive investigation of the rpg-toolkit's event bus system (Journey 012), we discovered a sophisticated, mature system designed specifically for game mechanics.

### Core Event Bus Architecture

**EventBus Interface** (`/home/frank/projects/rpg-toolkit/events/bus.go`):
```go
type EventBus interface {
    Publish(ctx context.Context, event Event) error        // Synchronous event publishing
    Subscribe(eventType string, handler Handler) string    // Register event handlers
    SubscribeFunc(eventType string, priority int, fn HandlerFunc) string
    Unsubscribe(subscriptionID string) error              // Remove subscriptions
}
```

**Key Characteristics:**
- **Thread-safe** with RWMutex protection
- **Synchronous delivery** (same goroutine)
- **Priority-based** handler execution (lower numbers first)
- **Event cancellation** capability
- **No built-in networking** (pure in-memory, in-process)

### Event System Components

**1. Event Interface** (`/home/frank/projects/rpg-toolkit/events/event.go`):
```go
type Event interface {
    GetType() string
    GetSource() core.Entity      // Source entity performing action
    GetTarget() core.Entity      // Target entity receiving action  
    GetContext() Context         // Rich data and modifier system
    IsCancelled() bool
    Cancel()
    GetTimestamp() time.Time
}
```

**2. Event Types** (47+ predefined constants):
```go
// Combat Events
EventBeforeAttackRoll = "before_attack_roll"
EventOnAttackRoll = "on_attack_roll"
EventAfterAttackRoll = "after_attack_roll"
EventBeforeDamageRoll = "before_damage_roll"
EventOnTakeDamage = "on_take_damage"

// Module-Specific Events (dot notation)
EventEntityPlaced = "spatial.entity.placed"
EventEntityMoved = "spatial.entity.moved"
EventRoomCreated = "spatial.room.created"
EventSelectionCompleted = "selectables.selection.completed"
```

**3. Context System** (100+ predefined keys):
```go
// Context provides type-safe data storage
type Context interface {
    Set(key string, value interface{})
    Get(key string) (interface{}, bool)
    GetString(key string) (string, bool)
    GetInt(key string) (int, bool)
    AddModifier(modifier Modifier)
    GetModifiers() []Modifier
}

// Example context keys
ContextKeyAttacker = "attacker"
ContextKeyWeapon = "weapon"
ContextKeyDamageType = "damage_type"
ContextKeyAdvantage = "advantage"
ContextKeyRoll = "roll"
```

**4. Modifier System** (advanced value modification):
```go
type Modifier interface {
    GetSource() string                    // What created this modifier
    GetType() string                      // What it modifies (attack_bonus, etc.)
    GetValue() ModifierValue              // The modification value
    GetPriority() int                     // Application order
    GetCondition() func(Event) bool       // When it applies
    GetDuration() Duration                // How long it lasts
}

type ModifierValue interface {
    GetValue() int                        // Final computed value
    GetDescription() string               // Human-readable (e.g., "+d4[3]=3 (bless)")
}
```

**5. Duration System** (10 duration types):
```go
DurationTypePermanent     // Never expires
DurationTypeRounds        // Combat rounds
DurationTypeMinutes       // Real time minutes
DurationTypeHours         // Real time hours
DurationTypeEncounter     // Until combat ends
DurationTypeConcentration // Until concentration broken
DurationTypeShortRest     // Until short rest
DurationTypeLongRest      // Until long rest
DurationTypeUntilDamaged  // Until damage taken
DurationTypeUntilSave     // Until saving throw made
```

### Module Integration Patterns

**Spatial Module Example**:
```go
// Publishing events
event := events.NewGameEvent(EventEntityMoved, entity, nil)
event.Context().Set("old_position", oldPos)
event.Context().Set("new_position", newPos)
eventBus.Publish(context.Background(), event)

// Subscribing to events
eventBus.SubscribeFunc(EventQueryPositionsInRange, 0, h.handlePositionsInRangeEvent)
```

**Combat System Example** (from DND bot):
```go
// Modifier injection during event processing
bus.SubscribeFunc(events.EventOnAttackRoll, 100, func(ctx context.Context, e events.Event) error {
    weapon, _ := e.Context().GetString("weapon")
    
    if proficiencyService.CheckProficiency(e.Source().GetID(), weapon) {
        bonus := GetProficiencyBonus(level)
        e.Context().AddModifier(events.NewModifier(
            "proficiency",
            events.ModifierAttackBonus,
            events.NewRawValue(bonus, "proficiency"),
            100,
        ))
    }
    return nil
})
```

## Multiplayer Architecture Insight (Journey 022)

**Key Breakthrough**: The event bus could become our networking layer, bypassing UE's networking stack entirely.

**Current Flow**:
```
UE Action → Toolkit Function → Event Bus → Local Subscribers
```

**Networked Flow**:
```
UE Client A → Toolkit Function → Event Bus → Network Transport → Event Bus (Client B) → UE Client B
```

**Why This Is Powerful**:
- **Toolkit-Native**: Events are already how modules communicate
- **Clean UE Integration**: UE doesn't need to understand D&D rules, just events
- **Network Agnostic**: Easy to swap transport layers
- **Consistent API**: Same event handling locally and networked

## Phase 2 Implementation Plan

### File Structure
```
Source/Seshat/RPGCore/
├── Entity/                              # Phase 1 (completed)
│   ├── RPGEntity.h/.cpp
│   └── RPGEntitySubsystem.h/.cpp
├── Events/                              # Phase 2 (new)
│   ├── RPGEvent.h/.cpp                  # Event interface and base implementation
│   ├── RPGEventContext.h/.cpp           # Context and modifier system
│   ├── RPGEventBusSubsystem.h/.cpp      # Central event management
│   └── RPGEventTypes.h                  # Event type constants and Blueprint enums
├── RPGCoreTypes.h/.cpp                  # Phase 1 (extend for events)
└── ...

Source/ThirdParty/RPGToolkit/
├── core_bindings.go                     # Phase 1 (completed)
├── event_bindings.go                    # Phase 2 (new)
├── rpg_toolkit.dll                      # Rebuild with event functions
└── rpg_toolkit.h                        # Updated with event exports
```

### 1. Event System Core Types

**File: `RPGCore/Events/RPGEventTypes.h`**

```cpp
#pragma once

#include "CoreMinimal.h"
#include "RPGEventTypes.generated.h"

/**
 * Event type enumeration for Blueprint integration
 * Maps to rpg-toolkit's string-based event types
 */
UENUM(BlueprintType)
enum class ERPGEventType : uint8
{
    // Combat Events
    BeforeAttackRoll    UMETA(DisplayName = "Before Attack Roll"),
    OnAttackRoll        UMETA(DisplayName = "On Attack Roll"),
    AfterAttackRoll     UMETA(DisplayName = "After Attack Roll"),
    BeforeDamageRoll    UMETA(DisplayName = "Before Damage Roll"),
    OnTakeDamage        UMETA(DisplayName = "On Take Damage"),
    
    // Spatial Events
    EntityPlaced        UMETA(DisplayName = "Entity Placed"),
    EntityMoved         UMETA(DisplayName = "Entity Moved"),
    RoomCreated         UMETA(DisplayName = "Room Created"),
    
    // Custom Events
    Custom              UMETA(DisplayName = "Custom Event")
};

/**
 * Modifier type enumeration
 */
UENUM(BlueprintType)
enum class ERPGModifierType : uint8
{
    AttackBonus         UMETA(DisplayName = "Attack Bonus"),
    DamageBonus         UMETA(DisplayName = "Damage Bonus"),
    ACBonus             UMETA(DisplayName = "AC Bonus"),
    Advantage           UMETA(DisplayName = "Advantage"),
    Disadvantage        UMETA(DisplayName = "Disadvantage"),
    Custom              UMETA(DisplayName = "Custom Modifier")
};

/**
 * Duration type enumeration
 */
UENUM(BlueprintType)
enum class ERPGDurationType : uint8
{
    Permanent           UMETA(DisplayName = "Permanent"),
    Rounds              UMETA(DisplayName = "Rounds"),
    Minutes             UMETA(DisplayName = "Minutes"),
    Hours               UMETA(DisplayName = "Hours"),
    Encounter           UMETA(DisplayName = "Encounter"),
    Concentration       UMETA(DisplayName = "Concentration"),
    ShortRest           UMETA(DisplayName = "Short Rest"),
    LongRest            UMETA(DisplayName = "Long Rest"),
    UntilDamaged        UMETA(DisplayName = "Until Damaged"),
    UntilSave           UMETA(DisplayName = "Until Save")
};

// Event type string constants (matching toolkit)
namespace RPGEventTypes
{
    // Combat
    const FString BeforeAttackRoll = TEXT("before_attack_roll");
    const FString OnAttackRoll = TEXT("on_attack_roll");
    const FString AfterAttackRoll = TEXT("after_attack_roll");
    const FString BeforeDamageRoll = TEXT("before_damage_roll");
    const FString OnTakeDamage = TEXT("on_take_damage");
    
    // Spatial
    const FString EntityPlaced = TEXT("spatial.entity.placed");
    const FString EntityMoved = TEXT("spatial.entity.moved");
    const FString RoomCreated = TEXT("spatial.room.created");
    
    // Utility functions
    FString GetEventTypeString(ERPGEventType EventType);
    ERPGEventType GetEventTypeFromString(const FString& EventTypeString);
}

// Context key constants (matching toolkit)
namespace RPGContextKeys
{
    const FString Attacker = TEXT("attacker");
    const FString Target = TEXT("target");
    const FString Weapon = TEXT("weapon");
    const FString DamageType = TEXT("damage_type");
    const FString Advantage = TEXT("advantage");
    const FString Roll = TEXT("roll");
    const FString OldPosition = TEXT("old_position");
    const FString NewPosition = TEXT("new_position");
    const FString RoomID = TEXT("room_id");
}
```

### 2. Event Context and Modifier System

**File: `RPGCore/Events/RPGEventContext.h`**

```cpp
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../RPGCoreTypes.h"
#include "RPGEventTypes.h"
#include "RPGEventContext.generated.h"

// Forward declarations
class IRPGEntityInterface;

/**
 * Modifier value interface for Blueprint integration
 */
USTRUCT(BlueprintType)
struct SESHAT_API FRPGModifierValue
{
    GENERATED_BODY()

    FRPGModifierValue()
        : Value(0)
    {}

    FRPGModifierValue(int32 InValue, const FString& InDescription)
        : Value(InValue)
        , Description(InDescription)
    {}

    UPROPERTY(BlueprintReadOnly, Category = "RPG Modifier")
    int32 Value;

    UPROPERTY(BlueprintReadOnly, Category = "RPG Modifier")
    FString Description;
};

/**
 * Duration information for modifiers
 */
USTRUCT(BlueprintType)
struct SESHAT_API FRPGDuration
{
    GENERATED_BODY()

    FRPGDuration()
        : Type(ERPGDurationType::Permanent)
        , Amount(0)
    {}

    FRPGDuration(ERPGDurationType InType, int32 InAmount = 0)
        : Type(InType)
        , Amount(InAmount)
    {}

    UPROPERTY(BlueprintReadOnly, Category = "RPG Duration")
    ERPGDurationType Type;

    UPROPERTY(BlueprintReadOnly, Category = "RPG Duration")
    int32 Amount;

    bool IsExpired() const;
    FString GetDescription() const;
};

/**
 * Event modifier for value adjustments
 */
USTRUCT(BlueprintType)
struct SESHAT_API FRPGEventModifier
{
    GENERATED_BODY()

    FRPGEventModifier()
        : Type(ERPGModifierType::Custom)
        , Priority(100)
    {}

    UPROPERTY(BlueprintReadOnly, Category = "RPG Modifier")
    FString Source;

    UPROPERTY(BlueprintReadOnly, Category = "RPG Modifier")
    ERPGModifierType Type;

    UPROPERTY(BlueprintReadOnly, Category = "RPG Modifier")
    FRPGModifierValue Value;

    UPROPERTY(BlueprintReadOnly, Category = "RPG Modifier")
    int32 Priority;

    UPROPERTY(BlueprintReadOnly, Category = "RPG Modifier")
    FRPGDuration Duration;

    // Condition function would need special handling for Blueprint integration
    // For now, use string-based condition evaluation
    UPROPERTY(BlueprintReadOnly, Category = "RPG Modifier")
    FString Condition;
};

/**
 * Event context for data storage and modifier management
 */
USTRUCT(BlueprintType)
struct SESHAT_API FRPGEventContext
{
    GENERATED_BODY()

    FRPGEventContext() = default;

    // Data storage (key-value pairs)
    UPROPERTY(BlueprintReadOnly, Category = "RPG Event Context")
    TMap<FString, FString> StringData;

    UPROPERTY(BlueprintReadOnly, Category = "RPG Event Context")
    TMap<FString, int32> IntData;

    UPROPERTY(BlueprintReadOnly, Category = "RPG Event Context")
    TMap<FString, float> FloatData;

    // Modifier system
    UPROPERTY(BlueprintReadOnly, Category = "RPG Event Context")
    TArray<FRPGEventModifier> Modifiers;

    // Utility methods for Blueprint access
    void SetString(const FString& Key, const FString& Value) { StringData.Add(Key, Value); }
    void SetInt(const FString& Key, int32 Value) { IntData.Add(Key, Value); }
    void SetFloat(const FString& Key, float Value) { FloatData.Add(Key, Value); }

    FString GetString(const FString& Key, const FString& DefaultValue = TEXT("")) const;
    int32 GetInt(const FString& Key, int32 DefaultValue = 0) const;
    float GetFloat(const FString& Key, float DefaultValue = 0.0f) const;

    void AddModifier(const FRPGEventModifier& Modifier);
    TArray<FRPGEventModifier> GetModifiersByType(ERPGModifierType Type) const;
    int32 CalculateModifierTotal(ERPGModifierType Type) const;
};
```

### 3. Event Interface and Implementation

**File: `RPGCore/Events/RPGEvent.h`**

```cpp
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "UObject/ScriptInterface.h"
#include "../Entity/RPGEntity.h"
#include "RPGEventContext.h"
#include "RPGEventTypes.h"
#include "RPGEvent.generated.h"

/**
 * Event interface matching rpg-toolkit's Event interface
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
    virtual FString GetType() const = 0;
    virtual TScriptInterface<IRPGEntityInterface> GetSource() const = 0;
    virtual TScriptInterface<IRPGEntityInterface> GetTarget() const = 0;
    virtual FRPGEventContext& GetContext() = 0;
    virtual const FRPGEventContext& GetContext() const = 0;
    virtual bool IsCancelled() const = 0;
    virtual void Cancel() = 0;
    virtual FDateTime GetTimestamp() const = 0;
};

/**
 * Base event implementation
 */
UCLASS(BlueprintType, Blueprintable)
class SESHAT_API URPGEvent : public UObject, public IRPGEventInterface
{
    GENERATED_BODY()

public:
    URPGEvent();

    // IRPGEventInterface implementation
    virtual FString GetType() const override;
    virtual TScriptInterface<IRPGEntityInterface> GetSource() const override;
    virtual TScriptInterface<IRPGEntityInterface> GetTarget() const override;
    virtual FRPGEventContext& GetContext() override;
    virtual const FRPGEventContext& GetContext() const override;
    virtual bool IsCancelled() const override;
    virtual void Cancel() override;
    virtual FDateTime GetTimestamp() const override;

    // Blueprint-accessible versions
    UFUNCTION(BlueprintCallable, Category = "RPG Event")
    FString GetEventType() const { return GetType(); }

    UFUNCTION(BlueprintCallable, Category = "RPG Event")
    TScriptInterface<IRPGEntityInterface> GetSourceEntity() const { return GetSource(); }

    UFUNCTION(BlueprintCallable, Category = "RPG Event")
    TScriptInterface<IRPGEntityInterface> GetTargetEntity() const { return GetTarget(); }

    UFUNCTION(BlueprintCallable, Category = "RPG Event")
    bool IsEventCancelled() const { return IsCancelled(); }

    UFUNCTION(BlueprintCallable, Category = "RPG Event")
    void CancelEvent() { Cancel(); }

    // Factory method
    UFUNCTION(BlueprintCallable, Category = "RPG Event", CallInEditor)
    static URPGEvent* CreateEvent(UObject* Outer, const FString& EventType,
                                 TScriptInterface<IRPGEntityInterface> Source = nullptr,
                                 TScriptInterface<IRPGEntityInterface> Target = nullptr);

    // Initialization
    void Initialize(const FString& InEventType,
                   TScriptInterface<IRPGEntityInterface> InSource,
                   TScriptInterface<IRPGEntityInterface> InTarget);

protected:
    UPROPERTY(BlueprintReadOnly, Category = "RPG Event")
    FString EventType;

    UPROPERTY(BlueprintReadOnly, Category = "RPG Event")
    TScriptInterface<IRPGEntityInterface> SourceEntity;

    UPROPERTY(BlueprintReadOnly, Category = "RPG Event")
    TScriptInterface<IRPGEntityInterface> TargetEntity;

    UPROPERTY(BlueprintReadOnly, Category = "RPG Event")
    FRPGEventContext Context;

    UPROPERTY(BlueprintReadOnly, Category = "RPG Event")
    bool bCancelled = false;

    UPROPERTY(BlueprintReadOnly, Category = "RPG Event")
    FDateTime Timestamp;
};
```

### 4. Event Bus Subsystem

**File: `RPGCore/Events/RPGEventBusSubsystem.h`**

```cpp
#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UObject/ScriptInterface.h"
#include "RPGEvent.h"
#include "RPGEventTypes.h"
#include "../RPGCoreTypes.h"
#include "HAL/PlatformProcess.h"
#include "RPGEventBusSubsystem.generated.h"

// Forward declarations
class IRPGEventInterface;

/**
 * Event handler delegate for Blueprint integration
 */
DECLARE_DYNAMIC_DELEGATE_RetVal_OneParam(bool, FRPGEventHandler, TScriptInterface<IRPGEventInterface>, Event);

/**
 * Event handler info for subscription management
 */
USTRUCT()
struct FRPGEventSubscription
{
    GENERATED_BODY()

    FString SubscriptionID;
    FString EventType;
    int32 Priority = 100;
    FRPGEventHandler Handler;
    bool bIsActive = true;

    FRPGEventSubscription() = default;
    FRPGEventSubscription(const FString& InID, const FString& InEventType, int32 InPriority)
        : SubscriptionID(InID), EventType(InEventType), Priority(InPriority) {}
};

/**
 * Central event bus system for RPG events
 * Bridges UE event handling with Go toolkit event bus
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
    bool PublishEvent(TScriptInterface<IRPGEventInterface> Event);

    UFUNCTION(BlueprintCallable, Category = "RPG Event Bus")
    bool PublishEventByType(const FString& EventType,
                           TScriptInterface<IRPGEntityInterface> Source = nullptr,
                           TScriptInterface<IRPGEntityInterface> Target = nullptr);

    // Event subscription
    UFUNCTION(BlueprintCallable, Category = "RPG Event Bus")
    FString SubscribeToEvent(const FString& EventType, const FRPGEventHandler& Handler, int32 Priority = 100);

    UFUNCTION(BlueprintCallable, Category = "RPG Event Bus")
    bool UnsubscribeFromEvent(const FString& SubscriptionID);

    UFUNCTION(BlueprintCallable, Category = "RPG Event Bus")
    void UnsubscribeAll();

    // Event queries
    UFUNCTION(BlueprintCallable, Category = "RPG Event Bus")
    TArray<FString> GetSubscribedEventTypes() const;

    UFUNCTION(BlueprintCallable, Category = "RPG Event Bus")
    int32 GetSubscriptionCount() const;

    // Toolkit integration
    UFUNCTION(BlueprintCallable, Category = "RPG Event Bus")
    bool IsToolkitEventBusLoaded() const { return bToolkitEventBusLoaded; }

    UFUNCTION(BlueprintCallable, Category = "RPG Event Bus")
    bool SyncEventWithToolkit(TScriptInterface<IRPGEventInterface> Event);

    // Debug utilities
    UFUNCTION(BlueprintCallable, Category = "RPG Event Bus", CallInEditor)
    void DumpEventSubscriptions() const;

protected:
    // Toolkit DLL integration
    void LoadEventBusFunctions();
    bool InitializeToolkitEventBus();

    // Event processing
    bool ProcessEventInternal(TScriptInterface<IRPGEventInterface> Event);
    void SortSubscribersByPriority(TArray<FRPGEventSubscription*>& Subscriptions);

    // Subscription management
    FString GenerateSubscriptionID();

private:
    // Event subscriptions: EventType -> Array of Subscriptions
    TMap<FString, TArray<FRPGEventSubscription>> EventSubscriptions;

    // Toolkit DLL integration (extending existing pattern)
    void* ToolkitDLLHandle = nullptr;
    bool bToolkitEventBusLoaded = false;

    // DLL function pointers for event bus operations
    typedef int32(*PublishEventFunc)(const char* eventType, int32 sourceHandle, int32 targetHandle, const char* contextJson);
    typedef int32(*SubscribeEventFunc)(const char* eventType, int32 priority);
    typedef int32(*UnsubscribeEventFunc)(int32 subscriptionHandle);
    typedef char*(*GetEventTypesFunc)();

    PublishEventFunc PublishEventFuncPtr = nullptr;
    SubscribeEventFunc SubscribeEventFuncPtr = nullptr;
    UnsubscribeEventFunc UnsubscribeEventFuncPtr = nullptr;
    GetEventTypesFunc GetEventTypesFuncPtr = nullptr;

    // Handle mapping for toolkit integration
    TMap<FString, int32> SubscriptionToHandleMap;
    TMap<int32, FString> HandleToSubscriptionMap;

    // Thread safety
    mutable FCriticalSection EventBusLock;

    // Subscription ID generation
    int32 NextSubscriptionID = 1;
};
```

### 5. Go Toolkit Event Bus Bindings

**File: `Source/ThirdParty/RPGToolkit/event_bindings.go`**

```go
package main

import "C"
import (
    "context"
    "encoding/json"
    "sync"
    "time"
)

// EventData represents event information for the binding layer
type EventData struct {
    Type        string                 `json:"type"`
    Source      int32                  `json:"source"`      // Entity handle
    Target      int32                  `json:"target"`      // Entity handle  
    Context     map[string]interface{} `json:"context"`
    Cancelled   bool                   `json:"cancelled"`
    Timestamp   time.Time              `json:"timestamp"`
}

// EventSubscription represents a subscription in the binding layer
type EventSubscription struct {
    ID       int32
    Type     string
    Priority int
    Active   bool
}

// Global event system storage
var (
    eventSubscriptions = make(map[int32]*EventSubscription)
    eventsByType       = make(map[string][]*EventSubscription)
    eventMutex         = sync.RWMutex{}
    nextEventSubID     = int32(1)
)

// Helper function to get next subscription ID
func getNextEventSubscriptionID() int32 {
    eventMutex.Lock()
    defer eventMutex.Unlock()
    id := nextEventSubID
    nextEventSubID++
    return id
}

//export PublishEvent
func PublishEvent(eventType *C.char, sourceHandle C.int, targetHandle C.int, contextJson *C.char) C.int {
    goEventType := C.GoString(eventType)
    goContextJson := C.GoString(contextJson)
    
    // Parse context JSON
    var contextData map[string]interface{}
    if err := json.Unmarshal([]byte(goContextJson), &contextData); err != nil {
        return -1 // JSON parse error
    }
    
    // Create event data
    eventData := &EventData{
        Type:      goEventType,
        Source:    int32(sourceHandle),
        Target:    int32(targetHandle),
        Context:   contextData,
        Cancelled: false,
        Timestamp: time.Now(),
    }
    
    // TODO: Integrate with actual rpg-toolkit event bus when available
    // For now, just simulate event processing
    
    eventMutex.RLock()
    subscriptions, exists := eventsByType[goEventType]
    eventMutex.RUnlock()
    
    if !exists {
        return 0 // No subscribers, but not an error
    }
    
    // Process subscriptions by priority
    processedCount := 0
    for _, sub := range subscriptions {
        if sub.Active && !eventData.Cancelled {
            // TODO: Call actual handlers
            processedCount++
        }
    }
    
    return C.int(processedCount)
}

//export SubscribeEvent
func SubscribeEvent(eventType *C.char, priority C.int) C.int {
    goEventType := C.GoString(eventType)
    goPriority := int(priority)
    
    // Create subscription
    subID := getNextEventSubscriptionID()
    subscription := &EventSubscription{
        ID:       subID,
        Type:     goEventType,
        Priority: goPriority,
        Active:   true,
    }
    
    eventMutex.Lock()
    eventSubscriptions[subID] = subscription
    
    // Add to type-based lookup
    if eventsByType[goEventType] == nil {
        eventsByType[goEventType] = make([]*EventSubscription, 0)
    }
    eventsByType[goEventType] = append(eventsByType[goEventType], subscription)
    eventMutex.Unlock()
    
    return C.int(subID)
}

//export UnsubscribeEvent
func UnsubscribeEvent(subscriptionHandle C.int) C.int {
    subID := int32(subscriptionHandle)
    
    eventMutex.Lock()
    subscription, exists := eventSubscriptions[subID]
    if !exists {
        eventMutex.Unlock()
        return -1 // Subscription not found
    }
    
    // Mark as inactive
    subscription.Active = false
    delete(eventSubscriptions, subID)
    
    // Remove from type-based lookup
    if subs, typeExists := eventsByType[subscription.Type]; typeExists {
        for i, sub := range subs {
            if sub.ID == subID {
                eventsByType[subscription.Type] = append(subs[:i], subs[i+1:]...)
                break
            }
        }
    }
    
    eventMutex.Unlock()
    return 0 // Success
}

//export GetEventTypes
func GetEventTypes() *C.char {
    eventMutex.RLock()
    defer eventMutex.RUnlock()
    
    types := make([]string, 0, len(eventsByType))
    for eventType := range eventsByType {
        types = append(types, eventType)
    }
    
    jsonData, err := json.Marshal(types)
    if err != nil {
        return C.CString("[]")
    }
    
    return C.CString(string(jsonData))
}

//export GetSubscriptionCount
func GetSubscriptionCount() C.int {
    eventMutex.RLock()
    count := len(eventSubscriptions)
    eventMutex.RUnlock()
    
    return C.int(count)
}
```

## Integration Strategy

### 1. Foundation Integration Points

**Entity System Connection:**
- Events reference entities as source/target using existing `IRPGEntityInterface`
- Entity handle mapping reuses Phase 1 infrastructure
- Entity subsystem can publish entity lifecycle events

**Dice System Integration:**
- Dice rolls become events with modifier support
- `RollForEntity` publishes `before_roll` and `after_roll` events
- Modifiers from event context automatically applied to rolls

### 2. Blueprint Integration Strategy

**Event Publishing:**
```cpp
// Blueprint node: "Publish RPG Event"
PublishEventByType("on_attack_roll", AttackerEntity, TargetEntity);
```

**Event Subscription:**
```cpp
// Blueprint event handler function
UFUNCTION(BlueprintImplementableEvent)
bool OnAttackRoll(TScriptInterface<IRPGEventInterface> Event);

// Subscribe in Blueprint construction
SubscribeToEvent("on_attack_roll", OnAttackRoll, 100);
```

**Modifier System:**
```cpp
// Blueprint modifier creation
FRPGEventModifier ProficiencyBonus;
ProficiencyBonus.Source = "Proficiency";
ProficiencyBonus.Type = ERPGModifierType::AttackBonus;
ProficiencyBonus.Value = FRPGModifierValue(2, "+2 (proficiency)");
Event->GetContext().AddModifier(ProficiencyBonus);
```

### 3. Performance Considerations

**Thread Safety:**
- Event bus operations protected by critical sections
- Subscription management thread-safe for multiplayer
- Event processing synchronous to maintain order

**Memory Management:**
- Events created as UObject instances for garbage collection
- Subscription cleanup on subsystem shutdown
- Handle mapping prevents memory leaks

**Networking Preparation:**
- Event serialization ready for network transport
- Context data designed for JSON serialization
- Entity references use stable handle system

## Testing Strategy

### Unit Tests
- Event creation and initialization
- Context data storage and retrieval
- Modifier calculation and priority ordering
- Subscription management lifecycle

### Integration Tests
- Entity-event integration
- Dice system event integration  
- Blueprint event publishing/subscribing
- Toolkit DLL event function integration

### Performance Tests
- Event throughput under load
- Thread safety under concurrent access
- Memory usage with large subscription counts

## Success Criteria

- [ ] Event interface matches toolkit Event contract
- [ ] Context system supports all toolkit context types
- [ ] Modifier system calculates values correctly with priority
- [ ] Event bus manages subscriptions thread-safely
- [ ] Blueprint integration provides full event access
- [ ] Toolkit DLL integration bridges UE events to Go
- [ ] Entity system publishes lifecycle events
- [ ] Dice system integrates with event modifiers
- [ ] Performance suitable for real-time gameplay

## Future Integration Points

With the event bus foundation, Phase 3+ can implement:
- **Spatial Events**: Entity movement, room transitions, line-of-sight
- **Combat Events**: Attack sequences, damage application, status effects
- **Condition Events**: Condition application, expiration, interactions
- **Resource Events**: Resource consumption, regeneration, limits
- **Multiplayer Events**: Network event distribution, state synchronization

## Key Design Decisions

### 1. **UE-Native Event Objects**
Use UObject-based events for proper UE integration and garbage collection

### 2. **JSON Context Serialization**
Use JSON for context data to enable network transport and toolkit compatibility

### 3. **Priority-Based Processing**
Maintain toolkit's priority system for proper modifier application order

### 4. **Thread-Safe Operations**
Protect all event bus operations for multiplayer and concurrent access

### 5. **Blueprint-First Design**
Ensure full Blueprint accessibility for designer/scripter event handling

This Phase 2 implementation will establish the event-driven foundation that enables sophisticated RPG mechanics while maintaining the clean UE integration patterns established in Phase 1.