# Core Integration Planning - Seshat UE Integration

## Current State Analysis

### What's Actually in rpg-toolkit/core

**Files:**
- `entity.go` - Single interface with 2 methods
- `errors.go` - Error constants and EntityError struct  
- `entity_test.go` - Tests
- `errors_test.go` - Tests
- `generate.go` - Code generation
- `mock/mock_entity.go` - Mock for testing

**Actual Core API:**
```go
// Entity interface (entity.go)
type Entity interface {
    GetID() string
    GetType() string  
}

// Error constants (errors.go)
var (
    ErrEntityNotFound = errors.New("entity not found")
    ErrInvalidEntity = errors.New("invalid entity")
    ErrDuplicateEntity = errors.New("duplicate entity")
    ErrNilEntity = errors.New("nil entity")
    ErrEmptyID = errors.New("empty entity ID")
    ErrInvalidType = errors.New("invalid entity type")
)

// EntityError struct (errors.go)
type EntityError struct {
    EntityID   string
    EntityType string
    Op         string
    Err        error
}

// EntityError methods (errors.go)  
func (e *EntityError) Error() string
func (e *EntityError) Unwrap() error
func NewEntityError(op, entityType, entityID string, err error) *EntityError
```

**That's it. The core package is intentionally minimal.**

### What We Currently Have in core_bindings.go

**❌ COMPLETELY WRONG - We implemented a custom entity system:**
```go
// Custom Entity struct - NOT from toolkit
type Entity struct {
    ID   string
    Type string
}

// Custom entity storage system - NOT from toolkit
var (
    entities    = make(map[int32]*Entity)
    entityMutex = sync.RWMutex{}
    nextHandle  = int32(1)
)

// Custom functions we made up - NONE of these exist in toolkit
//export CreateEntity
//export ValidateEntity  
//export GetEntityType
//export GetEntityID
//export DestroyEntity
//export GetEntityCount
//export EntityExists
```

## Problem Analysis

### Critical Issues

1. **We implemented NONE of the actual toolkit core**
   - We didn't expose the Entity interface
   - We didn't expose any of the error constants
   - We didn't expose the EntityError type or its methods

2. **We built a custom entity management system**
   - Handle-based storage (not in toolkit)
   - Entity creation/destruction (not in toolkit)  
   - Entity validation (not in toolkit)
   - Entity counting/existence checks (not in toolkit)

3. **We completely misunderstood what core provides**
   - Core is just interfaces and errors
   - Core doesn't manage entity instances
   - Core doesn't provide lifecycle management
   - Core doesn't provide storage

### What We Need to Fix

## Correct Core Integration Plan

### Phase 1: Remove All Custom Implementation

**Delete from core_bindings.go:**
- [ ] Custom Entity struct
- [ ] Custom entity storage system (entities map, mutex, handles)
- [ ] All custom entity management functions
- [ ] All validation logic we made up

### Phase 2: Expose Actual Toolkit Core

**Add to core_bindings.go:**
- [ ] Error constant exposure functions
- [ ] EntityError struct handling
- [ ] NewEntityError function

**Core error constants to expose:**
```go
//export GetErrEntityNotFound
func GetErrEntityNotFound() *C.char

//export GetErrInvalidEntity  
func GetErrInvalidEntity() *C.char

//export GetErrDuplicateEntity
func GetErrDuplicateEntity() *C.char

//export GetErrNilEntity
func GetErrNilEntity() *C.char

//export GetErrEmptyID
func GetErrEmptyID() *C.char

//export GetErrInvalidType
func GetErrInvalidType() *C.char
```

**EntityError handling:**
```go
//export NewEntityError
func NewEntityError(op, entityType, entityID, errMsg *C.char) unsafe.Pointer

//export EntityErrorGetMessage
func EntityErrorGetMessage(errorPtr unsafe.Pointer) *C.char

//export EntityErrorUnwrap  
func EntityErrorUnwrap(errorPtr unsafe.Pointer) *C.char
```

### Phase 3: Update UE Integration

**Update URPGEntitySubsystem to:**
- [ ] Remove all custom entity management
- [ ] Expose core error constants to Blueprint
- [ ] Provide EntityError handling utilities
- [ ] Focus on being a bridge to pass entities between other toolkit modules

### Phase 4: Entity Interface Handling

