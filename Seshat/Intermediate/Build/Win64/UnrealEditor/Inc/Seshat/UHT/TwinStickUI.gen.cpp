// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Seshat/Variant_TwinStick/TwinStickUI.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeTwinStickUI() {}

// ********** Begin Cross Module References ********************************************************
SESHAT_API UClass* Z_Construct_UClass_UTwinStickUI();
SESHAT_API UClass* Z_Construct_UClass_UTwinStickUI_NoRegister();
UMG_API UClass* Z_Construct_UClass_UUserWidget();
UPackage* Z_Construct_UPackage__Script_Seshat();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UTwinStickUI Function UpdateCombo ****************************************
struct TwinStickUI_eventUpdateCombo_Parms
{
	int32 Combo;
};
static FName NAME_UTwinStickUI_UpdateCombo = FName(TEXT("UpdateCombo"));
void UTwinStickUI::UpdateCombo(int32 Combo)
{
	TwinStickUI_eventUpdateCombo_Parms Parms;
	Parms.Combo=Combo;
	UFunction* Func = FindFunctionChecked(NAME_UTwinStickUI_UpdateCombo);
	ProcessEvent(Func,&Parms);
}
struct Z_Construct_UFunction_UTwinStickUI_UpdateCombo_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Score" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Blueprint handler to update the combo sub-widgets */" },
#endif
		{ "ModuleRelativePath", "Variant_TwinStick/TwinStickUI.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Blueprint handler to update the combo sub-widgets" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FIntPropertyParams NewProp_Combo;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UTwinStickUI_UpdateCombo_Statics::NewProp_Combo = { "Combo", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(TwinStickUI_eventUpdateCombo_Parms, Combo), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UTwinStickUI_UpdateCombo_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UTwinStickUI_UpdateCombo_Statics::NewProp_Combo,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UTwinStickUI_UpdateCombo_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UTwinStickUI_UpdateCombo_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UTwinStickUI, nullptr, "UpdateCombo", Z_Construct_UFunction_UTwinStickUI_UpdateCombo_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UTwinStickUI_UpdateCombo_Statics::PropPointers), sizeof(TwinStickUI_eventUpdateCombo_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08020800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UTwinStickUI_UpdateCombo_Statics::Function_MetaDataParams), Z_Construct_UFunction_UTwinStickUI_UpdateCombo_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(TwinStickUI_eventUpdateCombo_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UTwinStickUI_UpdateCombo()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UTwinStickUI_UpdateCombo_Statics::FuncParams);
	}
	return ReturnFunction;
}
// ********** End Class UTwinStickUI Function UpdateCombo ******************************************

// ********** Begin Class UTwinStickUI Function UpdateItems ****************************************
struct TwinStickUI_eventUpdateItems_Parms
{
	int32 Score;
};
static FName NAME_UTwinStickUI_UpdateItems = FName(TEXT("UpdateItems"));
void UTwinStickUI::UpdateItems(int32 Score)
{
	TwinStickUI_eventUpdateItems_Parms Parms;
	Parms.Score=Score;
	UFunction* Func = FindFunctionChecked(NAME_UTwinStickUI_UpdateItems);
	ProcessEvent(Func,&Parms);
}
struct Z_Construct_UFunction_UTwinStickUI_UpdateItems_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Score" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Blueprint handler to update the items counter */" },
#endif
		{ "ModuleRelativePath", "Variant_TwinStick/TwinStickUI.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Blueprint handler to update the items counter" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FIntPropertyParams NewProp_Score;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UTwinStickUI_UpdateItems_Statics::NewProp_Score = { "Score", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(TwinStickUI_eventUpdateItems_Parms, Score), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UTwinStickUI_UpdateItems_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UTwinStickUI_UpdateItems_Statics::NewProp_Score,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UTwinStickUI_UpdateItems_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UTwinStickUI_UpdateItems_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UTwinStickUI, nullptr, "UpdateItems", Z_Construct_UFunction_UTwinStickUI_UpdateItems_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UTwinStickUI_UpdateItems_Statics::PropPointers), sizeof(TwinStickUI_eventUpdateItems_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08020800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UTwinStickUI_UpdateItems_Statics::Function_MetaDataParams), Z_Construct_UFunction_UTwinStickUI_UpdateItems_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(TwinStickUI_eventUpdateItems_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UTwinStickUI_UpdateItems()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UTwinStickUI_UpdateItems_Statics::FuncParams);
	}
	return ReturnFunction;
}
// ********** End Class UTwinStickUI Function UpdateItems ******************************************

