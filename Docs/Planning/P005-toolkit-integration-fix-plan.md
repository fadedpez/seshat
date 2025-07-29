# Toolkit Integration Fix - Complete Implementation Plan

## Executive Summary

This document provides a comprehensive checklist and reference code for fixing the flawed toolkit integration. The current integration built custom orchestration layers instead of exposing the raw toolkit API. This plan removes all abstractions and exposes every public method/function/constant/type from the toolkit.

**Core Rule**: Every public method/function/constant/type in toolkit gets:
1. C binding in Go
2. UE function in subsystem  
3. Blueprint accessibility

## Current State Analysis

### What We Have (WRONG)
- **core_bindings.go**: Custom entity management system NOT in toolkit
- **dice_bindings.go**: Only 2 functions exposed, custom wrappers
- **URPGDiceSubsystem**: Advantage/disadvantage functions NOT in toolkit
- **URPGEntitySubsystem**: Custom entity storage NOT in toolkit

### What Toolkit Actually Provides
- **core/entity.go**: Entity interface (2 methods)
- **core/errors.go**: 6 error constants + EntityError struct
- **dice/roller.go**: Roller interface + CryptoRoller + DefaultRoller
- **dice/modifier.go**: Roll struct + 15+ functions

## Phase 1: Core Package Complete Exposure

### 1.1 Core Error Constants (6 items)
**File**: `/mnt/d/Projects/Seshat/Seshat/Source/ThirdParty/RPGToolkit/core_bindings.go`

**Toolkit Reference**:
```go
// From /home/frank/projects/rpg-toolkit/core/errors.go
var (
    ErrEntityNotFound = errors.New("entity not found")
    ErrInvalidEntity = errors.New("invalid entity")
    ErrDuplicateEntity = errors.New("duplicate entity")
    ErrNilEntity = errors.New("nil entity")
    ErrEmptyID = errors.New("empty entity ID")  
    ErrInvalidType = errors.New("invalid entity type")
)
```

**Required C Bindings**:
```go
//export GetEntityNotFoundError
func GetEntityNotFoundError() *C.char {
    return C.CString(core.ErrEntityNotFound.Error())
}

//export GetInvalidEntityError
func GetInvalidEntityError() *C.char {
    return C.CString(core.ErrInvalidEntity.Error())
}

//export GetDuplicateEntityError
func GetDuplicateEntityError() *C.char {
    return C.CString(core.ErrDuplicateEntity.Error())
}

//export GetNilEntityError
func GetNilEntityError() *C.char {
    return C.CString(core.ErrNilEntity.Error())
}

//export GetEmptyIDError
func GetEmptyIDError() *C.char {
    return C.CString(core.ErrEmptyID.Error())
}

//export GetInvalidTypeError
func GetInvalidTypeError() *C.char {
    return C.CString(core.ErrInvalidType.Error())
}

//export FreeString
func FreeString(str *C.char) {
    C.free(unsafe.Pointer(str))
}
```

### 1.2 EntityError Struct Handling
**Toolkit Reference**:
```go
// From /home/frank/projects/rpg-toolkit/core/errors.go
type EntityError struct {
    EntityID   string
    EntityType string
    Op         string
    Err        error
}

func NewEntityError(op, entityType, entityID string, err error) *EntityError
func (e *EntityError) Error() string
func (e *EntityError) Unwrap() error
```

**Required C Bindings**:
```go
//export CreateEntityError
func CreateEntityError(op, entityType, entityID, errMsg *C.char) unsafe.Pointer {
    opStr := C.GoString(op)
    typeStr := C.GoString(entityType)
    idStr := C.GoString(entityID)
    errStr := C.GoString(errMsg)
    
    baseErr := errors.New(errStr)
    entityErr := core.NewEntityError(opStr, typeStr, idStr, baseErr)
    
    return unsafe.Pointer(&entityErr)
}

//export GetEntityErrorMessage
func GetEntityErrorMessage(errPtr unsafe.Pointer) *C.char {
    entityErr := (*core.EntityError)(errPtr)
    return C.CString(entityErr.Error())
}

//export GetEntityErrorID
func GetEntityErrorID(errPtr unsafe.Pointer) *C.char {
    entityErr := (*core.EntityError)(errPtr)
    return C.CString(entityErr.EntityID)
}

//export GetEntityErrorType
func GetEntityErrorType(errPtr unsafe.Pointer) *C.char {
    entityErr := (*core.EntityError)(errPtr)
    return C.CString(entityErr.EntityType)
}

//export GetEntityErrorOp
func GetEntityErrorOp(errPtr unsafe.Pointer) *C.char {
    entityErr := (*core.EntityError)(errPtr)
    return C.CString(entityErr.Op)
}
```

