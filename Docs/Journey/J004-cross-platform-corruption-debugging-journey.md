# Cross-Platform Corruption Debugging Journey

## Overview
**Epic debugging session** that revealed multiple layers of path corruption from cross-platform development (WSL ↔ Windows) and corrupted UE engine installation. What started as a "simple save crash" turned into a comprehensive lesson in systematic debugging vs. trial-and-error approaches.

## The Problem Statement
- **Save crashes** with "illegal references to private object" when toolkit blueprint exists in world
- **Editor instability** during normal operations
- **Mysterious path corruption** showing `../../../../../Projects/share/seshat/Seshat/` instead of proper Windows paths

## Root Cause Analysis

### **Primary Issue #1: WSL Path Contamination in Go DLL**
**Discovery**: Our Go-compiled DLL contained embedded WSL debug symbols with paths like `/home/frank/projects/...` that contaminated Windows UE's file system resolution.

**Evidence**:
```bash
strings rpg_toolkit.dll | grep -E "/home|frank"
# Found embedded WSL paths in debug symbols
```

**Solution**: Recompile DLL with aggressive symbol stripping:
```bash
GOOS=windows GOARCH=amd64 CGO_ENABLED=1 CC=x86_64-w64-mingw32-gcc go build -buildmode=c-shared -ldflags="-s -w -extldflags=-static" -trimpath -o rpg_toolkit.dll
```

### **Primary Issue #2: Inconsistent DLL Loading Strategies**
**Discovery**: Three subsystems used different DLL loading patterns, causing instability.

**Before** (inconsistent):
- RPGDiceSubsystem: Used proper `Binaries/Win64/` pattern
- RPGEntitySubsystem: Used legacy `Source/ThirdParty/` pattern  
- RPGEventBusSubsystem: Used legacy `Source/ThirdParty/` pattern

**After** (normalized):
```cpp
// Standard pattern for ALL subsystems
FString BinariesDir = FPaths::Combine(FPaths::ProjectDir(), TEXT("Binaries"), FPlatformProcess::GetBinariesSubdirectory());
FString LibraryPath = FPaths::Combine(BinariesDir, TEXT("rpg_toolkit.dll"));
```

### **Primary Issue #3: Persistent Cache Corruption**
**Discovery**: Corrupted symlink paths were embedded in **multiple cache layers** that normal cleanup doesn't touch.

**Affected Locations**:
- Project cache: `Intermediate/`, `Saved/`, `DerivedDataCache/`
- Global UE cache: `%APPDATA%/Local/UnrealEngine/5.6/DerivedDataCache/`
- Zen storage: `%APPDATA%/Local/UnrealEngine/Common/Zen/Data/`
- User settings: `EditorPerProjectUserSettings.ini` with paths like `../../../../../Projects/share/seshat/Seshat/Content/`

### **Primary Issue #4: Corrupted UE Engine Installation**
**Discovery**: Epic Launcher's "verify installation" **completely failed** to detect missing core engine files.

**Evidence**:
```bash
LogStreaming: Warning: Failed to read file '../../../Engine/Content/Slate/Icons/doc_16x.png' error.
```

**Reality Check**:
```bash
ls "/mnt/d/Games/UE_5.6/Engine/Content/Slate/Icons/doc_16x.png"
# FILE MISSING - Engine installation corrupted
```

**Epic Launcher said**: ✅ Installation healthy  
**Actual reality**: ❌ Core engine files missing

## Debugging Methodology Evolution

### **Phase 1: Trial-and-Error (❌ Ineffective)**
- "Maybe it's the DLL path?" → Try moving DLL
- "Maybe it's screenshot directory?" → Change one setting
- "Maybe it's PIE?" → Toggle random options
- **Result**: Wasted time, no progress, frustrating

