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
    
    D4CompleteFuncPtr = nullptr;
    D6CompleteFuncPtr = nullptr;
    D8CompleteFuncPtr = nullptr;
    D10CompleteFuncPtr = nullptr;
    D12CompleteFuncPtr = nullptr;
    D20CompleteFuncPtr = nullptr;
    D100CompleteFuncPtr = nullptr;
    
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
    
    // No cleanup needed - automatic cleanup approach
    
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
    
    D4CompleteFuncPtr = nullptr;
    D6CompleteFuncPtr = nullptr;
    D8CompleteFuncPtr = nullptr;
    D10CompleteFuncPtr = nullptr;
    D12CompleteFuncPtr = nullptr;
    D20CompleteFuncPtr = nullptr;
    D100CompleteFuncPtr = nullptr;
    
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

// Legacy Roll Struct Functions (Deprecated - Use FRollResult functions instead)
// These functions remain for backward compatibility but should not be used
// New Blueprint code should use D4(), D6(), D8(), D10(), D12(), D20(), D100() functions

// Helper Functions Implementation
FRollResult URPGDiceSubsystem::D4(int32 Count)
{
    if (!IsSafeToCallFunction() || !D4CompleteFuncPtr)
    {
        return FRollResult(TEXT("Function not available"));
    }
    
    int32 value;
    ANSICHAR* desc;
    ANSICHAR* error;
    
    int32 success = D4CompleteFuncPtr(Count, &value, &desc, &error);
    
    FRollResult Result;
    Result.Value = value;
    Result.Description = ConvertAndFreeString(desc);
    Result.HasError = (success == 0);
    Result.ErrorMessage = ConvertAndFreeString(error);
    
    return Result;
}

FRollResult URPGDiceSubsystem::D6(int32 Count)
{
    if (!IsSafeToCallFunction() || !D6CompleteFuncPtr)
    {
        return FRollResult(TEXT("Function not available"));
    }
    
    int32 value;
    ANSICHAR* desc;
    ANSICHAR* error;
    
    int32 success = D6CompleteFuncPtr(Count, &value, &desc, &error);
    
    FRollResult Result;
    Result.Value = value;
    Result.Description = ConvertAndFreeString(desc);
    Result.HasError = (success == 0);
    Result.ErrorMessage = ConvertAndFreeString(error);
    
    return Result;
}

FRollResult URPGDiceSubsystem::D8(int32 Count)
{
    if (!IsSafeToCallFunction() || !D8CompleteFuncPtr)
    {
        return FRollResult(TEXT("Function not available"));
    }
    
    int32 value;
    ANSICHAR* desc;
    ANSICHAR* error;
    
    int32 success = D8CompleteFuncPtr(Count, &value, &desc, &error);
    
    FRollResult Result;
    Result.Value = value;
    Result.Description = ConvertAndFreeString(desc);
    Result.HasError = (success == 0);
    Result.ErrorMessage = ConvertAndFreeString(error);
    
    return Result;
}

FRollResult URPGDiceSubsystem::D10(int32 Count)
{
    if (!IsSafeToCallFunction() || !D10CompleteFuncPtr)
    {
        return FRollResult(TEXT("Function not available"));
    }
    
    int32 value;
    ANSICHAR* desc;
    ANSICHAR* error;
    
    int32 success = D10CompleteFuncPtr(Count, &value, &desc, &error);
    
    FRollResult Result;
    Result.Value = value;
    Result.Description = ConvertAndFreeString(desc);
    Result.HasError = (success == 0);
    Result.ErrorMessage = ConvertAndFreeString(error);
    
    return Result;
}

FRollResult URPGDiceSubsystem::D12(int32 Count)
{
    if (!IsSafeToCallFunction() || !D12CompleteFuncPtr)
    {
        return FRollResult(TEXT("Function not available"));
    }
    
    int32 value;
    ANSICHAR* desc;
    ANSICHAR* error;
    
    int32 success = D12CompleteFuncPtr(Count, &value, &desc, &error);
    
    FRollResult Result;
    Result.Value = value;
    Result.Description = ConvertAndFreeString(desc);
    Result.HasError = (success == 0);
    Result.ErrorMessage = ConvertAndFreeString(error);
    
    return Result;
}

FRollResult URPGDiceSubsystem::D20(int32 Count)
{
    if (!IsSafeToCallFunction() || !D20CompleteFuncPtr)
    {
        return FRollResult(TEXT("Function not available"));
    }
    
    int32 value;
    ANSICHAR* desc;
    ANSICHAR* error;
    
    int32 success = D20CompleteFuncPtr(Count, &value, &desc, &error);
    
    FRollResult Result;
    Result.Value = value;
    Result.Description = ConvertAndFreeString(desc);
    Result.HasError = (success == 0);
    Result.ErrorMessage = ConvertAndFreeString(error);
    
    return Result;
}

FRollResult URPGDiceSubsystem::D100(int32 Count)
{
    if (!IsSafeToCallFunction() || !D100CompleteFuncPtr)
    {
        return FRollResult(TEXT("Function not available"));
    }
    
    int32 value;
    ANSICHAR* desc;
    ANSICHAR* error;
    
    int32 success = D100CompleteFuncPtr(Count, &value, &desc, &error);
    
    FRollResult Result;
    Result.Value = value;
    Result.Description = ConvertAndFreeString(desc);
    Result.HasError = (success == 0);
    Result.ErrorMessage = ConvertAndFreeString(error);
    
    return Result;
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
    
    // Load automatic cleanup helper functions
    D4CompleteFuncPtr = (D4CompleteFunc)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("D4Complete"));
    D6CompleteFuncPtr = (D6CompleteFunc)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("D6Complete"));
    D8CompleteFuncPtr = (D8CompleteFunc)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("D8Complete"));
    D10CompleteFuncPtr = (D10CompleteFunc)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("D10Complete"));
    D12CompleteFuncPtr = (D12CompleteFunc)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("D12Complete"));
    D20CompleteFuncPtr = (D20CompleteFunc)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("D20Complete"));
    D100CompleteFuncPtr = (D100CompleteFunc)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("D100Complete"));
    
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
        
        UE_LOG(LogTemp, Log, TEXT("Automatic Cleanup Helper Functions:"));
        UE_LOG(LogTemp, Log, TEXT("  D4Complete: %s"), D4CompleteFuncPtr ? TEXT("OK") : TEXT("FAILED"));
        UE_LOG(LogTemp, Log, TEXT("  D6Complete: %s"), D6CompleteFuncPtr ? TEXT("OK") : TEXT("FAILED"));
        UE_LOG(LogTemp, Log, TEXT("  D8Complete: %s"), D8CompleteFuncPtr ? TEXT("OK") : TEXT("FAILED"));
        UE_LOG(LogTemp, Log, TEXT("  D10Complete: %s"), D10CompleteFuncPtr ? TEXT("OK") : TEXT("FAILED"));
        UE_LOG(LogTemp, Log, TEXT("  D12Complete: %s"), D12CompleteFuncPtr ? TEXT("OK") : TEXT("FAILED"));
        UE_LOG(LogTemp, Log, TEXT("  D20Complete: %s"), D20CompleteFuncPtr ? TEXT("OK") : TEXT("FAILED"));
        UE_LOG(LogTemp, Log, TEXT("  D100Complete: %s"), D100CompleteFuncPtr ? TEXT("OK") : TEXT("FAILED"));
        UE_LOG(LogTemp, Log, TEXT("================================"));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("RPGDiceSubsystem: Failed to load critical dice functions"));
    }
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

