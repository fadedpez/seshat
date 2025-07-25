// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Seshat/Variant_TwinStick/AI/TwinStickStateTreeUtility.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeTwinStickStateTreeUtility() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_ACharacter_NoRegister();
SESHAT_API UScriptStruct* Z_Construct_UScriptStruct_FStateTreeGetPlayerInstanceData();
SESHAT_API UScriptStruct* Z_Construct_UScriptStruct_FStateTreeGetPlayerTask();
STATETREEMODULE_API UScriptStruct* Z_Construct_UScriptStruct_FStateTreeTaskCommonBase();
UPackage* Z_Construct_UPackage__Script_Seshat();
// ********** End Cross Module References **********************************************************

// ********** Begin ScriptStruct FStateTreeGetPlayerInstanceData ***********************************
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FStateTreeGetPlayerInstanceData;
class UScriptStruct* FStateTreeGetPlayerInstanceData::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FStateTreeGetPlayerInstanceData.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FStateTreeGetPlayerInstanceData.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FStateTreeGetPlayerInstanceData, (UObject*)Z_Construct_UPackage__Script_Seshat(), TEXT("StateTreeGetPlayerInstanceData"));
	}
	return Z_Registration_Info_UScriptStruct_FStateTreeGetPlayerInstanceData.OuterSingleton;
}
struct Z_Construct_UScriptStruct_FStateTreeGetPlayerInstanceData_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  Instance data struct for the Get Player task\n */" },
#endif
		{ "ModuleRelativePath", "Variant_TwinStick/AI/TwinStickStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Instance data struct for the Get Player task" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Character_MetaData[] = {
		{ "Category", "Context" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Character that owns this task */" },
#endif
		{ "ModuleRelativePath", "Variant_TwinStick/AI/TwinStickStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Character that owns this task" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TargetPlayerCharacter_MetaData[] = {
		{ "Category", "StateTreeGetPlayerInstanceData" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Character that owns this task */" },
#endif
		{ "ModuleRelativePath", "Variant_TwinStick/AI/TwinStickStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Character that owns this task" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Character;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_TargetPlayerCharacter;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FStateTreeGetPlayerInstanceData>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UScriptStruct_FStateTreeGetPlayerInstanceData_Statics::NewProp_Character = { "Character", nullptr, (EPropertyFlags)0x0114000000000001, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FStateTreeGetPlayerInstanceData, Character), Z_Construct_UClass_ACharacter_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Character_MetaData), NewProp_Character_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UScriptStruct_FStateTreeGetPlayerInstanceData_Statics::NewProp_TargetPlayerCharacter = { "TargetPlayerCharacter", nullptr, (EPropertyFlags)0x0114000000020001, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FStateTreeGetPlayerInstanceData, TargetPlayerCharacter), Z_Construct_UClass_ACharacter_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TargetPlayerCharacter_MetaData), NewProp_TargetPlayerCharacter_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FStateTreeGetPlayerInstanceData_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FStateTreeGetPlayerInstanceData_Statics::NewProp_Character,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FStateTreeGetPlayerInstanceData_Statics::NewProp_TargetPlayerCharacter,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FStateTreeGetPlayerInstanceData_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FStateTreeGetPlayerInstanceData_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_Seshat,
	nullptr,
	&NewStructOps,
	"StateTreeGetPlayerInstanceData",
	Z_Construct_UScriptStruct_FStateTreeGetPlayerInstanceData_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FStateTreeGetPlayerInstanceData_Statics::PropPointers),
	sizeof(FStateTreeGetPlayerInstanceData),
	alignof(FStateTreeGetPlayerInstanceData),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FStateTreeGetPlayerInstanceData_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FStateTreeGetPlayerInstanceData_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FStateTreeGetPlayerInstanceData()
{
	if (!Z_Registration_Info_UScriptStruct_FStateTreeGetPlayerInstanceData.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FStateTreeGetPlayerInstanceData.InnerSingleton, Z_Construct_UScriptStruct_FStateTreeGetPlayerInstanceData_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_FStateTreeGetPlayerInstanceData.InnerSingleton;
}
// ********** End ScriptStruct FStateTreeGetPlayerInstanceData *************************************

// ********** Begin ScriptStruct FStateTreeGetPlayerTask *******************************************
static_assert(std::is_polymorphic<FStateTreeGetPlayerTask>() == std::is_polymorphic<FStateTreeTaskCommonBase>(), "USTRUCT FStateTreeGetPlayerTask cannot be polymorphic unless super FStateTreeTaskCommonBase is polymorphic");
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FStateTreeGetPlayerTask;
class UScriptStruct* FStateTreeGetPlayerTask::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FStateTreeGetPlayerTask.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FStateTreeGetPlayerTask.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FStateTreeGetPlayerTask, (UObject*)Z_Construct_UPackage__Script_Seshat(), TEXT("StateTreeGetPlayerTask"));
	}
	return Z_Registration_Info_UScriptStruct_FStateTreeGetPlayerTask.OuterSingleton;
}
struct Z_Construct_UScriptStruct_FStateTreeGetPlayerTask_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "Category", "TwinStick" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  StateTree task to get the player character\n */" },
#endif
		{ "DisplayName", "GetPlayer" },
		{ "ModuleRelativePath", "Variant_TwinStick/AI/TwinStickStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "StateTree task to get the player character" },
#endif
	};
#endif // WITH_METADATA
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FStateTreeGetPlayerTask>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FStateTreeGetPlayerTask_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_Seshat,
	Z_Construct_UScriptStruct_FStateTreeTaskCommonBase,
	&NewStructOps,
	"StateTreeGetPlayerTask",
	nullptr,
	0,
	sizeof(FStateTreeGetPlayerTask),
	alignof(FStateTreeGetPlayerTask),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FStateTreeGetPlayerTask_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FStateTreeGetPlayerTask_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FStateTreeGetPlayerTask()
{
	if (!Z_Registration_Info_UScriptStruct_FStateTreeGetPlayerTask.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FStateTreeGetPlayerTask.InnerSingleton, Z_Construct_UScriptStruct_FStateTreeGetPlayerTask_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_FStateTreeGetPlayerTask.InnerSingleton;
}
// ********** End ScriptStruct FStateTreeGetPlayerTask *********************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_TwinStick_AI_TwinStickStateTreeUtility_h__Script_Seshat_Statics
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FStateTreeGetPlayerInstanceData::StaticStruct, Z_Construct_UScriptStruct_FStateTreeGetPlayerInstanceData_Statics::NewStructOps, TEXT("StateTreeGetPlayerInstanceData"), &Z_Registration_Info_UScriptStruct_FStateTreeGetPlayerInstanceData, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FStateTreeGetPlayerInstanceData), 3735378663U) },
		{ FStateTreeGetPlayerTask::StaticStruct, Z_Construct_UScriptStruct_FStateTreeGetPlayerTask_Statics::NewStructOps, TEXT("StateTreeGetPlayerTask"), &Z_Registration_Info_UScriptStruct_FStateTreeGetPlayerTask, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FStateTreeGetPlayerTask), 3072982316U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_TwinStick_AI_TwinStickStateTreeUtility_h__Script_Seshat_2927433825(TEXT("/Script/Seshat"),
	nullptr, 0,
	Z_CompiledInDeferFile_FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_TwinStick_AI_TwinStickStateTreeUtility_h__Script_Seshat_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_TwinStick_AI_TwinStickStateTreeUtility_h__Script_Seshat_Statics::ScriptStructInfo),
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