### **Phase 2: Systematic Investigation (✅ Effective)**
- **Comprehensive file audit**: Read ALL config files for patterns
- **Evidence gathering**: Use tools like `strings` to examine binaries
- **Root cause analysis**: Look for fundamental issues vs. symptoms
- **Multi-vector approach**: Address all subsystems simultaneously
- **Community research**: Leverage UE community knowledge for version-specific issues

## Key Technical Learnings

### **Cross-Platform Development Patterns**

#### **🛡️ DLL Compilation for UE Integration**
```bash
# ❌ NEVER (embeds development paths)
go build -buildmode=c-shared -o rpg_toolkit.dll

# ✅ ALWAYS (clean, no embedded paths)
go build -buildmode=c-shared -ldflags="-s -w -extldflags=-static" -trimpath -o rpg_toolkit.dll
```

**Critical flags**:
- `-s`: Strip symbol table and debug information
- `-w`: Strip DWARF debug information  
- `-extldflags=-static`: Static linking
- `-trimpath`: Remove file system paths from executable

#### **🏗️ UE Subsystem DLL Loading Standard**
```cpp
// ✅ Standard pattern for ALL subsystems
void LoadToolkitDLL()
{
    FString BinariesDir = FPaths::Combine(FPaths::ProjectDir(), TEXT("Binaries"), FPlatformProcess::GetBinariesSubdirectory());
    FString LibraryPath = FPaths::Combine(BinariesDir, TEXT("rpg_toolkit.dll"));
    LibraryPath = FPaths::ConvertRelativePathToFull(LibraryPath);

    if (!FPaths::FileExists(LibraryPath))
    {
        UE_LOG(LogTemp, Warning, TEXT("DLL not found at: %s"), *LibraryPath);
        return;
    }

    ToolkitDLLHandle = FPlatformProcess::GetDllHandle(*LibraryPath);
}
```

#### **🔧 Complete Cache Cleanup Pattern**
**When experiencing cross-platform corruption**:

1. **Project cache cleanup**:
```bash
rm -rf Intermediate/ Saved/ DerivedDataCache/ .vs/
rm -f *.sln
```

2. **Global UE cache cleanup**:
```bash
# Windows paths
%APPDATA%\Local\UnrealEngine\5.6\DerivedDataCache\
%APPDATA%\Local\UnrealEngine\5.6\Intermediate\
%APPDATA%\Local\UnrealEngine\Common\DerivedDataCache\
%APPDATA%\Local\UnrealEngine\Common\Zen\Data\cache\
```

3. **Regenerate everything**:
- Right-click .uproject → Generate Visual Studio project files
- Clean + Rebuild in Visual Studio
- Launch UE from Windows (not WSL)

### **🚨 Engine Corruption Detection**
**Epic Launcher's "verify" is unreliable**. Manual verification:

```bash
# Check for missing core files
ls "ENGINE_INSTALL/Engine/Content/Slate/Icons/doc_16x.png"
ls "ENGINE_INSTALL/Engine/Content/Slate/Common/ButtonHoverHint.png"
```

**Symptoms of corrupted engine**:
- `LogStreaming: Warning: Failed to read file '../../../Engine/Content/...'`
- `LogSlate: Could not load file for Slate resource`
- UI elements missing or broken in editor

### **💡 Cross-Platform Best Practices**

1. **Always use relative paths in committed configs**:
```ini
# ✅ Good
GameScreenshotSaveDirectory=(Path="Saved/Screenshots")

# ❌ Bad (breaks team collaboration)  
GameScreenshotSaveDirectory=(Path="D:/Projects/share/seshat/Seshat/Saved/Screenshots")
```

2. **Never compile from WSL for Windows targets**:
- WSL paths contaminate Windows binaries
- Use proper cross-compilation flags instead

3. **Git configuration for UE projects**:
```gitignore
# Build artifacts (ignored)
Binaries/
Intermediate/
DerivedDataCache/
Saved/
.vs/

# Exception: Keep clean DLL
!Binaries/Win64/rpg_toolkit.dll
```

## Resolution Strategy