### 1.3 Entity Interface Exposure
**Toolkit Reference**:
```go
// From /home/frank/projects/rpg-toolkit/core/entity.go
type Entity interface {
    GetID() string
    GetType() string
}
```

**Note**: Interface exposure requires concrete implementations. For now, provide validation functions:

```go
//export ValidateEntityID
func ValidateEntityID(id *C.char) C.int {
    idStr := C.GoString(id)
    if idStr == "" {
        return 0 // false
    }
    return 1 // true
}

//export ValidateEntityType
func ValidateEntityType(entityType *C.char) C.int {
    typeStr := C.GoString(entityType)
    if typeStr == "" {
        return 0 // false
    }
    return 1 // true
}
```

### 1.4 URPGEntitySubsystem Updates
**File**: `/mnt/d/Projects/Seshat/Seshat/Source/Seshat/RPGEntitySubsystem.h`

**Current Wrong Pattern** (REMOVE ALL OF THIS):
- Custom entity storage maps
- Entity lifecycle management
- AddEntity/RemoveEntity functions

**New Correct Pattern** (UE Reference from RPGDiceSubsystem.h):
```cpp
UCLASS()
class SESHAT_API URPGEntitySubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    // Error constant accessors
    UFUNCTION(BlueprintCallable, Category = "RPG Core")
    FString GetEntityNotFoundError() const;
    
    UFUNCTION(BlueprintCallable, Category = "RPG Core")
    FString GetInvalidEntityError() const;
    
    UFUNCTION(BlueprintCallable, Category = "RPG Core")
    FString GetDuplicateEntityError() const;
    
    UFUNCTION(BlueprintCallable, Category = "RPG Core")
    FString GetNilEntityError() const;
    
    UFUNCTION(BlueprintCallable, Category = "RPG Core")
    FString GetEmptyIDError() const;
    
    UFUNCTION(BlueprintCallable, Category = "RPG Core")
    FString GetInvalidTypeError() const;
    
    // Entity validation functions
    UFUNCTION(BlueprintCallable, Category = "RPG Core")
    bool ValidateEntityID(const FString& ID) const;
    
    UFUNCTION(BlueprintCallable, Category = "RPG Core")
    bool ValidateEntityType(const FString& Type) const;

private:
    // Function pointers (following RPGDiceSubsystem pattern)
    typedef ANSICHAR* (*GetEntityNotFoundErrorFunc)();
    typedef ANSICHAR* (*GetInvalidEntityErrorFunc)();
    typedef ANSICHAR* (*GetDuplicateEntityErrorFunc)();
    typedef ANSICHAR* (*GetNilEntityErrorFunc)();
    typedef ANSICHAR* (*GetEmptyIDErrorFunc)();
    typedef ANSICHAR* (*GetInvalidTypeErrorFunc)();
    typedef int32 (*ValidateEntityIDFunc)(const ANSICHAR*);
    typedef int32 (*ValidateEntityTypeFunc)(const ANSICHAR*);
    typedef void (*FreeStringFunc)(ANSICHAR*);
    
    // Function pointer instances
    GetEntityNotFoundErrorFunc GetEntityNotFoundErrorFuncPtr;
    GetInvalidEntityErrorFunc GetInvalidEntityErrorFuncPtr;
    GetDuplicateEntityErrorFunc GetDuplicateEntityErrorFuncPtr;
    GetNilEntityErrorFunc GetNilEntityErrorFuncPtr;
    GetEmptyIDErrorFunc GetEmptyIDErrorFuncPtr;
    GetInvalidTypeErrorFunc GetInvalidTypeErrorFuncPtr;
    ValidateEntityIDFunc ValidateEntityIDFuncPtr;
    ValidateEntityTypeFunc ValidateEntityTypeFuncPtr;
    FreeStringFunc FreeStringFuncPtr;
    
    bool bFunctionsLoaded;
    void* ToolkitDLLHandle;
    
    void LoadDLLFunctions();
};
```

