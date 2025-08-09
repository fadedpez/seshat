// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Http.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "GRPCWeb/RPGWebTypes.h"
#include "RPGWebClient.generated.h"

// Forward declarations
class FHttpModule;

/**
 * Delegate for async gRPC-Web responses
 * S001 Phase 2: Blueprint-accessible async callbacks
 */
DECLARE_DYNAMIC_DELEGATE_TwoParams(FRPGWebResponseDelegate, bool, bSuccess, const FRPGWebResponse&, Response);

/**
 * Delegate for dice roll responses
 */
DECLARE_DYNAMIC_DELEGATE_TwoParams(FRPGDiceRollDelegate, bool, bSuccess, const FRPGDiceRollResponse&, Response);

/**
 * Base gRPC-Web HTTP client for rpg-api communication
 * S001 Phase 2: gRPC-Web HTTP Integration - Base Client
 */
UCLASS(BlueprintType, Blueprintable)
class SESHAT_API URPGWebClient : public UObject
{
	GENERATED_BODY()

public:
	URPGWebClient();
	virtual ~URPGWebClient();

	/**
	 * Initialize the client with server configuration
	 */
	UFUNCTION(BlueprintCallable, Category = "RPG Web Client")
	void Initialize(const FString& InServerUrl = TEXT("http://localhost:80"));

	/**
	 * Get the current server URL
	 */
	UFUNCTION(BlueprintPure, Category = "RPG Web Client")
	FString GetServerUrl() const { return ServerUrl; }

	/**
	 * Check if client is properly initialized
	 */
	UFUNCTION(BlueprintPure, Category = "RPG Web Client")
	bool IsInitialized() const { return bIsInitialized; }

	/**
	 * Call api.v1alpha1.DiceService/RollDice - direct proto contract implementation
	 */
	UFUNCTION(BlueprintCallable, Category = "RPG Web Client")
	void RollDice(const FRPGDiceRollRequest& Request, FRPGDiceRollDelegate OnComplete);

	/**
	 * Simple test function - call dice service and log results to console
	 */
	UFUNCTION(BlueprintCallable, Category = "RPG Web Client")
	void TestDiceRoll();

protected:
	/**
	 * Send a gRPC-Web request with pre-serialized protobuf data
	 * S001: Core HTTP+protobuf communication pattern (now isolated from protobuf headers)
	 */
	void SendGRPCWebRequest(
		const FString& ServicePath,
		const TArray<uint8>& RequestData,
		TFunction<void(bool, const TArray<uint8>&, const FRPGWebResponse&)> OnComplete
	);

	/**
	 * Parse gRPC-Web HTTP response 
	 * S001: Handle gRPC-Web wire format
	 */
	bool ParseGRPCWebResponse(
		FHttpResponsePtr Response,
		TArray<uint8>& OutMessageData,
		FRPGWebResponse& OutWebResponse
	);

	// S001: SerializeMessage removed - using isolated converter now

	/**
	 * Handle HTTP request completion
	 */
	void OnHttpRequestComplete(
		FHttpRequestPtr Request,
		FHttpResponsePtr Response,
		bool bWasSuccessful,
		TFunction<void(bool, const TArray<uint8>&, const FRPGWebResponse&)> OnComplete
	);

private:
	UPROPERTY()
	FString ServerUrl;

	UPROPERTY()
	bool bIsInitialized;

	// HTTP module reference
	FHttpModule* HttpModule;

	// Test callback for TestDiceRoll
	UFUNCTION()
	void OnTestDiceRollComplete(bool bSuccess, const FRPGDiceRollResponse& Response);
};