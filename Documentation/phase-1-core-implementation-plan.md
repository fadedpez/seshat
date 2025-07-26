# Phase 1: RPG-Toolkit Core Foundation Implementation Plan

*July 25, 2025*

## Overview

This document provides the complete implementation plan for Phase 1 of the rpg-toolkit integration: establishing the core Entity foundation that all other systems depend on.

## Background & Research Summary

### Lightning Bolt Insight ⚡

After thorough investigation of the rpg-toolkit architecture, we discovered we were approaching integration backwards. The **core package is the universal foundation** - implementing it first makes everything else natural:

- Event bus integration becomes straightforward (events need Entity interfaces)
- All other modules work seamlessly (they depend on core abstractions)
- We understand the actual abstractions instead of retrofitting

### RPG-Toolkit Core Architecture

**Universal Entity Interface:**
```go
type Entity interface {
    GetID() string    // Unique identifier within entity type scope
    GetType() string  // Entity categorization (e.g., "character", "item", "location")
}
```

**Design Principles:**
- **Pure identity contract**: Only ID and Type, no game-specific attributes
- **Universal applicability**: Works for characters, items, locations, rooms, conditions, spells
- **No dependencies**: Core package has zero dependencies on other toolkit packages
- **Immutable after creation**: IDs and types should be stable throughout lifecycle

**Dependency Architecture:**
```
┌─────────────────────────────────────┐
│            Applications             │  (rpg-api, Discord bots, etc.)
├─────────────────────────────────────┤
│              Tools                  │  (spatial, environments, selectables)
├─────────────────────────────────────┤  
│            Mechanics                │  (conditions, effects, features)
├─────────────────────────────────────┤
│      Events + Dice + Core           │  (coordination + randomization + identity)
├─────────────────────────────────────┤
│               Core                  │  (Entity interface, errors)
└─────────────────────────────────────┘
```

**Key Research Findings:**
- **47+ predefined event types** all work with Entity interfaces
- **Spatial system** positions entities using core.Entity
- **Event modifiers** reference entities for context
- **No existing C bindings** - we're creating the first integration
- **Thread-safe implementations** throughout toolkit
- **Rich error system** with structured EntityError types

## Phase 1 Implementation Plan

### File Structure

```
Seshat/Source/Seshat/
├── RPGCore/
│   ├── Entity/
│   │   ├── RPGEntity.h                    # IEntity interface + ARPGEntity base class
│   │   ├── RPGEntity.cpp                  # ARPGEntity implementation
│   │   ├── RPGEntityError.h               # Entity error system
│   │   └── RPGEntitySubsystem.h/.cpp      # Entity management subsystem
│   └── RPGCoreTypes.h                     # Core type definitions
├── RPGDiceSubsystem.h/.cpp                # Existing dice system (to be updated)
└── ...

Source/ThirdParty/RPGToolkit/
├── main.go                                # Existing entry point
├── simple_bindings.go                     # Existing bindings (to be extended)
├── core_bindings.go                       # NEW: Core entity bindings
├── rpg_toolkit.dll                        # Cross-compiled Windows DLL
├── rpg_toolkit.h                          # Generated C header
└── go.mod/go.sum                         # Go dependencies
```

### 1. Core Interface Definition

**File: `Seshat/Source/Seshat/RPGCore/Entity/RPGEntity.h`**

