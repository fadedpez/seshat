// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Seshat/RpgToolkit/RpgToolkitSubsystem.h"
#include "Engine/GameInstance.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeRpgToolkitSubsystem() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_UGameInstanceSubsystem();
SESHAT_API UClass* Z_Construct_UClass_URpgDiceRoller_NoRegister();
SESHAT_API UClass* Z_Construct_UClass_URpgToolkitSubsystem();
SESHAT_API UClass* Z_Construct_UClass_URpgToolkitSubsystem_NoRegister();
UPackage* Z_Construct_UPackage__Script_Seshat();
// ********** End Cross Module References **********************************************************

// ********** Begin Class URpgToolkitSubsystem Function GetDiceRoller ******************************
struct Z_Construct_UFunction_URpgToolkitSubsystem_GetDiceRoller_Statics
{
	struct RpgToolkitSubsystem_eventGetDiceRoller_Parms
	{
		URpgDiceRoller* ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "RPG|Toolkit" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Get the dice roller instance\n\x09 * @return Dice roller for Blueprint use\n\x09 */" },
#endif
		{ "ModuleRelativePath", "RpgToolkit/RpgToolkitSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Get the dice roller instance\n@return Dice roller for Blueprint use" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_URpgToolkitSubsystem_GetDiceRoller_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RpgToolkitSubsystem_eventGetDiceRoller_Parms, ReturnValue), Z_Construct_UClass_URpgDiceRoller_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_URpgToolkitSubsystem_GetDiceRoller_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URpgToolkitSubsystem_GetDiceRoller_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_URpgToolkitSubsystem_GetDiceRoller_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_URpgToolkitSubsystem_GetDiceRoller_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_URpgToolkitSubsystem, nullptr, "GetDiceRoller", Z_Construct_UFunction_URpgToolkitSubsystem_GetDiceRoller_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_URpgToolkitSubsystem_GetDiceRoller_Statics::PropPointers), sizeof(Z_Construct_UFunction_URpgToolkitSubsystem_GetDiceRoller_Statics::RpgToolkitSubsystem_eventGetDiceRoller_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_URpgToolkitSubsystem_GetDiceRoller_Statics::Function_MetaDataParams), Z_Construct_UFunction_URpgToolkitSubsystem_GetDiceRoller_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_URpgToolkitSubsystem_GetDiceRoller_Statics::RpgToolkitSubsystem_eventGetDiceRoller_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_URpgToolkitSubsystem_GetDiceRoller()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_URpgToolkitSubsystem_GetDiceRoller_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(URpgToolkitSubsystem::execGetDiceRoller)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(URpgDiceRoller**)Z_Param__Result=P_THIS->GetDiceRoller();
	P_NATIVE_END;
}
// ********** End Class URpgToolkitSubsystem Function GetDiceRoller ********************************

// ********** Begin Class URpgToolkitSubsystem Function GetToolkitStatus ***************************
struct Z_Construct_UFunction_URpgToolkitSubsystem_GetToolkitStatus_Statics
{
	struct RpgToolkitSubsystem_eventGetToolkitStatus_Parms
	{
		FString ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "RPG|Toolkit|Debug" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Get toolkit status information\n\x09 * @return Human-readable status string\n\x09 */" },
#endif
		{ "ModuleRelativePath", "RpgToolkit/RpgToolkitSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Get toolkit status information\n@return Human-readable status string" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_URpgToolkitSubsystem_GetToolkitStatus_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RpgToolkitSubsystem_eventGetToolkitStatus_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_URpgToolkitSubsystem_GetToolkitStatus_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URpgToolkitSubsystem_GetToolkitStatus_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_URpgToolkitSubsystem_GetToolkitStatus_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_URpgToolkitSubsystem_GetToolkitStatus_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_URpgToolkitSubsystem, nullptr, "GetToolkitStatus", Z_Construct_UFunction_URpgToolkitSubsystem_GetToolkitStatus_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_URpgToolkitSubsystem_GetToolkitStatus_Statics::PropPointers), sizeof(Z_Construct_UFunction_URpgToolkitSubsystem_GetToolkitStatus_Statics::RpgToolkitSubsystem_eventGetToolkitStatus_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_URpgToolkitSubsystem_GetToolkitStatus_Statics::Function_MetaDataParams), Z_Construct_UFunction_URpgToolkitSubsystem_GetToolkitStatus_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_URpgToolkitSubsystem_GetToolkitStatus_Statics::RpgToolkitSubsystem_eventGetToolkitStatus_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_URpgToolkitSubsystem_GetToolkitStatus()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_URpgToolkitSubsystem_GetToolkitStatus_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(URpgToolkitSubsystem::execGetToolkitStatus)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FString*)Z_Param__Result=P_THIS->GetToolkitStatus();
	P_NATIVE_END;
}
// ********** End Class URpgToolkitSubsystem Function GetToolkitStatus *****************************

