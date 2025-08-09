// Copyright Epic Games, Inc. All Rights Reserved.

#include "RPGProtobufConverter.h"
#include "GRPCWeb/RPGWebTypes.h"

// S001: Manual protobuf wire format implementation - NO C++ protobuf library
// This provides binary protobuf serialization without any external dependencies

namespace RPGProtobuf
{
    // Protobuf wire format constants
    enum WireType : uint8
    {
        VARINT = 0,      // int32, int64, uint32, uint64, sint32, sint64, bool, enum
        FIXED64 = 1,     // fixed64, sfixed64, double
        LENGTH_DELIMITED = 2, // string, bytes, embedded messages, repeated packed numeric
        START_GROUP = 3, // deprecated
        END_GROUP = 4,   // deprecated
        FIXED32 = 5      // fixed32, sfixed32, float
    };

    // Encode a varint (variable-length integer)
    static void WriteVarint(TArray<uint8>& Buffer, uint64 Value)
    {
        while (Value >= 0x80)
        {
            Buffer.Add(static_cast<uint8>((Value & 0x7F) | 0x80));
            Value >>= 7;
        }
        Buffer.Add(static_cast<uint8>(Value & 0x7F));
    }

    // Encode a field header (field number + wire type)
    static void WriteFieldHeader(TArray<uint8>& Buffer, uint32 FieldNumber, WireType Type)
    {
        uint32 Tag = (FieldNumber << 3) | Type;
        WriteVarint(Buffer, Tag);
    }

    // Encode a string field
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

    // Encode an int32 field
    static void WriteInt32Field(TArray<uint8>& Buffer, uint32 FieldNumber, int32 Value)
    {
        if (Value == 0)
        {
            return; // Skip zero values (proto3 default behavior)
        }

        WriteFieldHeader(Buffer, FieldNumber, VARINT);
        WriteVarint(Buffer, static_cast<uint32>(Value));
    }

    // Read a varint from buffer
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

    // Read a string from buffer
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

    // Parse a DiceRoll message from protobuf data
    static bool ParseDiceRoll(const uint8* Data, int32 DataSize, FRPGDiceRollResponse& Response)
    {
        int32 Offset = 0;
        FString RollId, Notation, Description;
        TArray<int32> Dice, Dropped;
        int32 Total = 0, DiceTotal = 0, Modifier = 0;

        while (Offset < DataSize)
        {
            // Read field header
            uint64 Tag;
            if (!ReadVarint(Data, DataSize, Offset, Tag))
            {
                return false;
            }

            uint32 FieldNumber = static_cast<uint32>(Tag >> 3);
            WireType Type = static_cast<WireType>(Tag & 0x07);

            switch (FieldNumber)
            {
            case 1: // roll_id
                if (Type == LENGTH_DELIMITED && !ReadString(Data, DataSize, Offset, RollId))
                {
                    return false;
                }
                break;

            case 2: // notation  
                if (Type == LENGTH_DELIMITED && !ReadString(Data, DataSize, Offset, Notation))
                {
                    return false;
                }
                break;

            case 3: // dice (repeated int32)
                if (Type == LENGTH_DELIMITED)
                {
                    uint64 PackedLength;
                    if (!ReadVarint(Data, DataSize, Offset, PackedLength))
                    {
                        return false;
                    }
                    
                    int32 EndOffset = Offset + static_cast<int32>(PackedLength);
                    while (Offset < EndOffset)
                    {
                        uint64 DiceValue;
                        if (!ReadVarint(Data, DataSize, Offset, DiceValue))
                        {
                            return false;
                        }
                        Dice.Add(static_cast<int32>(DiceValue));
                    }
                }
                break;

            case 4: // total
                if (Type == VARINT)
                {
                    uint64 Value;
                    if (!ReadVarint(Data, DataSize, Offset, Value))
                    {
                        return false;
                    }
                    Total = static_cast<int32>(Value);
                }
                break;

            case 8: // modifier
                if (Type == VARINT)
                {
                    uint64 Value;
                    if (!ReadVarint(Data, DataSize, Offset, Value))
                    {
                        return false;
                    }
                    Modifier = static_cast<int32>(Value);
                }
                break;

            default:
                // Skip unknown fields
                if (Type == VARINT)
                {
                    uint64 Value;
                    if (!ReadVarint(Data, DataSize, Offset, Value))
                    {
                        return false;
                    }
                }
                else if (Type == LENGTH_DELIMITED)
                {
                    uint64 Length;
                    if (!ReadVarint(Data, DataSize, Offset, Length))
                    {
                        return false;
                    }
                    Offset += static_cast<int32>(Length);
                }
                break;
            }
        }

        // Set response data
        Response.SessionId = RollId;
        Response.Results = Dice;
        Response.Total = Total;
        Response.Modifier = Modifier;
        Response.bSuccess = true;

        return true;
    }
}

