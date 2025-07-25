# Seshat Development Ideas & Optimizations

## Toolkit Update Pipeline Automation

### Current Workflow Issues
- Every toolkit update requires rebuilding Go → C DLL
- Every DLL update requires rebuilding UE solution in VS  
- Manual process creates friction for rapid iteration

### Potential Solutions to Explore

1. **Automated Build Pipeline**
   - Script that rebuilds Go DLL when toolkit changes
   - Automatically triggers UE build after DLL update
   - Single command for "update everything"

2. **Hot Reload Investigation**
   - Research if UE can hot-reload DLLs during development
   - Would eliminate need for full UE rebuilds during iteration
   - Faster development cycle

3. **Development vs Production Workflows**
   - Different build processes for dev iteration vs shipping
   - Maybe direct Go integration for dev, DLL for production?
   - Balance between speed and deployment simplicity

4. **CI/Build Integration**
   - Automated toolkit→UE builds in CI
   - Version management between toolkit updates and UE builds
   - Ensure compatibility across updates

### Why This Matters
- Toolkit is actively developed - frequent updates expected
- Manual rebuild friction will slow development velocity  
- Need seamless iteration between Go toolkit changes and UE testing
- The more friction in the pipeline, the less likely we are to iterate quickly

## Future Integration Ideas

(Add more ideas here as they come up)

## Development Notes

(Project-specific development notes and lessons learned)