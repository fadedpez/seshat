# Seshat: RPG-Toolkit Integration Journey

*July 25, 2025*

## Project Overview

Seshat is a tactical RPG game built in Unreal Engine 5 that integrates with the rpg-toolkit to provide sophisticated game mechanics while maintaining UE-native development experience.

## Integration Architecture

### Core Pattern: Go → C DLL → UE Subsystem

```
rpg-toolkit (Go modules) → C shared library → UE C++ Subsystem → Blueprint/Gameplay
```

**Why this approach:**
- **Performance**: No network overhead, direct function calls
- **UE Integration**: Feels like built-in UE functionality
- **Development Speed**: Rapid iteration without API layers
- **Maintainability**: Single codebase, clear boundaries

### File Structure

```
Seshat/
├── Source/
│   ├── Seshat/
│   │   ├── RPGDiceSubsystem.h          # UE Subsystem interface
│   │   ├── RPGDiceSubsystem.cpp        # DLL integration logic
│   │   └── ... (other UE code)
│   └── ThirdParty/
│       └── RPGToolkit/
│           ├── main.go                  # Go main package
│           ├── simple_bindings.go       # C export functions
│           ├── rpg_toolkit.dll          # Compiled Windows DLL
│           ├── rpg_toolkit.h            # Generated C header
│           └── go.mod                   # Go dependencies
└── Documentation/
    ├── integration-journey.md           # This file
    └── development-ideas.md             # Future optimizations
```

## Current Implementation: Dice Rolling

### Go Bindings (simple_bindings.go)
```go
//export RollDice
func RollDice(sides C.int) C.int {
    roller := &dice.CryptoRoller{}
    result, err := roller.Roll(int(sides))
    if err != nil {
        return -1 // error indicator
    }
    return C.int(result)
}
```

### UE Subsystem (URPGDiceSubsystem)
```cpp
UFUNCTION(BlueprintCallable, Category = "RPG Dice")
int32 Roll(int32 Sides) {
    if (!bFunctionsLoaded || !RollDiceFuncPtr) {
        return -1; // Error: toolkit not loaded
    }
    return RollDiceFuncPtr(Sides);
}
```

### Blueprint Integration
- **Subsystem Access**: Get Game Instance → Get Subsystem (RPG Dice Subsystem)
- **Function Calls**: Roll(20), RollWithAdvantage(20), RollMultiple(4, 6)
- **Timer Integration**: Set Timer by Event for periodic rolling
- **Output**: Print String for debugging, return values for game logic

## Technical Challenges Solved

### 1. Windows/WSL Development Environment
**Challenge**: Developing in WSL but UE runs on Windows
**Solution**: 
- Source control in WSL: `/home/frank/projects/share/seshat/`
- UE runtime path: `D:\Projects\share\seshat\`
- Cross-compilation: `GOOS=windows GOARCH=amd64 CGO_ENABLED=1`

### 2. DLL Format Compatibility  
**Challenge**: Linux ELF vs Windows PE32+ format mismatch
**Detection**: `file rpg_toolkit.dll` → "ELF 64-bit" (wrong)
**Solution**: mingw-w64 cross-compiler → "PE32+ executable (DLL)" (correct)

### 3. UE Module Integration
**Challenge**: Avoiding UE project structure corruption
**Solution**: 
- Work within existing Seshat module (no new .uproject entries)
- Use `SESHAT_API` export macro
- Subsystem pattern for global access

## Game Integration Patterns

### Current Usage
```cpp
// In any UE C++ class
URPGDiceSubsystem* DiceSystem = GetGameInstance()->GetSubsystem<URPGDiceSubsystem>();

// Basic rolling
int32 AttackRoll = DiceSystem->Roll(20);
int32 DamageRoll = DiceSystem->Roll(8);

// D&D mechanics
int32 AdvantageAttack = DiceSystem->RollWithAdvantage(20);
int32 DisadvantageAttack = DiceSystem->RollWithDisadvantage(20);

