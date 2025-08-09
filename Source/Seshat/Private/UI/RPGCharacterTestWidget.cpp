// Copyright Epic Games, Inc. All Rights Reserved.

#include "UI/RPGCharacterTestWidget.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "TimerManager.h"

// Default server URL for local testing
const FString URPGCharacterTestWidget::DefaultServerUrl = TEXT("http://localhost:80");

URPGCharacterTestWidget::URPGCharacterTestWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, CharacterServiceClient(nullptr)
	, CurrentTestResults(TEXT("Ready to test character creation"))
	, bTestRunning(false)
{
}

void URPGCharacterTestWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	UE_LOG(LogTemp, Log, TEXT("RPGCharacterTestWidget: Constructing UI"));
	
	// Initialize the character service
	InitializeCharacterService();
	
	// Start UI update timer (updates every 0.5 seconds)
	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().SetTimer(
			UpdateTimerHandle,
			this,
			&URPGCharacterTestWidget::UpdateUIResults,
			0.5f,
			true // Loop
		);
	}
	
	// Initial UI update
	UpdateUIResults();
}

void URPGCharacterTestWidget::NativeDestruct()
{
	// Clean up timer
	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(UpdateTimerHandle);
	}
	
	// Clean up client
	if (CharacterServiceClient)
	{
		CharacterServiceClient = nullptr;
	}
	
	Super::NativeDestruct();
}

void URPGCharacterTestWidget::InitializeCharacterService()
{
	UE_LOG(LogTemp, Log, TEXT("RPGCharacterTestWidget: Initializing Character Service"));
	
	// Create character service client
	CharacterServiceClient = NewObject<URPGCharacterServiceClient>(this);
	
	if (CharacterServiceClient)
	{
		// Initialize with local server
		CharacterServiceClient->Initialize(DefaultServerUrl);
		
		if (CharacterServiceClient->IsInitialized())
		{
			UE_LOG(LogTemp, Log, TEXT("Character Service initialized successfully with: %s"), *DefaultServerUrl);
			CurrentTestResults = FString::Printf(TEXT("🔗 Connected to: %s\n✅ Character Service Ready\n\nClick 'Start Test' to begin!"), *DefaultServerUrl);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to initialize Character Service"));
			CurrentTestResults = TEXT("❌ Failed to initialize Character Service\nCheck that rpg-deployment is running on localhost:80");
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to create Character Service Client"));
		CurrentTestResults = TEXT("❌ Failed to create Character Service Client");
	}
}

void URPGCharacterTestWidget::StartCharacterCreationTest()
{
	UE_LOG(LogTemp, Warning, TEXT("RPGCharacterTestWidget: Starting character creation test"));
	
	if (!CharacterServiceClient)
	{
		UE_LOG(LogTemp, Error, TEXT("Character Service Client is null"));
		CurrentTestResults = TEXT("❌ ERROR: Character Service Client not available");
		OnTestCompleted(false);
		return;
	}
	
	if (!CharacterServiceClient->IsInitialized())
	{
		UE_LOG(LogTemp, Error, TEXT("Character Service Client not initialized"));
		CurrentTestResults = TEXT("❌ ERROR: Character Service not initialized\nTry restarting the widget");
		OnTestCompleted(false);
		return;
	}
	
	if (bTestRunning)
	{
		UE_LOG(LogTemp, Warning, TEXT("Test already running, ignoring request"));
		return;
	}
	
	// Start the test
	bTestRunning = true;
	CurrentTestResults = TEXT("🚀 STARTING CHARACTER CREATION TEST...\n\nStep 1: Creating character draft...");
	
	// Trigger the comprehensive test
	CharacterServiceClient->TestCharacterCreation();
	
	// Notify Blueprint that test started
	OnTestResultsUpdated(CurrentTestResults);
}

FString URPGCharacterTestWidget::GetCurrentTestResults() const
{
	return CurrentTestResults;
}

bool URPGCharacterTestWidget::IsTestRunning() const
{
	return bTestRunning;
}

FString URPGCharacterTestWidget::GetConnectionStatus() const
{
	if (!CharacterServiceClient)
	{
		return TEXT("❌ No Client");
	}
	
	if (!CharacterServiceClient->IsInitialized())
	{
		return TEXT("❌ Not Connected");
	}
	
	return FString::Printf(TEXT("✅ Connected: %s"), *DefaultServerUrl);
}

void URPGCharacterTestWidget::UpdateUIResults()
{
	if (!CharacterServiceClient)
	{
		return;
	}
	
	// Get latest results from the service client
	FString LatestResults = CharacterServiceClient->GetLastTestResults();
	
	// Check if results have changed
	if (!LatestResults.IsEmpty() && LatestResults != CurrentTestResults)
	{
		CurrentTestResults = LatestResults;
		
		// Notify Blueprint of update
		OnTestResultsUpdated(CurrentTestResults);
		
		UE_LOG(LogTemp, Log, TEXT("UI Updated with new test results"));
		
		// Check if test completed (look for success or failure indicators)
		if (CurrentTestResults.Contains(TEXT("TEST SUCCESSFUL")) || CurrentTestResults.Contains(TEXT("FAILED")))
		{
			bool bSuccess = CurrentTestResults.Contains(TEXT("TEST SUCCESSFUL"));
			bTestRunning = false;
			
			UE_LOG(LogTemp, Warning, TEXT("Test completed with result: %s"), bSuccess ? TEXT("SUCCESS") : TEXT("FAILURE"));
			
			// Notify Blueprint of completion
			OnTestCompleted(bSuccess);
		}
	}
}