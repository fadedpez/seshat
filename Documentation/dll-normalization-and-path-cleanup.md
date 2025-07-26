# DLL Normalization and Path Cleanup - Issue Resolution

## Problem Discovered

Through systematic debugging, we identified that our UE project had **three different DLL loading strategies** and **embedded WSL paths in the compiled DLL** that were corrupting UE's file system during save operations.

## Root Cause Analysis

### 1. **Inconsistent DLL Loading Strategies**
Our three subsystems used different approaches:

**RPGDiceSubsystem** (Correct approach):
```cpp
// Looked in proper UE binary directory (but DLL wasn't there)
FString BinariesDir = FPaths::Combine(FPaths::ProjectDir(), TEXT("Binaries"), FPlatformProcess::GetBinariesSubdirectory());
FString LibraryPath = FPaths::Combine(BinariesDir, TEXT("rpg_toolkit.dll"));
```

**RPGEntitySubsystem** (Legacy approach):
```cpp
// Looked in source directory (DLL was there, but wrong pattern)
FString LibraryPath = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/RPGToolkit/rpg_toolkit.dll"));
```

**RPGEventBusSubsystem** (Legacy approach):
```cpp  
// Also looked in source directory (DLL was there, but wrong pattern)
FString LibraryPath = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/RPGToolkit/rpg_toolkit.dll"));
```

### 2. **Embedded WSL Paths in DLL**
The original Go DLL contained embedded debug symbols with WSL paths:
```
/home/frank/go/pkg/mod/github.com/google/uuid@v1.6.0/hash.go
/home/frank/go/pkg/mod/github.com/google/uuid@v1.6.0/uuid.go
/home/frank/projects/share/seshat/Seshat/Source/ThirdParty/RPGToolkit/core_bindings.go
```

**Impact**: When Windows UE loaded the DLL, these embedded WSL paths contaminated UE's internal file system state, causing "illegal references to private object" crashes during save operations.

### 3. **Inconsistent DLL Deployment**
- **DLL existed**: `Source/ThirdParty/RPGToolkit/rpg_toolkit.dll` (5.3MB with debug symbols)  
- **DLL missing**: `Binaries/Win64/rpg_toolkit.dll` (where UE expects it)

## Solution Implementation

### **Phase 1: Normalize DLL Loading Strategies**

**Standardized all three subsystems** to use the same UE-standard approach:

**Before (Entity & EventBus):**
```cpp
FString BaseDir = FPaths::ProjectDir();
FString LibraryPath = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/RPGToolkit/rpg_toolkit.dll"));
```

**After (All three subsystems):**
```cpp
// Construct the path to our DLL in the proper binary directory
FString BinariesDir = FPaths::Combine(FPaths::ProjectDir(), TEXT("Binaries"), FPlatformProcess::GetBinariesSubdirectory());
FString LibraryPath = FPaths::Combine(BinariesDir, TEXT("rpg_toolkit.dll"));
LibraryPath = FPaths::ConvertRelativePathToFull(LibraryPath);
```

### **Phase 2: Clean DLL Compilation**

**Recompiled Go DLL with aggressive symbol stripping:**

**Original compilation:**
```bash
GOOS=windows GOARCH=amd64 CGO_ENABLED=1 CC=x86_64-w64-mingw32-gcc go build -buildmode=c-shared -o rpg_toolkit.dll
```

**New clean compilation:**
```bash  
GOOS=windows GOARCH=amd64 CGO_ENABLED=1 CC=x86_64-w64-mingw32-gcc go build -buildmode=c-shared -ldflags="-s -w -extldflags=-static" -trimpath -o rpg_toolkit_clean.dll
```

**Flags explanation:**
- `-s`: Strip symbol table and debug information
- `-w`: Strip DWARF debug information  
- `-extldflags=-static`: Static linking to reduce dependencies
- `-trimpath`: Remove file system paths from compiled executable

### **Phase 3: DLL Deployment Standardization**

**Deployed clean DLL to both locations:**
1. **Standard UE location**: `Binaries/Win64/rpg_toolkit.dll` (where all subsystems now look)
2. **Source location**: `Source/ThirdParty/RPGToolkit/rpg_toolkit.dll` (for build consistency)

**Size reduction achieved**: 5.3MB → 2.0MB (62% smaller)

### **Phase 4: Verification**

**Confirmed clean DLL has no embedded WSL paths:**
```bash
strings rpg_toolkit_clean.dll | grep -E "/home|frank" | wc -l
# Result: 0 (no WSL paths found)
```

## Files Modified

### **C++ Subsystem Files:**
- `Source/Seshat/RPGCore/Entity/RPGEntitySubsystem.cpp` - Normalized DLL loading
- `Source/Seshat/RPGCore/Events/RPGEventBusSubsystem.cpp` - Normalized DLL loading  
- `Source/Seshat/RPGDiceSubsystem.cpp` - Already used correct pattern

### **DLL Files:**
- `Binaries/Win64/rpg_toolkit.dll` - New clean DLL (2.0MB)
- `Source/ThirdParty/RPGToolkit/rpg_toolkit.dll` - Replaced with clean version
- `Source/ThirdParty/RPGToolkit/rpg_toolkit_clean.dll` - Clean compilation artifact

## Technical Insights

### **Why This Caused Save Crashes**
1. **Path Contamination**: Embedded WSL paths in DLL leaked into UE's file system state
2. **Mixed Path Resolution**: WSL paths (`/home/frank/...`) mixed with Windows paths (`D:\Projects\...`)
3. **Object Reference Corruption**: Invalid path resolution created "illegal references to private object"
4. **Save Operation Failure**: UE couldn't resolve object references during save, causing crashes

### **Cross-Platform Development Lessons**
1. **Always strip debug symbols** when compiling libraries for production
2. **Use `-trimpath`** to prevent development environment paths from being embedded
3. **Standardize library deployment** - all subsystems should use same loading pattern
4. **Test with minimal DLL** - stripped versions help isolate path-related issues

### **UE Integration Best Practices**
1. **Use `Binaries/[Platform]/` directory** for third-party DLLs
2. **Consistent `FPlatformProcess::GetBinariesSubdirectory()`** usage
3. **Avoid hardcoded paths** in DLL loading code
4. **RuntimeDependencies.Add()** in Build.cs for automatic deployment

## Expected Outcome

With normalized DLL loading and clean symbol-stripped DLL:
1. **No more WSL path contamination** in UE's file system
2. **Consistent DLL loading** across all three subsystems  
3. **Proper UE binary deployment** pattern
4. **Resolved save operation crashes** due to clean object references

## Next Steps

1. **Test save operations** with clean DLL
2. **Verify all three subsystems** load DLL successfully
3. **Confirm no path-related crashes** during content save
4. **Monitor UE logs** for any remaining path issues

This normalization addresses the root cause of cross-platform path contamination that was corrupting UE's save operations.