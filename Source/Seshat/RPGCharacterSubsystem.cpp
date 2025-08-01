#include "RPGCharacterSubsystem.h"
#include "Engine/Engine.h"
#include "HAL/PlatformProcess.h"
#include "Misc/Paths.h"

void URPGCharacterSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
    
    UE_LOG(LogTemp, Warning, TEXT("RPGCharacterSubsystem initializing..."));
    LoadDLLFunctions();
    
    if (bFunctionsLoaded)
    {
        UE_LOG(LogTemp, Warning, TEXT("RPGCharacterSubsystem initialized successfully"));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("RPGCharacterSubsystem failed to initialize - DLL functions not loaded"));
    }
}

void URPGCharacterSubsystem::Deinitialize()
{
    UE_LOG(LogTemp, Warning, TEXT("RPGCharacterSubsystem deinitializing..."));
    
    if (ToolkitDLLHandle)
    {
        FPlatformProcess::FreeDllHandle(ToolkitDLLHandle);
        ToolkitDLLHandle = nullptr;
    }
    
    bFunctionsLoaded = false;
    CreateCharacterCompleteFuncPtr = nullptr;
    
    Super::Deinitialize();
}

void URPGCharacterSubsystem::LoadDLLFunctions()
{
    // Use proper UE binary directory (following established pattern)
    FString BinariesDir = FPaths::Combine(FPaths::ProjectDir(), TEXT("Binaries"), FPlatformProcess::GetBinariesSubdirectory());
    FString LibraryPath = FPaths::Combine(BinariesDir, TEXT("rpg_toolkit.dll"));
    LibraryPath = FPaths::ConvertRelativePathToFull(LibraryPath);

    if (!FPaths::FileExists(LibraryPath))
    {
        UE_LOG(LogTemp, Warning, TEXT("Toolkit DLL not found at: %s"), *LibraryPath);
        return;
    }

    ToolkitDLLHandle = FPlatformProcess::GetDllHandle(*LibraryPath);
    if (!ToolkitDLLHandle)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to load toolkit DLL from: %s"), *LibraryPath);
        return;
    }

    // Load the character creation function
    CreateCharacterCompleteFuncPtr = (CreateCharacterCompleteFunc)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("CreateCharacterComplete"));
    
    if (CreateCharacterCompleteFuncPtr)
    {
        bFunctionsLoaded = true;
        UE_LOG(LogTemp, Warning, TEXT("Character DLL functions loaded successfully"));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to find CreateCharacterComplete function in DLL"));
    }
}

