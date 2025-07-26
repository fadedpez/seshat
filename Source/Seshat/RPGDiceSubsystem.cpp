#include "RPGDiceSubsystem.h"
#include "HAL/PlatformProcess.h"
#include "Misc/Paths.h"
#include "RPGCore/Events/RPGEventBusSubsystem.h"
#include "RPGCore/Events/RPGEvent.h"

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
    // Construct the path to our DLL in the proper binary directory
    FString BinariesDir = FPaths::Combine(FPaths::ProjectDir(), TEXT("Binaries"), FPlatformProcess::GetBinariesSubdirectory());
    FString LibraryPath = FPaths::Combine(BinariesDir, TEXT("rpg_toolkit") PLATFORM_DYNAMIC_LIBRARY_EXTENSION);
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
    
    // Publish dice roll event
    if (Result > 0)
    {
        PublishDiceRollEvent(Sides, Result);
    }
    
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
    // Roll the dice without publishing event (we'll publish entity-specific event)
    if (!bFunctionsLoaded || !RollDiceFuncPtr)
    {
        UE_LOG(LogTemp, Error, TEXT("RPGDiceSubsystem::RollForEntity: Toolkit not loaded"));
        return -1;
    }
    
    if (Sides <= 0)
    {
        UE_LOG(LogTemp, Error, TEXT("RPGDiceSubsystem::RollForEntity: Invalid sides: %d"), Sides);
        return -1;
    }
    
    int32 BaseRoll = RollDiceFuncPtr(Sides);
    
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
    
    // Publish entity-specific dice roll event
    if (BaseRoll > 0)
    {
        PublishDiceRollEvent(Sides, BaseRoll, Entity);
    }
    
    return BaseRoll;
}

int32 URPGDiceSubsystem::RollWithAdvantageForEntity(int32 Sides, TScriptInterface<IRPGEntityInterface> Entity)
{
    // Roll dice with advantage without publishing individual roll events
    int32 Roll1 = RollDiceFuncPtr(Sides);
    int32 Roll2 = RollDiceFuncPtr(Sides);
    
    int32 Result = FMath::Max(Roll1, Roll2);
    
    if (Entity.GetInterface())
    {
        UE_LOG(LogTemp, Log, TEXT("RPGDiceSubsystem::RollWithAdvantageForEntity: Entity %s:%s rolled d%d with advantage: %d, %d -> %d"), 
               *Entity->GetType(), *Entity->GetID(), Sides, Roll1, Roll2, Result);
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("RPGDiceSubsystem::RollWithAdvantageForEntity: No entity provided, rolled d%d with advantage: %d, %d -> %d"), 
               Sides, Roll1, Roll2, Result);
    }
    
    // Publish entity-specific advantage roll event
    if (Result > 0)
    {
        PublishDiceRollEvent(Sides, Result, Entity);
    }
    
    return Result;
}

void URPGDiceSubsystem::PublishDiceRollEvent(int32 Sides, int32 Result, TScriptInterface<IRPGEntityInterface> Entity)
{
    if (!bPublishEvents)
    {
        return;
    }
    
    URPGEventBusSubsystem* EventBus = GetEventBusSubsystem();
    if (!EventBus)
    {
        UE_LOG(LogTemp, VeryVerbose, TEXT("RPGDiceSubsystem::PublishDiceRollEvent: Event bus not available"));
        return;
    }
    
    // Create dice roll event context
    FRPGEventContext EventContext = URPGEvent::CreateDiceRollEvent(Entity, Sides, Result);
    
    // Add additional dice roll specific data
    EventContext.SetStringData(TEXT("DiceType"), FString::Printf(TEXT("d%d"), Sides));
    EventContext.SetBoolData(TEXT("Success"), Result > 0);
    
    // Add modifiers if this was an advantage/disadvantage roll
    // (we could detect this by tracking the call stack in the future)
    
    // Publish the event
    bool bEventPublished = EventBus->PublishEvent(EventContext);
    
    UE_LOG(LogTemp, VeryVerbose, TEXT("RPGDiceSubsystem::PublishDiceRollEvent: Published dice roll event (d%d=%d) - %s"), 
           Sides, Result, bEventPublished ? TEXT("Success") : TEXT("Failed"));
}

URPGEventBusSubsystem* URPGDiceSubsystem::GetEventBusSubsystem() const
{
    if (UGameInstance* GameInstance = GetGameInstance())
    {
        return GameInstance->GetSubsystem<URPGEventBusSubsystem>();
    }
    return nullptr;
}