## Phase 2: Dice Package Complete Exposure

### 2.1 Current Dice Subsystem Analysis
**File**: `/mnt/d/Projects/Seshat/Seshat/Source/Seshat/RPGDiceSubsystem.h`

**What's WRONG (remove these)**:
- `RollWithAdvantage()` - NOT in toolkit
- `RollWithDisadvantage()` - NOT in toolkit  
- `RollForEntity()` - NOT in toolkit
- `RollWithAdvantageForEntity()` - NOT in toolkit
- `RollMultiple()` - calls toolkit but wrong pattern

**What's CORRECT (keep these)**:
- `Roll(int32 Sides)` - maps to `Roller.Roll(size)`
- DLL loading pattern
- Function pointer pattern

### 2.2 Roller Interface Complete Exposure
**Toolkit Reference**:
```go
// From /home/frank/projects/rpg-toolkit/dice/roller.go
type Roller interface {
    Roll(size int) (int, error)
    RollN(count, size int) ([]int, error)
}

var DefaultRoller Roller = &CryptoRoller{}
func SetDefaultRoller(r Roller)
```

**Required C Bindings**:
```go
//export CreateCryptoRoller
func CreateCryptoRoller() unsafe.Pointer {
    roller := &dice.CryptoRoller{}
    return unsafe.Pointer(roller)
}

//export RollerRoll
func RollerRoll(rollerPtr unsafe.Pointer, size C.int) C.int {
    roller := (*dice.CryptoRoller)(rollerPtr)
    result, err := roller.Roll(int(size))
    if err != nil {
        return -1 // Error indicator
    }
    return C.int(result)
}

//export RollerRollN
func RollerRollN(rollerPtr unsafe.Pointer, count, size C.int, results *C.int) C.int {
    roller := (*dice.CryptoRoller)(rollerPtr)
    rolls, err := roller.RollN(int(count), int(size))
    if err != nil {
        return -1 // Error indicator
    }
    
    // Copy results to C array
    resultsSlice := (*[1 << 30]C.int)(unsafe.Pointer(results))[:count:count]
    for i, roll := range rolls {
        resultsSlice[i] = C.int(roll)
    }
    return C.int(len(rolls))
}

//export GetDefaultRoller
func GetDefaultRoller() unsafe.Pointer {
    return unsafe.Pointer(&dice.DefaultRoller)
}

//export SetDefaultRoller
func SetDefaultRoller(rollerPtr unsafe.Pointer) {
    roller := (*dice.Roller)(rollerPtr)
    dice.SetDefaultRoller(*roller)
}
```

### 2.3 Roll Struct Complete Exposure
**Toolkit Reference**:
```go
// From /home/frank/projects/rpg-toolkit/dice/modifier.go
type Roll struct { /* private fields */ }

func NewRoll(count, size int) (*Roll, error)
func NewRollWithRoller(count, size int, roller Roller) (*Roll, error)
func (r *Roll) GetValue() int
func (r *Roll) Err() error
func (r *Roll) GetDescription() string
```

**Required C Bindings**:
```go
//export CreateRoll
func CreateRoll(count, size C.int) unsafe.Pointer {
    roll, err := dice.NewRoll(int(count), int(size))
    if err != nil {
        return nil
    }
    return unsafe.Pointer(roll)
}

//export CreateRollWithRoller
func CreateRollWithRoller(count, size C.int, rollerPtr unsafe.Pointer) unsafe.Pointer {
    roller := (*dice.Roller)(rollerPtr)
    roll, err := dice.NewRollWithRoller(int(count), int(size), *roller)
    if err != nil {
        return nil
    }
    return unsafe.Pointer(roll)
}

//export RollGetValue
func RollGetValue(rollPtr unsafe.Pointer) C.int {
    roll := (*dice.Roll)(rollPtr)
    return C.int(roll.GetValue())
}

//export RollGetDescription
func RollGetDescription(rollPtr unsafe.Pointer) *C.char {
    roll := (*dice.Roll)(rollPtr)
    return C.CString(roll.GetDescription())
}

//export RollHasError
func RollHasError(rollPtr unsafe.Pointer) C.int {
    roll := (*dice.Roll)(rollPtr)
    if roll.Err() != nil {
        return 1 // true
    }
    return 0 // false
}

//export RollGetError
func RollGetError(rollPtr unsafe.Pointer) *C.char {
    roll := (*dice.Roll)(rollPtr)
    err := roll.Err()
    if err != nil {
        return C.CString(err.Error())
    }
    return nil
}
```

