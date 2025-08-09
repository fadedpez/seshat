// Copyright Epic Games, Inc. All Rights Reserved.

#include "RPGCharacterProtobufConverter.h"
#include "Services/RPGCharacterTypes.h"

// S001: Manual protobuf wire format implementation for CharacterService - NO C++ protobuf library
// Following proven DiceService pattern with binary protobuf serialization

namespace RPGCharacterProtobuf
{
    // Protobuf wire format constants (reuse from DiceService)
    enum WireType : uint8
    {
        VARINT = 0,      // int32, int64, uint32, uint64, sint32, sint64, bool, enum
        FIXED64 = 1,     // fixed64, sfixed64, double
        LENGTH_DELIMITED = 2, // string, bytes, embedded messages, repeated packed numeric
        START_GROUP = 3, // deprecated
        END_GROUP = 4,   // deprecated
        FIXED32 = 5      // fixed32, sfixed32, float
    };

    // Core protobuf encoding functions (same as DiceService)
    static void WriteVarint(TArray<uint8>& Buffer, uint64 Value)
    {
        while (Value >= 0x80)
        {
            Buffer.Add(static_cast<uint8>((Value & 0x7F) | 0x80));
            Value >>= 7;
        }
        Buffer.Add(static_cast<uint8>(Value & 0x7F));
    }

    static void WriteFieldHeader(TArray<uint8>& Buffer, uint32 FieldNumber, WireType Type)
    {
        uint32 Tag = (FieldNumber << 3) | Type;
        WriteVarint(Buffer, Tag);
    }

    static void WriteStringField(TArray<uint8>& Buffer, uint32 FieldNumber, const FString& Value)
    {
        if (Value.IsEmpty())
        {
            return; // Skip empty strings (proto3 default behavior)
        }

        // Convert to UTF-8
        FTCHARToUTF8 UTF8String(*Value);
        const uint8* UTF8Data = reinterpret_cast<const uint8*>(UTF8String.Get());
        int32 UTF8Length = UTF8String.Length();

        // Write field header
        WriteFieldHeader(Buffer, FieldNumber, LENGTH_DELIMITED);
        
        // Write string length
        WriteVarint(Buffer, UTF8Length);
        
        // Write string data
        for (int32 i = 0; i < UTF8Length; ++i)
        {
            Buffer.Add(UTF8Data[i]);
        }
    }

    static void WriteInt32Field(TArray<uint8>& Buffer, uint32 FieldNumber, int32 Value)
    {
        if (Value == 0)
        {
            return; // Skip zero values (proto3 default behavior)
        }

        WriteFieldHeader(Buffer, FieldNumber, VARINT);
        WriteVarint(Buffer, static_cast<uint32>(Value));
    }

    static void WriteEnumField(TArray<uint8>& Buffer, uint32 FieldNumber, int32 EnumValue)
    {
        if (EnumValue == 0)
        {
            return; // Skip default enum values
        }

        WriteFieldHeader(Buffer, FieldNumber, VARINT);
        WriteVarint(Buffer, static_cast<uint32>(EnumValue));
    }

    // Core protobuf reading functions (same as DiceService)
    static bool ReadVarint(const uint8* Data, int32 DataSize, int32& Offset, uint64& Value)
    {
        Value = 0;
        int32 Shift = 0;
        
        while (Offset < DataSize)
        {
            uint8 Byte = Data[Offset++];
            Value |= (static_cast<uint64>(Byte & 0x7F) << Shift);
            
            if ((Byte & 0x80) == 0)
            {
                return true; // End of varint
            }
            
            Shift += 7;
            if (Shift >= 64)
            {
                return false; // Varint too long
            }
        }
        
        return false; // Unexpected end of data
    }

    static bool ReadString(const uint8* Data, int32 DataSize, int32& Offset, FString& Value)
    {
        uint64 Length;
        if (!ReadVarint(Data, DataSize, Offset, Length))
        {
            return false;
        }

        if (Offset + static_cast<int32>(Length) > DataSize)
        {
            return false; // Not enough data
        }

        // Convert from UTF-8 to FString
        FUTF8ToTCHAR TCHARData(reinterpret_cast<const ANSICHAR*>(Data + Offset), static_cast<int32>(Length));
        Value = FString(TCHARData.Length(), TCHARData.Get());
        
        Offset += static_cast<int32>(Length);
        return true;
    }
}

// S001: CharacterService Implementation

TArray<uint8> FRPGCharacterProtobufConverter::SerializeCreateDraftRequest(const FRPGCreateDraftRequest& Request)
{
    TArray<uint8> Buffer;
    Buffer.Reserve(256);

    // Field 1: player_id (string)
    RPGCharacterProtobuf::WriteStringField(Buffer, 1, Request.PlayerId);

    // Field 2: session_id (string) - optional
    RPGCharacterProtobuf::WriteStringField(Buffer, 2, Request.SessionId);

    return Buffer;
}

