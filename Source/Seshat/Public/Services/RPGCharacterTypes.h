// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RPGCharacterTypes.generated.h"

/**
 * S001 Character Service Types - D&D 5e Character Creation and Management
 * Following proven S001 pattern: UE USTRUCT types mirroring proto messages
 */

// D&D 5e Enums (matching proto enums exactly)

UENUM(BlueprintType)
enum class ERPGRace : uint8
{
	RACE_UNSPECIFIED = 0 UMETA(DisplayName = "Unspecified"),
	RACE_HUMAN = 1 UMETA(DisplayName = "Human"),
	RACE_ELF = 2 UMETA(DisplayName = "Elf"),
	RACE_DWARF = 3 UMETA(DisplayName = "Dwarf"),
	RACE_HALFLING = 4 UMETA(DisplayName = "Halfling"),
	RACE_DRAGONBORN = 5 UMETA(DisplayName = "Dragonborn"),
	RACE_GNOME = 6 UMETA(DisplayName = "Gnome"),
	RACE_HALF_ELF = 7 UMETA(DisplayName = "Half-Elf"),
	RACE_HALF_ORC = 8 UMETA(DisplayName = "Half-Orc"),
	RACE_TIEFLING = 9 UMETA(DisplayName = "Tiefling")
};

UENUM(BlueprintType)
enum class ERPGSubrace : uint8
{
	SUBRACE_UNSPECIFIED = 0 UMETA(DisplayName = "Unspecified"),
	SUBRACE_HIGH_ELF = 1 UMETA(DisplayName = "High Elf"),
	SUBRACE_WOOD_ELF = 2 UMETA(DisplayName = "Wood Elf"),
	SUBRACE_DARK_ELF = 3 UMETA(DisplayName = "Dark Elf"),
	SUBRACE_HILL_DWARF = 4 UMETA(DisplayName = "Hill Dwarf"),
	SUBRACE_MOUNTAIN_DWARF = 5 UMETA(DisplayName = "Mountain Dwarf"),
	SUBRACE_LIGHTFOOT_HALFLING = 6 UMETA(DisplayName = "Lightfoot Halfling"),
	SUBRACE_STOUT_HALFLING = 7 UMETA(DisplayName = "Stout Halfling"),
	SUBRACE_FOREST_GNOME = 8 UMETA(DisplayName = "Forest Gnome"),
	SUBRACE_ROCK_GNOME = 9 UMETA(DisplayName = "Rock Gnome")
};

UENUM(BlueprintType)
enum class ERPGClass : uint8
{
	CLASS_UNSPECIFIED = 0 UMETA(DisplayName = "Unspecified"),
	CLASS_BARBARIAN = 1 UMETA(DisplayName = "Barbarian"),
	CLASS_BARD = 2 UMETA(DisplayName = "Bard"),
	CLASS_CLERIC = 3 UMETA(DisplayName = "Cleric"),
	CLASS_DRUID = 4 UMETA(DisplayName = "Druid"),
	CLASS_FIGHTER = 5 UMETA(DisplayName = "Fighter"),
	CLASS_MONK = 6 UMETA(DisplayName = "Monk"),
	CLASS_PALADIN = 7 UMETA(DisplayName = "Paladin"),
	CLASS_RANGER = 8 UMETA(DisplayName = "Ranger"),
	CLASS_ROGUE = 9 UMETA(DisplayName = "Rogue"),
	CLASS_SORCERER = 10 UMETA(DisplayName = "Sorcerer"),
	CLASS_WARLOCK = 11 UMETA(DisplayName = "Warlock"),
	CLASS_WIZARD = 12 UMETA(DisplayName = "Wizard")
};

UENUM(BlueprintType)
enum class ERPGBackground : uint8
{
	BACKGROUND_UNSPECIFIED = 0 UMETA(DisplayName = "Unspecified"),
	BACKGROUND_ACOLYTE = 1 UMETA(DisplayName = "Acolyte"),
	BACKGROUND_CRIMINAL = 2 UMETA(DisplayName = "Criminal"),
	BACKGROUND_FOLK_HERO = 3 UMETA(DisplayName = "Folk Hero"),
	BACKGROUND_NOBLE = 4 UMETA(DisplayName = "Noble"),
	BACKGROUND_SAGE = 5 UMETA(DisplayName = "Sage"),
	BACKGROUND_SOLDIER = 6 UMETA(DisplayName = "Soldier"),
	BACKGROUND_CHARLATAN = 7 UMETA(DisplayName = "Charlatan"),
	BACKGROUND_ENTERTAINER = 8 UMETA(DisplayName = "Entertainer"),
	BACKGROUND_GUILD_ARTISAN = 9 UMETA(DisplayName = "Guild Artisan"),
	BACKGROUND_HERMIT = 10 UMETA(DisplayName = "Hermit"),
	BACKGROUND_OUTLANDER = 11 UMETA(DisplayName = "Outlander"),
	BACKGROUND_SAILOR = 12 UMETA(DisplayName = "Sailor")
};

