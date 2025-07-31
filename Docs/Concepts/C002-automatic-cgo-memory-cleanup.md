# C001: Automatic CGO Memory Cleanup

**Date:** July 30, 2025  
**Status:** Concept Proposal  
**Related:** P006 CGO Memory Management Implementation, ADR A001  
**Branch:** `cgo-memory-management`

## Problem Statement

The current CGO memory registry implementation requires manual `RollCleanup()` calls, which creates several user experience and reliability issues:

### Current Manual Cleanup Issues

1. **Blueprint Complexity:** Every Roll usage requires remembering to call cleanup
2. **Memory Leak Risk:** Forgotten cleanup calls accumulate objects indefinitely
3. **Error-Prone Pattern:** Easy to forget cleanup in complex Blueprint logic
4. **Cognitive Overhead:** Users must track handle lifecycles manually

### Current Usage Pattern (Problematic)
```cpp
// Blueprint must remember all of this:
int32 handle = DiceSubsystem->D20(1);           // Create
int32 value = DiceSubsystem->RollGetValue(handle);     // Use
FString desc = DiceSubsystem->RollGetDescription(handle); // Use  
DiceSubsystem->RollCleanup(handle);             // ❌ MUST REMEMBER THIS
```

## Proposed Solution: Automatic Cleanup

### Core Concept: Immediate Value Extraction

Instead of returning handles that require lifecycle management, extract all needed values immediately and return them in a structured format.

### Two Implementation Options

#### Option A: Multi-Return Blueprint Functions
```cpp
// New Blueprint functions that return everything at once:
UFUNCTION(BlueprintCallable, Category = "RPG Dice")
bool D20Complete(int32 Count, int32& OutValue, FString& OutDescription, FString& OutError);

// Usage becomes simple:
int32 value;
FString desc, error;
bool success = DiceSubsystem->D20Complete(1, value, desc, error);
// No cleanup needed - no handles to manage
```

#### Option B: Roll Result Struct
```cpp
// New Blueprint-friendly struct:
USTRUCT(BlueprintType)
struct FRollResult
{
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadOnly)
    int32 Value = -1;
    
    UPROPERTY(BlueprintReadOnly)
    FString Description;
    
    UPROPERTY(BlueprintReadOnly)
    bool HasError = false;
    
    UPROPERTY(BlueprintReadOnly)
    FString ErrorMessage;
};

// New Blueprint function:
UFUNCTION(BlueprintCallable, Category = "RPG Dice")
FRollResult D20Complete(int32 Count);

// Usage becomes elegant:
FRollResult result = DiceSubsystem->D20Complete(1);
int32 value = result.Value;
FString desc = result.Description;
// No cleanup needed - no handles to manage
```

## Technical Implementation

### Go Binding Changes (Minimal)
```go
// Keep existing registry for complex use cases, add new immediate functions:

//export D20Complete
func D20Complete(count C.int, outValue *C.int, outDesc **C.char, outError **C.char) C.int {
    roll := dice.D20(int(count))
    
    *outValue = C.int(roll.GetValue())
    *outDesc = C.CString(roll.GetDescription())
    
    if roll.Err() != nil {
        *outError = C.CString(roll.Err().Error())
        return 0 // Has error
    } else {
        *outError = C.CString("")
        return 1 // Success
    }
    
    // No registry needed - roll goes out of scope and gets GC'd naturally
}
```

### UE Subsystem Changes
```cpp
// Option B implementation:
FRollResult URPGDiceSubsystem::D20Complete(int32 Count)
{
    FRollResult Result;
    
    if (!IsSafeToCallFunction() || !D20CompleteFuncPtr)
    {
        Result.HasError = true;
        Result.ErrorMessage = TEXT("Function not available");
        return Result;
    }
    
    int32 value;
    ANSICHAR* desc;
    ANSICHAR* error;
    
    int32 success = D20CompleteFuncPtr(Count, &value, &desc, &error);
    
    Result.Value = value;
    Result.Description = ConvertAndFreeString(desc);
    Result.HasError = (success == 0);
    Result.ErrorMessage = ConvertAndFreeString(error);
    
    return Result;
}
```

## Benefits of Automatic Cleanup

### 1. Simplified Blueprint Usage
```cpp
// Before (manual cleanup):
int32 handle = DiceSubsystem->D20(1);
int32 value = DiceSubsystem->RollGetValue(handle);
FString desc = DiceSubsystem->RollGetDescription(handle);
DiceSubsystem->RollCleanup(handle); // ❌ Easy to forget

// After (automatic):
FRollResult result = DiceSubsystem->D20Complete(1);
int32 value = result.Value;          // ✅ Simple access
FString desc = result.Description;   // ✅ No cleanup needed
```