bool FRPGCharacterProtobufConverter::DeserializeCreateDraftResponse(const TArray<uint8>& Data, FRPGCreateDraftResponse& Response)
{
    if (Data.Num() == 0)
    {
        return false;
    }

    Response.bSuccess = false;
    int32 Offset = 0;
    const uint8* DataPtr = Data.GetData();

    // Parse CreateDraftResponse message
    while (Offset < Data.Num())
    {
        uint64 Tag;
        if (!RPGCharacterProtobuf::ReadVarint(DataPtr, Data.Num(), Offset, Tag))
        {
            return false;
        }

        uint32 FieldNumber = static_cast<uint32>(Tag >> 3);
        RPGCharacterProtobuf::WireType Type = static_cast<RPGCharacterProtobuf::WireType>(Tag & 0x07);

        switch (FieldNumber)
        {
        case 1: // draft (CharacterDraft)
            if (Type == RPGCharacterProtobuf::LENGTH_DELIMITED)
            {
                uint64 MessageLength;
                if (!RPGCharacterProtobuf::ReadVarint(DataPtr, Data.Num(), Offset, MessageLength))
                {
                    return false;
                }

                if (!ParseCharacterDraft(DataPtr + Offset, static_cast<int32>(MessageLength), Response.Draft))
                {
                    return false;
                }

                Offset += static_cast<int32>(MessageLength);
                Response.bSuccess = true;
            }
            break;

        default:
            // Skip unknown fields
            if (Type == RPGCharacterProtobuf::VARINT)
            {
                uint64 Value;
                if (!RPGCharacterProtobuf::ReadVarint(DataPtr, Data.Num(), Offset, Value))
                {
                    return false;
                }
            }
            else if (Type == RPGCharacterProtobuf::LENGTH_DELIMITED)
            {
                uint64 Length;
                if (!RPGCharacterProtobuf::ReadVarint(DataPtr, Data.Num(), Offset, Length))
                {
                    return false;
                }
                Offset += static_cast<int32>(Length);
            }
            break;
        }
    }

    return Response.bSuccess;
}

TArray<uint8> FRPGCharacterProtobufConverter::SerializeGetDraftRequest(const FRPGGetDraftRequest& Request)
{
    TArray<uint8> Buffer;
    Buffer.Reserve(128);

    // Field 1: draft_id (string)
    RPGCharacterProtobuf::WriteStringField(Buffer, 1, Request.DraftId);

    return Buffer;
}

bool FRPGCharacterProtobufConverter::DeserializeGetDraftResponse(const TArray<uint8>& Data, FRPGGetDraftResponse& Response)
{
    // Same structure as CreateDraftResponse
    FRPGCreateDraftResponse CreateResponse;
    bool bResult = DeserializeCreateDraftResponse(Data, CreateResponse);
    
    Response.Draft = CreateResponse.Draft;
    Response.bSuccess = CreateResponse.bSuccess;
    
    return bResult;
}

TArray<uint8> FRPGCharacterProtobufConverter::SerializeUpdateNameRequest(const FRPGUpdateNameRequest& Request)
{
    TArray<uint8> Buffer;
    Buffer.Reserve(256);

    // Field 1: draft_id (string)
    RPGCharacterProtobuf::WriteStringField(Buffer, 1, Request.DraftId);

    // Field 2: name (string)
    RPGCharacterProtobuf::WriteStringField(Buffer, 2, Request.Name);

    return Buffer;
}

bool FRPGCharacterProtobufConverter::DeserializeUpdateNameResponse(const TArray<uint8>& Data, FRPGUpdateNameResponse& Response)
{
    // Same structure as CreateDraftResponse - all update responses have same format
    FRPGCreateDraftResponse CreateResponse;
    bool bResult = DeserializeCreateDraftResponse(Data, CreateResponse);
    
    Response.Draft = CreateResponse.Draft;
    Response.bSuccess = CreateResponse.bSuccess;
    
    return bResult;
}

TArray<uint8> FRPGCharacterProtobufConverter::SerializeUpdateRaceRequest(const FRPGUpdateRaceRequest& Request)
{
    TArray<uint8> Buffer;
    Buffer.Reserve(256);

    // Field 1: draft_id (string)
    RPGCharacterProtobuf::WriteStringField(Buffer, 1, Request.DraftId);

    // Field 2: race (enum)
    RPGCharacterProtobuf::WriteEnumField(Buffer, 2, static_cast<int32>(Request.Race));

    // Field 3: subrace (enum) - optional
    RPGCharacterProtobuf::WriteEnumField(Buffer, 3, static_cast<int32>(Request.Subrace));

    return Buffer;
}

bool FRPGCharacterProtobufConverter::DeserializeUpdateRaceResponse(const TArray<uint8>& Data, FRPGUpdateRaceResponse& Response)
{
    // Same structure as CreateDraftResponse
    FRPGCreateDraftResponse CreateResponse;
    bool bResult = DeserializeCreateDraftResponse(Data, CreateResponse);
    
    Response.Draft = CreateResponse.Draft;
    Response.bSuccess = CreateResponse.bSuccess;
    
    return bResult;
}

