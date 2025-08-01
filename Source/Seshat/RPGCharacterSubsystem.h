#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "RPGCharacterSubsystem.generated.h"

USTRUCT(BlueprintType)
struct SESHAT_API FCharacterResult
{
    GENERATED_BODY()

    // Core identity
    UPROPERTY(BlueprintReadOnly, Category = "Character") FString ID;
    UPROPERTY(BlueprintReadOnly, Category = "Character") FString Name;
    UPROPERTY(BlueprintReadOnly, Category = "Character") int32 Level = 1;
    UPROPERTY(BlueprintReadOnly, Category = "Character") int32 ProficiencyBonus = 2;

    // References
    UPROPERTY(BlueprintReadOnly, Category = "Character") FString RaceID;
    UPROPERTY(BlueprintReadOnly, Category = "Character") FString ClassID;
    UPROPERTY(BlueprintReadOnly, Category = "Character") FString BackgroundID;

    // Ability Scores
    UPROPERTY(BlueprintReadOnly, Category = "Ability Scores") int32 Strength = 10;
    UPROPERTY(BlueprintReadOnly, Category = "Ability Scores") int32 Dexterity = 10;
    UPROPERTY(BlueprintReadOnly, Category = "Ability Scores") int32 Constitution = 10;
    UPROPERTY(BlueprintReadOnly, Category = "Ability Scores") int32 Intelligence = 10;
    UPROPERTY(BlueprintReadOnly, Category = "Ability Scores") int32 Wisdom = 10;
    UPROPERTY(BlueprintReadOnly, Category = "Ability Scores") int32 Charisma = 10;

    // Physical characteristics
    UPROPERTY(BlueprintReadOnly, Category = "Physical") FString Size;
    UPROPERTY(BlueprintReadOnly, Category = "Physical") int32 Speed = 30;

    // Combat stats
    UPROPERTY(BlueprintReadOnly, Category = "Combat") int32 HitPoints = 1;
    UPROPERTY(BlueprintReadOnly, Category = "Combat") int32 MaxHitPoints = 1;
    UPROPERTY(BlueprintReadOnly, Category = "Combat") int32 ArmorClass = 10;
    UPROPERTY(BlueprintReadOnly, Category = "Combat") int32 Initiative = 0;

    // Arrays (using Blueprint-friendly TArray)
    UPROPERTY(BlueprintReadOnly, Category = "Character") TArray<FString> Languages;
    UPROPERTY(BlueprintReadOnly, Category = "Character") TArray<FString> Features;

    // Error handling (automatic cleanup pattern)
    UPROPERTY(BlueprintReadOnly, Category = "Character") bool HasError = false;
    UPROPERTY(BlueprintReadOnly, Category = "Character") FString ErrorMessage;

    // Constructors
    FCharacterResult() = default;
    
    FCharacterResult(const FString& InErrorMessage)
        : HasError(true), ErrorMessage(InErrorMessage) {}
};

UCLASS()
class SESHAT_API URPGCharacterSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    // USubsystem interface
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;

    // Automatic cleanup character creation
    UFUNCTION(BlueprintCallable, Category = "RPG Character")
    FCharacterResult CreateCharacter(
        const FString& RaceDataJSON,
        const FString& ClassDataJSON, 
        const FString& BackgroundDataJSON,
        const FString& CharacterName,
        int32 Strength = 15, int32 Dexterity = 14, int32 Constitution = 13,
        int32 Intelligence = 12, int32 Wisdom = 10, int32 Charisma = 8
    );

    // Character validation
    UFUNCTION(BlueprintCallable, Category = "RPG Character")
    bool ValidateAbilityScores(int32 Str, int32 Dex, int32 Con, int32 Int, int32 Wis, int32 Cha);

    // Toolkit status
    UFUNCTION(BlueprintCallable, Category = "RPG Character")
    bool IsToolkitLoaded() const;

private:
    // DLL function pointer
    typedef int (*CreateCharacterCompleteFunc)(
        const char* raceDataJSON,
        const char* classDataJSON,
        const char* backgroundDataJSON,
        const char* characterName,
        int str, int dex, int con, int intel, int wis, int cha,
        char** outID, char** outName, int* outLevel, int* outProficiencyBonus,
        char** outRaceID, char** outClassID, char** outBackgroundID,
        int* outStr, int* outDex, int* outCon, int* outInt, int* outWis, int* outCha,
        char** outSize, int* outSpeed,
        int* outHP, int* outMaxHP, int* outAC, int* outInitiative,
        char** outLanguages, char** outFeatures,
        char** outError
    );
    CreateCharacterCompleteFunc CreateCharacterCompleteFuncPtr = nullptr;
    
    // Standard subsystem patterns (following established dice/entity patterns)
    bool bFunctionsLoaded = false;
    void* ToolkitDLLHandle = nullptr;
    
    void LoadDLLFunctions();
    FString ConvertAndFreeString(ANSICHAR* CStr) const;
    TArray<FString> ParseStringArray(const FString& ConcatenatedString) const;
    bool IsSafeToCallFunction() const;

public:
    // Sample data constants for testing (simplified format)
    static inline const FString SAMPLE_HUMAN_RACE = TEXT("{\"id\":\"human\",\"name\":\"Human\",\"size\":\"Medium\",\"speed\":30,\"ability_score_increases\":{\"strength\":1,\"dexterity\":1,\"constitution\":1,\"intelligence\":1,\"wisdom\":1,\"charisma\":1},\"languages\":[\"Common\"]}");
    static inline const FString SAMPLE_FIGHTER_CLASS = TEXT("{\"id\":\"fighter\",\"name\":\"Fighter\",\"hit_dice\":10,\"hit_points_at_1st\":10,\"saving_throws\":[\"Strength\",\"Constitution\"],\"skill_proficiency_count\":2,\"skill_options\":[\"Athletics\",\"Intimidation\"]}");
    static inline const FString SAMPLE_SOLDIER_BACKGROUND = TEXT("{\"id\":\"soldier\",\"name\":\"Soldier\",\"skill_proficiencies\":[\"Athletics\",\"Intimidation\"],\"languages\":[\"Common\"]}");
};