```cpp
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "RPGCoreTypes.h"
#include "RPGEntity.generated.h"

/**
 * Universal entity interface matching rpg-toolkit's core.Entity
 * Pure identity contract - only ID and Type
 */
UINTERFACE(MinimalAPI, Blueprintable)
class URPGEntityInterface : public UInterface
{
    GENERATED_BODY()
};

class SESHAT_API IRPGEntityInterface
{
    GENERATED_BODY()

public:
    /**
     * Get unique identifier for this entity within its type scope
     * Must be stable throughout entity lifecycle
     */
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "RPG Entity")
    FString GetEntityID() const;

    /**
     * Get entity type categorization (e.g., "character", "item", "location")
     * Must be stable throughout entity lifecycle  
     */
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "RPG Entity")
    FString GetEntityType() const;

    // C++ interface for direct access
    virtual FString GetID() const = 0;
    virtual FString GetType() const = 0;
};

/**
 * Base implementation of RPG Entity for UE Actors
 * Provides foundation for all game entities that need spatial representation
 */
UCLASS(Abstract, BlueprintType, Blueprintable)
class SESHAT_API ARPGEntity : public AActor, public IRPGEntityInterface
{
    GENERATED_BODY()

public:
    ARPGEntity();

    // IRPGEntityInterface implementation
    virtual FString GetID() const override;
    virtual FString GetType() const override;

    // Blueprint-accessible versions
    UFUNCTION(BlueprintCallable, Category = "RPG Entity")
    FString GetEntityID() const { return GetID(); }

    UFUNCTION(BlueprintCallable, Category = "RPG Entity")
    FString GetEntityType() const { return GetType(); }

    // Entity lifecycle
    UFUNCTION(BlueprintCallable, Category = "RPG Entity")
    bool IsValidEntity() const;

    UFUNCTION(BlueprintCallable, Category = "RPG Entity")
    void RegisterWithSubsystem();

    UFUNCTION(BlueprintCallable, Category = "RPG Entity")
    void UnregisterFromSubsystem();

protected:
    // Called when entity is first created to set up ID/Type
    virtual void InitializeEntity();

    // Override in subclasses to provide specific entity types
    virtual FString GetDefaultEntityType() const { return TEXT("entity"); }

    // Override in subclasses to provide custom ID generation
    virtual FString GenerateEntityID() const;

    // UE Actor lifecycle integration
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RPG Entity", 
              meta = (ToolTip = "Unique identifier for this entity"))
    FString EntityID;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RPG Entity",
              meta = (ToolTip = "Entity type categorization"))
    FString EntityType;

private:
    bool bEntityInitialized = false;
    bool bRegisteredWithSubsystem = false;
};

/**
 * Non-Actor entity implementation for objects that don't need spatial representation
 * Examples: items in inventory, abstract conditions, temporary effects
 */
UCLASS(BlueprintType, Blueprintable)
class SESHAT_API URPGEntityObject : public UObject, public IRPGEntityInterface
{
    GENERATED_BODY()

public:
    URPGEntityObject();

    // IRPGEntityInterface implementation
    virtual FString GetID() const override;
    virtual FString GetType() const override;

    // Blueprint-accessible versions
    UFUNCTION(BlueprintCallable, Category = "RPG Entity")
    FString GetEntityID() const { return GetID(); }

    UFUNCTION(BlueprintCallable, Category = "RPG Entity")
    FString GetEntityType() const { return GetType(); }

    // Factory method for creating entities
    UFUNCTION(BlueprintCallable, Category = "RPG Entity", CallInEditor = true)
    static URPGEntityObject* CreateEntity(UObject* Outer, const FString& EntityType, 
                                         const FString& EntityID = TEXT(""));

protected:
    virtual void InitializeEntity(const FString& Type, const FString& ID = TEXT(""));

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RPG Entity")
    FString EntityID;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RPG Entity")
    FString EntityType;
};
```

### 2. Core Types and Error System

**File: `Seshat/Source/Seshat/RPGCore/RPGCoreTypes.h`**