TArray<uint8> FRPGCharacterProtobufConverter::SerializeUpdateClassRequest(const FRPGUpdateClassRequest& Request)
{
    TArray<uint8> Buffer;
    Buffer.Reserve(256);

    // Field 1: draft_id (string)
    RPGCharacterProtobuf::WriteStringField(Buffer, 1, Request.DraftId);

    // Field 2: class (enum)
    RPGCharacterProtobuf::WriteEnumField(Buffer, 2, static_cast<int32>(Request.Class));

    return Buffer;
}

bool FRPGCharacterProtobufConverter::DeserializeUpdateClassResponse(const TArray<uint8>& Data, FRPGUpdateClassResponse& Response)
{
    // Same structure as CreateDraftResponse
    FRPGCreateDraftResponse CreateResponse;
    bool bResult = DeserializeCreateDraftResponse(Data, CreateResponse);
    
    Response.Draft = CreateResponse.Draft;
    Response.bSuccess = CreateResponse.bSuccess;
    
    return bResult;
}

TArray<uint8> FRPGCharacterProtobufConverter::SerializeUpdateAbilityScoresRequest(const FRPGUpdateAbilityScoresRequest& Request)
{
    TArray<uint8> Buffer;
    Buffer.Reserve(256);

    // Field 1: draft_id (string)
    RPGCharacterProtobuf::WriteStringField(Buffer, 1, Request.DraftId);

    // Oneof scores_input: either ability_scores (field 2) OR roll_assignments (field 3)
    if (Request.bUseRollAssignments)
    {
        // Field 3: roll_assignments (RollAssignments message) - server preferred method
        SerializeRollAssignments(Buffer, 3, Request.RollAssignments);
    }
    else
    {
        // Field 2: ability_scores (AbilityScores message) - legacy method
        SerializeAbilityScores(Buffer, 2, Request.AbilityScores);
    }

    return Buffer;
}

bool FRPGCharacterProtobufConverter::DeserializeUpdateAbilityScoresResponse(const TArray<uint8>& Data, FRPGUpdateAbilityScoresResponse& Response)
{
    // Same structure as CreateDraftResponse
    FRPGCreateDraftResponse CreateResponse;
    bool bResult = DeserializeCreateDraftResponse(Data, CreateResponse);
    
    Response.Draft = CreateResponse.Draft;
    Response.bSuccess = CreateResponse.bSuccess;
    
    return bResult;
}

TArray<uint8> FRPGCharacterProtobufConverter::SerializeListRacesRequest(const FRPGListRacesRequest& Request)
{
    TArray<uint8> Buffer;
    Buffer.Reserve(256);

    // Field 1: page_size (int32)
    RPGCharacterProtobuf::WriteInt32Field(Buffer, 1, Request.PageSize);

    // Field 2: page_token (string)
    RPGCharacterProtobuf::WriteStringField(Buffer, 2, Request.PageToken);

    // Field 3: include_subraces (bool) - for simplicity, we'll omit bool fields for now

    return Buffer;
}

bool FRPGCharacterProtobufConverter::DeserializeListRacesResponse(const TArray<uint8>& Data, FRPGListRacesResponse& Response)
{
    if (Data.Num() == 0)
    {
        return false;
    }

    Response.bSuccess = false;
    Response.Races.Empty();
    int32 Offset = 0;
    const uint8* DataPtr = Data.GetData();

    while (Offset < Data.Num())
    {
        uint64 Tag;
        if (!RPGCharacterProtobuf::ReadVarint(DataPtr, Data.Num(), Offset, Tag))
        {
            return false;
        }

        uint32 FieldNumber = static_cast<uint32>(Tag >> 3);
        RPGCharacterProtobuf::WireType Type = static_cast<RPGCharacterProtobuf::WireType>(Tag & 0x07);

        switch (FieldNumber)
        {
        case 1: // races (repeated RaceInfo)
            if (Type == RPGCharacterProtobuf::LENGTH_DELIMITED)
            {
                uint64 MessageLength;
                if (!RPGCharacterProtobuf::ReadVarint(DataPtr, Data.Num(), Offset, MessageLength))
                {
                    return false;
                }

                FRPGRaceInfo RaceInfo;
                if (!ParseRaceInfo(DataPtr + Offset, static_cast<int32>(MessageLength), RaceInfo))
                {
                    return false;
                }

                Response.Races.Add(RaceInfo);
                Offset += static_cast<int32>(MessageLength);
            }
            break;

        case 2: // next_page_token (string)
            if (Type == RPGCharacterProtobuf::LENGTH_DELIMITED)
            {
                if (!RPGCharacterProtobuf::ReadString(DataPtr, Data.Num(), Offset, Response.NextPageToken))
                {
                    return false;
                }
            }
            break;

        case 3: // total_size (int32)
            if (Type == RPGCharacterProtobuf::VARINT)
            {
                uint64 Value;
                if (!RPGCharacterProtobuf::ReadVarint(DataPtr, Data.Num(), Offset, Value))
                {
                    return false;
                }
                Response.TotalSize = static_cast<int32>(Value);
            }
            break;

        default:
            // Skip unknown fields
            if (Type == RPGCharacterProtobuf::VARINT)
            {
                uint64 Value;
                if (!RPGCharacterProtobuf::ReadVarint(DataPtr, Data.Num(), Offset, Value))
                {
                    return false;
                }
            }
            else if (Type == RPGCharacterProtobuf::LENGTH_DELIMITED)
            {
                uint64 Length;
                if (!RPGCharacterProtobuf::ReadVarint(DataPtr, Data.Num(), Offset, Length))
                {
                    return false;
                }
                Offset += static_cast<int32>(Length);
            }
            break;
        }
    }

    Response.bSuccess = true;
    return true;
}

