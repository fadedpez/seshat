// Copyright Epic Games, Inc. All Rights Reserved.

#include "GRPCWeb/RPGWebClient.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "RPGProtobufConverter.h"

// S001: No longer need protobuf includes - using isolated converter

URPGWebClient::URPGWebClient()
	: ServerUrl(TEXT("http://localhost:80"))
	, bIsInitialized(false)
	, HttpModule(nullptr)
{
}

URPGWebClient::~URPGWebClient()
{
	// Clean shutdown
	bIsInitialized = false;
	HttpModule = nullptr;
}

void URPGWebClient::Initialize(const FString& InServerUrl)
{
	ServerUrl = InServerUrl;
	HttpModule = &FHttpModule::Get();
	bIsInitialized = (HttpModule != nullptr);

	if (bIsInitialized)
	{
		UE_LOG(LogTemp, Log, TEXT("RPGWebClient initialized with server: %s"), *ServerUrl);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to initialize RPGWebClient - HTTP module not available"));
	}
}

void URPGWebClient::SendGRPCWebRequest(
	const FString& ServicePath,
	const TArray<uint8>& RequestData,
	TFunction<void(bool, const TArray<uint8>&, const FRPGWebResponse&)> OnComplete)
{
	if (!bIsInitialized)
	{
		UE_LOG(LogTemp, Error, TEXT("RPGWebClient not initialized"));
		FRPGWebResponse ErrorResponse;
		ErrorResponse.bSuccess = false;
		ErrorResponse.StatusCode = 0;
		ErrorResponse.ErrorMessage = TEXT("Client not initialized");
		OnComplete(false, TArray<uint8>(), ErrorResponse);
		return;
	}

	// Create HTTP request
	TSharedRef<IHttpRequest> HttpRequest = HttpModule->CreateRequest();
	
	// S001: gRPC-Web HTTP configuration
	HttpRequest->SetURL(ServerUrl + ServicePath);
	HttpRequest->SetVerb(TEXT("POST"));
	HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/grpc-web+proto"));
	HttpRequest->SetHeader(TEXT("Accept"), TEXT("application/grpc-web+proto"));
	
	// Use pre-serialized request data
	const TArray<uint8>& MessageData = RequestData;
	
	// S001: gRPC-Web wire format - Length-Prefixed Message
	// Format: [Compressed-Flag][Length][Message]
	TArray<uint8> RequestBody;
	RequestBody.Add(0); // Compressed-Flag: 0 = not compressed
	
	// Length (4 bytes, big-endian)
	int32 MessageLength = MessageData.Num();
	RequestBody.Add((MessageLength >> 24) & 0xFF);
	RequestBody.Add((MessageLength >> 16) & 0xFF);
	RequestBody.Add((MessageLength >> 8) & 0xFF);
	RequestBody.Add(MessageLength & 0xFF);
	
	// Message data
	RequestBody.Append(MessageData);
	
	HttpRequest->SetContent(RequestBody);

	// Bind completion callback
	HttpRequest->OnProcessRequestComplete().BindLambda(
		[this, OnComplete](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
		{
			OnHttpRequestComplete(Request, Response, bWasSuccessful, OnComplete);
		}
	);

	// Send the request
	if (!HttpRequest->ProcessRequest())
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to send HTTP request to %s"), *ServicePath);
		FRPGWebResponse ErrorResponse;
		ErrorResponse.bSuccess = false;
		ErrorResponse.StatusCode = 0;
		ErrorResponse.ErrorMessage = TEXT("Failed to send HTTP request");
		OnComplete(false, TArray<uint8>(), ErrorResponse);
	}
}

bool URPGWebClient::ParseGRPCWebResponse(
	FHttpResponsePtr Response,
	TArray<uint8>& OutMessageData,
	FRPGWebResponse& OutWebResponse)
{
	OutWebResponse.StatusCode = Response->GetResponseCode();
	OutWebResponse.StatusMessage = FString::Printf(TEXT("%d"), OutWebResponse.StatusCode);

	if (!EHttpResponseCodes::IsOk(OutWebResponse.StatusCode))
	{
		OutWebResponse.bSuccess = false;
		OutWebResponse.ErrorMessage = FString::Printf(TEXT("HTTP %d"), OutWebResponse.StatusCode);
		return false;
	}

	// Parse gRPC-Web response format
	TArray<uint8> ResponseData = Response->GetContent();
	
	if (ResponseData.Num() < 5) // Minimum: 1 byte flag + 4 bytes length
	{
		OutWebResponse.bSuccess = false;
		OutWebResponse.ErrorMessage = TEXT("Invalid gRPC-Web response format");
		return false;
	}

	// Parse gRPC-Web wire format
	uint8 CompressedFlag = ResponseData[0];
	
	// Extract message length (4 bytes, big-endian)
	int32 MessageLength = 
		(ResponseData[1] << 24) |
		(ResponseData[2] << 16) |
		(ResponseData[3] << 8) |
		ResponseData[4];

	if (ResponseData.Num() < 5 + MessageLength)
	{
		OutWebResponse.bSuccess = false;
		OutWebResponse.ErrorMessage = TEXT("Incomplete gRPC-Web response");
		return false;
	}

	// Extract message data
	OutMessageData.Empty();
	OutMessageData.Append(ResponseData.GetData() + 5, MessageLength);

	OutWebResponse.bSuccess = true;
	return true;
}

