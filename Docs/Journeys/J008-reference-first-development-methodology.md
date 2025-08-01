# J008 - Reference-First Development Methodology

**Date:** 2025-01-29  
**Catalyst:** Repeated implementation failures due to insufficient planning  
**Principle:** "Measure twice, cut once"

## The Problem Pattern

**Symptom:** Constant implementation rework due to incorrect assumptions
- "ok it's ready. wait no it doesn't compile. oh i forgot this. also this. forgot that too. also this isn't right."
- Building the same code 7, 8, 9 times because of guessed function signatures
- Planning documents that are too abstract to prevent implementation errors

**Root Cause:** Planning documents lack comprehensive reference material needed for correct implementation

## The Solution: Reference-First Development

### Core Principle
**Planning documents must BE comprehensive reference documents**

### What Every Planning Document Must Contain:

1. **Complete API Reference**
   - Exact function signatures (not assumptions)
   - Real parameter types and return values
   - Actual usage examples from source code

2. **Existing Pattern Analysis**
   - How we've solved similar problems before
   - Copy/paste-ready code structures from our codebase
   - Integration patterns that worked

3. **Implementation Templates**
   - Detailed code skeletons with correct signatures
   - Error handling patterns we use
   - Memory management approaches

4. **Integration Requirements**
   - What other systems need to align with this
   - Dependencies and their exact versions
   - Cross-system compatibility notes

### Planning Document Quality Standard

**Test:** Could you hand this planning doc to someone else and they'd build it correctly the first time?

**Requirements:**
- No assumptions or guesses needed during implementation
- All reference material embedded directly in the plan
- Specific enough to eliminate all implementation rework
- Single source of truth with every signature spelled out

### The Workflow Change

**Before (Broken Pattern):**
1. Write high-level planning doc
2. Start implementing and guess at details
3. Hit compilation errors
4. Research actual APIs
5. Fix implementation
6. Repeat steps 3-5 multiple times

**After (Reference-First Pattern):**
1. Research ALL reference material first
2. Document exact APIs, signatures, patterns in planning doc
3. Create comprehensive implementation blueprint
4. Follow the blueprint exactly - no improvisation
5. Build correctly the first time

### Memory/Rule for All Future Work

**Before writing ANY code that extends existing systems:**

1. **Gather ALL reference material first**
   - Check existing codebase patterns
   - Read actual API documentation/source
   - Review our planning documents
   - Look at similar implementations we've already done

2. **Build comprehensive planning document**
   - Include every function signature
   - Document every pattern we'll follow
   - Embed all reference material needed

3. **Build it right the first time**
   - No assumptions during implementation
   - Follow the planning blueprint exactly
   - If something's not in the plan, stop and research it properly

## Application to Current Work

This methodology applies to:
- **Go Toolkit Integration** - Get exact API signatures before writing bindings
- **UE Subsystem Development** - Document our Swiss Army Knife patterns
- **DLL Integration** - Capture function pointer setups and memory management
- **Cross-System Integration** - Map out all the connection points

## Success Metrics

- **First-time compilation success** - Code compiles on first attempt
- **No implementation rework** - Planning phase catches all requirements
- **Reusable patterns** - Planning docs become reference for future work
- **Faster overall development** - Less total time despite more planning time

## The Metaphor: "Measure Twice, Cut Once"

**Measuring Phase:** Comprehensive planning with all reference material  
**Cutting Phase:** Implementation that follows the blueprint exactly

**Investment:** More time in planning phase  
**Payoff:** Dramatically less time in implementation and debugging phases

## Future Journey Integration

This methodology should be applied to every future branch and feature. Planning documents become the authoritative reference for how we build systems in this codebase.

**Next Steps:** Apply this to any remaining work on Swiss Army Knife implementation and establish as standard practice.