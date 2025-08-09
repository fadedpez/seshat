// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GRPCWeb/RPGWebClient.h"
#include "Services/RPGCharacterTypes.h"
#include "RPGCharacterServiceClient.generated.h"

/**
 * S001 CharacterService Client - D&D 5e Character Creation and Management
 * Following proven S001 pattern: gRPC-Web HTTP → nginx:80 → envoy:8080 → rpg-api:50051
 */

// Delegate declarations for all CharacterService methods
DECLARE_DYNAMIC_DELEGATE_TwoParams(FRPGCreateDraftDelegate, bool, bSuccess, const FRPGCreateDraftResponse&, Response);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FRPGGetDraftDelegate, bool, bSuccess, const FRPGGetDraftResponse&, Response);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FRPGUpdateNameDelegate, bool, bSuccess, const FRPGUpdateNameResponse&, Response);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FRPGUpdateRaceDelegate, bool, bSuccess, const FRPGUpdateRaceResponse&, Response);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FRPGUpdateClassDelegate, bool, bSuccess, const FRPGUpdateClassResponse&, Response);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FRPGUpdateAbilityScoresDelegate, bool, bSuccess, const FRPGUpdateAbilityScoresResponse&, Response);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FRPGListRacesDelegate, bool, bSuccess, const FRPGListRacesResponse&, Response);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FRPGListClassesDelegate, bool, bSuccess, const FRPGListClassesResponse&, Response);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FRPGRollAbilityScoresDelegate, bool, bSuccess, const FRPGRollAbilityScoresResponse&, Response);

/**
 * gRPC-Web HTTP client for dnd5e.api.v1alpha1.CharacterService
 * S001: Complete CharacterService implementation using proven pattern
 */
UCLASS(BlueprintType, Blueprintable)
class SESHAT_API URPGCharacterServiceClient : public URPGWebClient
{
    GENERATED_BODY()

public:
    URPGCharacterServiceClient();
    virtual ~URPGCharacterServiceClient();

    // S001: All CharacterService methods following proven pattern

    /**
     * Call dnd5e.api.v1alpha1.CharacterService/CreateDraft
     * Creates a new character draft for step-by-step character creation
     */
    UFUNCTION(BlueprintCallable, Category = "RPG Character Service")
    void CreateDraft(const FRPGCreateDraftRequest& Request, FRPGCreateDraftDelegate OnComplete);

    /**
     * Call dnd5e.api.v1alpha1.CharacterService/GetDraft
     * Retrieves an existing character draft by ID
     */
    UFUNCTION(BlueprintCallable, Category = "RPG Character Service")
    void GetDraft(const FRPGGetDraftRequest& Request, FRPGGetDraftDelegate OnComplete);

    /**
     * Call dnd5e.api.v1alpha1.CharacterService/UpdateName
     * Updates the name of a character draft
     */
    UFUNCTION(BlueprintCallable, Category = "RPG Character Service")
    void UpdateName(const FRPGUpdateNameRequest& Request, FRPGUpdateNameDelegate OnComplete);

    /**
     * Call dnd5e.api.v1alpha1.CharacterService/UpdateRace
     * Updates the race and subrace of a character draft
     */
    UFUNCTION(BlueprintCallable, Category = "RPG Character Service")
    void UpdateRace(const FRPGUpdateRaceRequest& Request, FRPGUpdateRaceDelegate OnComplete);

    /**
     * Call dnd5e.api.v1alpha1.CharacterService/UpdateClass
     * Updates the class of a character draft
     */
    UFUNCTION(BlueprintCallable, Category = "RPG Character Service")
    void UpdateClass(const FRPGUpdateClassRequest& Request, FRPGUpdateClassDelegate OnComplete);