```cpp
#pragma once

#include "CoreMinimal.h"
#include "Engine/Engine.h"
#include "RPGCoreTypes.generated.h"

/**
 * Entity error types matching rpg-toolkit's core error system
 */
UENUM(BlueprintType)
enum class ERPGEntityError : uint8
{
    None            UMETA(DisplayName = "No Error"),
    NotFound        UMETA(DisplayName = "Entity Not Found"),
    Invalid         UMETA(DisplayName = "Invalid Entity"),
    Duplicate       UMETA(DisplayName = "Duplicate Entity"),
    NilEntity       UMETA(DisplayName = "Nil Entity"),
    EmptyID         UMETA(DisplayName = "Empty ID"),
    InvalidType     UMETA(DisplayName = "Invalid Type"),
    RegistrationFailed UMETA(DisplayName = "Registration Failed"),
    AlreadyRegistered UMETA(DisplayName = "Already Registered")
};

/**
 * Structured entity error information
 */
USTRUCT(BlueprintType)
struct SESHAT_API FRPGEntityError
{
    GENERATED_BODY()

    FRPGEntityError()
        : ErrorType(ERPGEntityError::None)
    {}

    FRPGEntityError(ERPGEntityError InErrorType, const FString& InEntityID = TEXT(""), 
                   const FString& InEntityType = TEXT(""), const FString& InOperation = TEXT(""),
                   const FString& InMessage = TEXT(""))
        : EntityID(InEntityID)
        , EntityType(InEntityType)
        , Operation(InOperation)
        , ErrorType(InErrorType)
        , ErrorMessage(InMessage)
    {}

    UPROPERTY(BlueprintReadOnly, Category = "RPG Entity Error")
    FString EntityID;

    UPROPERTY(BlueprintReadOnly, Category = "RPG Entity Error")
    FString EntityType;

    UPROPERTY(BlueprintReadOnly, Category = "RPG Entity Error")
    FString Operation;

    UPROPERTY(BlueprintReadOnly, Category = "RPG Entity Error")
    ERPGEntityError ErrorType;

    UPROPERTY(BlueprintReadOnly, Category = "RPG Entity Error")
    FString ErrorMessage;

    // Utility methods
    UFUNCTION(BlueprintCallable, Category = "RPG Entity Error")
    bool IsValid() const { return ErrorType == ERPGEntityError::None; }

    UFUNCTION(BlueprintCallable, Category = "RPG Entity Error")
    FString GetFormattedMessage() const;
};

/**
 * Entity validation result
 */
USTRUCT(BlueprintType)
struct SESHAT_API FRPGEntityValidationResult
{
    GENERATED_BODY()

    FRPGEntityValidationResult()
        : bIsValid(false)
    {}

    FRPGEntityValidationResult(bool bValid, const FRPGEntityError& Error = FRPGEntityError())
        : bIsValid(bValid)
        , Error(Error)
    {}

    UPROPERTY(BlueprintReadOnly, Category = "RPG Entity Validation")
    bool bIsValid;

    UPROPERTY(BlueprintReadOnly, Category = "RPG Entity Validation")
    FRPGEntityError Error;
};

// Common entity types as constants
namespace RPGEntityTypes
{
    const FString Character = TEXT("character");
    const FString Item = TEXT("item");
    const FString Location = TEXT("location");
    const FString Room = TEXT("room");
    const FString Condition = TEXT("condition");
    const FString Effect = TEXT("effect");
    const FString Spell = TEXT("spell");
    const FString Weapon = TEXT("weapon");
    const FString Armor = TEXT("armor");
}
```

### 3. Entity Management Subsystem

**File: `Seshat/Source/Seshat/RPGCore/Entity/RPGEntitySubsystem.h`**