**Since Entity is an interface, we need patterns for:**
- [ ] Accepting entities from other toolkit modules
- [ ] Passing entities between toolkit modules  
- [ ] Extracting ID/Type from entities in UE

**Pattern for entity interface:**
```go
//export GetEntityID
func GetEntityID(entityPtr unsafe.Pointer) *C.char {
    if entityPtr == nil {
        return C.CString("")
    }
    entity := (*interface{})(entityPtr)
    if e, ok := (*entity).(core.Entity); ok {
        return C.CString(e.GetID())
    }
    return C.CString("")
}

//export GetEntityType  
func GetEntityType(entityPtr unsafe.Pointer) *C.char {
    // Similar pattern
}
```

## Dice Integration Analysis

### What's Actually in rpg-toolkit/dice

**Core Types:**
```go
// Roller interface (roller.go)
type Roller interface {
    Roll(size int) (int, error)
    RollN(count, size int) ([]int, error)
}

// CryptoRoller struct (roller.go) 
type CryptoRoller struct{}
// Methods: Roll(size int), RollN(count, size int)

// Roll struct (modifier.go)
type Roll struct {
    count, size int
    // private fields
}
// Methods: GetValue(), Err(), GetDescription()

// Functions:
func NewRoll(count, size int) (*Roll, error)
func NewRollWithRoller(count, size int, roller Roller) (*Roll, error)
func SetDefaultRoller(r Roller)

// Helper functions:
func D4(count int) *Roll
func D6(count int) *Roll  
func D8(count int) *Roll
func D10(count int) *Roll
func D12(count int) *Roll
func D20(count int) *Roll
func D100(count int) *Roll

// Variables:
var DefaultRoller Roller = &CryptoRoller{}
```

### What We Currently Have in dice_bindings.go

**❌ PARTIALLY WRONG - We only exposed 2 functions:**
```go
//export CreateDiceRoller  // Custom - returns dummy pointer
func CreateDiceRoller() unsafe.Pointer

//export RollDie          // Wrapper around dice.NewRoll + GetValue
func RollDie(rollerPtr unsafe.Pointer, sides C.int) C.int
```

### What We Have in URPGDiceSubsystem  

**❌ WRONG - We built convenience functions:**
```cpp  
// These are NOT in the toolkit - we made them up
UFUNCTION(BlueprintCallable)
int32 RollWithAdvantage(int32 Sides);

UFUNCTION(BlueprintCallable) 
int32 RollWithDisadvantage(int32 Sides);

UFUNCTION(BlueprintCallable)
TArray<int32> RollMultiple(int32 Count, int32 Sides);

UFUNCTION(BlueprintCallable)
int32 RollForEntity(int32 Sides, TScriptInterface<IRPGEntityInterface> Entity);
```

## Major Problems with Current Integration

### 1. Core - Completely Wrong
- Built custom entity management instead of exposing actual core
- Missing all actual core functionality (errors, EntityError)

### 2. Dice - Partially Wrong  
- Only exposed 2 out of ~15 actual functions
- Built UE convenience functions instead of exposing raw toolkit
- Missing: Roll struct, Roller interface, helper functions (D4, D6, etc.)
- Missing: NewRoll, NewRollWithRoller, GetDescription, Err methods

### 3. Abstraction Layer Problem
**We built an orchestration/convenience layer in UE that doesn't exist in toolkit:**
- `RollWithAdvantage` - toolkit doesn't have this
- `RollWithDisadvantage` - toolkit doesn't have this  
- `RollMultiple` - toolkit has RollN but we wrapped it
- `RollForEntity` - toolkit doesn't have entity-specific rolling

**This is exactly what you told me not to do.**

## Key Realizations

1. **Core doesn't manage entities** - it just defines what an entity is
2. **Entity management happens in other modules** (like spatial, character systems)
3. **Our job is to expose the interface** - not implement entity storage
4. **Core is about contracts** - interfaces and errors, not implementations
5. **Dice has rich API** - Roll struct, Roller interface, helper functions, descriptions
6. **We built UE conveniences** - instead of exposing the actual toolkit dice API

## Complete Fix Plan

### Phase 1: Start Over - Delete Wrong Implementation

**Delete from core_bindings.go:**
- [ ] Custom Entity struct (lines 11-24)
- [ ] Custom entity storage system (lines 27-40) 
- [ ] All custom entity management functions (lines 42-158)