    /**
     * Call dnd5e.api.v1alpha1.CharacterService/UpdateAbilityScores
     * Updates the ability scores of a character draft
     */
    UFUNCTION(BlueprintCallable, Category = "RPG Character Service")
    void UpdateAbilityScores(const FRPGUpdateAbilityScoresRequest& Request, FRPGUpdateAbilityScoresDelegate OnComplete);

    /**
     * Call dnd5e.api.v1alpha1.CharacterService/ListRaces
     * Lists all available D&D 5e races for character creation
     */
    UFUNCTION(BlueprintCallable, Category = "RPG Character Service")
    void ListRaces(const FRPGListRacesRequest& Request, FRPGListRacesDelegate OnComplete);

    /**
     * Call dnd5e.api.v1alpha1.CharacterService/ListClasses
     * Lists all available D&D 5e classes for character creation
     */
    UFUNCTION(BlueprintCallable, Category = "RPG Character Service")
    void ListClasses(const FRPGListClassesRequest& Request, FRPGListClassesDelegate OnComplete);

    /**
     * Call dnd5e.api.v1alpha1.CharacterService/RollAbilityScores
     * Server-side rolls 6 sets of 4d6 (drop lowest) for ability score assignment
     */
    UFUNCTION(BlueprintCallable, Category = "RPG Character Service")
    void RollAbilityScores(const FRPGRollAbilityScoresRequest& Request, FRPGRollAbilityScoresDelegate OnComplete);

    /**
     * Simple test function - create a test draft and log results to console
     */
    UFUNCTION(BlueprintCallable, Category = "RPG Character Service")
    void TestCreateDraft();

    /**
     * Simple test function - list races and log results to console
     */
    UFUNCTION(BlueprintCallable, Category = "RPG Character Service")
    void TestListRaces();

    /**
     * Complete character creation workflow test (7 steps)
     * Creates draft → Lists races → Selects Human → Lists classes → Selects Fighter → Sets abilities → Gets final draft
     * Follows the exact pattern used by rpg-dnd5e-web for full end-to-end validation
     */
    UFUNCTION(BlueprintCallable, Category = "RPG Character Service")
    void TestCharacterCreation();

    /**
     * Get current test results for UI display
     * Returns formatted strings ready for UI widgets
     */
    UFUNCTION(BlueprintCallable, Category = "RPG Character Service")
    FString GetLastTestResults() const;

private:
    // Simple test callback functions
    UFUNCTION()
    void OnTestCreateDraftComplete(bool bSuccess, const FRPGCreateDraftResponse& Response);

    UFUNCTION()
    void OnTestListRacesComplete(bool bSuccess, const FRPGListRacesResponse& Response);

    // Complete character creation workflow callbacks (Step 1-7)
    UFUNCTION()
    void OnTestCharacterCreationStep1Complete(bool bSuccess, const FRPGCreateDraftResponse& Response);

    UFUNCTION()
    void OnTestCharacterCreationStep2Complete(bool bSuccess, const FRPGListRacesResponse& Response);

    UFUNCTION()
    void OnTestCharacterCreationStep3Complete(bool bSuccess, const FRPGUpdateRaceResponse& Response);

    UFUNCTION()
    void OnTestCharacterCreationStep4Complete(bool bSuccess, const FRPGListClassesResponse& Response);

    UFUNCTION()
    void OnTestCharacterCreationStep5Complete(bool bSuccess, const FRPGUpdateClassResponse& Response);

    UFUNCTION()
    void OnTestCharacterCreationStep6Complete(bool bSuccess, const FRPGUpdateAbilityScoresResponse& Response);

    UFUNCTION()
    void OnTestCharacterCreationStep7Complete(bool bSuccess, const FRPGGetDraftResponse& Response);

    // Server-side ability score rolling callbacks
    UFUNCTION()
    void OnTestCharacterCreationStep6aComplete(bool bSuccess, const FRPGRollAbilityScoresResponse& Response);

    // UI data storage
    UPROPERTY()
    FString LastTestResults;

    UPROPERTY()
    FString CurrentDraftId;

};