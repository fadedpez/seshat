// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

// Forward declarations only - no protobuf headers in this file
// S001: Character Service Types
struct FRPGCreateDraftRequest;
struct FRPGCreateDraftResponse;
struct FRPGGetDraftRequest;
struct FRPGGetDraftResponse;
struct FRPGUpdateNameRequest;
struct FRPGUpdateNameResponse;
struct FRPGUpdateRaceRequest;
struct FRPGUpdateRaceResponse;
struct FRPGUpdateClassRequest;
struct FRPGUpdateClassResponse;
struct FRPGUpdateAbilityScoresRequest;
struct FRPGUpdateAbilityScoresResponse;
struct FRPGListRacesRequest;
struct FRPGListRacesResponse;
struct FRPGListClassesRequest;
struct FRPGListClassesResponse;
struct FRPGRollAbilityScoresRequest;
struct FRPGRollAbilityScoresResponse;

/**
 * S001: CharacterService Protobuf converter - completely isolates protobuf from UE headers
 * Following proven DiceService pattern with manual binary serialization
 */
class SESHAT_API FRPGCharacterProtobufConverter
{
public:
    // Draft Management Methods
    static TArray<uint8> SerializeCreateDraftRequest(const FRPGCreateDraftRequest& Request);
    static bool DeserializeCreateDraftResponse(const TArray<uint8>& Data, FRPGCreateDraftResponse& Response);
    
    static TArray<uint8> SerializeGetDraftRequest(const FRPGGetDraftRequest& Request);
    static bool DeserializeGetDraftResponse(const TArray<uint8>& Data, FRPGGetDraftResponse& Response);

    // Draft Update Methods
    static TArray<uint8> SerializeUpdateNameRequest(const FRPGUpdateNameRequest& Request);
    static bool DeserializeUpdateNameResponse(const TArray<uint8>& Data, FRPGUpdateNameResponse& Response);
    
    static TArray<uint8> SerializeUpdateRaceRequest(const FRPGUpdateRaceRequest& Request);
    static bool DeserializeUpdateRaceResponse(const TArray<uint8>& Data, FRPGUpdateRaceResponse& Response);
    
    static TArray<uint8> SerializeUpdateClassRequest(const FRPGUpdateClassRequest& Request);
    static bool DeserializeUpdateClassResponse(const TArray<uint8>& Data, FRPGUpdateClassResponse& Response);
    
    static TArray<uint8> SerializeUpdateAbilityScoresRequest(const FRPGUpdateAbilityScoresRequest& Request);
    static bool DeserializeUpdateAbilityScoresResponse(const TArray<uint8>& Data, FRPGUpdateAbilityScoresResponse& Response);

    // Data Loading Methods
    static TArray<uint8> SerializeListRacesRequest(const FRPGListRacesRequest& Request);
    static bool DeserializeListRacesResponse(const TArray<uint8>& Data, FRPGListRacesResponse& Response);
    
    static TArray<uint8> SerializeListClassesRequest(const FRPGListClassesRequest& Request);
    static bool DeserializeListClassesResponse(const TArray<uint8>& Data, FRPGListClassesResponse& Response);
    
    // Dice Rolling Methods
    static TArray<uint8> SerializeRollAbilityScoresRequest(const FRPGRollAbilityScoresRequest& Request);
    static bool DeserializeRollAbilityScoresResponse(const TArray<uint8>& Data, FRPGRollAbilityScoresResponse& Response);
    
    // Validation helpers
    static bool IsValidCharacterRequestData(const TArray<uint8>& Data);
    static bool IsValidCharacterResponseData(const TArray<uint8>& Data);

private:
    // Helper functions for character-specific data structures
    static void SerializeAbilityScores(TArray<uint8>& Buffer, uint32 FieldNumber, const struct FRPGAbilityScores& AbilityScores);
    static bool ParseAbilityScores(const uint8* Data, int32 DataSize, struct FRPGAbilityScores& AbilityScores);
    
    static void SerializeRollAssignments(TArray<uint8>& Buffer, uint32 FieldNumber, const struct FRPGRollAssignments& RollAssignments);
    static bool ParseRollAssignments(const uint8* Data, int32 DataSize, struct FRPGRollAssignments& RollAssignments);
    
    static void SerializeCharacterDraft(TArray<uint8>& Buffer, uint32 FieldNumber, const struct FRPGCharacterDraft& Draft);
    static bool ParseCharacterDraft(const uint8* Data, int32 DataSize, struct FRPGCharacterDraft& Draft);
    
    static void SerializeRaceInfo(TArray<uint8>& Buffer, uint32 FieldNumber, const struct FRPGRaceInfo& RaceInfo);
    static bool ParseRaceInfo(const uint8* Data, int32 DataSize, struct FRPGRaceInfo& RaceInfo);
    
    static void SerializeClassInfo(TArray<uint8>& Buffer, uint32 FieldNumber, const struct FRPGClassInfo& ClassInfo);
    static bool ParseClassInfo(const uint8* Data, int32 DataSize, struct FRPGClassInfo& ClassInfo);
    
    static bool ParseAbilityScoreRoll(const uint8* Data, int32 DataSize, struct FRPGAbilityScoreRoll& Roll);
};