#include "RPGDiceSubsystem.h"
#include "HAL/PlatformProcess.h"
#include "Misc/Paths.h"

void URPGDiceSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
    
    UE_LOG(LogTemp, Warning, TEXT("RPGDiceSubsystem: Initializing"));
    
    bFunctionsLoaded = false;
    ToolkitDLLHandle = nullptr;
    RollDiceFuncPtr = nullptr;
    GetVersionFuncPtr = nullptr;
    InitializeFuncPtr = nullptr;
    
    // Load DLL functions
    LoadDLLFunctions();
    
    if (bFunctionsLoaded)
    {
        UE_LOG(LogTemp, Warning, TEXT("RPGDiceSubsystem: Successfully initialized"));
        
        // Test the version function
        if (GetVersionFuncPtr)
        {
            char* Version = GetVersionFuncPtr();
            if (Version)
            {
                FString VersionString = FString(UTF8_TO_TCHAR(Version));
                UE_LOG(LogTemp, Warning, TEXT("RPGDiceSubsystem: Toolkit version: %s"), *VersionString);
            }
        }
        
        // Initialize the toolkit
        if (InitializeFuncPtr)
        {
            int32 InitResult = InitializeFuncPtr();
            UE_LOG(LogTemp, Warning, TEXT("RPGDiceSubsystem: Toolkit initialize result: %d"), InitResult);
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("RPGDiceSubsystem: Failed to load DLL functions"));
    }
}

void URPGDiceSubsystem::Deinitialize()
{
    // Clear function state to prevent any calls during shutdown
    bFunctionsLoaded = false;
    RollDiceFuncPtr = nullptr;
    GetVersionFuncPtr = nullptr;
    InitializeFuncPtr = nullptr;
    ToolkitDLLHandle = nullptr;
    
    // Don't unload DLL - let Windows handle cleanup on process exit
    // No FreeDllHandle call, no logging, minimal operations
    
    Super::Deinitialize();
}

void URPGDiceSubsystem::LoadDLLFunctions()
{
    // Construct the path to our DLL
    FString BaseDir = FPaths::ProjectDir();
    FString LibraryPath = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/RPGToolkit/rpg_toolkit.dll"));
    LibraryPath = FPaths::ConvertRelativePathToFull(LibraryPath);

    UE_LOG(LogTemp, Warning, TEXT("RPGDiceSubsystem: Attempting to load DLL from: %s"), *LibraryPath);

    // Check if the DLL exists
    if (!FPaths::FileExists(LibraryPath))
    {
        UE_LOG(LogTemp, Error, TEXT("RPGDiceSubsystem: DLL not found at path: %s"), *LibraryPath);
        ToolkitDLLHandle = nullptr;
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
    
    // Load function pointers
    RollDiceFuncPtr = (RollDiceFunc)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("RollDice"));
    GetVersionFuncPtr = (GetVersionFunc)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("GetVersion"));
    InitializeFuncPtr = (InitializeFunc)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("Initialize"));
    
    // Check if all functions were loaded
    bFunctionsLoaded = (RollDiceFuncPtr != nullptr) && 
                      (GetVersionFuncPtr != nullptr) && 
                      (InitializeFuncPtr != nullptr);
    
    if (bFunctionsLoaded)
    {
        UE_LOG(LogTemp, Warning, TEXT("RPGDiceSubsystem: All DLL functions loaded successfully"));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("RPGDiceSubsystem: Failed to load some DLL functions"));
        UE_LOG(LogTemp, Error, TEXT("  RollDice: %s"), RollDiceFuncPtr ? TEXT("OK") : TEXT("FAILED"));
        UE_LOG(LogTemp, Error, TEXT("  GetVersion: %s"), GetVersionFuncPtr ? TEXT("OK") : TEXT("FAILED"));
        UE_LOG(LogTemp, Error, TEXT("  Initialize: %s"), InitializeFuncPtr ? TEXT("OK") : TEXT("FAILED"));
    }
}