// ********** Begin Class URpgToolkitSubsystem Function InitializeServer ***************************
struct Z_Construct_UFunction_URpgToolkitSubsystem_InitializeServer_Statics
{
	struct RpgToolkitSubsystem_eventInitializeServer_Parms
	{
		FString ServerUrl;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "RPG|Toolkit|Config" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Initialize connection to Seshat server\n\x09 * @param ServerUrl URL of the Seshat gRPC server\n\x09 * @return True if connection was successful\n\x09 */" },
#endif
		{ "CPP_Default_ServerUrl", "http://localhost:9090" },
		{ "ModuleRelativePath", "RpgToolkit/RpgToolkitSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Initialize connection to Seshat server\n@param ServerUrl URL of the Seshat gRPC server\n@return True if connection was successful" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ServerUrl_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_ServerUrl;
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_URpgToolkitSubsystem_InitializeServer_Statics::NewProp_ServerUrl = { "ServerUrl", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RpgToolkitSubsystem_eventInitializeServer_Parms, ServerUrl), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ServerUrl_MetaData), NewProp_ServerUrl_MetaData) };
void Z_Construct_UFunction_URpgToolkitSubsystem_InitializeServer_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((RpgToolkitSubsystem_eventInitializeServer_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_URpgToolkitSubsystem_InitializeServer_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(RpgToolkitSubsystem_eventInitializeServer_Parms), &Z_Construct_UFunction_URpgToolkitSubsystem_InitializeServer_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_URpgToolkitSubsystem_InitializeServer_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URpgToolkitSubsystem_InitializeServer_Statics::NewProp_ServerUrl,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URpgToolkitSubsystem_InitializeServer_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_URpgToolkitSubsystem_InitializeServer_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_URpgToolkitSubsystem_InitializeServer_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_URpgToolkitSubsystem, nullptr, "InitializeServer", Z_Construct_UFunction_URpgToolkitSubsystem_InitializeServer_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_URpgToolkitSubsystem_InitializeServer_Statics::PropPointers), sizeof(Z_Construct_UFunction_URpgToolkitSubsystem_InitializeServer_Statics::RpgToolkitSubsystem_eventInitializeServer_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_URpgToolkitSubsystem_InitializeServer_Statics::Function_MetaDataParams), Z_Construct_UFunction_URpgToolkitSubsystem_InitializeServer_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_URpgToolkitSubsystem_InitializeServer_Statics::RpgToolkitSubsystem_eventInitializeServer_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_URpgToolkitSubsystem_InitializeServer()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_URpgToolkitSubsystem_InitializeServer_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(URpgToolkitSubsystem::execInitializeServer)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_ServerUrl);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->InitializeServer(Z_Param_ServerUrl);
	P_NATIVE_END;
}
// ********** End Class URpgToolkitSubsystem Function InitializeServer *****************************

