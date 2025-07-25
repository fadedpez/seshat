// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Seshat/RpgToolkit/RpgDiceRoller.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeRpgDiceRoller() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
SESHAT_API UClass* Z_Construct_UClass_URpgDiceRoller();
SESHAT_API UClass* Z_Construct_UClass_URpgDiceRoller_NoRegister();
UPackage* Z_Construct_UPackage__Script_Seshat();
// ********** End Cross Module References **********************************************************

// ********** Begin Class URpgDiceRoller Function GetRollHistory ***********************************
struct Z_Construct_UFunction_URpgDiceRoller_GetRollHistory_Statics
{
	struct RpgDiceRoller_eventGetRollHistory_Parms
	{
		FString EntityId;
		int32 Limit;
		TArray<FString> ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "RPG|Dice" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Get roll history for a specific entity\n\x09 * @param EntityId Entity to get history for\n\x09 * @param Limit Maximum number of historical rolls to return\n\x09 * @return Array of roll results as strings (formatted for display)\n\x09 */" },
#endif
		{ "CPP_Default_Limit", "10" },
		{ "ModuleRelativePath", "RpgToolkit/RpgDiceRoller.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Get roll history for a specific entity\n@param EntityId Entity to get history for\n@param Limit Maximum number of historical rolls to return\n@return Array of roll results as strings (formatted for display)" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EntityId_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_EntityId;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Limit;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ReturnValue_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_URpgDiceRoller_GetRollHistory_Statics::NewProp_EntityId = { "EntityId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RpgDiceRoller_eventGetRollHistory_Parms, EntityId), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EntityId_MetaData), NewProp_EntityId_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_URpgDiceRoller_GetRollHistory_Statics::NewProp_Limit = { "Limit", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RpgDiceRoller_eventGetRollHistory_Parms, Limit), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_URpgDiceRoller_GetRollHistory_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_URpgDiceRoller_GetRollHistory_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RpgDiceRoller_eventGetRollHistory_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_URpgDiceRoller_GetRollHistory_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URpgDiceRoller_GetRollHistory_Statics::NewProp_EntityId,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URpgDiceRoller_GetRollHistory_Statics::NewProp_Limit,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URpgDiceRoller_GetRollHistory_Statics::NewProp_ReturnValue_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URpgDiceRoller_GetRollHistory_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_URpgDiceRoller_GetRollHistory_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_URpgDiceRoller_GetRollHistory_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_URpgDiceRoller, nullptr, "GetRollHistory", Z_Construct_UFunction_URpgDiceRoller_GetRollHistory_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_URpgDiceRoller_GetRollHistory_Statics::PropPointers), sizeof(Z_Construct_UFunction_URpgDiceRoller_GetRollHistory_Statics::RpgDiceRoller_eventGetRollHistory_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_URpgDiceRoller_GetRollHistory_Statics::Function_MetaDataParams), Z_Construct_UFunction_URpgDiceRoller_GetRollHistory_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_URpgDiceRoller_GetRollHistory_Statics::RpgDiceRoller_eventGetRollHistory_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_URpgDiceRoller_GetRollHistory()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_URpgDiceRoller_GetRollHistory_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(URpgDiceRoller::execGetRollHistory)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_EntityId);
	P_GET_PROPERTY(FIntProperty,Z_Param_Limit);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(TArray<FString>*)Z_Param__Result=P_THIS->GetRollHistory(Z_Param_EntityId,Z_Param_Limit);
	P_NATIVE_END;
}
// ********** End Class URpgDiceRoller Function GetRollHistory *************************************

// ********** Begin Class URpgDiceRoller Function RollD20 ******************************************
struct Z_Construct_UFunction_URpgDiceRoller_RollD20_Statics
{
	struct RpgDiceRoller_eventRollD20_Parms
	{
		int32 ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "RPG|Dice" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Roll a standard d20 die\n\x09 * @return Random number between 1 and 20\n\x09 */" },
#endif
		{ "ModuleRelativePath", "RpgToolkit/RpgDiceRoller.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Roll a standard d20 die\n@return Random number between 1 and 20" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_URpgDiceRoller_RollD20_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RpgDiceRoller_eventRollD20_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_URpgDiceRoller_RollD20_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URpgDiceRoller_RollD20_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_URpgDiceRoller_RollD20_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_URpgDiceRoller_RollD20_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_URpgDiceRoller, nullptr, "RollD20", Z_Construct_UFunction_URpgDiceRoller_RollD20_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_URpgDiceRoller_RollD20_Statics::PropPointers), sizeof(Z_Construct_UFunction_URpgDiceRoller_RollD20_Statics::RpgDiceRoller_eventRollD20_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_URpgDiceRoller_RollD20_Statics::Function_MetaDataParams), Z_Construct_UFunction_URpgDiceRoller_RollD20_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_URpgDiceRoller_RollD20_Statics::RpgDiceRoller_eventRollD20_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_URpgDiceRoller_RollD20()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_URpgDiceRoller_RollD20_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(URpgDiceRoller::execRollD20)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(int32*)Z_Param__Result=P_THIS->RollD20();
	P_NATIVE_END;
}
// ********** End Class URpgDiceRoller Function RollD20 ********************************************

// ********** Begin Class URpgDiceRoller Function RollDice *****************************************
struct Z_Construct_UFunction_URpgDiceRoller_RollDice_Statics
{
	struct RpgDiceRoller_eventRollDice_Parms
	{
		int32 Sides;
		int32 ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "RPG|Dice" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Roll a die with specified number of sides\n\x09 * @param Sides Number of sides on the die (4, 6, 8, 10, 12, 20, 100)\n\x09 * @return Random number between 1 and Sides\n\x09 */" },
#endif
		{ "ModuleRelativePath", "RpgToolkit/RpgDiceRoller.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Roll a die with specified number of sides\n@param Sides Number of sides on the die (4, 6, 8, 10, 12, 20, 100)\n@return Random number between 1 and Sides" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FIntPropertyParams NewProp_Sides;
	static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_URpgDiceRoller_RollDice_Statics::NewProp_Sides = { "Sides", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RpgDiceRoller_eventRollDice_Parms, Sides), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_URpgDiceRoller_RollDice_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RpgDiceRoller_eventRollDice_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_URpgDiceRoller_RollDice_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URpgDiceRoller_RollDice_Statics::NewProp_Sides,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URpgDiceRoller_RollDice_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_URpgDiceRoller_RollDice_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_URpgDiceRoller_RollDice_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_URpgDiceRoller, nullptr, "RollDice", Z_Construct_UFunction_URpgDiceRoller_RollDice_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_URpgDiceRoller_RollDice_Statics::PropPointers), sizeof(Z_Construct_UFunction_URpgDiceRoller_RollDice_Statics::RpgDiceRoller_eventRollDice_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_URpgDiceRoller_RollDice_Statics::Function_MetaDataParams), Z_Construct_UFunction_URpgDiceRoller_RollDice_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_URpgDiceRoller_RollDice_Statics::RpgDiceRoller_eventRollDice_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_URpgDiceRoller_RollDice()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_URpgDiceRoller_RollDice_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(URpgDiceRoller::execRollDice)
{
	P_GET_PROPERTY(FIntProperty,Z_Param_Sides);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(int32*)Z_Param__Result=P_THIS->RollDice(Z_Param_Sides);
	P_NATIVE_END;
}
// ********** End Class URpgDiceRoller Function RollDice *******************************************

// ********** Begin Class URpgDiceRoller Function RollMultipleDice *********************************
struct Z_Construct_UFunction_URpgDiceRoller_RollMultipleDice_Statics
{
	struct RpgDiceRoller_eventRollMultipleDice_Parms
	{
		int32 Count;
		int32 Sides;
		TArray<int32> ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "RPG|Dice" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Roll multiple dice of the same type\n\x09 * @param Count Number of dice to roll\n\x09 * @param Sides Number of sides per die\n\x09 * @return Array of individual roll results\n\x09 */" },
#endif
		{ "ModuleRelativePath", "RpgToolkit/RpgDiceRoller.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Roll multiple dice of the same type\n@param Count Number of dice to roll\n@param Sides Number of sides per die\n@return Array of individual roll results" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FIntPropertyParams NewProp_Count;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Sides;
	static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_URpgDiceRoller_RollMultipleDice_Statics::NewProp_Count = { "Count", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RpgDiceRoller_eventRollMultipleDice_Parms, Count), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_URpgDiceRoller_RollMultipleDice_Statics::NewProp_Sides = { "Sides", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RpgDiceRoller_eventRollMultipleDice_Parms, Sides), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_URpgDiceRoller_RollMultipleDice_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_URpgDiceRoller_RollMultipleDice_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RpgDiceRoller_eventRollMultipleDice_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_URpgDiceRoller_RollMultipleDice_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URpgDiceRoller_RollMultipleDice_Statics::NewProp_Count,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URpgDiceRoller_RollMultipleDice_Statics::NewProp_Sides,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URpgDiceRoller_RollMultipleDice_Statics::NewProp_ReturnValue_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URpgDiceRoller_RollMultipleDice_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_URpgDiceRoller_RollMultipleDice_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_URpgDiceRoller_RollMultipleDice_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_URpgDiceRoller, nullptr, "RollMultipleDice", Z_Construct_UFunction_URpgDiceRoller_RollMultipleDice_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_URpgDiceRoller_RollMultipleDice_Statics::PropPointers), sizeof(Z_Construct_UFunction_URpgDiceRoller_RollMultipleDice_Statics::RpgDiceRoller_eventRollMultipleDice_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_URpgDiceRoller_RollMultipleDice_Statics::Function_MetaDataParams), Z_Construct_UFunction_URpgDiceRoller_RollMultipleDice_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_URpgDiceRoller_RollMultipleDice_Statics::RpgDiceRoller_eventRollMultipleDice_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_URpgDiceRoller_RollMultipleDice()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_URpgDiceRoller_RollMultipleDice_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(URpgDiceRoller::execRollMultipleDice)
{
	P_GET_PROPERTY(FIntProperty,Z_Param_Count);
	P_GET_PROPERTY(FIntProperty,Z_Param_Sides);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(TArray<int32>*)Z_Param__Result=P_THIS->RollMultipleDice(Z_Param_Count,Z_Param_Sides);
	P_NATIVE_END;
}
// ********** End Class URpgDiceRoller Function RollMultipleDice ***********************************

// ********** Begin Class URpgDiceRoller Function RollWithContext **********************************
struct Z_Construct_UFunction_URpgDiceRoller_RollWithContext_Statics
{
	struct RpgDiceRoller_eventRollWithContext_Parms
	{
		int32 Sides;
		FString EntityId;
		FString Context;
		int32 ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "RPG|Dice" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Roll dice with context information (for logging/history)\n\x09 * @param Sides Number of sides on the die\n\x09 * @param EntityId Identifier for the entity rolling (e.g., \"Player1\", \"Goblin_3\")\n\x09 * @param Context Purpose of the roll (e.g., \"Attack\", \"Damage\", \"Saving_Throw\")\n\x09 * @return Random number between 1 and Sides\n\x09 */" },
#endif
		{ "ModuleRelativePath", "RpgToolkit/RpgDiceRoller.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Roll dice with context information (for logging/history)\n@param Sides Number of sides on the die\n@param EntityId Identifier for the entity rolling (e.g., \"Player1\", \"Goblin_3\")\n@param Context Purpose of the roll (e.g., \"Attack\", \"Damage\", \"Saving_Throw\")\n@return Random number between 1 and Sides" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EntityId_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Context_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FIntPropertyParams NewProp_Sides;
	static const UECodeGen_Private::FStrPropertyParams NewProp_EntityId;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Context;
	static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_URpgDiceRoller_RollWithContext_Statics::NewProp_Sides = { "Sides", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RpgDiceRoller_eventRollWithContext_Parms, Sides), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_URpgDiceRoller_RollWithContext_Statics::NewProp_EntityId = { "EntityId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RpgDiceRoller_eventRollWithContext_Parms, EntityId), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EntityId_MetaData), NewProp_EntityId_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_URpgDiceRoller_RollWithContext_Statics::NewProp_Context = { "Context", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RpgDiceRoller_eventRollWithContext_Parms, Context), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Context_MetaData), NewProp_Context_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_URpgDiceRoller_RollWithContext_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RpgDiceRoller_eventRollWithContext_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_URpgDiceRoller_RollWithContext_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URpgDiceRoller_RollWithContext_Statics::NewProp_Sides,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URpgDiceRoller_RollWithContext_Statics::NewProp_EntityId,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URpgDiceRoller_RollWithContext_Statics::NewProp_Context,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URpgDiceRoller_RollWithContext_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_URpgDiceRoller_RollWithContext_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_URpgDiceRoller_RollWithContext_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_URpgDiceRoller, nullptr, "RollWithContext", Z_Construct_UFunction_URpgDiceRoller_RollWithContext_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_URpgDiceRoller_RollWithContext_Statics::PropPointers), sizeof(Z_Construct_UFunction_URpgDiceRoller_RollWithContext_Statics::RpgDiceRoller_eventRollWithContext_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_URpgDiceRoller_RollWithContext_Statics::Function_MetaDataParams), Z_Construct_UFunction_URpgDiceRoller_RollWithContext_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_URpgDiceRoller_RollWithContext_Statics::RpgDiceRoller_eventRollWithContext_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_URpgDiceRoller_RollWithContext()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_URpgDiceRoller_RollWithContext_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(URpgDiceRoller::execRollWithContext)
{
	P_GET_PROPERTY(FIntProperty,Z_Param_Sides);
	P_GET_PROPERTY(FStrProperty,Z_Param_EntityId);
	P_GET_PROPERTY(FStrProperty,Z_Param_Context);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(int32*)Z_Param__Result=P_THIS->RollWithContext(Z_Param_Sides,Z_Param_EntityId,Z_Param_Context);
	P_NATIVE_END;
}
// ********** End Class URpgDiceRoller Function RollWithContext ************************************

// ********** Begin Class URpgDiceRoller Function SetServerUrl *************************************
struct Z_Construct_UFunction_URpgDiceRoller_SetServerUrl_Statics
{
	struct RpgDiceRoller_eventSetServerUrl_Parms
	{
		FString ServerUrl;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "RPG|Dice|Config" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Set the server URL for dice service communication\n\x09 * @param ServerUrl URL of the Seshat server (default: http://localhost:9090)\n\x09 */" },
#endif
		{ "ModuleRelativePath", "RpgToolkit/RpgDiceRoller.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Set the server URL for dice service communication\n@param ServerUrl URL of the Seshat server (default: http://localhost:9090)" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ServerUrl_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_ServerUrl;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_URpgDiceRoller_SetServerUrl_Statics::NewProp_ServerUrl = { "ServerUrl", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RpgDiceRoller_eventSetServerUrl_Parms, ServerUrl), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ServerUrl_MetaData), NewProp_ServerUrl_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_URpgDiceRoller_SetServerUrl_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URpgDiceRoller_SetServerUrl_Statics::NewProp_ServerUrl,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_URpgDiceRoller_SetServerUrl_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_URpgDiceRoller_SetServerUrl_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_URpgDiceRoller, nullptr, "SetServerUrl", Z_Construct_UFunction_URpgDiceRoller_SetServerUrl_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_URpgDiceRoller_SetServerUrl_Statics::PropPointers), sizeof(Z_Construct_UFunction_URpgDiceRoller_SetServerUrl_Statics::RpgDiceRoller_eventSetServerUrl_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_URpgDiceRoller_SetServerUrl_Statics::Function_MetaDataParams), Z_Construct_UFunction_URpgDiceRoller_SetServerUrl_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_URpgDiceRoller_SetServerUrl_Statics::RpgDiceRoller_eventSetServerUrl_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_URpgDiceRoller_SetServerUrl()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_URpgDiceRoller_SetServerUrl_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(URpgDiceRoller::execSetServerUrl)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_ServerUrl);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetServerUrl(Z_Param_ServerUrl);
	P_NATIVE_END;
}
// ********** End Class URpgDiceRoller Function SetServerUrl ***************************************

// ********** Begin Class URpgDiceRoller Function TestConnection ***********************************
struct Z_Construct_UFunction_URpgDiceRoller_TestConnection_Statics
{
	struct RpgDiceRoller_eventTestConnection_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "RPG|Dice|Config" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Test connection to the dice service\n\x09 * @return True if server is reachable and responding\n\x09 */" },
#endif
		{ "ModuleRelativePath", "RpgToolkit/RpgDiceRoller.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Test connection to the dice service\n@return True if server is reachable and responding" },
#endif
	};
#endif // WITH_METADATA
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
void Z_Construct_UFunction_URpgDiceRoller_TestConnection_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((RpgDiceRoller_eventTestConnection_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_URpgDiceRoller_TestConnection_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(RpgDiceRoller_eventTestConnection_Parms), &Z_Construct_UFunction_URpgDiceRoller_TestConnection_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_URpgDiceRoller_TestConnection_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URpgDiceRoller_TestConnection_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_URpgDiceRoller_TestConnection_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_URpgDiceRoller_TestConnection_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_URpgDiceRoller, nullptr, "TestConnection", Z_Construct_UFunction_URpgDiceRoller_TestConnection_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_URpgDiceRoller_TestConnection_Statics::PropPointers), sizeof(Z_Construct_UFunction_URpgDiceRoller_TestConnection_Statics::RpgDiceRoller_eventTestConnection_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_URpgDiceRoller_TestConnection_Statics::Function_MetaDataParams), Z_Construct_UFunction_URpgDiceRoller_TestConnection_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_URpgDiceRoller_TestConnection_Statics::RpgDiceRoller_eventTestConnection_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_URpgDiceRoller_TestConnection()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_URpgDiceRoller_TestConnection_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(URpgDiceRoller::execTestConnection)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->TestConnection();
	P_NATIVE_END;
}
// ********** End Class URpgDiceRoller Function TestConnection *************************************

// ********** Begin Class URpgDiceRoller Function TestDiceFairness *********************************
struct Z_Construct_UFunction_URpgDiceRoller_TestDiceFairness_Statics
{
	struct RpgDiceRoller_eventTestDiceFairness_Parms
	{
		int32 Sides;
		int32 SampleSize;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "RPG|Dice" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Test dice fairness with statistical analysis\n\x09 * @param Sides Number of sides to test\n\x09 * @param SampleSize Number of rolls to perform for the test\n\x09 * @return True if the dice appear statistically fair\n\x09 */" },
#endif
		{ "ModuleRelativePath", "RpgToolkit/RpgDiceRoller.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Test dice fairness with statistical analysis\n@param Sides Number of sides to test\n@param SampleSize Number of rolls to perform for the test\n@return True if the dice appear statistically fair" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FIntPropertyParams NewProp_Sides;
	static const UECodeGen_Private::FIntPropertyParams NewProp_SampleSize;
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_URpgDiceRoller_TestDiceFairness_Statics::NewProp_Sides = { "Sides", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RpgDiceRoller_eventTestDiceFairness_Parms, Sides), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_URpgDiceRoller_TestDiceFairness_Statics::NewProp_SampleSize = { "SampleSize", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RpgDiceRoller_eventTestDiceFairness_Parms, SampleSize), METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_URpgDiceRoller_TestDiceFairness_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((RpgDiceRoller_eventTestDiceFairness_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_URpgDiceRoller_TestDiceFairness_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(RpgDiceRoller_eventTestDiceFairness_Parms), &Z_Construct_UFunction_URpgDiceRoller_TestDiceFairness_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_URpgDiceRoller_TestDiceFairness_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URpgDiceRoller_TestDiceFairness_Statics::NewProp_Sides,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URpgDiceRoller_TestDiceFairness_Statics::NewProp_SampleSize,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URpgDiceRoller_TestDiceFairness_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_URpgDiceRoller_TestDiceFairness_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_URpgDiceRoller_TestDiceFairness_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_URpgDiceRoller, nullptr, "TestDiceFairness", Z_Construct_UFunction_URpgDiceRoller_TestDiceFairness_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_URpgDiceRoller_TestDiceFairness_Statics::PropPointers), sizeof(Z_Construct_UFunction_URpgDiceRoller_TestDiceFairness_Statics::RpgDiceRoller_eventTestDiceFairness_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_URpgDiceRoller_TestDiceFairness_Statics::Function_MetaDataParams), Z_Construct_UFunction_URpgDiceRoller_TestDiceFairness_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_URpgDiceRoller_TestDiceFairness_Statics::RpgDiceRoller_eventTestDiceFairness_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_URpgDiceRoller_TestDiceFairness()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_URpgDiceRoller_TestDiceFairness_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(URpgDiceRoller::execTestDiceFairness)
{
	P_GET_PROPERTY(FIntProperty,Z_Param_Sides);
	P_GET_PROPERTY(FIntProperty,Z_Param_SampleSize);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->TestDiceFairness(Z_Param_Sides,Z_Param_SampleSize);
	P_NATIVE_END;
}
// ********** End Class URpgDiceRoller Function TestDiceFairness ***********************************

// ********** Begin Class URpgDiceRoller ***********************************************************
void URpgDiceRoller::StaticRegisterNativesURpgDiceRoller()
{
	UClass* Class = URpgDiceRoller::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "GetRollHistory", &URpgDiceRoller::execGetRollHistory },
		{ "RollD20", &URpgDiceRoller::execRollD20 },
		{ "RollDice", &URpgDiceRoller::execRollDice },
		{ "RollMultipleDice", &URpgDiceRoller::execRollMultipleDice },
		{ "RollWithContext", &URpgDiceRoller::execRollWithContext },
		{ "SetServerUrl", &URpgDiceRoller::execSetServerUrl },
		{ "TestConnection", &URpgDiceRoller::execTestConnection },
		{ "TestDiceFairness", &URpgDiceRoller::execTestDiceFairness },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_URpgDiceRoller;
UClass* URpgDiceRoller::GetPrivateStaticClass()
{
	using TClass = URpgDiceRoller;
	if (!Z_Registration_Info_UClass_URpgDiceRoller.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("RpgDiceRoller"),
			Z_Registration_Info_UClass_URpgDiceRoller.InnerSingleton,
			StaticRegisterNativesURpgDiceRoller,
			sizeof(TClass),
			alignof(TClass),
			TClass::StaticClassFlags,
			TClass::StaticClassCastFlags(),
			TClass::StaticConfigName(),
			(UClass::ClassConstructorType)InternalConstructor<TClass>,
			(UClass::ClassVTableHelperCtorCallerType)InternalVTableHelperCtorCaller<TClass>,
			UOBJECT_CPPCLASS_STATICFUNCTIONS_FORCLASS(TClass),
			&TClass::Super::StaticClass,
			&TClass::WithinClass::StaticClass
		);
	}
	return Z_Registration_Info_UClass_URpgDiceRoller.InnerSingleton;
}
UClass* Z_Construct_UClass_URpgDiceRoller_NoRegister()
{
	return URpgDiceRoller::GetPrivateStaticClass();
}
struct Z_Construct_UClass_URpgDiceRoller_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * RPG Dice Roller - UE wrapper for Seshat gRPC dice service\n * \n * This class provides Blueprint-accessible dice rolling functionality\n * by communicating with the Seshat gRPC server (currently via HTTP bridge)\n */" },
#endif
		{ "IncludePath", "RpgToolkit/RpgDiceRoller.h" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "RpgToolkit/RpgDiceRoller.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "RPG Dice Roller - UE wrapper for Seshat gRPC dice service\n\nThis class provides Blueprint-accessible dice rolling functionality\nby communicating with the Seshat gRPC server (currently via HTTP bridge)" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ServerUrl_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** URL of the Seshat gRPC server */" },
#endif
		{ "ModuleRelativePath", "RpgToolkit/RpgDiceRoller.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "URL of the Seshat gRPC server" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_ServerUrl;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_URpgDiceRoller_GetRollHistory, "GetRollHistory" }, // 4143561338
		{ &Z_Construct_UFunction_URpgDiceRoller_RollD20, "RollD20" }, // 4036067947
		{ &Z_Construct_UFunction_URpgDiceRoller_RollDice, "RollDice" }, // 2744385997
		{ &Z_Construct_UFunction_URpgDiceRoller_RollMultipleDice, "RollMultipleDice" }, // 297764949
		{ &Z_Construct_UFunction_URpgDiceRoller_RollWithContext, "RollWithContext" }, // 1696734880
		{ &Z_Construct_UFunction_URpgDiceRoller_SetServerUrl, "SetServerUrl" }, // 830635188
		{ &Z_Construct_UFunction_URpgDiceRoller_TestConnection, "TestConnection" }, // 1959186229
		{ &Z_Construct_UFunction_URpgDiceRoller_TestDiceFairness, "TestDiceFairness" }, // 3344623735
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<URpgDiceRoller>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_URpgDiceRoller_Statics::NewProp_ServerUrl = { "ServerUrl", nullptr, (EPropertyFlags)0x0040000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(URpgDiceRoller, ServerUrl), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ServerUrl_MetaData), NewProp_ServerUrl_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_URpgDiceRoller_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URpgDiceRoller_Statics::NewProp_ServerUrl,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_URpgDiceRoller_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_URpgDiceRoller_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UObject,
	(UObject* (*)())Z_Construct_UPackage__Script_Seshat,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_URpgDiceRoller_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_URpgDiceRoller_Statics::ClassParams = {
	&URpgDiceRoller::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_URpgDiceRoller_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_URpgDiceRoller_Statics::PropPointers),
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_URpgDiceRoller_Statics::Class_MetaDataParams), Z_Construct_UClass_URpgDiceRoller_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_URpgDiceRoller()
{
	if (!Z_Registration_Info_UClass_URpgDiceRoller.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_URpgDiceRoller.OuterSingleton, Z_Construct_UClass_URpgDiceRoller_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_URpgDiceRoller.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(URpgDiceRoller);
URpgDiceRoller::~URpgDiceRoller() {}
// ********** End Class URpgDiceRoller *************************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Projects_share_seshat_Seshat_Source_Seshat_RpgToolkit_RpgDiceRoller_h__Script_Seshat_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_URpgDiceRoller, URpgDiceRoller::StaticClass, TEXT("URpgDiceRoller"), &Z_Registration_Info_UClass_URpgDiceRoller, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(URpgDiceRoller), 4063759569U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Projects_share_seshat_Seshat_Source_Seshat_RpgToolkit_RpgDiceRoller_h__Script_Seshat_636745329(TEXT("/Script/Seshat"),
	Z_CompiledInDeferFile_FID_Projects_share_seshat_Seshat_Source_Seshat_RpgToolkit_RpgDiceRoller_h__Script_Seshat_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Projects_share_seshat_Seshat_Source_Seshat_RpgToolkit_RpgDiceRoller_h__Script_Seshat_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