UENUM(BlueprintType)
enum class ERPGAbility : uint8
{
	ABILITY_UNSPECIFIED = 0 UMETA(DisplayName = "Unspecified"),
	ABILITY_STRENGTH = 1 UMETA(DisplayName = "Strength"),
	ABILITY_DEXTERITY = 2 UMETA(DisplayName = "Dexterity"),
	ABILITY_CONSTITUTION = 3 UMETA(DisplayName = "Constitution"),
	ABILITY_INTELLIGENCE = 4 UMETA(DisplayName = "Intelligence"),
	ABILITY_WISDOM = 5 UMETA(DisplayName = "Wisdom"),
	ABILITY_CHARISMA = 6 UMETA(DisplayName = "Charisma")
};

UENUM(BlueprintType)
enum class ERPGSkill : uint8
{
	SKILL_UNSPECIFIED = 0 UMETA(DisplayName = "Unspecified"),
	SKILL_ACROBATICS = 1 UMETA(DisplayName = "Acrobatics"),
	SKILL_ANIMAL_HANDLING = 2 UMETA(DisplayName = "Animal Handling"),
	SKILL_ARCANA = 3 UMETA(DisplayName = "Arcana"),
	SKILL_ATHLETICS = 4 UMETA(DisplayName = "Athletics"),
	SKILL_DECEPTION = 5 UMETA(DisplayName = "Deception"),
	SKILL_HISTORY = 6 UMETA(DisplayName = "History"),
	SKILL_INSIGHT = 7 UMETA(DisplayName = "Insight"),
	SKILL_INTIMIDATION = 8 UMETA(DisplayName = "Intimidation"),
	SKILL_INVESTIGATION = 9 UMETA(DisplayName = "Investigation"),
	SKILL_MEDICINE = 10 UMETA(DisplayName = "Medicine"),
	SKILL_NATURE = 11 UMETA(DisplayName = "Nature"),
	SKILL_PERCEPTION = 12 UMETA(DisplayName = "Perception"),
	SKILL_PERFORMANCE = 13 UMETA(DisplayName = "Performance"),
	SKILL_PERSUASION = 14 UMETA(DisplayName = "Persuasion"),
	SKILL_RELIGION = 15 UMETA(DisplayName = "Religion"),
	SKILL_SLEIGHT_OF_HAND = 16 UMETA(DisplayName = "Sleight of Hand"),
	SKILL_STEALTH = 17 UMETA(DisplayName = "Stealth"),
	SKILL_SURVIVAL = 18 UMETA(DisplayName = "Survival")
};

UENUM(BlueprintType)
enum class ERPGAlignment : uint8
{
	ALIGNMENT_UNSPECIFIED = 0 UMETA(DisplayName = "Unspecified"),
	ALIGNMENT_LAWFUL_GOOD = 1 UMETA(DisplayName = "Lawful Good"),
	ALIGNMENT_NEUTRAL_GOOD = 2 UMETA(DisplayName = "Neutral Good"),
	ALIGNMENT_CHAOTIC_GOOD = 3 UMETA(DisplayName = "Chaotic Good"),
	ALIGNMENT_LAWFUL_NEUTRAL = 4 UMETA(DisplayName = "Lawful Neutral"),
	ALIGNMENT_TRUE_NEUTRAL = 5 UMETA(DisplayName = "True Neutral"),
	ALIGNMENT_CHAOTIC_NEUTRAL = 6 UMETA(DisplayName = "Chaotic Neutral"),
	ALIGNMENT_LAWFUL_EVIL = 7 UMETA(DisplayName = "Lawful Evil"),
	ALIGNMENT_NEUTRAL_EVIL = 8 UMETA(DisplayName = "Neutral Evil"),
	ALIGNMENT_CHAOTIC_EVIL = 9 UMETA(DisplayName = "Chaotic Evil")
};