### 2. Zero Memory Leak Risk
- No handles to track or clean up
- Go objects naturally garbage collected after value extraction
- No registry accumulation over time

### 3. Better Blueprint Integration
- Follows UE patterns (structs are Blueprint-native)
- Single function call gets all needed data
- Works naturally with Blueprint's visual scripting

### 4. Performance Benefits
- No registry overhead for simple use cases
- Fewer CGO calls (1 instead of 3-4)
- Natural Go GC behavior

## Migration Strategy

### Phase 1: Add New Complete Functions (Non-Breaking)
```cpp
// Keep existing handle-based functions for backward compatibility:
int32 D20(int32 Count);              // Current - returns handle
int32 RollGetValue(int32 Handle);    // Current - uses handle
void RollCleanup(int32 Handle);      // Current - manual cleanup

// Add new automatic functions:
FRollResult D20Complete(int32 Count); // New - automatic cleanup
```

### Phase 2: Deprecate Handle Functions
- Mark handle-based functions as deprecated
- Update documentation to recommend Complete functions
- Migrate existing Blueprints to new pattern

### Phase 3: Remove Handle Functions (Breaking Change)
- Remove handle-based API after sufficient migration period
- Simplify CGO bindings by removing registry for simple cases
- Keep registry only for complex objects that truly need persistence

## Use Cases Analysis

### Simple Dice Rolling (95% of use cases)
```cpp
// Perfect fit for automatic cleanup:
FRollResult result = DiceSubsystem->D20Complete(1);
UE_LOG(LogTemp, Log, TEXT("Rolled %d: %s"), result.Value, *result.Description);
```

### Complex Roll Analysis (5% of use cases)
```cpp
// Could still use handle-based approach if needed:
int32 handle = DiceSubsystem->D20(1);
// ... complex analysis over multiple frames ...
DiceSubsystem->RollCleanup(handle);
```

## Comparison with Industry Patterns

### Game Engine APIs
- **Unity:** Returns values directly, no handle management
- **Godot:** Immediate value extraction pattern
- **UE Native:** USTRUCT returns are standard pattern

### Database APIs  
- **Most ORMs:** Return result objects, automatic cleanup
- **Modern APIs:** RAII/smart pointer patterns eliminate manual cleanup

### Our Current Pattern
- **Similar to:** Raw C APIs (malloc/free style)
- **Problem:** Requires manual memory management in high-level language

## Success Metrics

### Developer Experience
- **Before:** 4 function calls + manual cleanup = 5 steps
- **After:** 1 function call = 1 step
- **Improvement:** 80% reduction in complexity

### Memory Safety
- **Before:** Memory leaks possible with forgotten cleanup
- **After:** Zero memory leak risk
- **Improvement:** 100% elimination of leak risk

### Blueprint Integration
- **Before:** Handle management not Blueprint-native
- **After:** USTRUCT returns are Blueprint-native
- **Improvement:** Natural UE integration

## Implementation Priority

### High Priority Benefits
1. **Eliminate memory leak risk** - Critical for production games
2. **Simplify Blueprint usage** - Major developer experience improvement  
3. **Follow UE conventions** - Better integration with existing patterns

### Low Risk Implementation
- Non-breaking addition alongside existing API
- Can be implemented incrementally
- Easy to test and validate
- Natural migration path

## Recommendation

**Implement Option B (FRollResult struct)** for the following reasons:

1. **Blueprint Native:** USTRUCTs are first-class Blueprint types
2. **Type Safety:** Compile-time checking of result access
3. **Extensible:** Easy to add new fields (critical hits, modifiers, etc.)
4. **Performance:** Single CGO call instead of multiple
5. **Memory Safe:** Zero manual cleanup required

This approach transforms the dice system from a low-level handle-based API into a high-level, Blueprint-friendly interface that eliminates memory management complexity while providing better integration with UE patterns.

## Next Steps

1. **Create ADR** for automatic cleanup decision
2. **Implement FRollResult struct** and D20Complete function
3. **Add new CGO bindings** for immediate value extraction
4. **Test Blueprint integration** with new pattern
5. **Migrate existing usage** to new automatic cleanup pattern
6. **Deprecate handle-based functions** once migration is complete

This change will make the dice system significantly more user-friendly while eliminating a major source of potential memory leaks and complexity.