// S001: SerializeMessage removed - now using isolated converter

void URPGWebClient::OnHttpRequestComplete(
	FHttpRequestPtr Request,
	FHttpResponsePtr Response,
	bool bWasSuccessful,
	TFunction<void(bool, const TArray<uint8>&, const FRPGWebResponse&)> OnComplete)
{
	FRPGWebResponse WebResponse;
	TArray<uint8> MessageData;
	bool bSuccess = false;

	if (bWasSuccessful && Response.IsValid())
	{
		bSuccess = ParseGRPCWebResponse(Response, MessageData, WebResponse);
	}
	else
	{
		WebResponse.bSuccess = false;
		WebResponse.StatusCode = Response.IsValid() ? Response->GetResponseCode() : 0;
		WebResponse.ErrorMessage = TEXT("HTTP request failed");
	}

	// Call completion callback
	OnComplete(bSuccess, MessageData, WebResponse);
}

void URPGWebClient::RollDice(const FRPGDiceRollRequest& Request, FRPGDiceRollDelegate OnComplete)
{
	// Serialize request using manual protobuf converter
	TArray<uint8> RequestData = FRPGProtobufConverter::SerializeRollRequest(Request);
	
	// Call the exact proto contract: api.v1alpha1.DiceService/RollDice (via nginx to Envoy)
	SendGRPCWebRequest(
		TEXT("/api.v1alpha1.DiceService/RollDice"),
		RequestData,
		[OnComplete](bool bSuccess, const TArray<uint8>& ResponseData, const FRPGWebResponse& WebResponse)
		{
			FRPGDiceRollResponse DiceResponse;
			
			UE_LOG(LogTemp, Warning, TEXT("HTTP callback: bSuccess=%s, StatusCode=%d, ResponseSize=%d"), 
				bSuccess ? TEXT("true") : TEXT("false"), WebResponse.StatusCode, ResponseData.Num());
			
			if (bSuccess && !ResponseData.IsEmpty())
			{
				// Deserialize response using manual protobuf converter
				bool bParseSuccess = FRPGProtobufConverter::DeserializeRollResponse(ResponseData, DiceResponse);
				UE_LOG(LogTemp, Warning, TEXT("Protobuf parse success: %s"), bParseSuccess ? TEXT("true") : TEXT("false"));
				bSuccess = bParseSuccess;
			}
			else if (!bSuccess)
			{
				UE_LOG(LogTemp, Error, TEXT("HTTP request failed: %s"), *WebResponse.ErrorMessage);
			}
			else if (ResponseData.IsEmpty())
			{
				UE_LOG(LogTemp, Error, TEXT("HTTP response was empty"));
			}
			
			// Execute Blueprint delegate
			OnComplete.ExecuteIfBound(bSuccess, DiceResponse);
		}
	);
}

void URPGWebClient::TestDiceRoll()
{
	UE_LOG(LogTemp, Warning, TEXT("TestDiceRoll called"));
	
	if (!bIsInitialized)
	{
		UE_LOG(LogTemp, Error, TEXT("WebClient not initialized"));
		return;
	}

	// Create a simple test request: roll 1d20
	FRPGDiceRollRequest TestRequest;
	TestRequest.Sides = 20;
	TestRequest.Count = 1;
	TestRequest.Modifier = 0;
	TestRequest.SessionId = TEXT("test-session-123");

	UE_LOG(LogTemp, Warning, TEXT("Sending test dice roll: 1d20"));

	// Create a simple delegate that logs results
	FRPGDiceRollDelegate TestDelegate;
	TestDelegate.BindUFunction(this, FName("OnTestDiceRollComplete"));

	RollDice(TestRequest, TestDelegate);
}

UFUNCTION()
void URPGWebClient::OnTestDiceRollComplete(bool bSuccess, const FRPGDiceRollResponse& Response)
{
	if (bSuccess)
	{
		UE_LOG(LogTemp, Warning, TEXT("Dice roll SUCCESS! Total: %d"), Response.Total);
		for (int32 i = 0; i < Response.Results.Num(); i++)
		{
			UE_LOG(LogTemp, Warning, TEXT("Die %d: %d"), i + 1, Response.Results[i]);
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Dice roll FAILED - HTTP or parsing error"));
	}
}