int32 URPGDiceSubsystem::Roll(int32 Sides)
{
    if (!bFunctionsLoaded || !RollDiceFuncPtr)
    {
        UE_LOG(LogTemp, Error, TEXT("RPGDiceSubsystem::Roll: Toolkit not loaded"));
        return -1;
    }
    
    if (Sides <= 0)
    {
        UE_LOG(LogTemp, Error, TEXT("RPGDiceSubsystem::Roll: Invalid sides: %d"), Sides);
        return -1;
    }
    
    int32 Result = RollDiceFuncPtr(Sides);
    UE_LOG(LogTemp, Log, TEXT("RPGDiceSubsystem::Roll: Rolled d%d = %d"), Sides, Result);
    
    return Result;
}

int32 URPGDiceSubsystem::RollWithAdvantage(int32 Sides)
{
    int32 Roll1 = Roll(Sides);
    int32 Roll2 = Roll(Sides);
    
    int32 Result = FMath::Max(Roll1, Roll2);
    UE_LOG(LogTemp, Log, TEXT("RPGDiceSubsystem::RollWithAdvantage: d%d advantage: %d, %d -> %d"), 
           Sides, Roll1, Roll2, Result);
    
    return Result;
}

int32 URPGDiceSubsystem::RollWithDisadvantage(int32 Sides)
{
    int32 Roll1 = Roll(Sides);
    int32 Roll2 = Roll(Sides);
    
    int32 Result = FMath::Min(Roll1, Roll2);
    UE_LOG(LogTemp, Log, TEXT("RPGDiceSubsystem::RollWithDisadvantage: d%d disadvantage: %d, %d -> %d"), 
           Sides, Roll1, Roll2, Result);
    
    return Result;
}

TArray<int32> URPGDiceSubsystem::RollMultiple(int32 Count, int32 Sides)
{
    TArray<int32> Results;
    
    if (Count <= 0 || Sides <= 0)
    {
        UE_LOG(LogTemp, Error, TEXT("RPGDiceSubsystem::RollMultiple: Invalid parameters - Count: %d, Sides: %d"), Count, Sides);
        return Results;
    }
    
    Results.Reserve(Count);
    
    for (int32 i = 0; i < Count; i++)
    {
        int32 RollResult = Roll(Sides);
        if (RollResult > 0)
        {
            Results.Add(RollResult);
        }
    }
    
    UE_LOG(LogTemp, Log, TEXT("RPGDiceSubsystem::RollMultiple: Rolled %dd%d"), Count, Sides);
    
    return Results;
}

bool URPGDiceSubsystem::IsToolkitLoaded() const
{
    return bFunctionsLoaded;
}

int32 URPGDiceSubsystem::RollForEntity(int32 Sides, TScriptInterface<IRPGEntityInterface> Entity)
{
    // For now, just roll normally - in the future this will include entity-specific modifiers via event system
    int32 BaseRoll = Roll(Sides);
    
    if (Entity.GetInterface())
    {
        UE_LOG(LogTemp, Log, TEXT("RPGDiceSubsystem::RollForEntity: Entity %s:%s rolled d%d = %d"), 
               *Entity->GetType(), *Entity->GetID(), Sides, BaseRoll);
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("RPGDiceSubsystem::RollForEntity: No entity provided, rolled d%d = %d"), 
               Sides, BaseRoll);
    }
    
    return BaseRoll;
}

int32 URPGDiceSubsystem::RollWithAdvantageForEntity(int32 Sides, TScriptInterface<IRPGEntityInterface> Entity)
{
    // For now, just roll with advantage - in the future this will include entity-specific modifiers via event system
    int32 Result = RollWithAdvantage(Sides);
    
    if (Entity.GetInterface())
    {
        UE_LOG(LogTemp, Log, TEXT("RPGDiceSubsystem::RollWithAdvantageForEntity: Entity %s:%s rolled d%d with advantage = %d"), 
               *Entity->GetType(), *Entity->GetID(), Sides, Result);
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("RPGDiceSubsystem::RollWithAdvantageForEntity: No entity provided, rolled d%d with advantage = %d"), 
               Sides, Result);
    }
    
    return Result;
}