**Delete from dice_bindings.go:**
- [ ] CreateDiceRoller dummy function
- [ ] Keep only basic RollDie but will expand massively

**Delete from URPGDiceSubsystem:**
- [ ] RollWithAdvantage (not in toolkit)
- [ ] RollWithDisadvantage (not in toolkit)  
- [ ] RollMultiple (toolkit has RollN, expose that instead)
- [ ] RollForEntity (not in toolkit)
- [ ] All event publishing logic (that's orchestration)

### Phase 2: Expose Actual Core Package

**Add to core_bindings.go - Error Constants:**
```go
//export GetErrEntityNotFound
func GetErrEntityNotFound() *C.char {
    return C.CString(core.ErrEntityNotFound.Error())
}

//export GetErrInvalidEntity  
func GetErrInvalidEntity() *C.char {
    return C.CString(core.ErrInvalidEntity.Error())
}

//export GetErrDuplicateEntity
func GetErrDuplicateEntity() *C.char {
    return C.CString(core.ErrDuplicateEntity.Error())
}

//export GetErrNilEntity
func GetErrNilEntity() *C.char {
    return C.CString(core.ErrNilEntity.Error())
}

//export GetErrEmptyID
func GetErrEmptyID() *C.char {
    return C.CString(core.ErrEmptyID.Error())
}

//export GetErrInvalidType
func GetErrInvalidType() *C.char {
    return C.CString(core.ErrInvalidType.Error())
}
```

**Add to core_bindings.go - EntityError:**
```go
//export NewEntityError
func NewEntityError(op, entityType, entityID, errMsg *C.char) unsafe.Pointer {
    goOp := C.GoString(op)
    goEntityType := C.GoString(entityType)
    goEntityID := C.GoString(entityID)
    goErrMsg := C.GoString(errMsg)
    
    err := errors.New(goErrMsg)
    entityError := core.NewEntityError(goOp, goEntityType, goEntityID, err)
    return unsafe.Pointer(entityError)
}

//export EntityErrorGetMessage
func EntityErrorGetMessage(errorPtr unsafe.Pointer) *C.char {
    if errorPtr == nil {
        return C.CString("")
    }
    entityError := (*core.EntityError)(errorPtr)
    return C.CString(entityError.Error())
}

//export EntityErrorUnwrap
func EntityErrorUnwrap(errorPtr unsafe.Pointer) *C.char {
    if errorPtr == nil {
        return C.CString("")
    }
    entityError := (*core.EntityError)(errorPtr)
    if err := entityError.Unwrap(); err != nil {
        return C.CString(err.Error())
    }
    return C.CString("")
}
```

**Add to core_bindings.go - Entity Interface:**
```go
//export GetEntityID
func GetEntityID(entityPtr unsafe.Pointer) *C.char {
    if entityPtr == nil {
        return C.CString("")
    }
    entity := (*core.Entity)(entityPtr)
    return C.CString((*entity).GetID())
}

//export GetEntityType
func GetEntityType(entityPtr unsafe.Pointer) *C.char {
    if entityPtr == nil {
        return C.CString("")
    }
    entity := (*core.Entity)(entityPtr)
    return C.CString((*entity).GetType())
}
```

### Phase 3: Expose Complete Dice Package

**Replace dice_bindings.go completely:**
```go
// Roller interface functions
//export NewCryptoRoller
func NewCryptoRoller() unsafe.Pointer

//export RollerRoll
func RollerRoll(rollerPtr unsafe.Pointer, size C.int) C.int

//export RollerRollN  
func RollerRollN(rollerPtr unsafe.Pointer, count, size C.int) unsafe.Pointer // returns int array

//export SetDefaultRoller
func SetDefaultRoller(rollerPtr unsafe.Pointer)

// Roll struct functions
//export NewRoll
func NewRoll(count, size C.int) unsafe.Pointer

//export NewRollWithRoller
func NewRollWithRoller(count, size C.int, rollerPtr unsafe.Pointer) unsafe.Pointer

//export RollGetValue
func RollGetValue(rollPtr unsafe.Pointer) C.int

//export RollErr
func RollErr(rollPtr unsafe.Pointer) *C.char

//export RollGetDescription
func RollGetDescription(rollPtr unsafe.Pointer) *C.char

// Helper functions - all the D4, D6, D8, D10, D12, D20, D100 functions
//export D4
func D4(count C.int) unsafe.Pointer

//export D6
func D6(count C.int) unsafe.Pointer

//export D8  
func D8(count C.int) unsafe.Pointer

//export D10
func D10(count C.int) unsafe.Pointer

//export D12
func D12(count C.int) unsafe.Pointer

//export D20
func D20(count C.int) unsafe.Pointer

//export D100
func D100(count C.int) unsafe.Pointer
```

### Phase 4: Update UE Subsystems - Raw Toolkit Only

**URPGCoreSubsystem - Just expose core errors and EntityError:**
```cpp
UFUNCTION(BlueprintCallable)
FString GetErrEntityNotFound();

UFUNCTION(BlueprintCallable)
FString GetErrInvalidEntity();

UFUNCTION(BlueprintCallable)
FString GetErrDuplicateEntity();

UFUNCTION(BlueprintCallable)
FString GetErrNilEntity();

UFUNCTION(BlueprintCallable)
FString GetErrEmptyID();

UFUNCTION(BlueprintCallable)
FString GetErrInvalidType();

UFUNCTION(BlueprintCallable)
int32 NewEntityError(const FString& Op, const FString& EntityType, const FString& EntityID, const FString& ErrorMsg);

UFUNCTION(BlueprintCallable)
FString GetEntityErrorMessage(int32 ErrorHandle);

UFUNCTION(BlueprintCallable)
FString GetEntityID(int32 EntityHandle);

UFUNCTION(BlueprintCallable) 
FString GetEntityType(int32 EntityHandle);
```

**URPGDiceSubsystem - Expose ALL dice functions:**
```cpp
// Roller interface
UFUNCTION(BlueprintCallable)
int32 NewCryptoRoller();

UFUNCTION(BlueprintCallable)
int32 RollerRoll(int32 RollerHandle, int32 Size);

UFUNCTION(BlueprintCallable)
TArray<int32> RollerRollN(int32 RollerHandle, int32 Count, int32 Size);

UFUNCTION(BlueprintCallable)
void SetDefaultRoller(int32 RollerHandle);

// Roll struct  
UFUNCTION(BlueprintCallable)
int32 NewRoll(int32 Count, int32 Size);

UFUNCTION(BlueprintCallable)
int32 NewRollWithRoller(int32 Count, int32 Size, int32 RollerHandle);

UFUNCTION(BlueprintCallable)
int32 RollGetValue(int32 RollHandle);

UFUNCTION(BlueprintCallable)
FString RollErr(int32 RollHandle);

UFUNCTION(BlueprintCallable)
FString RollGetDescription(int32 RollHandle);

// Helper functions
UFUNCTION(BlueprintCallable)
int32 D4(int32 Count);

UFUNCTION(BlueprintCallable)
int32 D6(int32 Count);

UFUNCTION(BlueprintCallable)
int32 D8(int32 Count);

UFUNCTION(BlueprintCallable)
int32 D10(int32 Count);

UFUNCTION(BlueprintCallable)
int32 D12(int32 Count);

UFUNCTION(BlueprintCallable)
int32 D20(int32 Count);

UFUNCTION(BlueprintCallable)
int32 D100(int32 Count);
```

### Phase 5: Test Raw Toolkit Usage

**Create Blueprint test to verify you can:**
- [ ] Use all core error constants
- [ ] Create and use EntityError
- [ ] Use complete dice API (Roll objects, descriptions, helpers)
- [ ] Chain toolkit functions together
- [ ] See what orchestration patterns YOU want to build

## Success Criteria - Complete Toolkit Exposure

**Core Package (100% coverage):**
- [ ] All 6 error constants accessible
- [ ] EntityError struct fully usable
- [ ] Entity interface methods accessible 
- [ ] NewEntityError function exposed

**Dice Package (100% coverage):**
- [ ] Roller interface completely exposed
- [ ] Roll struct completely exposed  
- [ ] All helper functions (D4-D100) exposed
- [ ] SetDefaultRoller function exposed
- [ ] Error handling (Roll.Err()) exposed
- [ ] Description system (Roll.GetDescription()) exposed

**No Custom Logic:**
- [ ] No convenience functions
- [ ] No orchestration layers
- [ ] No entity management systems
- [ ] Pure toolkit function mapping only

**User Can Now:**
- [ ] See exactly what toolkit provides
- [ ] Use raw toolkit in UE/Blueprint
- [ ] Decide what orchestration they want
- [ ] Build their own convenience layers if desired