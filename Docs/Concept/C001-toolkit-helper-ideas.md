# Toolkit Helper Ideas - Future Evaluation

## Purpose

This document captures potential helper functions, orchestration patterns, and convenience APIs that could be built on top of the raw toolkit exposure. These are editorial observations about what might be useful, but are NOT implemented during the initial integration phase.

**Rule**: Expose raw toolkit first, evaluate helper ideas later.

## Dice Package Helper Ideas

### Idea 001: Advantage/Disadvantage Wrapper
**Current Status**: Removed from URPGDiceSubsystem (was wrong implementation)  
**Raw Toolkit Foundation**: `Roller.Roll()` + comparison logic  
**Potential Helper**:
```cpp
// Built on top of raw Roller.Roll() calls
int32 RollWithAdvantage(int32 Sides) {
    int32 roll1 = RollerRoll(Sides);
    int32 roll2 = RollerRoll(Sides);
    return FMath::Max(roll1, roll2);
}
```
**Editorial Opinion**: Very common D&D pattern, could be useful for D&D-specific applications
**Evaluation Criteria**: How often is this pattern used vs direct toolkit calls?

### Idea 002: Entity-Aware Rolling
**Current Status**: Removed from URPGDiceSubsystem (was wrong implementation)  
**Raw Toolkit Foundation**: `Roller.Roll()` + entity data + potential modifiers  
**Potential Helper**:
```cpp
// Built on top of raw toolkit + entity system integration
int32 RollForEntity(int32 Sides, TScriptInterface<IRPGEntityInterface> Entity) {
    int32 baseRoll = RollerRoll(Sides);
    // Future: Add entity modifiers, proficiency, etc.
    return ApplyEntityModifiers(baseRoll, Entity);
}
```
**Editorial Opinion**: Bridges raw dice with game entity system, could be valuable orchestration layer
**Evaluation Criteria**: Do we need entity-specific modifiers? How complex is the modifier logic?

### Idea 003: Roll Result Caching/History
**Current Status**: Not implemented  
**Raw Toolkit Foundation**: `Roll.GetDescription()` + custom storage  
**Potential Helper**:
```cpp
// Built on top of raw Roll struct
class URollHistoryManager {
    TArray<FRollResult> RollHistory;
    void RecordRoll(int32 RollHandle, FString Context);
    TArray<FRollResult> GetRecentRolls(int32 Count);
};
```
**Editorial Opinion**: Useful for combat logs, roll verification, debugging
**Evaluation Criteria**: How important is roll history vs just using Roll.GetDescription()?

### Idea 004: Dice Expression Parser
**Current Status**: Not implemented  
**Raw Toolkit Foundation**: Multiple `Roll` structs + mathematical operations  
**Potential Helper**:
```cpp
// Built on top of raw D4(), D6(), etc. functions
int32 ParseAndRoll(const FString& Expression); // "2d6+1d4+3"
```
**Editorial Opinion**: Very convenient for complex roll expressions, common RPG pattern
**Evaluation Criteria**: How often do we need complex expressions vs simple rolls?

## Core Package Helper Ideas

### Idea 005: Entity Registry/Manager
**Current Status**: Removed from URPGEntitySubsystem (was wrong implementation)  
**Raw Toolkit Foundation**: `Entity` interface + validation functions  
**Potential Helper**:
```cpp
// Built on top of raw entity validation
class UEntityRegistry {
    TMap<FString, TScriptInterface<IRPGEntityInterface>> Entities;
    bool RegisterEntity(TScriptInterface<IRPGEntityInterface> Entity);
    void UnregisterEntity(const FString& ID);
};
```
**Editorial Opinion**: Useful for entity lifecycle management, but not part of core toolkit
**Evaluation Criteria**: Do we need centralized entity management vs distributed entity storage?

### Idea 006: EntityError to UE Error Conversion
**Current Status**: Not implemented  
**Raw Toolkit Foundation**: `EntityError` struct + error constants  
**Potential Helper**:
```cpp
// Built on top of raw EntityError exposure
FString ConvertEntityErrorToReadableMessage(const FEntityError& Error);
void ShowEntityErrorToPlayer(const FEntityError& Error);
```
**Editorial Opinion**: Bridges toolkit errors with UE UI systems
**Evaluation Criteria**: How much error presentation logic do we need vs raw error access?

## Future Integration Helper Ideas

### Idea 007: Event Bus Integration
**Current Status**: Exists but not connected to dice/core yet  
**Raw Toolkit Foundation**: Raw dice/core functions + existing event bus  
**Potential Helper**:
```cpp
// Built on top of raw toolkit + event system
void PublishDiceRollEvent(int32 Result, const FString& Context);
void PublishEntityValidationEvent(bool IsValid, const FString& EntityID);
```
**Editorial Opinion**: Natural bridge between toolkit operations and game event system
**Evaluation Criteria**: Which toolkit operations should trigger events vs silent operations?