```cpp
#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "RPGEntity.h"
#include "RPGCoreTypes.h"
#include "HAL/PlatformProcess.h"
#include "RPGEntitySubsystem.generated.h"

// Forward declarations
class IRPGEntityInterface;

/**
 * Delegate for entity lifecycle events
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEntityRegistered, const FString&, EntityID, const FString&, EntityType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEntityUnregistered, const FString&, EntityID, const FString&, EntityType);

/**
 * Central entity management system for RPG entities
 * Provides registry, validation, and lifecycle management
 * Bridges UE entities with Go toolkit entities
 */
UCLASS()
class SESHAT_API URPGEntitySubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    // USubsystem interface
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;

    // Entity registration and management
    UFUNCTION(BlueprintCallable, Category = "RPG Entity")
    FRPGEntityValidationResult RegisterEntity(TScriptInterface<IRPGEntityInterface> Entity);

    UFUNCTION(BlueprintCallable, Category = "RPG Entity")
    bool UnregisterEntity(const FString& EntityID, const FString& EntityType);

    UFUNCTION(BlueprintCallable, Category = "RPG Entity")
    TScriptInterface<IRPGEntityInterface> GetEntity(const FString& EntityID, const FString& EntityType);

    UFUNCTION(BlueprintCallable, Category = "RPG Entity")
    TArray<TScriptInterface<IRPGEntityInterface>> GetEntitiesByType(const FString& EntityType);

    UFUNCTION(BlueprintCallable, Category = "RPG Entity")
    TArray<FString> GetAllEntityTypes() const;

    UFUNCTION(BlueprintCallable, Category = "RPG Entity")
    int32 GetEntityCount() const;

    UFUNCTION(BlueprintCallable, Category = "RPG Entity")
    int32 GetEntityCountByType(const FString& EntityType) const;

    // Entity validation
    UFUNCTION(BlueprintCallable, Category = "RPG Entity")
    FRPGEntityValidationResult ValidateEntity(TScriptInterface<IRPGEntityInterface> Entity);

    UFUNCTION(BlueprintCallable, Category = "RPG Entity")
    bool IsEntityRegistered(const FString& EntityID, const FString& EntityType) const;

    // Entity queries
    UFUNCTION(BlueprintCallable, Category = "RPG Entity")
    bool DoesEntityExist(const FString& EntityID, const FString& EntityType) const;

    UFUNCTION(BlueprintCallable, Category = "RPG Entity")
    TScriptInterface<IRPGEntityInterface> FindEntityByID(const FString& EntityID) const;

    // Toolkit integration
    UFUNCTION(BlueprintCallable, Category = "RPG Entity")
    bool IsToolkitLoaded() const { return bToolkitLoaded; }

    UFUNCTION(BlueprintCallable, Category = "RPG Entity")
    int32 SyncEntityWithToolkit(TScriptInterface<IRPGEntityInterface> Entity);

    // Events
    UPROPERTY(BlueprintAssignable, Category = "RPG Entity")
    FOnEntityRegistered OnEntityRegistered;

    UPROPERTY(BlueprintAssignable, Category = "RPG Entity")
    FOnEntityUnregistered OnEntityUnregistered;

    // Debug and utilities
    UFUNCTION(BlueprintCallable, Category = "RPG Entity", CallInEditor = true)
    void DumpEntityRegistry() const;

    UFUNCTION(BlueprintCallable, Category = "RPG Entity")
    void ClearEntityRegistry();

protected:
    // DLL loading and toolkit integration
    void LoadToolkitDLL();
    void LoadDLLFunctions();
    bool InitializeToolkit();

    // Validation helpers
    bool IsValidEntityID(const FString& EntityID) const;
    bool IsValidEntityType(const FString& EntityType) const;
    FRPGEntityError CreateEntityError(ERPGEntityError ErrorType, const FString& EntityID,
                                     const FString& EntityType, const FString& Operation,
                                     const FString& Message = TEXT("")) const;

private:
    // Entity registry: EntityType -> EntityID -> Entity
    TMap<FString, TMap<FString, TScriptInterface<IRPGEntityInterface>>> EntityRegistry;

    // Toolkit DLL integration
    void* ToolkitDLLHandle = nullptr;
    bool bToolkitLoaded = false;

    // DLL function pointers (extend existing pattern)
    typedef int32(*CreateEntityFunc)(const char* entityType, const char* entityID);
    typedef int32(*ValidateEntityFunc)(const char* entityType, const char* entityID);
    typedef char*(*GetEntityTypeFunc)(int32 entityHandle);
    typedef void(*DestroyEntityFunc)(int32 entityHandle);

    CreateEntityFunc CreateEntityFuncPtr = nullptr;
    ValidateEntityFunc ValidateEntityFuncPtr = nullptr;
    GetEntityTypeFunc GetEntityTypeFuncPtr = nullptr;
    DestroyEntityFunc DestroyEntityFuncPtr = nullptr;

    // Entity handle mapping (UE Entity <-> Go toolkit handle)
    TMap<FString, int32> EntityToHandleMap; // "EntityType:EntityID" -> toolkit handle
    TMap<int32, FString> HandleToEntityMap; // toolkit handle -> "EntityType:EntityID"
    int32 NextEntityHandle = 1;

    // Thread safety
    mutable FCriticalSection EntityRegistryLock;
};
```