TArray<uint8> FRPGCharacterProtobufConverter::SerializeListClassesRequest(const FRPGListClassesRequest& Request)
{
    TArray<uint8> Buffer;
    Buffer.Reserve(256);

    // Field 1: page_size (int32)
    RPGCharacterProtobuf::WriteInt32Field(Buffer, 1, Request.PageSize);

    // Field 2: page_token (string)
    RPGCharacterProtobuf::WriteStringField(Buffer, 2, Request.PageToken);

    return Buffer;
}

bool FRPGCharacterProtobufConverter::DeserializeListClassesResponse(const TArray<uint8>& Data, FRPGListClassesResponse& Response)
{
    // Similar structure to ListRacesResponse
    if (Data.Num() == 0)
    {
        return false;
    }

    Response.bSuccess = false;
    Response.Classes.Empty();
    int32 Offset = 0;
    const uint8* DataPtr = Data.GetData();

    while (Offset < Data.Num())
    {
        uint64 Tag;
        if (!RPGCharacterProtobuf::ReadVarint(DataPtr, Data.Num(), Offset, Tag))
        {
            return false;
        }

        uint32 FieldNumber = static_cast<uint32>(Tag >> 3);
        RPGCharacterProtobuf::WireType Type = static_cast<RPGCharacterProtobuf::WireType>(Tag & 0x07);

        switch (FieldNumber)
        {
        case 1: // classes (repeated ClassInfo)
            if (Type == RPGCharacterProtobuf::LENGTH_DELIMITED)
            {
                uint64 MessageLength;
                if (!RPGCharacterProtobuf::ReadVarint(DataPtr, Data.Num(), Offset, MessageLength))
                {
                    return false;
                }

                FRPGClassInfo ClassInfo;
                if (!ParseClassInfo(DataPtr + Offset, static_cast<int32>(MessageLength), ClassInfo))
                {
                    return false;
                }

                Response.Classes.Add(ClassInfo);
                Offset += static_cast<int32>(MessageLength);
            }
            break;

        case 2: // next_page_token (string)
            if (Type == RPGCharacterProtobuf::LENGTH_DELIMITED)
            {
                if (!RPGCharacterProtobuf::ReadString(DataPtr, Data.Num(), Offset, Response.NextPageToken))
                {
                    return false;
                }
            }
            break;

        case 3: // total_size (int32)
            if (Type == RPGCharacterProtobuf::VARINT)
            {
                uint64 Value;
                if (!RPGCharacterProtobuf::ReadVarint(DataPtr, Data.Num(), Offset, Value))
                {
                    return false;
                }
                Response.TotalSize = static_cast<int32>(Value);
            }
            break;

        default:
            // Skip unknown fields
            if (Type == RPGCharacterProtobuf::VARINT)
            {
                uint64 Value;
                if (!RPGCharacterProtobuf::ReadVarint(DataPtr, Data.Num(), Offset, Value))
                {
                    return false;
                }
            }
            else if (Type == RPGCharacterProtobuf::LENGTH_DELIMITED)
            {
                uint64 Length;
                if (!RPGCharacterProtobuf::ReadVarint(DataPtr, Data.Num(), Offset, Length))
                {
                    return false;
                }
                Offset += static_cast<int32>(Length);
            }
            break;
        }
    }

    Response.bSuccess = true;
    return true;
}

bool FRPGCharacterProtobufConverter::IsValidCharacterRequestData(const TArray<uint8>& Data)
{
    if (Data.Num() == 0)
    {
        return false;
    }

    // Simple validation: try to parse at least one field
    int32 Offset = 0;
    uint64 Tag;
    return RPGCharacterProtobuf::ReadVarint(Data.GetData(), Data.Num(), Offset, Tag);
}

bool FRPGCharacterProtobufConverter::IsValidCharacterResponseData(const TArray<uint8>& Data)
{
    if (Data.Num() == 0)
    {
        return false;
    }

    // Simple validation: try to parse at least one field
    int32 Offset = 0;
    uint64 Tag;
    return RPGCharacterProtobuf::ReadVarint(Data.GetData(), Data.Num(), Offset, Tag);
}

// Helper function implementations