// Multiple dice
TArray<int32> Stats = DiceSystem->RollMultiple(6, 6); // Character stats
```

### Blueprint Patterns
- **Timer-based rolling**: Combat rounds, environmental effects
- **Event-driven rolling**: Player actions, ability checks
- **UI integration**: Character sheets, combat logs
- **Debugging**: Development testing, balance validation

## Future Expansions

### Ready for Integration
1. **Spatial System**: Room generation, positioning, line of sight
2. **Condition System**: Status effects, buffs/debuffs, relationships  
3. **Resource System**: Spell slots, ability uses, resource pools
4. **Environment System**: Procedural dungeons, room themes
5. **Selectables System**: Loot tables, random encounters

### Integration Pattern
For each new system:
1. **Add Go bindings** to appropriate `*_bindings.go` file
2. **Rebuild DLL** with Windows cross-compilation
3. **Extend UE subsystem** with new `UFUNCTION(BlueprintCallable)` methods
4. **Test in Blueprint** before C++ integration
5. **Document usage patterns** for game development

## Development Workflow

### Daily Development
1. **Modify Go bindings** in WSL
2. **Cross-compile**: `GOOS=windows ... go build -buildmode=c-shared`
3. **UE rebuild**: Visual Studio solution build
4. **Test in PIE**: Play in Editor for immediate feedback

### Current Inefficiencies
- Manual rebuild process for each toolkit update
- Full UE rebuild required for DLL changes
- No hot-reload capability during development

### Future Optimizations (see development-ideas.md)
- Automated build pipeline (Go → UE)
- Hot-reload investigation
- Development vs production build workflows

## Success Indicators

✅ **Clean UE Integration**: No project corruption, follows UE conventions
✅ **Cross-Platform Development**: WSL development, Windows runtime
✅ **Blueprint Accessibility**: Full designer/scripter access to toolkit
✅ **Performance**: Direct function calls, no network overhead
✅ **Maintainability**: Clear separation of concerns, extensible pattern
✅ **Debugging**: Proper UE logging, error handling, health checks

## Critical Issue: UE Shutdown Crashes

### Problem Encountered
UE Editor crashed to desktop every time stopping PIE (Play in Editor), immediately after dice rolling functionality was working.

### Root Cause Analysis
DLL cleanup timing conflicts during UE shutdown sequence:
- UE's subsystem cleanup called our `Deinitialize()`
- We called `FPlatformProcess::FreeDllHandle()` to clean up
- UE still had active references or pending operations with the DLL
- Access violation crash when UE tried to access unloaded DLL

### Solution: Industry Standard Practice
**Don't manually unload DLLs** - let Windows handle cleanup on process exit.

```cpp
void URPGDiceSubsystem::Deinitialize()
{
    // Clear function state to prevent calls during shutdown
    bFunctionsLoaded = false;
    RollDiceFuncPtr = nullptr;
    GetVersionFuncPtr = nullptr;
    InitializeFuncPtr = nullptr;
    
    // Don't unload DLL - let Windows handle cleanup on process exit
    if (ToolkitDLLHandle)
    {
        UE_LOG(LogTemp, Warning, TEXT("Leaving DLL loaded for Windows cleanup"));
        // FPlatformProcess::FreeDllHandle(ToolkitDLLHandle); // Commented out
        ToolkitDLLHandle = nullptr; // Clear reference but don't unload
    }
    
    Super::Deinitialize();
}
```

### Why This Works
- **Standard practice**: Most shipping UE games with DLL integration do this
- **Zero performance cost**: DLL stays loaded until process exit anyway  
- **Eliminates timing issues**: No coordination needed between UE and DLL cleanup
- **Windows handles it**: OS automatically cleans up DLLs on process termination
- **Development friendly**: No more crashes when stopping PIE

## Key Learnings

1. **Respect the engine**: Work within UE's patterns, don't force changes
2. **Cross-compilation is critical**: Development platform ≠ runtime platform
3. **Subsystem pattern is powerful**: Global access without singletons
4. **Blueprint integration multiplies value**: Designers can use toolkit directly
5. **Error handling matters**: Graceful degradation when toolkit unavailable
6. **DLL lifecycle management**: Don't manually unload - let OS handle cleanup
7. **Industry patterns exist for a reason**: Common practices solve common problems
8. **Visual Studio rebuild fixes UE crashes**: When UE Editor crashes during PIE, rebuild solution in VS

## Debugging Patterns

### UE Editor Crashes During PIE
**Symptom**: Editor crashes to desktop when stopping Play in Editor
**First debugging step**: Build → Rebuild Solution in Visual Studio
**Why it works**: Resolves stale object files, corrupted intermediate builds, and environment inconsistencies

This integration represents the foundation for a sophisticated RPG game that leverages both UE's visual capabilities and rpg-toolkit's game logic expertise.