// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

// Forward declarations only - no protobuf headers in this file
struct FRPGDiceRollRequest;
struct FRPGDiceRollResponse;

// S001: Protobuf converter interface - completely isolates protobuf from UE headers
class SESHAT_API FRPGProtobufConverter
{
public:
    // Convert UE types to serialized protobuf data
    static TArray<uint8> SerializeRollRequest(const FRPGDiceRollRequest& Request);
    static bool DeserializeRollResponse(const TArray<uint8>& Data, FRPGDiceRollResponse& Response);
    
    // Validate protobuf data without exposing protobuf types
    static bool IsValidRollRequestData(const TArray<uint8>& Data);
    static bool IsValidRollResponseData(const TArray<uint8>& Data);
};