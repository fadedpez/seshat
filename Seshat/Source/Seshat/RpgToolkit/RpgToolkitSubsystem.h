#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "RpgDiceRoller.h"
#include "RpgToolkitSubsystem.generated.h"

/**
 * RPG Toolkit Subsystem - Global access to RPG toolkit functionality
 * 
 * This subsystem provides easy access to all RPG toolkit services
 * from anywhere in the game. It manages connections to the Seshat server
 * and provides Blueprint-accessible interfaces.
 */
UCLASS(BlueprintType)
class SESHAT_API URpgToolkitSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	// USubsystem interface
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	/**
	 * Get the dice roller instance
	 * @return Dice roller for Blueprint use
	 */
	UFUNCTION(BlueprintCallable, Category = "RPG|Toolkit", BlueprintPure)
	URpgDiceRoller* GetDiceRoller() const { return DiceRoller; }

	/**
	 * Quick dice rolling functions for common use cases
	 */
	UFUNCTION(BlueprintCallable, Category = "RPG|Quick", meta = (CallInEditor = "true"))
	int32 QuickRollD20() { return DiceRoller ? DiceRoller->RollD20() : 1; }

	UFUNCTION(BlueprintCallable, Category = "RPG|Quick", meta = (CallInEditor = "true"))
	int32 QuickRoll(int32 Sides) { return DiceRoller ? DiceRoller->RollDice(Sides) : 1; }

	UFUNCTION(BlueprintCallable, Category = "RPG|Quick", meta = (CallInEditor = "true"))
	TArray<int32> QuickRollMultiple(int32 Count, int32 Sides) 
	{ 
		return DiceRoller ? DiceRoller->RollMultipleDice(Count, Sides) : TArray<int32>(); 
	}

	/**
	 * Initialize connection to Seshat server
	 * @param ServerUrl URL of the Seshat gRPC server
	 * @return True if connection was successful
	 */
	UFUNCTION(BlueprintCallable, Category = "RPG|Toolkit|Config")
	bool InitializeServer(const FString& ServerUrl = TEXT("http://localhost:9090"));

	/**
	 * Test all toolkit services
	 * @return True if all services are working correctly
	 */
	UFUNCTION(BlueprintCallable, Category = "RPG|Toolkit|Debug", meta = (CallInEditor = "true"))
	bool RunDiagnostics();

	/**
	 * Get toolkit status information
	 * @return Human-readable status string
	 */
	UFUNCTION(BlueprintCallable, Category = "RPG|Toolkit|Debug", BlueprintPure)
	FString GetToolkitStatus() const;

private:
	/** Dice rolling service */
	UPROPERTY()
	URpgDiceRoller* DiceRoller;

	/** Server connection status */
	UPROPERTY()
	bool bServerConnected;

	/** Server URL */
	UPROPERTY()
	FString ServerUrl;

	/** Initialize all toolkit services */
	void InitializeServices();

	/** Test server connectivity */
	bool TestServerConnection();
};