### 2.4 Helper Functions Complete Exposure
**Toolkit Reference**:
```go
// From /home/frank/projects/rpg-toolkit/dice/modifier.go
func D4(count int) *Roll
func D6(count int) *Roll
func D8(count int) *Roll
func D10(count int) *Roll
func D12(count int) *Roll
func D20(count int) *Roll
func D100(count int) *Roll
```

**Required C Bindings**:
```go
//export D4
func D4(count C.int) unsafe.Pointer {
    roll := dice.D4(int(count))
    return unsafe.Pointer(roll)
}

//export D6
func D6(count C.int) unsafe.Pointer {
    roll := dice.D6(int(count))
    return unsafe.Pointer(roll)
}

//export D8
func D8(count C.int) unsafe.Pointer {
    roll := dice.D8(int(count))
    return unsafe.Pointer(roll)
}

//export D10
func D10(count C.int) unsafe.Pointer {
    roll := dice.D10(int(count))
    return unsafe.Pointer(roll)
}

//export D12
func D12(count C.int) unsafe.Pointer {
    roll := dice.D12(int(count))
    return unsafe.Pointer(roll)
}

//export D20
func D20(count C.int) unsafe.Pointer {
    roll := dice.D20(int(count))
    return unsafe.Pointer(roll)
}

//export D100
func D100(count C.int) unsafe.Pointer {
    roll := dice.D100(int(count))
    return unsafe.Pointer(roll)
}
```

### 2.5 Updated URPGDiceSubsystem
**File**: `/mnt/d/Projects/Seshat/Seshat/Source/Seshat/RPGDiceSubsystem.h`

**Functions to REMOVE**:
```cpp
// ❌ REMOVE - Not in toolkit
int32 RollWithAdvantage(int32 Sides);
int32 RollWithDisadvantage(int32 Sides);
int32 RollForEntity(int32 Sides, TScriptInterface<IRPGEntityInterface> Entity);
int32 RollWithAdvantageForEntity(int32 Sides, TScriptInterface<IRPGEntityInterface> Entity);
TArray<int32> RollMultiple(int32 Count, int32 Sides); // Wrong pattern
```

**Functions to ADD**:
```cpp
// Roller interface functions
UFUNCTION(BlueprintCallable, Category = "RPG Dice")
int32 RollerRoll(int32 Size);

UFUNCTION(BlueprintCallable, Category = "RPG Dice")
TArray<int32> RollerRollN(int32 Count, int32 Size);

// Roll struct functions
UFUNCTION(BlueprintCallable, Category = "RPG Dice")
int32 CreateRoll(int32 Count, int32 Size);

UFUNCTION(BlueprintCallable, Category = "RPG Dice")
int32 RollGetValue(int32 RollHandle);

UFUNCTION(BlueprintCallable, Category = "RPG Dice")
FString RollGetDescription(int32 RollHandle);

UFUNCTION(BlueprintCallable, Category = "RPG Dice")
bool RollHasError(int32 RollHandle);

// Helper functions
UFUNCTION(BlueprintCallable, Category = "RPG Dice")
int32 D4(int32 Count);

UFUNCTION(BlueprintCallable, Category = "RPG Dice")
int32 D6(int32 Count);

UFUNCTION(BlueprintCallable, Category = "RPG Dice")
int32 D8(int32 Count);

UFUNCTION(BlueprintCallable, Category = "RPG Dice")
int32 D10(int32 Count);

UFUNCTION(BlueprintCallable, Category = "RPG Dice")
int32 D12(int32 Count);

UFUNCTION(BlueprintCallable, Category = "RPG Dice")
int32 D20(int32 Count);

UFUNCTION(BlueprintCallable, Category = "RPG Dice")
int32 D100(int32 Count);
```