void FRPGCharacterProtobufConverter::SerializeAbilityScores(TArray<uint8>& Buffer, uint32 FieldNumber, const FRPGAbilityScores& AbilityScores)
{
    // Calculate size of AbilityScores message
    TArray<uint8> AbilityBuffer;
    
    // Field 1: strength
    RPGCharacterProtobuf::WriteInt32Field(AbilityBuffer, 1, AbilityScores.Strength);
    
    // Field 2: dexterity
    RPGCharacterProtobuf::WriteInt32Field(AbilityBuffer, 2, AbilityScores.Dexterity);
    
    // Field 3: constitution
    RPGCharacterProtobuf::WriteInt32Field(AbilityBuffer, 3, AbilityScores.Constitution);
    
    // Field 4: intelligence
    RPGCharacterProtobuf::WriteInt32Field(AbilityBuffer, 4, AbilityScores.Intelligence);
    
    // Field 5: wisdom
    RPGCharacterProtobuf::WriteInt32Field(AbilityBuffer, 5, AbilityScores.Wisdom);
    
    // Field 6: charisma
    RPGCharacterProtobuf::WriteInt32Field(AbilityBuffer, 6, AbilityScores.Charisma);

    if (AbilityBuffer.Num() == 0)
    {
        return; // All default values, skip
    }

    // Write as embedded message
    RPGCharacterProtobuf::WriteFieldHeader(Buffer, FieldNumber, RPGCharacterProtobuf::LENGTH_DELIMITED);
    RPGCharacterProtobuf::WriteVarint(Buffer, AbilityBuffer.Num());
    Buffer.Append(AbilityBuffer);
}

void FRPGCharacterProtobufConverter::SerializeRollAssignments(TArray<uint8>& Buffer, uint32 FieldNumber, const FRPGRollAssignments& RollAssignments)
{
    // Calculate size of RollAssignments message
    TArray<uint8> RollBuffer;
    
    // Field 1: strength_roll_id (string)
    RPGCharacterProtobuf::WriteStringField(RollBuffer, 1, RollAssignments.StrengthRollId);
    
    // Field 2: dexterity_roll_id (string)
    RPGCharacterProtobuf::WriteStringField(RollBuffer, 2, RollAssignments.DexterityRollId);
    
    // Field 3: constitution_roll_id (string)
    RPGCharacterProtobuf::WriteStringField(RollBuffer, 3, RollAssignments.ConstitutionRollId);
    
    // Field 4: intelligence_roll_id (string)
    RPGCharacterProtobuf::WriteStringField(RollBuffer, 4, RollAssignments.IntelligenceRollId);
    
    // Field 5: wisdom_roll_id (string)
    RPGCharacterProtobuf::WriteStringField(RollBuffer, 5, RollAssignments.WisdomRollId);
    
    // Field 6: charisma_roll_id (string)
    RPGCharacterProtobuf::WriteStringField(RollBuffer, 6, RollAssignments.CharismaRollId);

    if (RollBuffer.Num() == 0)
    {
        return; // All empty roll IDs, skip
    }

    // Write as embedded message
    RPGCharacterProtobuf::WriteFieldHeader(Buffer, FieldNumber, RPGCharacterProtobuf::LENGTH_DELIMITED);
    RPGCharacterProtobuf::WriteVarint(Buffer, RollBuffer.Num());
    Buffer.Append(RollBuffer);
}

bool FRPGCharacterProtobufConverter::ParseAbilityScores(const uint8* Data, int32 DataSize, FRPGAbilityScores& AbilityScores)
{
    int32 Offset = 0;

    // Initialize with defaults
    AbilityScores.Strength = 10;
    AbilityScores.Dexterity = 10;
    AbilityScores.Constitution = 10;
    AbilityScores.Intelligence = 10;
    AbilityScores.Wisdom = 10;
    AbilityScores.Charisma = 10;

    while (Offset < DataSize)
    {
        uint64 Tag;
        if (!RPGCharacterProtobuf::ReadVarint(Data, DataSize, Offset, Tag))
        {
            return false;
        }

        uint32 FieldNumber = static_cast<uint32>(Tag >> 3);
        RPGCharacterProtobuf::WireType Type = static_cast<RPGCharacterProtobuf::WireType>(Tag & 0x07);

        if (Type == RPGCharacterProtobuf::VARINT)
        {
            uint64 Value;
            if (!RPGCharacterProtobuf::ReadVarint(Data, DataSize, Offset, Value))
            {
                return false;
            }

            switch (FieldNumber)
            {
            case 1: AbilityScores.Strength = static_cast<int32>(Value); break;
            case 2: AbilityScores.Dexterity = static_cast<int32>(Value); break;
            case 3: AbilityScores.Constitution = static_cast<int32>(Value); break;
            case 4: AbilityScores.Intelligence = static_cast<int32>(Value); break;
            case 5: AbilityScores.Wisdom = static_cast<int32>(Value); break;
            case 6: AbilityScores.Charisma = static_cast<int32>(Value); break;
            }
        }
        else
        {
            // Skip other types
            if (Type == RPGCharacterProtobuf::LENGTH_DELIMITED)
            {
                uint64 Length;
                if (!RPGCharacterProtobuf::ReadVarint(Data, DataSize, Offset, Length))
                {
                    return false;
                }
                Offset += static_cast<int32>(Length);
            }
        }
    }

    return true;
}