FCharacterResult URPGCharacterSubsystem::CreateCharacter(
    const FString& RaceDataJSON,
    const FString& ClassDataJSON,
    const FString& BackgroundDataJSON,
    const FString& CharacterName,
    int32 Strength, int32 Dexterity, int32 Constitution,
    int32 Intelligence, int32 Wisdom, int32 Charisma)
{
    // Safety check - following established pattern
    if (!IsSafeToCallFunction())
    {
        return FCharacterResult(TEXT("Character system not available during shutdown"));
    }

    // Convert inputs to C strings (UE-friendly approach)
    const char* RaceJSON = TCHAR_TO_UTF8(*RaceDataJSON);
    const char* ClassJSON = TCHAR_TO_UTF8(*ClassDataJSON);
    const char* BackgroundJSON = TCHAR_TO_UTF8(*BackgroundDataJSON);
    const char* CharName = TCHAR_TO_UTF8(*CharacterName);

    // Output parameters for automatic cleanup pattern
    char* OutID = nullptr;
    char* OutName = nullptr;
    int OutLevel = 0;
    int OutProficiencyBonus = 0;
    char* OutRaceID = nullptr;
    char* OutClassID = nullptr;
    char* OutBackgroundID = nullptr;
    int OutStr = 0, OutDex = 0, OutCon = 0, OutInt = 0, OutWis = 0, OutCha = 0;
    char* OutSize = nullptr;
    int OutSpeed = 0;
    int OutHP = 0, OutMaxHP = 0, OutAC = 0, OutInitiative = 0;
    char* OutLanguages = nullptr;
    char* OutFeatures = nullptr;
    char* OutError = nullptr;

    // Call the toolkit function with automatic cleanup pattern
    int Result = CreateCharacterCompleteFuncPtr(
        RaceJSON, ClassJSON, BackgroundJSON, CharName,
        Strength, Dexterity, Constitution, Intelligence, Wisdom, Charisma,
        &OutID, &OutName, &OutLevel, &OutProficiencyBonus,
        &OutRaceID, &OutClassID, &OutBackgroundID,
        &OutStr, &OutDex, &OutCon, &OutInt, &OutWis, &OutCha,
        &OutSize, &OutSpeed,
        &OutHP, &OutMaxHP, &OutAC, &OutInitiative,
        &OutLanguages, &OutFeatures,
        &OutError
    );

    // Handle error case
    if (Result == 0 || OutError)
    {
        FString ErrorMsg = ConvertAndFreeString(OutError);
        
        // Clean up any other allocated strings
        if (OutID) free(OutID);
        if (OutName) free(OutName);
        if (OutRaceID) free(OutRaceID);
        if (OutClassID) free(OutClassID);
        if (OutBackgroundID) free(OutBackgroundID);
        if (OutSize) free(OutSize);
        if (OutLanguages) free(OutLanguages);
        if (OutFeatures) free(OutFeatures);
        
        return FCharacterResult(ErrorMsg.IsEmpty() ? TEXT("Unknown character creation error") : ErrorMsg);
    }

    // Success - build FCharacterResult with all extracted data
    FCharacterResult CharacterResult;
    
    // Core identity
    CharacterResult.ID = ConvertAndFreeString(OutID);
    CharacterResult.Name = ConvertAndFreeString(OutName);
    CharacterResult.Level = OutLevel;
    CharacterResult.ProficiencyBonus = OutProficiencyBonus;

    // References
    CharacterResult.RaceID = ConvertAndFreeString(OutRaceID);
    CharacterResult.ClassID = ConvertAndFreeString(OutClassID);
    CharacterResult.BackgroundID = ConvertAndFreeString(OutBackgroundID);

    // Ability scores (final values after racial bonuses)
    CharacterResult.Strength = OutStr;
    CharacterResult.Dexterity = OutDex;
    CharacterResult.Constitution = OutCon;
    CharacterResult.Intelligence = OutInt;
    CharacterResult.Wisdom = OutWis;
    CharacterResult.Charisma = OutCha;

    // Physical characteristics
    CharacterResult.Size = ConvertAndFreeString(OutSize);
    CharacterResult.Speed = OutSpeed;

    // Combat stats
    CharacterResult.HitPoints = OutHP;
    CharacterResult.MaxHitPoints = OutMaxHP;
    CharacterResult.ArmorClass = OutAC;
    CharacterResult.Initiative = OutInitiative;

    // Arrays (parse concatenated strings)
    CharacterResult.Languages = ParseStringArray(ConvertAndFreeString(OutLanguages));
    CharacterResult.Features = ParseStringArray(ConvertAndFreeString(OutFeatures));

    // No error
    CharacterResult.HasError = false;
    CharacterResult.ErrorMessage = TEXT("");
    
    // Clean up error string
    if (OutError) free(OutError);

    return CharacterResult;
}

bool URPGCharacterSubsystem::ValidateAbilityScores(int32 Str, int32 Dex, int32 Con, int32 Int, int32 Wis, int32 Cha)
{
    // Basic D&D 5e validation - scores should be 3-20 for valid characters
    TArray<int32> Scores = {Str, Dex, Con, Int, Wis, Cha};
    
    for (int32 Score : Scores)
    {
        if (Score < 3 || Score > 20)
        {
            return false;
        }
    }
    
    return true;
}

bool URPGCharacterSubsystem::IsToolkitLoaded() const
{
    return bFunctionsLoaded && CreateCharacterCompleteFuncPtr != nullptr;
}

FString URPGCharacterSubsystem::ConvertAndFreeString(ANSICHAR* CStr) const
{
    if (!CStr)
    {
        return FString();
    }
    
    FString Result = FString(UTF8_TO_TCHAR(CStr));
    free(CStr);
    return Result;
}

TArray<FString> URPGCharacterSubsystem::ParseStringArray(const FString& ConcatenatedString) const
{
    TArray<FString> Result;
    if (!ConcatenatedString.IsEmpty())
    {
        ConcatenatedString.ParseIntoArray(Result, TEXT(","), true);
    }
    return Result;
}

bool URPGCharacterSubsystem::IsSafeToCallFunction() const
{
    // Following established pattern from other subsystems
    return bFunctionsLoaded && CreateCharacterCompleteFuncPtr && !IsEngineExitRequested();
}

// Note: Sample data constants moved to header to avoid raw string literal issues in implementation file