// Copyright Epic Games, Inc. All Rights Reserved.

#include "GRPCWeb/RPGWebTypes.h"
#include "RPGProtobufConverter.h"

// S001: Use isolated converter instead of direct protobuf includes
// This eliminates all UE/protobuf macro conflicts

void FRPGDiceRollRequest::ToProtobuf(void* OutRequest) const
{
	// Legacy function - conversion now happens through isolated converter
	UE_LOG(LogTemp, Warning, TEXT("FRPGDiceRollRequest::ToProtobuf is deprecated, use SerializeToProtobuf instead"));
}

void FRPGDiceRollRequest::FromProtobuf(const void* InRequest)
{
	// Legacy function - conversion now happens through isolated converter
	UE_LOG(LogTemp, Warning, TEXT("FRPGDiceRollRequest::FromProtobuf is deprecated, use SerializeToProtobuf instead"));
}

void FRPGDiceRollResponse::ToProtobuf(void* OutResponse) const
{
	// Legacy function - conversion now happens through isolated converter
	UE_LOG(LogTemp, Warning, TEXT("FRPGDiceRollResponse::ToProtobuf is deprecated, use DeserializeFromProtobuf instead"));
}

void FRPGDiceRollResponse::FromProtobuf(const void* InResponse)
{
	// Legacy function - conversion now happens through isolated converter
	UE_LOG(LogTemp, Warning, TEXT("FRPGDiceRollResponse::FromProtobuf is deprecated, use DeserializeFromProtobuf instead"));
}

// S001: New isolated conversion methods
TArray<uint8> FRPGDiceRollRequest::SerializeToProtobuf() const
{
	return FRPGProtobufConverter::SerializeRollRequest(*this);
}

bool FRPGDiceRollResponse::DeserializeFromProtobuf(const TArray<uint8>& Data)
{
	return FRPGProtobufConverter::DeserializeRollResponse(Data, *this);
}