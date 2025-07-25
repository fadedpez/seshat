#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/Engine.h"
#include "RpgDiceRoller.generated.h"

/**
 * RPG Dice Roller - UE wrapper for Seshat gRPC dice service
 * 
 * This class provides Blueprint-accessible dice rolling functionality
 * by communicating with the Seshat gRPC server (currently via HTTP bridge)
 */
UCLASS(BlueprintType, Blueprintable)
class SESHAT_API URpgDiceRoller : public UObject
{
	GENERATED_BODY()

public:
	URpgDiceRoller();

	/**
	 * Roll a standard d20 die
	 * @return Random number between 1 and 20
	 */
	UFUNCTION(BlueprintCallable, Category = "RPG|Dice")
	int32 RollD20();

	/**
	 * Roll a die with specified number of sides
	 * @param Sides Number of sides on the die (4, 6, 8, 10, 12, 20, 100)
	 * @return Random number between 1 and Sides
	 */
	UFUNCTION(BlueprintCallable, Category = "RPG|Dice")
	int32 RollDice(int32 Sides);

	/**
	 * Roll multiple dice of the same type
	 * @param Count Number of dice to roll
	 * @param Sides Number of sides per die
	 * @return Array of individual roll results
	 */
	UFUNCTION(BlueprintCallable, Category = "RPG|Dice")
	TArray<int32> RollMultipleDice(int32 Count, int32 Sides);

	/**
	 * Roll dice with context information (for logging/history)
	 * @param Sides Number of sides on the die
	 * @param EntityId Identifier for the entity rolling (e.g., "Player1", "Goblin_3")
	 * @param Context Purpose of the roll (e.g., "Attack", "Damage", "Saving_Throw")
	 * @return Random number between 1 and Sides
	 */
	UFUNCTION(BlueprintCallable, Category = "RPG|Dice")
	int32 RollWithContext(int32 Sides, const FString& EntityId, const FString& Context);

	/**
	 * Test dice fairness with statistical analysis
	 * @param Sides Number of sides to test
	 * @param SampleSize Number of rolls to perform for the test
	 * @return True if the dice appear statistically fair
	 */
	UFUNCTION(BlueprintCallable, Category = "RPG|Dice")
	bool TestDiceFairness(int32 Sides, int32 SampleSize);

	/**
	 * Get roll history for a specific entity
	 * @param EntityId Entity to get history for
	 * @param Limit Maximum number of historical rolls to return
	 * @return Array of roll results as strings (formatted for display)
	 */
	UFUNCTION(BlueprintCallable, Category = "RPG|Dice")
	TArray<FString> GetRollHistory(const FString& EntityId, int32 Limit = 10);

	/**
	 * Set the server URL for dice service communication
	 * @param ServerUrl URL of the Seshat server (default: http://localhost:9090)
	 */
	UFUNCTION(BlueprintCallable, Category = "RPG|Dice|Config")
	void SetServerUrl(const FString& ServerUrl);

	/**
	 * Test connection to the dice service
	 * @return True if server is reachable and responding
	 */
	UFUNCTION(BlueprintCallable, Category = "RPG|Dice|Config")
	bool TestConnection();

private:
	/** URL of the Seshat gRPC server */
	UPROPERTY()
	FString ServerUrl;

	/**
	 * Fallback dice rolling when server is unavailable
	 * Uses UE's built-in random number generation
	 */
	int32 FallbackRoll(int32 Sides);

	/**
	 * Log dice roll for debugging purposes
	 */
	void LogRoll(int32 Sides, int32 Result, const FString& EntityId, const FString& Context);
};