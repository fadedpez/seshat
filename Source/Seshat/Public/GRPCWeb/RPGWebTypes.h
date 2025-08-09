// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RPGWebTypes.generated.h"

/**
 * UE-friendly wrapper for dice roll requests
 * S001 Phase 2: gRPC-Web HTTP Integration - UE Type Wrappers
 */
USTRUCT(BlueprintType)
struct SESHAT_API FRPGDiceRollRequest
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dice")
	int32 Sides = 20;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dice")
	int32 Count = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dice")
	int32 Modifier = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dice")
	FString SessionId;

	FRPGDiceRollRequest() = default;
	
	// S001: Isolated conversion methods - no protobuf types exposed
	TArray<uint8> SerializeToProtobuf() const;
	
	// Legacy conversion functions (deprecated, kept for compatibility)
	void ToProtobuf(void* OutRequest) const;
	void FromProtobuf(const void* InRequest);
};

/**
 * UE-friendly wrapper for dice roll responses
 */
USTRUCT(BlueprintType)
struct SESHAT_API FRPGDiceRollResponse
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dice")
	TArray<int32> Results;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dice")
	int32 Total = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dice")
	int32 Modifier = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dice")
	FString SessionId;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dice")
	bool bSuccess = false;

	FRPGDiceRollResponse() = default;

	// S001: Isolated conversion methods - no protobuf types exposed
	bool DeserializeFromProtobuf(const TArray<uint8>& Data);

	// Legacy conversion functions (deprecated, kept for compatibility)
	void ToProtobuf(void* OutResponse) const;
	void FromProtobuf(const void* InResponse);
};

/**
 * HTTP response wrapper for gRPC-Web calls
 * S001: Standardized HTTP response handling
 */
USTRUCT(BlueprintType)
struct SESHAT_API FRPGWebResponse
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Response")
	int32 StatusCode = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Response")
	FString StatusMessage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Response")
	bool bSuccess = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Response")
	FString ErrorMessage;

	FRPGWebResponse() = default;
};