### Idea 008: Blueprint Convenience Wrappers
**Current Status**: Not implemented  
**Raw Toolkit Foundation**: All raw toolkit functions  
**Potential Helper**:
```cpp
// Built on top of raw toolkit functions
UFUNCTION(BlueprintCallable, Category = "RPG Helpers")
int32 QuickD20Roll(); // Just calls D20(1).GetValue()

UFUNCTION(BlueprintCallable, Category = "RPG Helpers")  
bool IsValidEntityID(const FString& ID); // Just calls ValidateEntityID()
```
**Editorial Opinion**: Makes Blueprint usage more convenient for simple cases
**Evaluation Criteria**: Blueprint complexity vs exposing raw toolkit functions directly?

## Spatial Package Helper Ideas (Future)

### Idea 009: Tactical Movement Helpers
**Current Status**: Spatial package not yet integrated  
**Raw Toolkit Foundation**: Future spatial toolkit functions  
**Potential Helper**:
```cpp
// Built on top of raw spatial functions
bool CanEntityMoveTo(const FString& EntityID, FVector NewPosition);
TArray<FVector> GetValidMovePositions(const FString& EntityID, int32 MoveDistance);
```
**Editorial Opinion**: Common tactical RPG patterns, very game-specific
**Evaluation Criteria**: How much game-specific logic vs raw spatial queries?

### Idea 010: Line of Sight Helpers
**Current Status**: Spatial package not yet integrated  
**Raw Toolkit Foundation**: Future spatial toolkit functions  
**Potential Helper**:
```cpp
// Built on top of raw spatial functions
bool HasLineOfSight(const FString& EntityID1, const FString& EntityID2);
TArray<FString> GetVisibleEntities(const FString& EntityID);
```
**Editorial Opinion**: Essential for tactical combat, but could be game-specific
**Evaluation Criteria**: How much of this is spatial math vs game rules?

## Evaluation Framework

### Helper Value Assessment
For each idea, consider:
1. **Frequency**: How often would this pattern be used?
2. **Complexity**: How complex is building this on raw toolkit vs direct toolkit usage?
3. **Game Specificity**: Is this D&D-specific or generally useful?
4. **Performance**: Does the helper add significant overhead?
5. **Maintenance**: How much additional complexity does this helper add?

### Implementation Priority
1. **Phase 1**: Raw toolkit exposure complete and tested
2. **Phase 2**: Identify actual usage patterns from Phase 1
3. **Phase 3**: Evaluate top 3-5 most valuable helpers based on real usage
4. **Phase 4**: Implement selected helpers as optional orchestration layer

### Decision Criteria
**Implement Helper If**:
- Used frequently (>80% of use cases)
- Significantly reduces boilerplate code
- Provides clear performance benefit
- Reduces error-prone patterns

**Skip Helper If**:
- Used infrequently (<20% of use cases)
- Adds complexity without clear benefit
- Too game-specific for general toolkit
- Raw toolkit usage is already simple

## Notes for Future Evaluation

- All helpers must be built ON TOP OF raw toolkit, never replacing it
- Raw toolkit functions must remain accessible even with helpers
- Helpers should be optional - raw toolkit should work standalone
- Document which raw toolkit functions each helper uses
- Measure actual usage patterns before building helpers
- Consider Blueprint vs C++ usage patterns separately

### Idea 011: Multiple Dice Rolling  
**Current Status**: Implemented as TArray<int32> RollMultiple() - wrong pattern  
**Raw Toolkit Foundation**: `Roller.RollN()` function  
**Potential Helper**:
```cpp
// Built on top of raw RollerRollN() call
TArray<int32> RollMultiple(int32 Count, int32 Sides) {
    TArray<int32> Results;
    Results.SetNum(Count);
    int32 ReturnedCount = RollerRollN(DiceRollerPtr, Count, Sides, Results.GetData());
    return Results;
}
```
**Editorial Opinion**: Convenient for Blueprint usage, maps directly to toolkit RollN
**Evaluation Criteria**: How often are multiple dice rolls needed vs single rolls?

## Status Tracking

- **Ideas Captured**: 11
- **Raw Toolkit Exposure**: In Progress  
- **Functions Removed from URPGDiceSubsystem**: RollWithAdvantage, RollWithDisadvantage, RollForEntity, RollWithAdvantageForEntity
- **Usage Pattern Collection**: Not Started
- **Helper Evaluation**: Not Started
- **Helper Implementation**: Not Started