// ********** Begin Class UTwinStickUI Function UpdateScore ****************************************
struct TwinStickUI_eventUpdateScore_Parms
{
	int32 Score;
};
static FName NAME_UTwinStickUI_UpdateScore = FName(TEXT("UpdateScore"));
void UTwinStickUI::UpdateScore(int32 Score)
{
	TwinStickUI_eventUpdateScore_Parms Parms;
	Parms.Score=Score;
	UFunction* Func = FindFunctionChecked(NAME_UTwinStickUI_UpdateScore);
	ProcessEvent(Func,&Parms);
}
struct Z_Construct_UFunction_UTwinStickUI_UpdateScore_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Score" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Blueprint handler to update the score sub-widgets */" },
#endif
		{ "ModuleRelativePath", "Variant_TwinStick/TwinStickUI.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Blueprint handler to update the score sub-widgets" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FIntPropertyParams NewProp_Score;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UTwinStickUI_UpdateScore_Statics::NewProp_Score = { "Score", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(TwinStickUI_eventUpdateScore_Parms, Score), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UTwinStickUI_UpdateScore_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UTwinStickUI_UpdateScore_Statics::NewProp_Score,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UTwinStickUI_UpdateScore_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UTwinStickUI_UpdateScore_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UTwinStickUI, nullptr, "UpdateScore", Z_Construct_UFunction_UTwinStickUI_UpdateScore_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UTwinStickUI_UpdateScore_Statics::PropPointers), sizeof(TwinStickUI_eventUpdateScore_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08020800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UTwinStickUI_UpdateScore_Statics::Function_MetaDataParams), Z_Construct_UFunction_UTwinStickUI_UpdateScore_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(TwinStickUI_eventUpdateScore_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UTwinStickUI_UpdateScore()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UTwinStickUI_UpdateScore_Statics::FuncParams);
	}
	return ReturnFunction;
}
// ********** End Class UTwinStickUI Function UpdateScore ******************************************

// ********** Begin Class UTwinStickUI *************************************************************
void UTwinStickUI::StaticRegisterNativesUTwinStickUI()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_UTwinStickUI;
UClass* UTwinStickUI::GetPrivateStaticClass()
{
	using TClass = UTwinStickUI;
	if (!Z_Registration_Info_UClass_UTwinStickUI.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("TwinStickUI"),
			Z_Registration_Info_UClass_UTwinStickUI.InnerSingleton,
			StaticRegisterNativesUTwinStickUI,
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
	return Z_Registration_Info_UClass_UTwinStickUI.InnerSingleton;
}
UClass* Z_Construct_UClass_UTwinStickUI_NoRegister()
{
	return UTwinStickUI::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UTwinStickUI_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  A simple Twin Stick Shooter UI widget\n *  Provides a blueprint interface to expose score values to the UI\n */" },
#endif
		{ "IncludePath", "Variant_TwinStick/TwinStickUI.h" },
		{ "ModuleRelativePath", "Variant_TwinStick/TwinStickUI.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "A simple Twin Stick Shooter UI widget\nProvides a blueprint interface to expose score values to the UI" },
#endif
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UTwinStickUI_UpdateCombo, "UpdateCombo" }, // 3363646061
		{ &Z_Construct_UFunction_UTwinStickUI_UpdateItems, "UpdateItems" }, // 2219142936
		{ &Z_Construct_UFunction_UTwinStickUI_UpdateScore, "UpdateScore" }, // 928918212
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UTwinStickUI>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UTwinStickUI_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UUserWidget,
	(UObject* (*)())Z_Construct_UPackage__Script_Seshat,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UTwinStickUI_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UTwinStickUI_Statics::ClassParams = {
	&UTwinStickUI::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	0,
	0,
	0x00A010A1u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UTwinStickUI_Statics::Class_MetaDataParams), Z_Construct_UClass_UTwinStickUI_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UTwinStickUI()
{
	if (!Z_Registration_Info_UClass_UTwinStickUI.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UTwinStickUI.OuterSingleton, Z_Construct_UClass_UTwinStickUI_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UTwinStickUI.OuterSingleton;
}
UTwinStickUI::UTwinStickUI(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UTwinStickUI);
UTwinStickUI::~UTwinStickUI() {}
// ********** End Class UTwinStickUI ***************************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_TwinStick_TwinStickUI_h__Script_Seshat_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UTwinStickUI, UTwinStickUI::StaticClass, TEXT("UTwinStickUI"), &Z_Registration_Info_UClass_UTwinStickUI, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UTwinStickUI), 545978231U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_TwinStick_TwinStickUI_h__Script_Seshat_2957415478(TEXT("/Script/Seshat"),
	Z_CompiledInDeferFile_FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_TwinStick_TwinStickUI_h__Script_Seshat_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_TwinStick_TwinStickUI_h__Script_Seshat_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