bool FRPGCharacterProtobufConverter::ParseCharacterDraft(const uint8* Data, int32 DataSize, FRPGCharacterDraft& Draft)
{
    int32 Offset = 0;

    while (Offset < DataSize)
    {
        uint64 Tag;
        if (!RPGCharacterProtobuf::ReadVarint(Data, DataSize, Offset, Tag))
        {
            return false;
        }

        uint32 FieldNumber = static_cast<uint32>(Tag >> 3);
        RPGCharacterProtobuf::WireType Type = static_cast<RPGCharacterProtobuf::WireType>(Tag & 0x07);

        switch (FieldNumber)
        {
        case 1: // id (string)
            if (Type == RPGCharacterProtobuf::LENGTH_DELIMITED)
            {
                if (!RPGCharacterProtobuf::ReadString(Data, DataSize, Offset, Draft.Id))
                {
                    return false;
                }
            }
            break;

        case 2: // player_id (string)
            if (Type == RPGCharacterProtobuf::LENGTH_DELIMITED)
            {
                if (!RPGCharacterProtobuf::ReadString(Data, DataSize, Offset, Draft.PlayerId))
                {
                    return false;
                }
            }
            break;

        case 3: // session_id (string)
            if (Type == RPGCharacterProtobuf::LENGTH_DELIMITED)
            {
                if (!RPGCharacterProtobuf::ReadString(Data, DataSize, Offset, Draft.SessionId))
                {
                    return false;
                }
            }
            break;

        case 4: // name (string)
            if (Type == RPGCharacterProtobuf::LENGTH_DELIMITED)
            {
                if (!RPGCharacterProtobuf::ReadString(Data, DataSize, Offset, Draft.Name))
                {
                    return false;
                }
            }
            break;

        case 17: // race_id (enum) - using the enum field per proto spec
            if (Type == RPGCharacterProtobuf::VARINT)
            {
                uint64 Value;
                if (!RPGCharacterProtobuf::ReadVarint(Data, DataSize, Offset, Value))
                {
                    return false;
                }
                Draft.Race = static_cast<ERPGRace>(Value);
            }
            break;

        case 18: // subrace_id (enum)
            if (Type == RPGCharacterProtobuf::VARINT)
            {
                uint64 Value;
                if (!RPGCharacterProtobuf::ReadVarint(Data, DataSize, Offset, Value))
                {
                    return false;
                }
                Draft.Subrace = static_cast<ERPGSubrace>(Value);
            }
            break;

        case 19: // class_id (enum)
            if (Type == RPGCharacterProtobuf::VARINT)
            {
                uint64 Value;
                if (!RPGCharacterProtobuf::ReadVarint(Data, DataSize, Offset, Value))
                {
                    return false;
                }
                Draft.Class = static_cast<ERPGClass>(Value);
            }
            break;

        case 20: // background_id (enum)
            if (Type == RPGCharacterProtobuf::VARINT)
            {
                uint64 Value;
                if (!RPGCharacterProtobuf::ReadVarint(Data, DataSize, Offset, Value))
                {
                    return false;
                }
                Draft.Background = static_cast<ERPGBackground>(Value);
            }
            break;

        case 9: // ability_scores (AbilityScores message)
            if (Type == RPGCharacterProtobuf::LENGTH_DELIMITED)
            {
                uint64 MessageLength;
                if (!RPGCharacterProtobuf::ReadVarint(Data, DataSize, Offset, MessageLength))
                {
                    return false;
                }

                if (!ParseAbilityScores(Data + Offset, static_cast<int32>(MessageLength), Draft.AbilityScores))
                {
                    return false;
                }

                Offset += static_cast<int32>(MessageLength);
            }
            break;

        case 10: // alignment (enum)
            if (Type == RPGCharacterProtobuf::VARINT)
            {
                uint64 Value;
                if (!RPGCharacterProtobuf::ReadVarint(Data, DataSize, Offset, Value))
                {
                    return false;
                }
                Draft.Alignment = static_cast<ERPGAlignment>(Value);
            }
            break;

        default:
            // Skip unknown fields
            if (Type == RPGCharacterProtobuf::VARINT)
            {
                uint64 Value;
                if (!RPGCharacterProtobuf::ReadVarint(Data, DataSize, Offset, Value))
                {
                    return false;
                }
            }
            else if (Type == RPGCharacterProtobuf::LENGTH_DELIMITED)
            {
                uint64 Length;
                if (!RPGCharacterProtobuf::ReadVarint(Data, DataSize, Offset, Length))
                {
                    return false;
                }
                Offset += static_cast<int32>(Length);
            }
            break;
        }
    }

    return true;
}

