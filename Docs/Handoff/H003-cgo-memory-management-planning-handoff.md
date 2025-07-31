# H003: CGO Memory Management Planning Handoff

**Date:** July 29, 2025  
**Context:** CGO memory management implementation planning and industry research  
**Status:** 🚨 **PLANNING PHASE INCOMPLETE** - 9 critical decisions still needed  
**Next Session Focus:** Resolve all 9 open questions before ANY implementation begins

## Summary

Created comprehensive implementation plan (P006) for CGO memory registry pattern to fix Blueprint crashes when accessing Go toolkit objects. Researched industry standards for handle management and identified 9 critical decisions needed before implementation.

## Key Accomplishments

### 1. **Created ADR A001: CGO Memory Management Architecture**
- **Location:** `/mnt/d/Projects/Seshat/Seshat/Docs/ADR/A001-cgo-memory-management-architecture.md`
- **Committed to branch:** `cgo-memory-management`
- **GitHub Issue:** #11 created with implementation roadmap

### 2. **Created P006: Implementation Planning Document**
- **Location:** `/mnt/d/Projects/Seshat/Seshat/Docs/Planning/P006-cgo-memory-management-implementation-plan.md`
- **Contains:** Complete 3-phase implementation plan with exact code examples
- **Based on:** Actual toolkit API signatures from dice/modifier.go and dice/roller.go

### 3. **Industry Research on CGO Handle Management**
- **Standard:** Go 1.17+ `runtime/cgo.Handle` using `uintptr` (platform-native sizing)
- **Pattern:** Platform adapts handle size (32-bit on 32-bit systems, 64-bit on 64-bit)
- **Best Practice:** Explicit cleanup with `Delete()` calls (matches our cleanup pattern)

## Critical Finding: Root Cause Confirmed

**Problem:** Go garbage collector deallocates `*Roll` objects while C++/UE holds `unsafe.Pointer` references
**Solution:** CGO memory registry pattern with handle-based API (industry standard approach)
**Impact:** Required for all rich RPG object integration (Entity, Room, Spell systems)

## Current State

### What Works
- `RollerRoll(20)` returns `int32` directly - **no crashes**
- All subsystems load and initialize correctly
- Swiss Army Knife integration architecture is solid

### What Crashes
- `D20(1)` → `RollGetValue(handle)` - **consistent crashes due to GC**
- All object-returning functions need the registry pattern

## 9 Critical Decisions Needed (from P006)

### **IMMEDIATE DECISION REQUIRED:**
**1. Handle ID Range and Type Mapping**
- **Industry Standard:** Use `uintptr` (platform-native) with UE mapping layer
- **Recommendation:** Option A - Keep internal mapping (int32 ↔ uintptr_t in UE subsystem)
- **Reasoning:** Follows Go 1.17+ runtime/cgo.Handle pattern

### **IMPLEMENTATION SCOPE DECISIONS:**
**2. CreateRoll vs CreateRollWithRoller Function Gaps**
- Do we expose toolkit constructors that can error, or just use helpers (D4-D100)?

**3. FreeString Memory Management** 
- How do we handle C string cleanup in new registry pattern?

**6. Legacy Function Compatibility**
- Do `CreateDiceRoller()` and `RollDie()` need registry pattern too?

### **QUALITY/SAFETY DECISIONS:**
**4. Error Handling Strategy**
- Logging for handle lifecycle debugging?
- Handle range validation before registry lookup?

**5. Rollback Strategy**
- How to test phases independently?
- Revert strategy if Phase 2 (UE subsystem) fails?

**8. Memory Registry Size Limits**
- Registry size limits for long-running games?

### **VERIFICATION NEEDED:**
**7. Current Handle Usage Patterns**
- Check existing Blueprints for handle dependency

**9. Thread Safety in UE Context**
- Confirm UE subsystem access patterns (single vs multi-threaded)

## 3-Phase Implementation Plan Ready

### Phase 1: CGO Memory Registry Foundation
- Task 1.1: Implement global registry in dice_bindings.go
- Task 1.2: Update helper functions (D4-D100) to use registry
- Task 1.3: Update Roll access functions with handle lookup
- Task 1.4: Add cleanup function

### Phase 2: Update UE Subsystem  
- Task 2.1: Update function signatures in RPGDiceSubsystem.h
- Task 2.2: Update handle management in RPGDiceSubsystem.cpp
- Task 2.3: Add cleanup management

### Phase 3: Validation and Testing
- Task 3.1: Recompile DLL with new functions
- Task 3.2: Blueprint testing workflow
- Task 3.3: Memory lifecycle validation

## Template Pattern Established

This implementation creates the template for all future toolkit integrations:
- `entity_bindings.go` - Character creation object management
- `spatial_bindings.go` - Room generation object management  
- `spell_bindings.go` - Spell effect object management

## Next Session Priority

**🚨 CRITICAL: PLANNING PHASE MUST BE COMPLETED FIRST 🚨**

### **MANDATORY: Resolve ALL 9 Open Questions Before Implementation**

1. **RESOLVE QUESTION #1** - Handle ID mapping decision (recommend Option A based on industry standard)
2. **RESOLVE QUESTION #2** - CreateRoll vs CreateRollWithRoller function scope
3. **RESOLVE QUESTION #3** - FreeString memory management approach
4. **RESOLVE QUESTION #4** - Error handling and logging strategy
5. **RESOLVE QUESTION #5** - Rollback strategy and phase independence testing
6. **RESOLVE QUESTION #6** - Legacy function compatibility requirements
7. **INVESTIGATE QUESTION #7** - Current handle usage patterns in existing code
8. **RESOLVE QUESTION #8** - Memory registry size limits and cleanup policies
9. **VERIFY QUESTION #9** - UE subsystem thread safety patterns

### **ONLY AFTER ALL 9 QUESTIONS RESOLVED:**
10. **BEGIN TASK 1.1** - Implement CGO memory registry foundation
11. **TEST BLUEPRINT WORKFLOW** - Validate `D20(1)` → `RollGetValue(handle)` fixes crashes

## Files Ready for Next Session

- **P006:** Complete implementation plan with exact code examples
- **ADR A001:** Architectural decision documentation  
- **GitHub Issue #11:** Implementation tracking
- **Branch:** `cgo-memory-management` ready for development

## Key Quote

*"This pattern will become the foundation for all rich RPG object integration in the Seshat UE5 toolkit."* - The memory registry isn't just for dice rolling, it's foundational infrastructure for the entire RPG system vision.

---

**Status:** 🚨 **PLANNING INCOMPLETE** - 9 critical decisions must be resolved before any code is written. Industry research confirms our approach aligns with Go team standards, but implementation scope and details require decisions on all open questions first.