## Phase 3: Implementation Checklist

### 3.1 Core Package Checklist
- [ ] Remove all custom entity management from `core_bindings.go`
- [ ] Add 6 error constant C bindings
- [ ] Add EntityError struct C bindings (5 functions)
- [ ] Add entity validation C bindings (2 functions)
- [ ] Update `URPGEntitySubsystem.h` with new function signatures
- [ ] Update `URPGEntitySubsystem.cpp` with new implementations
- [ ] Remove custom entity storage from URPGEntitySubsystem
- [ ] Test error constant access from Blueprint

### 3.2 Dice Package Checklist
- [ ] Add Roller interface C bindings (4 functions)
- [ ] Add Roll struct C bindings (6 functions)  
- [ ] Add 7 helper function C bindings (D4-D100)
- [ ] Remove advantage/disadvantage functions from URPGDiceSubsystem
- [ ] Remove entity-aware functions from URPGDiceSubsystem
- [ ] Add all new toolkit functions to URPGDiceSubsystem
- [ ] Update function pointer declarations
- [ ] Update DLL loading function
- [ ] Test all functions from Blueprint

### 3.3 Build System Checklist
- [ ] Recompile Go DLL with all new exports
- [ ] Update C header if needed
- [ ] Clean UE build cache
- [ ] Rebuild UE project
- [ ] Verify DLL loads without errors
- [ ] Test subsystem initialization

### 3.4 Testing Checklist
- [ ] Test error constant functions work
- [ ] Test entity validation functions work
- [ ] Test basic roller functions work
- [ ] Test Roll struct lifecycle (create → getValue → getDescription)
- [ ] Test all 7 helper functions (D4-D100)
- [ ] Test error handling for invalid inputs
- [ ] Verify Blueprint access to all functions

## Phase 4: Memory Management Pattern

### 4.1 Handle-Based System (For Roll Objects)
```cpp
// In URPGDiceSubsystem.h
private:
    TMap<int32, void*> RollHandles;
    int32 NextRollHandle = 1;
    
    int32 CreateRollHandle(void* RollPtr);
    void* GetRollPtr(int32 Handle);
    void ReleaseRollHandle(int32 Handle);
```

### 4.2 String Memory Management
```cpp
// Always free C strings after use
FString ConvertAndFreeString(ANSICHAR* CStr)
{
    if (!CStr) return FString();
    FString Result = FString(ANSI_TO_TCHAR(CStr));
    if (FreeStringFuncPtr) {
        FreeStringFuncPtr(CStr);
    }
    return Result;
}
```

## Phase 5: Documentation Update

### 5.1 Update CLAUDE.md
Add section about faithful toolkit exposure:
```markdown
## Critical: Faithful Toolkit Exposure Rule

**NEVER create orchestration layers or convenience functions.**

When integrating rpg-toolkit:
- Every public method/function/constant/type gets C binding
- Every C binding gets UE subsystem function  
- Every UE function gets Blueprint access
- NO editorial decisions about usefulness
- NO "helpful" abstractions or wrappers

This enables:
- Testing individual toolkit functions in isolation
- Debugging at toolkit level rather than wrapper level
- Full access to toolkit capabilities for architectural decisions
```

### 5.2 Function Reference Documentation
Create complete reference showing:
- Toolkit function → C binding → UE function → Blueprint usage
- For every exposed function
- With parameter types and return types
- With error handling patterns

## Success Criteria

1. **Complete Exposure**: Every public toolkit method accessible from Blueprint
2. **No Abstractions**: Zero custom convenience functions or orchestration
3. **Faithful Mapping**: UE functions match toolkit signatures exactly
4. **Error Handling**: All toolkit errors properly exposed and handled
5. **Memory Safety**: Proper string and handle management
6. **Testing**: All functions work correctly from Blueprint

## Risk Mitigation

1. **Backup Current State**: Git commit before starting changes
2. **Incremental Implementation**: One package at a time
3. **Test Each Phase**: Verify each phase works before proceeding
4. **Rollback Plan**: Keep old functions until new ones verified
5. **Documentation**: Document every change for future reference

This plan provides complete fidelity to the toolkit while enabling full UE/Blueprint integration without abstraction layers.