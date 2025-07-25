#include "RpgDiceRoller.h"
#include "Engine/Engine.h"

URpgDiceRoller::URpgDiceRoller()
{
	ServerUrl = TEXT("http://localhost:9090");
}

int32 URpgDiceRoller::RollD20()
{
	return RollDice(20);
}

int32 URpgDiceRoller::RollDice(int32 Sides)
{
	return RollWithContext(Sides, TEXT("UE_Player"), TEXT("Generic_Roll"));
}

TArray<int32> URpgDiceRoller::RollMultipleDice(int32 Count, int32 Sides)
{
	TArray<int32> Results;
	
	// For now, make multiple individual calls
	// Later this will be optimized to use the RollMultiple gRPC method
	for (int32 i = 0; i < Count; i++)
	{
		int32 Roll = RollDice(Sides);
		Results.Add(Roll);
	}
	
	return Results;
}

int32 URpgDiceRoller::RollWithContext(int32 Sides, const FString& EntityId, const FString& Context)
{
	// Validate input
	if (Sides <= 0)
	{
		UE_LOG(LogTemp, Error, TEXT("RpgDiceRoller: Invalid die size: %d"), Sides);
		return -1;
	}

	// For now, use fallback until we implement HTTP/gRPC bridge
	// TODO: Implement actual server communication
	int32 Result = FallbackRoll(Sides);
	
	LogRoll(Sides, Result, EntityId, Context);
	
	return Result;
}

bool URpgDiceRoller::TestDiceFairness(int32 Sides, int32 SampleSize)
{
	// Perform basic fairness test using fallback rolling
	TMap<int32, int32> Distribution;
	
	// Initialize distribution map
	for (int32 i = 1; i <= Sides; i++)
	{
		Distribution.Add(i, 0);
	}
	
	// Perform test rolls
	for (int32 i = 0; i < SampleSize; i++)
	{
		int32 Roll = FallbackRoll(Sides);
		if (Distribution.Contains(Roll))
		{
			Distribution[Roll]++;
		}
	}
	
	// Simple fairness check - each face should appear roughly equally
	float Expected = (float)SampleSize / (float)Sides;
	float Tolerance = Expected * 0.2f; // 20% tolerance
	
	for (auto& Pair : Distribution)
	{
		float Actual = (float)Pair.Value;
		if (FMath::Abs(Actual - Expected) > Tolerance)
		{
			UE_LOG(LogTemp, Warning, TEXT("RpgDiceRoller: Fairness test failed for face %d: expected ~%.1f, got %d"), 
				   Pair.Key, Expected, Pair.Value);
			return false;
		}
	}
	
	UE_LOG(LogTemp, Log, TEXT("RpgDiceRoller: Fairness test passed for d%d with %d samples"), Sides, SampleSize);
	return true;
}

TArray<FString> URpgDiceRoller::GetRollHistory(const FString& EntityId, int32 Limit)
{
	TArray<FString> History;
	
	// TODO: Implement server communication to get actual history
	// For now, return placeholder data
	History.Add(FString::Printf(TEXT("d20: 15 (Context: Attack)")));
	History.Add(FString::Printf(TEXT("d6: 4 (Context: Damage)")));
	History.Add(FString::Printf(TEXT("d20: 8 (Context: Saving_Throw)")));
	
	return History;
}

void URpgDiceRoller::SetServerUrl(const FString& NewServerUrl)
{
	ServerUrl = NewServerUrl;
	UE_LOG(LogTemp, Log, TEXT("RpgDiceRoller: Server URL set to %s"), *ServerUrl);
}

bool URpgDiceRoller::TestConnection()
{
	// TODO: Implement actual connection test to gRPC server
	// For now, always return true since we're using fallback
	UE_LOG(LogTemp, Log, TEXT("RpgDiceRoller: Connection test - using fallback dice rolling"));
	return true;
}

int32 URpgDiceRoller::FallbackRoll(int32 Sides)
{
	// Use UE's secure random number generator
	return FMath::RandRange(1, Sides);
}


void URpgDiceRoller::LogRoll(int32 Sides, int32 Result, const FString& EntityId, const FString& Context)
{
	UE_LOG(LogTemp, Log, TEXT("🎲 RPG Dice Roll: d%d = %d [Entity: %s, Context: %s]"), 
		   Sides, Result, *EntityId, *Context);
	
	// Also display on screen for debugging
	if (GEngine)
	{
		FString Message = FString::Printf(TEXT("🎲 d%d = %d (%s: %s)"), 
										  Sides, Result, *EntityId, *Context);
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Cyan, Message);
	}
}