bool FRPGCharacterProtobufConverter::ParseRaceInfo(const uint8* Data, int32 DataSize, FRPGRaceInfo& RaceInfo)
{
    int32 Offset = 0;

    while (Offset < DataSize)
    {
        uint64 Tag;
        if (!RPGCharacterProtobuf::ReadVarint(Data, DataSize, Offset, Tag))
        {
            return false;
        }

        uint32 FieldNumber = static_cast<uint32>(Tag >> 3);
        RPGCharacterProtobuf::WireType Type = static_cast<RPGCharacterProtobuf::WireType>(Tag & 0x07);

        switch (FieldNumber)
        {
        case 1: // id (string)
            if (Type == RPGCharacterProtobuf::LENGTH_DELIMITED)
            {
                if (!RPGCharacterProtobuf::ReadString(Data, DataSize, Offset, RaceInfo.Id))
                {
                    return false;
                }
            }
            break;

        case 2: // name (string)
            if (Type == RPGCharacterProtobuf::LENGTH_DELIMITED)
            {
                if (!RPGCharacterProtobuf::ReadString(Data, DataSize, Offset, RaceInfo.Name))
                {
                    return false;
                }
            }
            break;

        case 3: // description (string)
            if (Type == RPGCharacterProtobuf::LENGTH_DELIMITED)
            {
                if (!RPGCharacterProtobuf::ReadString(Data, DataSize, Offset, RaceInfo.Description))
                {
                    return false;
                }
            }
            break;

        case 4: // speed (int32)
            if (Type == RPGCharacterProtobuf::VARINT)
            {
                uint64 Value;
                if (!RPGCharacterProtobuf::ReadVarint(Data, DataSize, Offset, Value))
                {
                    return false;
                }
                RaceInfo.Speed = static_cast<int32>(Value);
            }
            break;

        default:
            // Skip unknown fields (including repeated fields for languages/proficiencies)
            if (Type == RPGCharacterProtobuf::VARINT)
            {
                uint64 Value;
                if (!RPGCharacterProtobuf::ReadVarint(Data, DataSize, Offset, Value))
                {
                    return false;
                }
            }
            else if (Type == RPGCharacterProtobuf::LENGTH_DELIMITED)
            {
                uint64 Length;
                if (!RPGCharacterProtobuf::ReadVarint(Data, DataSize, Offset, Length))
                {
                    return false;
                }
                Offset += static_cast<int32>(Length);
            }
            break;
        }
    }

    return true;
}

bool FRPGCharacterProtobufConverter::ParseClassInfo(const uint8* Data, int32 DataSize, FRPGClassInfo& ClassInfo)
{
    int32 Offset = 0;

    while (Offset < DataSize)
    {
        uint64 Tag;
        if (!RPGCharacterProtobuf::ReadVarint(Data, DataSize, Offset, Tag))
        {
            return false;
        }

        uint32 FieldNumber = static_cast<uint32>(Tag >> 3);
        RPGCharacterProtobuf::WireType Type = static_cast<RPGCharacterProtobuf::WireType>(Tag & 0x07);

        switch (FieldNumber)
        {
        case 1: // id (string)
            if (Type == RPGCharacterProtobuf::LENGTH_DELIMITED)
            {
                if (!RPGCharacterProtobuf::ReadString(Data, DataSize, Offset, ClassInfo.Id))
                {
                    return false;
                }
            }
            break;

        case 2: // name (string)
            if (Type == RPGCharacterProtobuf::LENGTH_DELIMITED)
            {
                if (!RPGCharacterProtobuf::ReadString(Data, DataSize, Offset, ClassInfo.Name))
                {
                    return false;
                }
            }
            break;

        case 3: // description (string)
            if (Type == RPGCharacterProtobuf::LENGTH_DELIMITED)
            {
                if (!RPGCharacterProtobuf::ReadString(Data, DataSize, Offset, ClassInfo.Description))
                {
                    return false;
                }
            }
            break;

        case 4: // hit_die (string)
            if (Type == RPGCharacterProtobuf::LENGTH_DELIMITED)
            {
                if (!RPGCharacterProtobuf::ReadString(Data, DataSize, Offset, ClassInfo.HitDie))
                {
                    return false;
                }
            }
            break;

        default:
            // Skip unknown fields (including repeated fields for abilities/saving throws)
            if (Type == RPGCharacterProtobuf::VARINT)
            {
                uint64 Value;
                if (!RPGCharacterProtobuf::ReadVarint(Data, DataSize, Offset, Value))
                {
                    return false;
                }
            }
            else if (Type == RPGCharacterProtobuf::LENGTH_DELIMITED)
            {
                uint64 Length;
                if (!RPGCharacterProtobuf::ReadVarint(Data, DataSize, Offset, Length))
                {
                    return false;
                }
                Offset += static_cast<int32>(Length);
            }
            break;
        }
    }

    return true;
}

// Empty stub implementations for unused helper functions
void FRPGCharacterProtobufConverter::SerializeCharacterDraft(TArray<uint8>& Buffer, uint32 FieldNumber, const FRPGCharacterDraft& Draft)
{
    // Not needed for current requests
}

void FRPGCharacterProtobufConverter::SerializeRaceInfo(TArray<uint8>& Buffer, uint32 FieldNumber, const FRPGRaceInfo& RaceInfo)
{
    // Not needed for current requests
}

void FRPGCharacterProtobufConverter::SerializeClassInfo(TArray<uint8>& Buffer, uint32 FieldNumber, const FRPGClassInfo& ClassInfo)
{
    // Not needed for current requests
}