TArray<uint8> FRPGProtobufConverter::SerializeRollRequest(const FRPGDiceRollRequest& Request)
{
    TArray<uint8> Buffer;
    Buffer.Reserve(256); // Pre-allocate reasonable size

    // Field 1: entity_id (string)
    RPGProtobuf::WriteStringField(Buffer, 1, Request.SessionId);

    // Field 2: context (string)
    RPGProtobuf::WriteStringField(Buffer, 2, TEXT("dice_roll"));

    // Field 3: notation (string) - Build from UE fields
    FString Notation = FString::Printf(TEXT("%dd%d"), Request.Count, Request.Sides);
    if (Request.Modifier != 0)
    {
        Notation += FString::Printf(TEXT("%+d"), Request.Modifier);
    }
    RPGProtobuf::WriteStringField(Buffer, 3, Notation);

    // Field 4: count (int32) - Always 1 for now
    RPGProtobuf::WriteInt32Field(Buffer, 4, 1);

    // Field 5: ttl_seconds (int32) - 5 minute default
    RPGProtobuf::WriteInt32Field(Buffer, 5, 300);

    // Field 6: modifier_description (string) - Optional
    if (Request.Modifier != 0)
    {
        FString ModDesc = FString::Printf(TEXT("Modifier: %+d"), Request.Modifier);
        RPGProtobuf::WriteStringField(Buffer, 6, ModDesc);
    }

    return Buffer;
}

bool FRPGProtobufConverter::DeserializeRollResponse(const TArray<uint8>& Data, FRPGDiceRollResponse& Response)
{
    if (Data.Num() == 0)
    {
        return false;
    }

    // Initialize response
    Response.Results.Empty();
    Response.Total = 0;
    Response.Modifier = 0;
    Response.bSuccess = false;

    int32 Offset = 0;
    const uint8* DataPtr = Data.GetData();

    // Parse RollDiceResponse message
    while (Offset < Data.Num())
    {
        // Read field header
        uint64 Tag;
        if (!RPGProtobuf::ReadVarint(DataPtr, Data.Num(), Offset, Tag))
        {
            return false;
        }

        uint32 FieldNumber = static_cast<uint32>(Tag >> 3);
        RPGProtobuf::WireType Type = static_cast<RPGProtobuf::WireType>(Tag & 0x07);

        switch (FieldNumber)
        {
        case 1: // rolls (repeated DiceRoll)
            if (Type == RPGProtobuf::LENGTH_DELIMITED)
            {
                uint64 MessageLength;
                if (!RPGProtobuf::ReadVarint(DataPtr, Data.Num(), Offset, MessageLength))
                {
                    return false;
                }

                // Parse the DiceRoll message
                if (!RPGProtobuf::ParseDiceRoll(DataPtr + Offset, static_cast<int32>(MessageLength), Response))
                {
                    return false;
                }

                Offset += static_cast<int32>(MessageLength);
            }
            break;

        case 2: // expires_at (int64) - Skip for now
            if (Type == RPGProtobuf::VARINT)
            {
                uint64 Value;
                if (!RPGProtobuf::ReadVarint(DataPtr, Data.Num(), Offset, Value))
                {
                    return false;
                }
            }
            break;

        default:
            // Skip unknown fields
            if (Type == RPGProtobuf::VARINT)
            {
                uint64 Value;
                if (!RPGProtobuf::ReadVarint(DataPtr, Data.Num(), Offset, Value))
                {
                    return false;
                }
            }
            else if (Type == RPGProtobuf::LENGTH_DELIMITED)
            {
                uint64 Length;
                if (!RPGProtobuf::ReadVarint(DataPtr, Data.Num(), Offset, Length))
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

bool FRPGProtobufConverter::IsValidRollRequestData(const TArray<uint8>& Data)
{
    if (Data.Num() == 0)
    {
        return false;
    }

    // Simple validation: try to parse at least one field
    int32 Offset = 0;
    uint64 Tag;
    return RPGProtobuf::ReadVarint(Data.GetData(), Data.Num(), Offset, Tag);
}

bool FRPGProtobufConverter::IsValidRollResponseData(const TArray<uint8>& Data)
{
    if (Data.Num() == 0)
    {
        return false;
    }

    // Simple validation: try to parse at least one field
    int32 Offset = 0;
    uint64 Tag;
    return RPGProtobuf::ReadVarint(Data.GetData(), Data.Num(), Offset, Tag);
}