### 4. Go Toolkit Bindings Extension

**File: `Seshat/Source/ThirdParty/RPGToolkit/core_bindings.go`**

```go
package main

import "C"
import (
    "context"
    "fmt"
    "sync"
    "github.com/google/uuid"
)

// Entity represents a game entity in the toolkit
type Entity struct {
    ID   string
    Type string
}

// GetID implements core.Entity interface
func (e *Entity) GetID() string {
    return e.ID
}

// GetType implements core.Entity interface  
func (e *Entity) GetType() string {
    return e.Type
}

// Global entity storage for the binding layer
var (
    entities     = make(map[int32]*Entity)
    entityMutex  = sync.RWMutex{}
    nextHandle   = int32(1)
)

// Helper function to get next entity handle
func getNextHandle() int32 {
    entityMutex.Lock()
    defer entityMutex.Unlock()
    handle := nextHandle
    nextHandle++
    return handle
}

//export CreateEntity
func CreateEntity(entityType *C.char, entityID *C.char) C.int {
    goType := C.GoString(entityType)
    goID := C.GoString(entityID)

    // Generate ID if not provided
    if goID == "" {
        goID = uuid.New().String()
    }

    // Validate entity type
    if goType == "" {
        return -1 // Invalid entity type
    }

    // Create entity
    entity := &Entity{
        ID:   goID,
        Type: goType,
    }

    // Store entity and return handle
    handle := getNextHandle()
    entityMutex.Lock()
    entities[handle] = entity
    entityMutex.Unlock()

    // TODO: Integrate with actual toolkit core package when available
    // For now, just store in our binding layer

    return C.int(handle)
}

//export ValidateEntity
func ValidateEntity(entityType *C.char, entityID *C.char) C.int {
    goType := C.GoString(entityType)
    goID := C.GoString(entityID)

    // Basic validation rules
    if goType == "" {
        return 5 // EmptyType error
    }

    if goID == "" {
        return 4 // EmptyID error
    }

    // Additional validation can be added here
    // TODO: Use actual toolkit validation when core package is integrated

    return 0 // No error
}

//export GetEntityType
func GetEntityType(entityHandle C.int) *C.char {
    handle := int32(entityHandle)

    entityMutex.RLock()
    entity, exists := entities[handle]
    entityMutex.RUnlock()

    if !exists {
        return C.CString("") // Entity not found
    }

    return C.CString(entity.Type)
}

//export GetEntityID
func GetEntityID(entityHandle C.int) *C.char {
    handle := int32(entityHandle)

    entityMutex.RLock()
    entity, exists := entities[handle]
    entityMutex.RUnlock()

    if !exists {
        return C.CString("") // Entity not found
    }

    return C.CString(entity.ID)
}

//export DestroyEntity
func DestroyEntity(entityHandle C.int) {
    handle := int32(entityHandle)

    entityMutex.Lock()
    delete(entities, handle)
    entityMutex.Unlock()
}

//export GetEntityCount
func GetEntityCount() C.int {
    entityMutex.RLock()
    count := len(entities)
    entityMutex.RUnlock()

    return C.int(count)
}

//export EntityExists
func EntityExists(entityType *C.char, entityID *C.char) C.int {
    goType := C.GoString(entityType)
    goID := C.GoString(entityID)

    entityMutex.RLock()
    defer entityMutex.RUnlock()

    for _, entity := range entities {
        if entity.Type == goType && entity.ID == goID {
            return 1 // Found
        }
    }

    return 0 // Not found
}
```