// RollAbilityScores - Server-side dice rolling for ability scores
TArray<uint8> FRPGCharacterProtobufConverter::SerializeRollAbilityScoresRequest(const FRPGRollAbilityScoresRequest& Request)
{
    TArray<uint8> Buffer;
    
    // Field 1: draft_id (string)
    RPGCharacterProtobuf::WriteStringField(Buffer, 1, Request.DraftId);
    
    return Buffer;
}

bool FRPGCharacterProtobufConverter::DeserializeRollAbilityScoresResponse(const TArray<uint8>& Data, FRPGRollAbilityScoresResponse& Response)
{
    if (Data.Num() == 0)
    {
        return false;
    }
    
    Response.bSuccess = false;
    Response.Rolls.Empty();
    Response.ExpiresAt = 0;
    
    int32 Offset = 0;
    const uint8* DataPtr = Data.GetData();
    
    // Parse RollAbilityScoresResponse message (following existing pattern)
    while (Offset < Data.Num())
    {
        uint64 Tag;
        if (!RPGCharacterProtobuf::ReadVarint(DataPtr, Data.Num(), Offset, Tag))
            break;
            
        uint32 FieldNumber = static_cast<uint32>(Tag >> 3);
        uint32 WireType = static_cast<uint32>(Tag & 0x7);
        
        if (FieldNumber == 1 && WireType == RPGCharacterProtobuf::LENGTH_DELIMITED) // repeated AbilityScoreRoll rolls
        {
            uint64 Length;
            if (!RPGCharacterProtobuf::ReadVarint(DataPtr, Data.Num(), Offset, Length))
                break;
                
            if (Offset + static_cast<int32>(Length) > Data.Num())
                break;
                
            FRPGAbilityScoreRoll Roll;
            if (ParseAbilityScoreRoll(DataPtr + Offset, static_cast<int32>(Length), Roll))
            {
                Response.Rolls.Add(Roll);
            }
            Offset += static_cast<int32>(Length);
        }
        else if (FieldNumber == 2 && WireType == RPGCharacterProtobuf::VARINT) // int64 expires_at
        {
            uint64 Value;
            if (!RPGCharacterProtobuf::ReadVarint(DataPtr, Data.Num(), Offset, Value))
                break;
            Response.ExpiresAt = static_cast<int64>(Value);
        }
        else
        {
            // Skip unknown field using existing pattern
            if (WireType == RPGCharacterProtobuf::LENGTH_DELIMITED)
            {
                uint64 Length;
                if (!RPGCharacterProtobuf::ReadVarint(DataPtr, Data.Num(), Offset, Length))
                    break;
                Offset += static_cast<int32>(Length);
            }
            else if (WireType == RPGCharacterProtobuf::VARINT)
            {
                uint64 Value;
                if (!RPGCharacterProtobuf::ReadVarint(DataPtr, Data.Num(), Offset, Value))
                    break;
            }
        }
    }
    
    Response.bSuccess = true;
    return true;
}

bool FRPGCharacterProtobufConverter::ParseAbilityScoreRoll(const uint8* Data, int32 DataSize, FRPGAbilityScoreRoll& Roll)
{
    int32 Offset = 0;
    
    Roll.RollId = TEXT("");
    Roll.Dice.Empty();
    Roll.Total = 0;
    
    // Parse AbilityScoreRoll message (following existing C++ pattern)
    while (Offset < DataSize)
    {
        uint64 Tag;
        if (!RPGCharacterProtobuf::ReadVarint(Data, DataSize, Offset, Tag))
            break;
            
        uint32 FieldNumber = static_cast<uint32>(Tag >> 3);
        uint32 WireType = static_cast<uint32>(Tag & 0x7);
        
        if (FieldNumber == 1 && WireType == RPGCharacterProtobuf::LENGTH_DELIMITED) // string roll_id
        {
            FString Value;
            if (RPGCharacterProtobuf::ReadString(Data, DataSize, Offset, Value))
            {
                Roll.RollId = Value;
            }
        }
        else if (FieldNumber == 2 && WireType == RPGCharacterProtobuf::VARINT) // repeated int32 dice
        {
            uint64 Value;
            if (RPGCharacterProtobuf::ReadVarint(Data, DataSize, Offset, Value))
            {
                Roll.Dice.Add(static_cast<int32>(Value));
            }
        }
        else if (FieldNumber == 3 && WireType == RPGCharacterProtobuf::VARINT) // int32 total
        {
            uint64 Value;
            if (RPGCharacterProtobuf::ReadVarint(Data, DataSize, Offset, Value))
            {
                Roll.Total = static_cast<int32>(Value);
            }
        }
        else
        {
            // Skip unknown field using existing pattern
            if (WireType == RPGCharacterProtobuf::LENGTH_DELIMITED)
            {
                uint64 Length;
                if (!RPGCharacterProtobuf::ReadVarint(Data, DataSize, Offset, Length))
                    break;
                Offset += static_cast<int32>(Length);
            }
            else if (WireType == RPGCharacterProtobuf::VARINT)
            {
                uint64 Value;
                if (!RPGCharacterProtobuf::ReadVarint(Data, DataSize, Offset, Value))
                    break;
            }
        }
    }
    
    return true;
}