// Core D&D 5e Structures

USTRUCT(BlueprintType)
struct SESHAT_API FRPGAbilityScores
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Scores", meta = (ClampMin = "3", ClampMax = "18"))
	int32 Strength = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Scores", meta = (ClampMin = "3", ClampMax = "18"))
	int32 Dexterity = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Scores", meta = (ClampMin = "3", ClampMax = "18"))
	int32 Constitution = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Scores", meta = (ClampMin = "3", ClampMax = "18"))
	int32 Intelligence = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Scores", meta = (ClampMin = "3", ClampMax = "18"))
	int32 Wisdom = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Scores", meta = (ClampMin = "3", ClampMax = "18"))
	int32 Charisma = 10;

	FRPGAbilityScores() = default;
};

// S001: Request/Response Structures for CharacterService Methods

/**
 * CreateDraft Request/Response
 */
USTRUCT(BlueprintType)
struct SESHAT_API FRPGCreateDraftRequest
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Draft")
	FString PlayerId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Draft")
	FString SessionId;

	FRPGCreateDraftRequest() = default;
};

USTRUCT(BlueprintType)
struct SESHAT_API FRPGCharacterDraft
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Draft")
	FString Id;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Draft")
	FString PlayerId;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Draft")
	FString SessionId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	ERPGRace Race = ERPGRace::RACE_UNSPECIFIED;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	ERPGSubrace Subrace = ERPGSubrace::SUBRACE_UNSPECIFIED;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	ERPGClass Class = ERPGClass::CLASS_UNSPECIFIED;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	ERPGBackground Background = ERPGBackground::BACKGROUND_UNSPECIFIED;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	ERPGAlignment Alignment = ERPGAlignment::ALIGNMENT_UNSPECIFIED;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	FRPGAbilityScores AbilityScores;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Draft")
	int64 ExpiresAt = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Draft")
	int64 CreatedAt = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Draft")
	int64 UpdatedAt = 0;

	FRPGCharacterDraft() = default;
};

USTRUCT(BlueprintType)
struct SESHAT_API FRPGCreateDraftResponse
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Response")
	FRPGCharacterDraft Draft;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Response")
	bool bSuccess = false;

	FRPGCreateDraftResponse() = default;
};

/**
 * GetDraft Request/Response
 */
USTRUCT(BlueprintType)
struct SESHAT_API FRPGGetDraftRequest
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Draft")
	FString DraftId;

	FRPGGetDraftRequest() = default;
};

USTRUCT(BlueprintType)
struct SESHAT_API FRPGGetDraftResponse
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Response")
	FRPGCharacterDraft Draft;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Response")
	bool bSuccess = false;

	FRPGGetDraftResponse() = default;
};

/**
 * UpdateName Request/Response
 */
USTRUCT(BlueprintType)
struct SESHAT_API FRPGUpdateNameRequest
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Draft")
	FString DraftId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	FString Name;

	FRPGUpdateNameRequest() = default;
};

USTRUCT(BlueprintType)
struct SESHAT_API FRPGUpdateNameResponse
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Response")
	FRPGCharacterDraft Draft;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Response")
	bool bSuccess = false;

	FRPGUpdateNameResponse() = default;
};

/**
 * UpdateRace Request/Response
 */
USTRUCT(BlueprintType)
struct SESHAT_API FRPGUpdateRaceRequest
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Draft")
	FString DraftId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	ERPGRace Race = ERPGRace::RACE_UNSPECIFIED;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	ERPGSubrace Subrace = ERPGSubrace::SUBRACE_UNSPECIFIED;

	FRPGUpdateRaceRequest() = default;
};

USTRUCT(BlueprintType)
struct SESHAT_API FRPGUpdateRaceResponse
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Response")
	FRPGCharacterDraft Draft;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Response")
	bool bSuccess = false;

	FRPGUpdateRaceResponse() = default;
};

/**
 * UpdateClass Request/Response
 */
USTRUCT(BlueprintType)
struct SESHAT_API FRPGUpdateClassRequest
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Draft")
	FString DraftId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	ERPGClass Class = ERPGClass::CLASS_UNSPECIFIED;

	FRPGUpdateClassRequest() = default;
};