**Update: `Seshat/Source/ThirdParty/RPGToolkit/simple_bindings.go`**

```go
// Add import for core_bindings integration
// (existing dice bindings remain unchanged)

// TODO: When integrating with actual rpg-toolkit core package:
// import "github.com/fadedpez/rpg-toolkit/core"
// 
// Then entities would be created as:
// entity := &core.GameEntity{ID: goID, Type: goType}
// 
// And validation would use:
// err := core.ValidateEntity(entity)
```

### 5. Integration with Existing Systems

**Update: `Seshat/Source/Seshat/RPGDiceSubsystem.h`**

```cpp
// Add to existing RPGDiceSubsystem
#include "RPGCore/Entity/RPGEntity.h"
#include "RPGCore/RPGCoreTypes.h"

// Add entity-aware dice rolling methods
UFUNCTION(BlueprintCallable, Category = "RPG Dice")
int32 RollForEntity(int32 Sides, TScriptInterface<IRPGEntityInterface> Entity);

UFUNCTION(BlueprintCallable, Category = "RPG Dice")
int32 RollWithAdvantageForEntity(int32 Sides, TScriptInterface<IRPGEntityInterface> Entity);

// This prepares for event system integration where dice rolls
// will include entity context for modifiers
```

### 6. Implementation Patterns from Research

**Entity Lifecycle Pattern (from toolkit analysis):**
```cpp
// UE implementation following toolkit patterns
void ARPGEntity::BeginPlay()
{
    Super::BeginPlay();
    
    if (!bEntityInitialized)
    {
        InitializeEntity();
    }
    
    RegisterWithSubsystem();
}

void ARPGEntity::InitializeEntity()
{
    if (EntityID.IsEmpty())
    {
        EntityID = GenerateEntityID();
    }
    
    if (EntityType.IsEmpty())
    {
        EntityType = GetDefaultEntityType();
    }
    
    bEntityInitialized = true;
}
```

**Validation Pattern (mirroring toolkit error system):**
```cpp
FRPGEntityValidationResult URPGEntitySubsystem::ValidateEntity(TScriptInterface<IRPGEntityInterface> Entity)
{
    if (!Entity.GetInterface())
    {
        return FRPGEntityValidationResult(false, 
            FRPGEntityError(ERPGEntityError::NilEntity, TEXT(""), TEXT(""), TEXT("ValidateEntity")));
    }
    
    FString EntityID = Entity->GetID();
    FString EntityType = Entity->GetType();
    
    if (EntityID.IsEmpty())
    {
        return FRPGEntityValidationResult(false,
            FRPGEntityError(ERPGEntityError::EmptyID, EntityID, EntityType, TEXT("ValidateEntity")));
    }
    
    if (EntityType.IsEmpty())
    {
        return FRPGEntityValidationResult(false,
            FRPGEntityError(ERPGEntityError::InvalidType, EntityID, EntityType, TEXT("ValidateEntity")));
    }
    
    return FRPGEntityValidationResult(true);
}
```

**Registry Pattern (thread-safe like toolkit):**
```cpp
FRPGEntityValidationResult URPGEntitySubsystem::RegisterEntity(TScriptInterface<IRPGEntityInterface> Entity)
{
    FScopeLock Lock(&EntityRegistryLock);
    
    // Validate first
    FRPGEntityValidationResult ValidationResult = ValidateEntity(Entity);
    if (!ValidationResult.bIsValid)
    {
        return ValidationResult;
    }
    
    FString EntityID = Entity->GetID();
    FString EntityType = Entity->GetType();
    
    // Check for duplicates
    if (EntityRegistry.Contains(EntityType))
    {
        if (EntityRegistry[EntityType].Contains(EntityID))
        {
            return FRPGEntityValidationResult(false,
                FRPGEntityError(ERPGEntityError::Duplicate, EntityID, EntityType, TEXT("RegisterEntity")));
        }
    }
    else
    {
        EntityRegistry.Add(EntityType, TMap<FString, TScriptInterface<IRPGEntityInterface>>());
    }
    
    // Register entity
    EntityRegistry[EntityType].Add(EntityID, Entity);
    
    // Sync with toolkit
    SyncEntityWithToolkit(Entity);
    
    // Broadcast event
    OnEntityRegistered.Broadcast(EntityID, EntityType);
    
    return FRPGEntityValidationResult(true);
}
```