### **Immediate Fix Applied**
1. ✅ **Normalized DLL loading** across all three subsystems
2. ✅ **Recompiled clean DLL** with symbol stripping (5.3MB → 2.0MB)
3. ✅ **Complete cache cleanup** (project + global UE cache)
4. ✅ **Identified corrupted engine** requiring reinstall

### **Long-term Prevention**
1. **Systematic debugging protocol** documented
2. **Cross-platform compilation patterns** established
3. **Engine corruption detection** methods recorded
4. **Complete cache cleanup procedures** documented

## Critical Insights

### **When to Switch from Trial-and-Error to Systematic Debugging**
- **Surface attempts**: 2-3 tries maximum
- **If still broken**: Stop changing, start gathering comprehensive data
- **Read everything**: Config files, logs, build artifacts, community knowledge
- **Evidence-based hypotheses**: Multiple causes based on data, not guessing

### **UE Community Research Pattern**
- Always search for version-specific solutions (UE 5.6.0)
- Check forums, Stack Overflow, Reddit r/unrealengine
- Different UE versions have different implementations
- Example searches:
  - "UE 5.6.0 DirectoryWatcher file cache permission error"
  - "Unreal Engine 5.6 cross platform DLL loading"
  - "UE5.6 save crash illegal references"

### **Corruption vs. Configuration Issues**
- **Configuration issues**: Can be fixed by changing settings
- **Corruption issues**: Require complete cleanup/reinstall
- **Mixed issues**: Address both systematically (our case)

### **Epic Launcher Reliability**
- **"Verify installation" is unreliable** - often misses missing core files
- **Manual verification required** for corruption detection
- **Reinstalling 9GB engine** > hours of debugging corruption
- **"Twice on Sunday"** - absolutely worth it for clean slate

## Future Protocol

### **When Experiencing UE Issues**:

1. **Quick surface checks** (5 minutes max)
2. **Systematic evidence gathering**:
   - Read relevant config files
   - Check logs for error patterns  
   - Search UE community for version-specific issues
3. **Validate project vs. engine**:
   - Is project corrupted? → Clean project cache
   - Is engine corrupted? → Manual file verification
   - Both corrupted? → Clean project cache + reinstall engine
4. **Choose your battle**:
   - **Simple config issue**: Fix systematically
   - **Deep corruption**: Nuke and reinstall (faster than debugging)

### **The 9GB vs. 9 Hours Decision**
> "I'll take reinstalling a 9 gig engine on high speed over what we just went through with this any day lol, twice on sunday"

**Wisdom gained**: Sometimes the nuclear option (reinstall) is more efficient than surgical debugging, especially when corruption is multi-layered.

## Success Metrics

### **Technical Achievement**
- ✅ **Save operations work** without crashes
- ✅ **Cross-platform path contamination eliminated**
- ✅ **DLL loading standardized** across all subsystems
- ✅ **Systematic debugging methodology** established

### **Process Achievement**  
- ✅ **Evolved from trial-and-error to systematic approach**
- ✅ **Documented reusable patterns** for future issues
- ✅ **Established engine corruption detection** methods
- ✅ **Created complete cache cleanup procedures**

### **Wisdom Achievement**
- ✅ **Know when to debug vs. when to reinstall**
- ✅ **Don't trust Epic Launcher's verify function**
- ✅ **Cross-platform development requires extra care with paths**
- ✅ **UE community knowledge is invaluable for version-specific issues**

## Conclusion

This debugging journey transformed from a frustrating path corruption chase into a comprehensive learning experience about:
- **Cross-platform development pitfalls**
- **Systematic vs. trial-and-error debugging**
- **UE cache architecture complexity**
- **Engine corruption detection and resolution**

**Key Takeaway**: Sometimes the most efficient solution is the simplest one - when facing multi-layered corruption, reinstalling the problematic component (9GB download) can be faster and more reliable than hours of surgical debugging.

**The journey wasn't on a soft grass path** - but we came out with robust patterns, proven methodologies, and the wisdom to choose the right approach for future issues.