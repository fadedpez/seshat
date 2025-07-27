# Seshat - Tactical RPG with Go Toolkit Integration

**A tactical RPG built with Unreal Engine 5.6.0 and Go-based rpg-toolkit integration**

[![UE Version](https://img.shields.io/badge/Unreal%20Engine-5.6.0-blue)](https://unrealengine.com/)
[![Go Version](https://img.shields.io/badge/Go-1.21+-00ADD8)](https://golang.org/)
[![Integration Status](https://img.shields.io/badge/Integration-Working%20POC-green)](#integration-status)

---

## 🎯 **Project Overview**

Seshat demonstrates **successful integration** between Unreal Engine and Go-based game logic through a C DLL bridge. The project showcases:

- **Cross-platform development** (WSL Linux → Windows UE Runtime)
- **Real-time toolkit integration** (Go rpg-toolkit → UE subsystems)
- **Event-driven architecture** (UE event bus with Go backend)
- **Blueprint accessibility** (Toolkit functions callable from UE Blueprints)

## 🏗️ **Architecture**

```
UE Blueprint System
    ↓ (Blueprint Events)
UE Game Instance Subsystems
    ↓ (C DLL Function Calls)  
Go rpg-toolkit Bindings (CGO)
    ↓ (Native Go Calls)
github.com/KirkDiggler/rpg-toolkit
```

**Key Components:**
- **`URPGDiceSubsystem`** - GameInstanceSubsystem for dice rolling
- **`URPGEventBusSubsystem`** - Event publishing and subscription
- **`dice_bindings.go`** - CGO bridge to rpg-toolkit
- **`rpg_toolkit.dll`** - Cross-compiled Windows DLL

## 🚀 **Quick Start**

### **Prerequisites**
- **Unreal Engine 5.6.0**
- **Visual Studio 2022** (with C++ game development workload)
- **Go 1.21+** (for DLL development)
- **Git** (configured with SSH for GitHub)

### **Setup**
```bash
# 1. Clone the repository
git clone git@github.com:yourusername/seshat.git
cd seshat

# 2. Open in UE Editor
# Double-click Seshat.uproject (will prompt to rebuild modules)

# 3. Rebuild in Visual Studio  
# Build → Rebuild Solution

# 4. Test integration
# PIE → Walk into test cube → See dice roll results in output log
```

## 🔧 **Development Workflow**

### **Modifying Go Toolkit Integration**
```bash
# 1. Edit bindings
cd Source/ThirdParty/RPGToolkit
# Edit dice_bindings.go or add new bindings

# 2. Recompile DLL (CRITICAL: Use clean compilation flags)
GOOS=windows GOARCH=amd64 CGO_ENABLED=1 CC=x86_64-w64-mingw32-gcc \
go build -buildmode=c-shared \
-ldflags="-s -w -extldflags=-static" \
-trimpath \
-o rpg_toolkit.dll

# 3. Deploy to UE
cp rpg_toolkit.dll ../../Binaries/Win64/

# 4. Rebuild UE project
# Visual Studio → Build → Rebuild Solution
```

### **Verifying Clean Compilation**
```bash
# Ensure no WSL paths embedded (should return 0)
strings Binaries/Win64/rpg_toolkit.dll | grep -E "/home|frank" | wc -l
```

## 🎮 **Integration Status**

### ✅ **Working Components**
- [x] **DLL Loading** - rpg-toolkit.dll loads successfully in UE
- [x] **Function Resolution** - All exported functions resolve correctly  
- [x] **Dice Rolling** - `CreateDiceRoller` + `RollDie` integration complete
- [x] **Event Publishing** - Dice roll events published through UE event bus
- [x] **Blueprint Access** - Subsystems accessible via Blueprint nodes
- [x] **Cross-Platform Build** - Clean WSL development → Windows runtime

### 🚧 **Known Issues**
- **Mouse Input:** OnClicked events blocked by viewport mouse capture settings
  - **Workaround:** Use OnHit/collision events or configure mouse capture
  - **Fix Location:** `Config/DefaultInput.ini` - `DefaultViewportMouseCaptureMode`

### 🔮 **Planned Features**
- [ ] **Spatial Integration** - Room generation and positioning
- [ ] **Environment System** - Procedural content generation  
- [ ] **Entity Management** - Character and object lifecycle
- [ ] **Combat System** - Turn-based tactical combat
- [ ] **Character Creation** - D&D 5e character building

## 📁 **Project Structure**

```
Seshat/
├── Content/                    # UE assets and maps
├── Source/
│   ├── Seshat/                # Main UE C++ module
│   │   ├── RPGDiceSubsystem.*     # Dice rolling subsystem
│   │   ├── RPGCore/Events/        # Event bus system  
│   │   └── Seshat.h               # Module definitions
│   └── ThirdParty/RPGToolkit/ # Go toolkit integration
│       ├── dice_bindings.go       # CGO exports
│       ├── go.mod                 # Go dependencies
│       └── rpg_toolkit.dll        # Compiled DLL
├── Binaries/Win64/            # Runtime binaries
├── Config/                    # UE project configuration
├── INTEGRATION_JOURNEY.md     # Detailed technical documentation
└── README.md                  # This file
```

## 🔍 **Debugging & Troubleshooting**

### **Common Issues**

**1. DLL Loading Failures**
```cpp
// Check UE Output Log for:
UE_LOG: RPGDiceSubsystem: DLL not found at path: [path]
UE_LOG: RPGDiceSubsystem: Failed to load DLL
```
**Solution:** Verify `rpg_toolkit.dll` exists in `Binaries/Win64/`

**2. Function Resolution Failures** 
```cpp
// Check UE Output Log for:
UE_LOG: RPGDiceSubsystem: Failed to load some DLL functions
UE_LOG:   CreateDiceRoller: FAILED
```
**Solution:** Recompile DLL with proper CGO export tags

**3. UE Save/PIE Crashes**
**Symptoms:** "Illegal references to private object" errors
**Cause:** WSL paths embedded in DLL
**Solution:** Recompile with `-trimpath` flag

### **Useful Log Locations**
- **UE Output Log:** Window → Developer Tools → Output Log
- **UE Editor Log:** `Saved/Logs/Seshat.log`
- **Visual Studio Output:** Build → Output Window

## 🤝 **Contributing**

### **Development Environment**
- **OS:** WSL2 Ubuntu (development) + Windows 11 (runtime)
- **IDE:** Visual Studio 2022 + VS Code (Go development)
- **Tools:** Go cross-compilation toolchain for Windows

### **Code Style**
- **UE C++:** Follow Unreal Engine coding standards
- **Go:** Follow standard Go conventions (`gofmt`, `golint`)
- **Blueprints:** Use descriptive node names and organize logically

### **Pull Request Process**
1. **Test integration** - Verify DLL compiles and loads
2. **Check path cleanliness** - No embedded development paths
3. **Update documentation** - Reflect changes in relevant docs
4. **Verify cross-platform** - Test on Windows runtime

## 📚 **Documentation**

- **[Integration Journey](INTEGRATION_JOURNEY.md)** - Complete technical implementation details
- **[CLAUDE.md](../../../CLAUDE.md)** - Multi-repository ecosystem overview
- **[Cross-Platform Learnings](~/projects/docs/cross-platform-ue-go-integration-learnings.md)** - High-level insights

## 🛡️ **License**

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 🔗 **Related Projects**

- **[rpg-toolkit](https://github.com/KirkDiggler/rpg-toolkit)** - Core Go game mechanics library
- **[rpg-api](https://github.com/yourusername/rpg-api)** - API server orchestration layer  
- **[rpg-api-protos](https://github.com/yourusername/rpg-api-protos)** - gRPC service definitions

---

**🎲 Built with determination, debugged with patience, documented with care.**