// ********** Begin Class URpgToolkitSubsystem Function QuickRoll **********************************
struct Z_Construct_UFunction_URpgToolkitSubsystem_QuickRoll_Statics
{
	struct RpgToolkitSubsystem_eventQuickRoll_Parms
	{
		int32 Sides;
		int32 ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "Category", "RPG|Quick" },
		{ "ModuleRelativePath", "RpgToolkit/RpgToolkitSubsystem.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FIntPropertyParams NewProp_Sides;
	static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_URpgToolkitSubsystem_QuickRoll_Statics::NewProp_Sides = { "Sides", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RpgToolkitSubsystem_eventQuickRoll_Parms, Sides), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_URpgToolkitSubsystem_QuickRoll_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RpgToolkitSubsystem_eventQuickRoll_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_URpgToolkitSubsystem_QuickRoll_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URpgToolkitSubsystem_QuickRoll_Statics::NewProp_Sides,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URpgToolkitSubsystem_QuickRoll_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_URpgToolkitSubsystem_QuickRoll_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_URpgToolkitSubsystem_QuickRoll_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_URpgToolkitSubsystem, nullptr, "QuickRoll", Z_Construct_UFunction_URpgToolkitSubsystem_QuickRoll_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_URpgToolkitSubsystem_QuickRoll_Statics::PropPointers), sizeof(Z_Construct_UFunction_URpgToolkitSubsystem_QuickRoll_Statics::RpgToolkitSubsystem_eventQuickRoll_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_URpgToolkitSubsystem_QuickRoll_Statics::Function_MetaDataParams), Z_Construct_UFunction_URpgToolkitSubsystem_QuickRoll_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_URpgToolkitSubsystem_QuickRoll_Statics::RpgToolkitSubsystem_eventQuickRoll_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_URpgToolkitSubsystem_QuickRoll()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_URpgToolkitSubsystem_QuickRoll_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(URpgToolkitSubsystem::execQuickRoll)
{
	P_GET_PROPERTY(FIntProperty,Z_Param_Sides);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(int32*)Z_Param__Result=P_THIS->QuickRoll(Z_Param_Sides);
	P_NATIVE_END;
}
// ********** End Class URpgToolkitSubsystem Function QuickRoll ************************************

// ********** Begin Class URpgToolkitSubsystem Function QuickRollD20 *******************************
struct Z_Construct_UFunction_URpgToolkitSubsystem_QuickRollD20_Statics
{
	struct RpgToolkitSubsystem_eventQuickRollD20_Parms
	{
		int32 ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "Category", "RPG|Quick" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Quick dice rolling functions for common use cases\n\x09 */" },
#endif
		{ "ModuleRelativePath", "RpgToolkit/RpgToolkitSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Quick dice rolling functions for common use cases" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_URpgToolkitSubsystem_QuickRollD20_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RpgToolkitSubsystem_eventQuickRollD20_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_URpgToolkitSubsystem_QuickRollD20_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URpgToolkitSubsystem_QuickRollD20_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_URpgToolkitSubsystem_QuickRollD20_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_URpgToolkitSubsystem_QuickRollD20_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_URpgToolkitSubsystem, nullptr, "QuickRollD20", Z_Construct_UFunction_URpgToolkitSubsystem_QuickRollD20_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_URpgToolkitSubsystem_QuickRollD20_Statics::PropPointers), sizeof(Z_Construct_UFunction_URpgToolkitSubsystem_QuickRollD20_Statics::RpgToolkitSubsystem_eventQuickRollD20_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_URpgToolkitSubsystem_QuickRollD20_Statics::Function_MetaDataParams), Z_Construct_UFunction_URpgToolkitSubsystem_QuickRollD20_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_URpgToolkitSubsystem_QuickRollD20_Statics::RpgToolkitSubsystem_eventQuickRollD20_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_URpgToolkitSubsystem_QuickRollD20()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_URpgToolkitSubsystem_QuickRollD20_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(URpgToolkitSubsystem::execQuickRollD20)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(int32*)Z_Param__Result=P_THIS->QuickRollD20();
	P_NATIVE_END;
}
// ********** End Class URpgToolkitSubsystem Function QuickRollD20 *********************************

// ********** Begin Class URpgToolkitSubsystem Function QuickRollMultiple **************************
struct Z_Construct_UFunction_URpgToolkitSubsystem_QuickRollMultiple_Statics
{
	struct RpgToolkitSubsystem_eventQuickRollMultiple_Parms
	{
		int32 Count;
		int32 Sides;
		TArray<int32> ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "Category", "RPG|Quick" },
		{ "ModuleRelativePath", "RpgToolkit/RpgToolkitSubsystem.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FIntPropertyParams NewProp_Count;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Sides;
	static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_URpgToolkitSubsystem_QuickRollMultiple_Statics::NewProp_Count = { "Count", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RpgToolkitSubsystem_eventQuickRollMultiple_Parms, Count), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_URpgToolkitSubsystem_QuickRollMultiple_Statics::NewProp_Sides = { "Sides", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RpgToolkitSubsystem_eventQuickRollMultiple_Parms, Sides), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_URpgToolkitSubsystem_QuickRollMultiple_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_URpgToolkitSubsystem_QuickRollMultiple_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RpgToolkitSubsystem_eventQuickRollMultiple_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_URpgToolkitSubsystem_QuickRollMultiple_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URpgToolkitSubsystem_QuickRollMultiple_Statics::NewProp_Count,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URpgToolkitSubsystem_QuickRollMultiple_Statics::NewProp_Sides,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URpgToolkitSubsystem_QuickRollMultiple_Statics::NewProp_ReturnValue_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URpgToolkitSubsystem_QuickRollMultiple_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_URpgToolkitSubsystem_QuickRollMultiple_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_URpgToolkitSubsystem_QuickRollMultiple_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_URpgToolkitSubsystem, nullptr, "QuickRollMultiple", Z_Construct_UFunction_URpgToolkitSubsystem_QuickRollMultiple_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_URpgToolkitSubsystem_QuickRollMultiple_Statics::PropPointers), sizeof(Z_Construct_UFunction_URpgToolkitSubsystem_QuickRollMultiple_Statics::RpgToolkitSubsystem_eventQuickRollMultiple_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_URpgToolkitSubsystem_QuickRollMultiple_Statics::Function_MetaDataParams), Z_Construct_UFunction_URpgToolkitSubsystem_QuickRollMultiple_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_URpgToolkitSubsystem_QuickRollMultiple_Statics::RpgToolkitSubsystem_eventQuickRollMultiple_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_URpgToolkitSubsystem_QuickRollMultiple()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_URpgToolkitSubsystem_QuickRollMultiple_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(URpgToolkitSubsystem::execQuickRollMultiple)
{
	P_GET_PROPERTY(FIntProperty,Z_Param_Count);
	P_GET_PROPERTY(FIntProperty,Z_Param_Sides);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(TArray<int32>*)Z_Param__Result=P_THIS->QuickRollMultiple(Z_Param_Count,Z_Param_Sides);
	P_NATIVE_END;
}
// ********** End Class URpgToolkitSubsystem Function QuickRollMultiple ****************************

// ********** Begin Class URpgToolkitSubsystem Function RunDiagnostics *****************************
struct Z_Construct_UFunction_URpgToolkitSubsystem_RunDiagnostics_Statics
{
	struct RpgToolkitSubsystem_eventRunDiagnostics_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "Category", "RPG|Toolkit|Debug" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Test all toolkit services\n\x09 * @return True if all services are working correctly\n\x09 */" },
#endif
		{ "ModuleRelativePath", "RpgToolkit/RpgToolkitSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Test all toolkit services\n@return True if all services are working correctly" },
#endif
	};
#endif // WITH_METADATA
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
void Z_Construct_UFunction_URpgToolkitSubsystem_RunDiagnostics_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((RpgToolkitSubsystem_eventRunDiagnostics_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_URpgToolkitSubsystem_RunDiagnostics_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(RpgToolkitSubsystem_eventRunDiagnostics_Parms), &Z_Construct_UFunction_URpgToolkitSubsystem_RunDiagnostics_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_URpgToolkitSubsystem_RunDiagnostics_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URpgToolkitSubsystem_RunDiagnostics_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_URpgToolkitSubsystem_RunDiagnostics_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_URpgToolkitSubsystem_RunDiagnostics_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_URpgToolkitSubsystem, nullptr, "RunDiagnostics", Z_Construct_UFunction_URpgToolkitSubsystem_RunDiagnostics_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_URpgToolkitSubsystem_RunDiagnostics_Statics::PropPointers), sizeof(Z_Construct_UFunction_URpgToolkitSubsystem_RunDiagnostics_Statics::RpgToolkitSubsystem_eventRunDiagnostics_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_URpgToolkitSubsystem_RunDiagnostics_Statics::Function_MetaDataParams), Z_Construct_UFunction_URpgToolkitSubsystem_RunDiagnostics_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_URpgToolkitSubsystem_RunDiagnostics_Statics::RpgToolkitSubsystem_eventRunDiagnostics_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_URpgToolkitSubsystem_RunDiagnostics()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_URpgToolkitSubsystem_RunDiagnostics_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(URpgToolkitSubsystem::execRunDiagnostics)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->RunDiagnostics();
	P_NATIVE_END;
}
// ********** End Class URpgToolkitSubsystem Function RunDiagnostics *******************************

// ********** Begin Class URpgToolkitSubsystem *****************************************************
void URpgToolkitSubsystem::StaticRegisterNativesURpgToolkitSubsystem()
{
	UClass* Class = URpgToolkitSubsystem::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "GetDiceRoller", &URpgToolkitSubsystem::execGetDiceRoller },
		{ "GetToolkitStatus", &URpgToolkitSubsystem::execGetToolkitStatus },
		{ "InitializeServer", &URpgToolkitSubsystem::execInitializeServer },
		{ "QuickRoll", &URpgToolkitSubsystem::execQuickRoll },
		{ "QuickRollD20", &URpgToolkitSubsystem::execQuickRollD20 },
		{ "QuickRollMultiple", &URpgToolkitSubsystem::execQuickRollMultiple },
		{ "RunDiagnostics", &URpgToolkitSubsystem::execRunDiagnostics },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_URpgToolkitSubsystem;
UClass* URpgToolkitSubsystem::GetPrivateStaticClass()
{
	using TClass = URpgToolkitSubsystem;
	if (!Z_Registration_Info_UClass_URpgToolkitSubsystem.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("RpgToolkitSubsystem"),
			Z_Registration_Info_UClass_URpgToolkitSubsystem.InnerSingleton,
			StaticRegisterNativesURpgToolkitSubsystem,
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
	return Z_Registration_Info_UClass_URpgToolkitSubsystem.InnerSingleton;
}
UClass* Z_Construct_UClass_URpgToolkitSubsystem_NoRegister()
{
	return URpgToolkitSubsystem::GetPrivateStaticClass();
}
struct Z_Construct_UClass_URpgToolkitSubsystem_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * RPG Toolkit Subsystem - Global access to RPG toolkit functionality\n * \n * This subsystem provides easy access to all RPG toolkit services\n * from anywhere in the game. It manages connections to the Seshat server\n * and provides Blueprint-accessible interfaces.\n */" },
#endif
		{ "IncludePath", "RpgToolkit/RpgToolkitSubsystem.h" },
		{ "ModuleRelativePath", "RpgToolkit/RpgToolkitSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "RPG Toolkit Subsystem - Global access to RPG toolkit functionality\n\nThis subsystem provides easy access to all RPG toolkit services\nfrom anywhere in the game. It manages connections to the Seshat server\nand provides Blueprint-accessible interfaces." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DiceRoller_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Dice rolling service */" },
#endif
		{ "ModuleRelativePath", "RpgToolkit/RpgToolkitSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Dice rolling service" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bServerConnected_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Server connection status */" },
#endif
		{ "ModuleRelativePath", "RpgToolkit/RpgToolkitSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Server connection status" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ServerUrl_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Server URL */" },
#endif
		{ "ModuleRelativePath", "RpgToolkit/RpgToolkitSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Server URL" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_DiceRoller;
	static void NewProp_bServerConnected_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bServerConnected;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ServerUrl;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_URpgToolkitSubsystem_GetDiceRoller, "GetDiceRoller" }, // 3446425509
		{ &Z_Construct_UFunction_URpgToolkitSubsystem_GetToolkitStatus, "GetToolkitStatus" }, // 3349913860
		{ &Z_Construct_UFunction_URpgToolkitSubsystem_InitializeServer, "InitializeServer" }, // 2927096099
		{ &Z_Construct_UFunction_URpgToolkitSubsystem_QuickRoll, "QuickRoll" }, // 3346031986
		{ &Z_Construct_UFunction_URpgToolkitSubsystem_QuickRollD20, "QuickRollD20" }, // 3965616687
		{ &Z_Construct_UFunction_URpgToolkitSubsystem_QuickRollMultiple, "QuickRollMultiple" }, // 2034996183
		{ &Z_Construct_UFunction_URpgToolkitSubsystem_RunDiagnostics, "RunDiagnostics" }, // 2838412587
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<URpgToolkitSubsystem>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_URpgToolkitSubsystem_Statics::NewProp_DiceRoller = { "DiceRoller", nullptr, (EPropertyFlags)0x0040000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(URpgToolkitSubsystem, DiceRoller), Z_Construct_UClass_URpgDiceRoller_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DiceRoller_MetaData), NewProp_DiceRoller_MetaData) };
void Z_Construct_UClass_URpgToolkitSubsystem_Statics::NewProp_bServerConnected_SetBit(void* Obj)
{
	((URpgToolkitSubsystem*)Obj)->bServerConnected = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_URpgToolkitSubsystem_Statics::NewProp_bServerConnected = { "bServerConnected", nullptr, (EPropertyFlags)0x0040000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(URpgToolkitSubsystem), &Z_Construct_UClass_URpgToolkitSubsystem_Statics::NewProp_bServerConnected_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bServerConnected_MetaData), NewProp_bServerConnected_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_URpgToolkitSubsystem_Statics::NewProp_ServerUrl = { "ServerUrl", nullptr, (EPropertyFlags)0x0040000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(URpgToolkitSubsystem, ServerUrl), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ServerUrl_MetaData), NewProp_ServerUrl_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_URpgToolkitSubsystem_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URpgToolkitSubsystem_Statics::NewProp_DiceRoller,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URpgToolkitSubsystem_Statics::NewProp_bServerConnected,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URpgToolkitSubsystem_Statics::NewProp_ServerUrl,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_URpgToolkitSubsystem_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_URpgToolkitSubsystem_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UGameInstanceSubsystem,
	(UObject* (*)())Z_Construct_UPackage__Script_Seshat,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_URpgToolkitSubsystem_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_URpgToolkitSubsystem_Statics::ClassParams = {
	&URpgToolkitSubsystem::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_URpgToolkitSubsystem_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_URpgToolkitSubsystem_Statics::PropPointers),
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_URpgToolkitSubsystem_Statics::Class_MetaDataParams), Z_Construct_UClass_URpgToolkitSubsystem_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_URpgToolkitSubsystem()
{
	if (!Z_Registration_Info_UClass_URpgToolkitSubsystem.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_URpgToolkitSubsystem.OuterSingleton, Z_Construct_UClass_URpgToolkitSubsystem_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_URpgToolkitSubsystem.OuterSingleton;
}
URpgToolkitSubsystem::URpgToolkitSubsystem() {}
DEFINE_VTABLE_PTR_HELPER_CTOR(URpgToolkitSubsystem);
URpgToolkitSubsystem::~URpgToolkitSubsystem() {}
// ********** End Class URpgToolkitSubsystem *******************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Projects_share_seshat_Seshat_Source_Seshat_RpgToolkit_RpgToolkitSubsystem_h__Script_Seshat_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_URpgToolkitSubsystem, URpgToolkitSubsystem::StaticClass, TEXT("URpgToolkitSubsystem"), &Z_Registration_Info_UClass_URpgToolkitSubsystem, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(URpgToolkitSubsystem), 3366283899U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Projects_share_seshat_Seshat_Source_Seshat_RpgToolkit_RpgToolkitSubsystem_h__Script_Seshat_752302949(TEXT("/Script/Seshat"),
	Z_CompiledInDeferFile_FID_Projects_share_seshat_Seshat_Source_Seshat_RpgToolkit_RpgToolkitSubsystem_h__Script_Seshat_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Projects_share_seshat_Seshat_Source_Seshat_RpgToolkit_RpgToolkitSubsystem_h__Script_Seshat_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
