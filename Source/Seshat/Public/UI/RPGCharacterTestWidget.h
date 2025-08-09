// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Services/RPGCharacterServiceClient.h"
#include "RPGCharacterTestWidget.generated.h"

/**
 * UI Widget for testing Character Service integration
 * Provides visual feedback for character creation workflow testing
 */
UCLASS(BlueprintType, Blueprintable)
class SESHAT_API URPGCharacterTestWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	URPGCharacterTestWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

public:
	/**
	 * Start the character creation test
	 * Call this from a button press in Blueprint
	 */
	UFUNCTION(BlueprintCallable, Category = "Character Test")
	void StartCharacterCreationTest();

	/**
	 * Get the current test results for display
	 * Call this from Blueprint to update text displays
	 */
	UFUNCTION(BlueprintCallable, Category = "Character Test")
	FString GetCurrentTestResults() const;

	/**
	 * Check if test is currently running
	 */
	UFUNCTION(BlueprintCallable, Category = "Character Test")
	bool IsTestRunning() const;

	/**
	 * Get connection status for display
	 */
	UFUNCTION(BlueprintCallable, Category = "Character Test")
	FString GetConnectionStatus() const;

	/**
	 * Blueprint event fired when test results are updated
	 * Implement this in Blueprint to update your text displays
	 */
	UFUNCTION(BlueprintImplementableEvent, Category = "Character Test")
	void OnTestResultsUpdated(const FString& NewResults);

	/**
	 * Blueprint event fired when test completes (success or failure)
	 * Implement this in Blueprint to handle completion
	 */
	UFUNCTION(BlueprintImplementableEvent, Category = "Character Test") 
	void OnTestCompleted(bool bSuccess);

protected:
	/**
	 * Initialize the character service client
	 */
	UFUNCTION(BlueprintCallable, Category = "Character Test")
	void InitializeCharacterService();

private:
	// Character service client instance
	UPROPERTY()
	TObjectPtr<URPGCharacterServiceClient> CharacterServiceClient;

	// Current test results for display
	UPROPERTY()
	FString CurrentTestResults;

	// Track if test is running
	UPROPERTY()
	bool bTestRunning;

	// Timer for updating UI
	FTimerHandle UpdateTimerHandle;

	// Update UI with latest results
	void UpdateUIResults();

	// Default server URL
	static const FString DefaultServerUrl;
};