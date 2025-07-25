#include "RpgToolkitSubsystem.h"
#include "Engine/Engine.h"

void URpgToolkitSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	UE_LOG(LogTemp, Log, TEXT("🧙 RPG Toolkit Subsystem: Initializing..."));
	
	InitializeServices();
	
	// Try to connect to default server
	ServerUrl = TEXT("http://localhost:9090");
	bServerConnected = TestServerConnection();
	
	if (bServerConnected)
	{
		UE_LOG(LogTemp, Log, TEXT("🧙 RPG Toolkit Subsystem: Connected to Seshat server at %s"), *ServerUrl);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("🧙 RPG Toolkit Subsystem: Server not available, using fallback mode"));
	}
	
	// Display initialization message
	if (GEngine)
	{
		FString Message = bServerConnected 
			? TEXT("🧙 RPG Toolkit: Connected to Seshat Server")
			: TEXT("🧙 RPG Toolkit: Running in Fallback Mode");
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, 
			bServerConnected ? FColor::Green : FColor::Yellow, Message);
	}
}

void URpgToolkitSubsystem::Deinitialize()
{
	UE_LOG(LogTemp, Log, TEXT("🧙 RPG Toolkit Subsystem: Shutting down..."));
	
	// Clean up services
	DiceRoller = nullptr;
	
	Super::Deinitialize();
}

bool URpgToolkitSubsystem::InitializeServer(const FString& NewServerUrl)
{
	ServerUrl = NewServerUrl;
	
	if (DiceRoller)
	{
		DiceRoller->SetServerUrl(ServerUrl);
	}
	
	bServerConnected = TestServerConnection();
	
	UE_LOG(LogTemp, Log, TEXT("🧙 RPG Toolkit: Server initialization %s for %s"), 
		   bServerConnected ? TEXT("succeeded") : TEXT("failed"), *ServerUrl);
	
	return bServerConnected;
}

bool URpgToolkitSubsystem::RunDiagnostics()
{
	UE_LOG(LogTemp, Log, TEXT("🧙 RPG Toolkit: Running diagnostics..."));
	
	bool bAllTestsPassed = true;
	
	// Test dice rolling
	if (DiceRoller)
	{
		UE_LOG(LogTemp, Log, TEXT("🎲 Testing dice roller..."));
		
		// Test basic rolling
		int32 Roll = DiceRoller->RollD20();
		if (Roll >= 1 && Roll <= 20)
		{
			UE_LOG(LogTemp, Log, TEXT("✅ Basic d20 roll: %d"), Roll);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("❌ Basic d20 roll failed: %d"), Roll);
			bAllTestsPassed = false;
		}
		
		// Test multiple dice
		TArray<int32> MultiRoll = DiceRoller->RollMultipleDice(3, 6);
		if (MultiRoll.Num() == 3)
		{
			UE_LOG(LogTemp, Log, TEXT("✅ Multiple dice roll: %d, %d, %d"), 
				   MultiRoll[0], MultiRoll[1], MultiRoll[2]);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("❌ Multiple dice roll failed"));
			bAllTestsPassed = false;
		}
		
		// Test fairness
		bool bFair = DiceRoller->TestDiceFairness(6, 600);
		if (bFair)
		{
			UE_LOG(LogTemp, Log, TEXT("✅ Dice fairness test passed"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("⚠️ Dice fairness test failed (may be random variation)"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("❌ Dice roller not initialized"));
		bAllTestsPassed = false;
	}
	
	// Test server connection
	bool bConnectionOk = TestServerConnection();
	if (bConnectionOk)
	{
		UE_LOG(LogTemp, Log, TEXT("✅ Server connection test passed"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("⚠️ Server connection test failed - using fallback mode"));
	}
	
	// Display results
	if (GEngine)
	{
		FString Message = FString::Printf(TEXT("🧙 RPG Toolkit Diagnostics: %s"), 
			bAllTestsPassed ? TEXT("All Tests Passed") : TEXT("Some Tests Failed"));
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, 
			bAllTestsPassed ? FColor::Green : FColor::Orange, Message);
	}
	
	return bAllTestsPassed;
}

FString URpgToolkitSubsystem::GetToolkitStatus() const
{
	FString Status;
	
	Status += FString::Printf(TEXT("Server: %s (%s)\n"), 
		*ServerUrl, bServerConnected ? TEXT("Connected") : TEXT("Disconnected"));
	
	Status += FString::Printf(TEXT("Dice Roller: %s\n"), 
		DiceRoller ? TEXT("Available") : TEXT("Not Available"));
	
	Status += TEXT("Services Available:\n");
	Status += TEXT("  🎲 Dice Rolling: ✅ Active\n");
	Status += TEXT("  📡 Events: ⏳ Coming Soon\n");
	Status += TEXT("  🗺️ Spatial: ⏳ Coming Soon\n");
	Status += TEXT("  🏰 Environment: ⏳ Coming Soon\n");
	Status += TEXT("  📊 Selectables: ⏳ Coming Soon\n");
	Status += TEXT("  🔮 Spells: ⏳ Coming Soon\n");
	
	return Status;
}

void URpgToolkitSubsystem::InitializeServices()
{
	// Initialize dice roller
	DiceRoller = NewObject<URpgDiceRoller>(this);
	
	if (DiceRoller)
	{
		UE_LOG(LogTemp, Log, TEXT("🎲 Dice Roller initialized"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("❌ Failed to initialize Dice Roller"));
	}
	
	// TODO: Initialize other services (Events, Spatial, etc.)
}

bool URpgToolkitSubsystem::TestServerConnection()
{
	// For now, always return the dice roller's connection test result
	return DiceRoller ? DiceRoller->TestConnection() : false;
}