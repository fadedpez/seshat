#include "RPGDiceSubsystem.h"
#include "HAL/PlatformProcess.h"
#include "Misc/Paths.h"

void URPGDiceSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
    
    UE_LOG(LogTemp, Warning, TEXT("RPGDiceSubsystem: Initializing"));
    
    // Initialize all function pointers to nullptr
    bFunctionsLoaded = false;
    ToolkitDLLHandle = nullptr;
    DiceRollerPtr = nullptr;
    NextRollHandle = 1;
    
    // Initialize all function pointers
    CreateCryptoRollerFuncPtr = nullptr;
    RollerRollFuncPtr = nullptr;
    RollerRollNFuncPtr = nullptr;
    GetDefaultRollerFuncPtr = nullptr;
    SetDefaultRollerFuncPtr = nullptr;
    
    CreateRollFuncPtr = nullptr;
    CreateRollWithRollerFuncPtr = nullptr;
    RollGetValueFuncPtr = nullptr;
    RollGetDescriptionFuncPtr = nullptr;
    RollHasErrorFuncPtr = nullptr;
    RollGetErrorFuncPtr = nullptr;
    
    D4FuncPtr = nullptr;
    D6FuncPtr = nullptr;
    D8FuncPtr = nullptr;
    D10FuncPtr = nullptr;
    D12FuncPtr = nullptr;
    D20FuncPtr = nullptr;
    D100FuncPtr = nullptr;
    
    CreateDiceRollerFuncPtr = nullptr;
    RollDieFuncPtr = nullptr;
    FreeStringFuncPtr = nullptr;
    
    // Load DLL functions
    LoadDLLFunctions();
    
    if (bFunctionsLoaded)
    {
        UE_LOG(LogTemp, Warning, TEXT("RPGDiceSubsystem: Successfully initialized"));
        
        // Create dice roller instance using the new function
        if (CreateCryptoRollerFuncPtr)
        {
            DiceRollerPtr = CreateCryptoRollerFuncPtr();
            UE_LOG(LogTemp, Warning, TEXT("RPGDiceSubsystem: CryptoRoller created: %s"), DiceRollerPtr ? TEXT("OK") : TEXT("FAILED"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("RPGDiceSubsystem: Failed to initialize - DLL functions not loaded"));
    }
}

void URPGDiceSubsystem::Deinitialize()
{
    UE_LOG(LogTemp, Warning, TEXT("RPGDiceSubsystem: Deinitializing"));
    
    // Clean up roll handles
    CleanupRollHandles();
    
    // Clear all function pointers
    CreateCryptoRollerFuncPtr = nullptr;
    RollerRollFuncPtr = nullptr;
    RollerRollNFuncPtr = nullptr;
    GetDefaultRollerFuncPtr = nullptr;
    SetDefaultRollerFuncPtr = nullptr;
    
    CreateRollFuncPtr = nullptr;
    CreateRollWithRollerFuncPtr = nullptr;
    RollGetValueFuncPtr = nullptr;
    RollGetDescriptionFuncPtr = nullptr;
    RollHasErrorFuncPtr = nullptr;
    RollGetErrorFuncPtr = nullptr;
    
    D4FuncPtr = nullptr;
    D6FuncPtr = nullptr;
    D8FuncPtr = nullptr;
    D10FuncPtr = nullptr;
    D12FuncPtr = nullptr;
    D20FuncPtr = nullptr;
    D100FuncPtr = nullptr;
    
    CreateDiceRollerFuncPtr = nullptr;
    RollDieFuncPtr = nullptr;
    FreeStringFuncPtr = nullptr;
    
    bFunctionsLoaded = false;
    ToolkitDLLHandle = nullptr;
    DiceRollerPtr = nullptr;
    
    Super::Deinitialize();
}

// Roller Interface Functions Implementation
int32 URPGDiceSubsystem::RollerRoll(int32 Size)
{
    if (!IsSafeToCallFunction() || !RollerRollFuncPtr || !DiceRollerPtr)
    {
        return -1;
    }
    
    return RollerRollFuncPtr(DiceRollerPtr, Size);
}

TArray<int32> URPGDiceSubsystem::RollerRollN(int32 Count, int32 Size)
{
    TArray<int32> Results;
    
    if (!IsSafeToCallFunction() || !RollerRollNFuncPtr || !DiceRollerPtr || Count <= 0)
    {
        return Results;
    }
    
    Results.SetNum(Count);
    int32 ReturnedCount = RollerRollNFuncPtr(DiceRollerPtr, Count, Size, Results.GetData());
    
    if (ReturnedCount != Count)
    {
        UE_LOG(LogTemp, Warning, TEXT("RPGDiceSubsystem::RollerRollN: Expected %d results, got %d"), Count, ReturnedCount);
        Results.Empty();
    }
    
    return Results;
}

// Roll Struct Functions Implementation
int32 URPGDiceSubsystem::CreateRoll(int32 Count, int32 Size)
{
    if (!IsSafeToCallFunction() || !CreateRollFuncPtr)
    {
        return -1;
    }
    
    void* RollPtr = CreateRollFuncPtr(Count, Size);
    if (!RollPtr)
    {
        return -1;
    }
    
    return CreateRollHandle(RollPtr);
}

int32 URPGDiceSubsystem::RollGetValue(int32 RollHandle)
{
    if (!IsSafeToCallFunction() || !RollGetValueFuncPtr)
    {
        return -1;
    }
    
    void* RollPtr = GetRollPtr(RollHandle);
    if (!RollPtr)
    {
        return -1;
    }
    
    return RollGetValueFuncPtr(RollPtr);
}

FString URPGDiceSubsystem::RollGetDescription(int32 RollHandle)
{
    if (!IsSafeToCallFunction() || !RollGetDescriptionFuncPtr)
    {
        return TEXT("Error: Function not available");
    }
    
    void* RollPtr = GetRollPtr(RollHandle);
    if (!RollPtr)
    {
        return TEXT("Error: Invalid roll handle");
    }
    
    ANSICHAR* CStr = RollGetDescriptionFuncPtr(RollPtr);
    return ConvertAndFreeString(CStr);
}

bool URPGDiceSubsystem::RollHasError(int32 RollHandle)
{
    if (!IsSafeToCallFunction() || !RollHasErrorFuncPtr)
    {
        return true; // Assume error if can't check
    }
    
    void* RollPtr = GetRollPtr(RollHandle);
    if (!RollPtr)
    {
        return true;
    }
    
    return RollHasErrorFuncPtr(RollPtr) != 0;
}

FString URPGDiceSubsystem::RollGetError(int32 RollHandle)
{
    if (!IsSafeToCallFunction() || !RollGetErrorFuncPtr)
    {
        return TEXT("Error: Function not available");
    }
    
    void* RollPtr = GetRollPtr(RollHandle);
    if (!RollPtr)
    {
        return TEXT("Error: Invalid roll handle");
    }
    
    ANSICHAR* CStr = RollGetErrorFuncPtr(RollPtr);
    return ConvertAndFreeString(CStr);
}

// Helper Functions Implementation
int32 URPGDiceSubsystem::D4(int32 Count)
{
    if (!IsSafeToCallFunction() || !D4FuncPtr)
    {
        return -1;
    }
    
    void* RollPtr = D4FuncPtr(Count);
    if (!RollPtr)
    {
        return -1;
    }
    
    return CreateRollHandle(RollPtr);
}

int32 URPGDiceSubsystem::D6(int32 Count)
{
    if (!IsSafeToCallFunction() || !D6FuncPtr)
    {
        return -1;
    }
    
    void* RollPtr = D6FuncPtr(Count);
    if (!RollPtr)
    {
        return -1;
    }
    
    return CreateRollHandle(RollPtr);
}

int32 URPGDiceSubsystem::D8(int32 Count)
{
    if (!IsSafeToCallFunction() || !D8FuncPtr)
    {
        return -1;
    }
    
    void* RollPtr = D8FuncPtr(Count);
    if (!RollPtr)
    {
        return -1;
    }
    
    return CreateRollHandle(RollPtr);
}

int32 URPGDiceSubsystem::D10(int32 Count)
{
    if (!IsSafeToCallFunction() || !D10FuncPtr)
    {
        return -1;
    }
    
    void* RollPtr = D10FuncPtr(Count);
    if (!RollPtr)
    {
        return -1;
    }
    
    return CreateRollHandle(RollPtr);
}

int32 URPGDiceSubsystem::D12(int32 Count)
{
    if (!IsSafeToCallFunction() || !D12FuncPtr)
    {
        return -1;
    }
    
    void* RollPtr = D12FuncPtr(Count);
    if (!RollPtr)
    {
        return -1;
    }
    
    return CreateRollHandle(RollPtr);
}

int32 URPGDiceSubsystem::D20(int32 Count)
{
    if (!IsSafeToCallFunction() || !D20FuncPtr)
    {
        return -1;
    }
    
    void* RollPtr = D20FuncPtr(Count);
    if (!RollPtr)
    {
        return -1;
    }
    
    return CreateRollHandle(RollPtr);
}

int32 URPGDiceSubsystem::D100(int32 Count)
{
    if (!IsSafeToCallFunction() || !D100FuncPtr)
    {
        return -1;
    }
    
    void* RollPtr = D100FuncPtr(Count);
    if (!RollPtr)
    {
        return -1;
    }
    
    return CreateRollHandle(RollPtr);
}


// Toolkit Status
bool URPGDiceSubsystem::IsToolkitLoaded() const
{
    return bFunctionsLoaded;
}

// Private Implementation
void URPGDiceSubsystem::LoadDLLFunctions()
{
    // Use proper UE binary directory (following established pattern)
    FString BinariesDir = FPaths::Combine(FPaths::ProjectDir(), TEXT("Binaries"), FPlatformProcess::GetBinariesSubdirectory());
    FString LibraryPath = FPaths::Combine(BinariesDir, TEXT("rpg_toolkit.dll"));
    LibraryPath = FPaths::ConvertRelativePathToFull(LibraryPath);

    UE_LOG(LogTemp, Warning, TEXT("RPGDiceSubsystem: Attempting to load DLL from: %s"), *LibraryPath);

    // Check if the DLL exists
    if (!FPaths::FileExists(LibraryPath))
    {
        UE_LOG(LogTemp, Error, TEXT("RPGDiceSubsystem: DLL not found at path: %s"), *LibraryPath);
        return;
    }

    // Load the DLL
    ToolkitDLLHandle = FPlatformProcess::GetDllHandle(*LibraryPath);
    if (!ToolkitDLLHandle)
    {
        UE_LOG(LogTemp, Error, TEXT("RPGDiceSubsystem: Failed to load DLL"));
        return;
    }

    UE_LOG(LogTemp, Warning, TEXT("RPGDiceSubsystem: Successfully loaded DLL"));
    
    // Load Roller interface functions
    CreateCryptoRollerFuncPtr = (CreateCryptoRollerFunc)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("CreateCryptoRoller"));
    RollerRollFuncPtr = (RollerRollFunc)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("RollerRoll"));
    RollerRollNFuncPtr = (RollerRollNFunc)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("RollerRollN"));
    GetDefaultRollerFuncPtr = (GetDefaultRollerFunc)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("GetDefaultRoller"));
    SetDefaultRollerFuncPtr = (SetDefaultRollerFunc)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("SetDefaultRoller"));
    
    // Load Roll struct functions
    CreateRollFuncPtr = (CreateRollFunc)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("CreateRoll"));
    CreateRollWithRollerFuncPtr = (CreateRollWithRollerFunc)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("CreateRollWithRoller"));
    RollGetValueFuncPtr = (RollGetValueFunc)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("RollGetValue"));
    RollGetDescriptionFuncPtr = (RollGetDescriptionFunc)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("RollGetDescription"));
    RollHasErrorFuncPtr = (RollHasErrorFunc)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("RollHasError"));
    RollGetErrorFuncPtr = (RollGetErrorFunc)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("RollGetError"));
    
    // Load helper functions
    D4FuncPtr = (D4Func)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("D4"));
    D6FuncPtr = (D6Func)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("D6"));
    D8FuncPtr = (D8Func)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("D8"));
    D10FuncPtr = (D10Func)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("D10"));
    D12FuncPtr = (D12Func)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("D12"));
    D20FuncPtr = (D20Func)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("D20"));
    D100FuncPtr = (D100Func)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("D100"));
    
    // Load legacy functions
    CreateDiceRollerFuncPtr = (CreateDiceRollerFunc)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("CreateDiceRoller"));
    RollDieFuncPtr = (RollDieFunc)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("RollDie"));
    FreeStringFuncPtr = (FreeStringFunc)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("FreeString"));
    
    // Check if critical functions were loaded
    bool bCriticalFunctionsLoaded = (CreateCryptoRollerFuncPtr != nullptr) && 
                                   (RollerRollFuncPtr != nullptr) && 
                                   (CreateRollFuncPtr != nullptr) &&
                                   (RollGetValueFuncPtr != nullptr) &&
                                   (FreeStringFuncPtr != nullptr);
    
    if (bCriticalFunctionsLoaded)
    {
        bFunctionsLoaded = true;
        UE_LOG(LogTemp, Warning, TEXT("RPGDiceSubsystem: All critical dice functions loaded successfully"));
        
        // Log status of all functions
        UE_LOG(LogTemp, Log, TEXT("=== Dice Function Loading Status ==="));
        UE_LOG(LogTemp, Log, TEXT("Roller Functions:"));
        UE_LOG(LogTemp, Log, TEXT("  CreateCryptoRoller: %s"), CreateCryptoRollerFuncPtr ? TEXT("OK") : TEXT("FAILED"));
        UE_LOG(LogTemp, Log, TEXT("  RollerRoll: %s"), RollerRollFuncPtr ? TEXT("OK") : TEXT("FAILED"));
        UE_LOG(LogTemp, Log, TEXT("  RollerRollN: %s"), RollerRollNFuncPtr ? TEXT("OK") : TEXT("FAILED"));
        
        UE_LOG(LogTemp, Log, TEXT("Roll Functions:"));
        UE_LOG(LogTemp, Log, TEXT("  CreateRoll: %s"), CreateRollFuncPtr ? TEXT("OK") : TEXT("FAILED"));
        UE_LOG(LogTemp, Log, TEXT("  RollGetValue: %s"), RollGetValueFuncPtr ? TEXT("OK") : TEXT("FAILED"));
        UE_LOG(LogTemp, Log, TEXT("  RollGetDescription: %s"), RollGetDescriptionFuncPtr ? TEXT("OK") : TEXT("FAILED"));
        
        UE_LOG(LogTemp, Log, TEXT("Helper Functions:"));
        UE_LOG(LogTemp, Log, TEXT("  D4: %s"), D4FuncPtr ? TEXT("OK") : TEXT("FAILED"));
        UE_LOG(LogTemp, Log, TEXT("  D6: %s"), D6FuncPtr ? TEXT("OK") : TEXT("FAILED"));
        UE_LOG(LogTemp, Log, TEXT("  D8: %s"), D8FuncPtr ? TEXT("OK") : TEXT("FAILED"));
        UE_LOG(LogTemp, Log, TEXT("  D10: %s"), D10FuncPtr ? TEXT("OK") : TEXT("FAILED"));
        UE_LOG(LogTemp, Log, TEXT("  D12: %s"), D12FuncPtr ? TEXT("OK") : TEXT("FAILED"));
        UE_LOG(LogTemp, Log, TEXT("  D20: %s"), D20FuncPtr ? TEXT("OK") : TEXT("FAILED"));
        UE_LOG(LogTemp, Log, TEXT("  D100: %s"), D100FuncPtr ? TEXT("OK") : TEXT("FAILED"));
        UE_LOG(LogTemp, Log, TEXT("================================"));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("RPGDiceSubsystem: Failed to load critical dice functions"));
    }
}