USTRUCT(BlueprintType)
struct SESHAT_API FRPGUpdateClassResponse
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Response")
	FRPGCharacterDraft Draft;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Response")
	bool bSuccess = false;

	FRPGUpdateClassResponse() = default;
};

/**
 * Roll assignments for ability scores (alternative to raw values)
 */
USTRUCT(BlueprintType)
struct SESHAT_API FRPGRollAssignments
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Roll Assignments")
	FString StrengthRollId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Roll Assignments")
	FString DexterityRollId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Roll Assignments")
	FString ConstitutionRollId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Roll Assignments")
	FString IntelligenceRollId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Roll Assignments")
	FString WisdomRollId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Roll Assignments")
	FString CharismaRollId;

	FRPGRollAssignments() = default;
};

/**
 * UpdateAbilityScores Request/Response
 */
USTRUCT(BlueprintType)
struct SESHAT_API FRPGUpdateAbilityScoresRequest
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Draft")
	FString DraftId;

	// Proto oneof: either raw ability scores OR roll assignments (server prefers roll assignments)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	FRPGAbilityScores AbilityScores;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Roll Assignments")
	FRPGRollAssignments RollAssignments;

	// Flag to indicate which field to use (true = use RollAssignments, false = use AbilityScores)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Draft")
	bool bUseRollAssignments = false;

	FRPGUpdateAbilityScoresRequest() = default;
};

USTRUCT(BlueprintType)
struct SESHAT_API FRPGUpdateAbilityScoresResponse
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Response")
	FRPGCharacterDraft Draft;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Response")
	bool bSuccess = false;

	FRPGUpdateAbilityScoresResponse() = default;
};

/**
 * ListRaces Request/Response  
 */
USTRUCT(BlueprintType)
struct SESHAT_API FRPGListRacesRequest
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pagination")
	int32 PageSize = 20;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pagination")
	FString PageToken;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Options")
	bool bIncludeSubraces = true;

	FRPGListRacesRequest() = default;
};

USTRUCT(BlueprintType)
struct SESHAT_API FRPGRaceInfo
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Race")
	FString Id;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Race")
	FString Name;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Race")
	FString Description;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Race")
	int32 Speed = 30;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Race")
	TArray<FString> Languages;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Race")
	TArray<FString> Proficiencies;

	FRPGRaceInfo() = default;
};

USTRUCT(BlueprintType)
struct SESHAT_API FRPGListRacesResponse
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Response")
	TArray<FRPGRaceInfo> Races;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Response")
	FString NextPageToken;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Response")
	int32 TotalSize = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Response")
	bool bSuccess = false;

	FRPGListRacesResponse() = default;
};

/**
 * RollAbilityScores Request/Response
 */
USTRUCT(BlueprintType)
struct SESHAT_API FRPGRollAbilityScoresRequest
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Draft")
	FString DraftId;

	FRPGRollAbilityScoresRequest() = default;
};

USTRUCT(BlueprintType)
struct SESHAT_API FRPGAbilityScoreRoll
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dice Roll")
	FString RollId;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dice Roll")
	TArray<int32> Dice;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dice Roll")
	int32 Total = 0;

	FRPGAbilityScoreRoll() = default;
};

USTRUCT(BlueprintType)
struct SESHAT_API FRPGRollAbilityScoresResponse
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Response")
	TArray<FRPGAbilityScoreRoll> Rolls;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Response")
	int64 ExpiresAt = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Response")
	bool bSuccess = false;

	FRPGRollAbilityScoresResponse() = default;
};

/**
 * ListClasses Request/Response
 */
USTRUCT(BlueprintType)
struct SESHAT_API FRPGListClassesRequest
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pagination")
	int32 PageSize = 20;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pagination")
	FString PageToken;

	FRPGListClassesRequest() = default;
};

USTRUCT(BlueprintType)
struct SESHAT_API FRPGClassInfo
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Class")
	FString Id;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Class")
	FString Name;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Class")
	FString Description;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Class")
	FString HitDie;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Class")
	TArray<FString> PrimaryAbilities;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Class")
	TArray<FString> SavingThrows;

	FRPGClassInfo() = default;
};

USTRUCT(BlueprintType)
struct SESHAT_API FRPGListClassesResponse
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Response")
	TArray<FRPGClassInfo> Classes;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Response")
	FString NextPageToken;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Response")
	int32 TotalSize = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Response")
	bool bSuccess = false;

	FRPGListClassesResponse() = default;
};