## Testing Strategy

### Unit Tests
```cpp
// Test entity creation and validation
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRPGEntityCreationTest, "RPG.Core.Entity.Creation", 
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FRPGEntityCreationTest::RunTest(const FString& Parameters)
{
    // Test entity creation
    ARPGEntity* TestEntity = NewObject<ARPGEntity>();
    TestCase(TEXT("Entity created"), TestEntity != nullptr);
    
    // Test ID generation
    FString EntityID = TestEntity->GetID();
    TestCase(TEXT("Entity has valid ID"), !EntityID.IsEmpty());
    
    // Test type assignment
    FString EntityType = TestEntity->GetType();
    TestCase(TEXT("Entity has valid type"), !EntityType.IsEmpty());
    
    return true;
}
```

### Integration Tests
```cpp
// Test subsystem registration
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRPGEntitySubsystemTest, "RPG.Core.EntitySubsystem.Registration",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FRPGEntitySubsystemTest::RunTest(const FString& Parameters)
{
    URPGEntitySubsystem* Subsystem = GEngine->GetEngineSubsystem<URPGEntitySubsystem>();
    TestCase(TEXT("Subsystem exists"), Subsystem != nullptr);
    
    // Create test entity
    ARPGEntity* TestEntity = NewObject<ARPGEntity>();
    TScriptInterface<IRPGEntityInterface> EntityInterface(TestEntity);
    
    // Test registration
    FRPGEntityValidationResult Result = Subsystem->RegisterEntity(EntityInterface);
    TestCase(TEXT("Entity registration successful"), Result.bIsValid);
    
    return true;
}
```

## Success Criteria

- [ ] IEntity interface defined and functional
- [ ] ARPGEntity and URPGEntityObject implementations working
- [ ] URPGEntitySubsystem managing entity lifecycle
- [ ] Go bindings bridging UE entities to toolkit
- [ ] Error system providing clear validation feedback
- [ ] Blueprint integration for all entity operations
- [ ] Thread-safe entity registry operations
- [ ] Integration with existing dice rolling system
- [ ] Comprehensive test coverage
- [ ] Documentation for entity patterns

## Future Integration Points

Once Phase 1 is complete, this foundation enables:

1. **Event System Integration**: Events can reference entities naturally
2. **Spatial System**: Entities can be positioned and queried spatially  
3. **Combat System**: Combat actions work with entity references
4. **Condition System**: Status effects can be attached to entities
5. **Inventory System**: Items are entities with proper identity
6. **Character System**: Characters are entities with rich properties

## Dependencies

- Existing RPGDiceSubsystem integration (established foundation)
- UE subsystem patterns (proven working)
- Cross-compilation pipeline (established)
- rpg-toolkit core package understanding (research completed)

## Implementation Notes

1. **Follow UE Conventions**: Proper UPROPERTY usage, Blueprint integration, UE naming
2. **Maintain Backward Compatibility**: Existing dice rolling must continue working
3. **Thread Safety**: Entity registry operations must be thread-safe for multiplayer
4. **Extensibility**: Design for inheritance - specific entity types will extend ARPGEntity  
5. **Testing**: Comprehensive test coverage for foundational systems
6. **Documentation**: Clear patterns for future entity type implementation

This implementation plan provides the complete foundation for the rpg-toolkit integration, establishing the universal Entity abstraction that all other systems depend on.