// Handle Management Implementation
int32 URPGDiceSubsystem::CreateRollHandle(void* RollPtr)
{
    if (!RollPtr)
    {
        return -1;
    }
    
    int32 Handle = NextRollHandle++;
    RollHandles.Add(Handle, RollPtr);
    return Handle;
}

void* URPGDiceSubsystem::GetRollPtr(int32 Handle)
{
    if (void** Found = RollHandles.Find(Handle))
    {
        return *Found;
    }
    return nullptr;
}

void URPGDiceSubsystem::ReleaseRollHandle(int32 Handle)
{
    RollHandles.Remove(Handle);
}

FString URPGDiceSubsystem::ConvertAndFreeString(ANSICHAR* CStr) const
{
    if (!CStr)
    {
        return FString();
    }
    
    FString Result = FString(ANSI_TO_TCHAR(CStr));
    
    // Free the C string memory
    if (FreeStringFuncPtr)
    {
        FreeStringFuncPtr(CStr);
    }
    
    return Result;
}

bool URPGDiceSubsystem::IsSafeToCallFunction() const
{
    // Following established pattern for shutdown safety
    return bFunctionsLoaded && ToolkitDLLHandle != nullptr;
}

void URPGDiceSubsystem::CleanupRollHandles()
{
    UE_LOG(LogTemp, Warning, TEXT("RPGDiceSubsystem: Cleaning up %d roll handles"), RollHandles.Num());
    RollHandles.Empty();
    NextRollHandle = 1;
}