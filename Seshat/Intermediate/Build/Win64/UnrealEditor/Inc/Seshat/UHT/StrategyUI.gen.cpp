// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Seshat/Variant_Strategy/StrategyUI.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeStrategyUI() {}

// ********** Begin Cross Module References ********************************************************
SESHAT_API UClass* Z_Construct_UClass_UStrategyUI();
SESHAT_API UClass* Z_Construct_UClass_UStrategyUI_NoRegister();
UMG_API UClass* Z_Construct_UClass_UUserWidget();
UPackage* Z_Construct_UPackage__Script_Seshat();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UStrategyUI Function BP_UpdateUnitsCount *********************************
static FName NAME_UStrategyUI_BP_UpdateUnitsCount = FName(TEXT("BP_UpdateUnitsCount"));
void UStrategyUI::BP_UpdateUnitsCount()
{
	UFunction* Func = FindFunctionChecked(NAME_UStrategyUI_BP_UpdateUnitsCount);
	ProcessEvent(Func,NULL);
}
struct Z_Construct_UFunction_UStrategyUI_BP_UpdateUnitsCount_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "UI" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Blueprint handler to update unit count sub-widgets */" },
#endif
		{ "DisplayName", "Update Units Count" },
		{ "ModuleRelativePath", "Variant_Strategy/StrategyUI.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Blueprint handler to update unit count sub-widgets" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UStrategyUI_BP_UpdateUnitsCount_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UStrategyUI, nullptr, "BP_UpdateUnitsCount", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08020800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UStrategyUI_BP_UpdateUnitsCount_Statics::Function_MetaDataParams), Z_Construct_UFunction_UStrategyUI_BP_UpdateUnitsCount_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_UStrategyUI_BP_UpdateUnitsCount()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UStrategyUI_BP_UpdateUnitsCount_Statics::FuncParams);
	}
	return ReturnFunction;
}
// ********** End Class UStrategyUI Function BP_UpdateUnitsCount ***********************************

// ********** Begin Class UStrategyUI Function GetSelectedUnitsCount *******************************
struct Z_Construct_UFunction_UStrategyUI_GetSelectedUnitsCount_Statics
{
	struct StrategyUI_eventGetSelectedUnitsCount_Parms
	{
		int32 ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "UI" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Returns the number of units selected */" },
#endif
		{ "ModuleRelativePath", "Variant_Strategy/StrategyUI.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Returns the number of units selected" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UStrategyUI_GetSelectedUnitsCount_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(StrategyUI_eventGetSelectedUnitsCount_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UStrategyUI_GetSelectedUnitsCount_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UStrategyUI_GetSelectedUnitsCount_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UStrategyUI_GetSelectedUnitsCount_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UStrategyUI_GetSelectedUnitsCount_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UStrategyUI, nullptr, "GetSelectedUnitsCount", Z_Construct_UFunction_UStrategyUI_GetSelectedUnitsCount_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UStrategyUI_GetSelectedUnitsCount_Statics::PropPointers), sizeof(Z_Construct_UFunction_UStrategyUI_GetSelectedUnitsCount_Statics::StrategyUI_eventGetSelectedUnitsCount_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UStrategyUI_GetSelectedUnitsCount_Statics::Function_MetaDataParams), Z_Construct_UFunction_UStrategyUI_GetSelectedUnitsCount_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UStrategyUI_GetSelectedUnitsCount_Statics::StrategyUI_eventGetSelectedUnitsCount_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UStrategyUI_GetSelectedUnitsCount()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UStrategyUI_GetSelectedUnitsCount_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UStrategyUI::execGetSelectedUnitsCount)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(int32*)Z_Param__Result=P_THIS->GetSelectedUnitsCount();
	P_NATIVE_END;
}
// ********** End Class UStrategyUI Function GetSelectedUnitsCount *********************************

// ********** Begin Class UStrategyUI **************************************************************
void UStrategyUI::StaticRegisterNativesUStrategyUI()
{
	UClass* Class = UStrategyUI::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "GetSelectedUnitsCount", &UStrategyUI::execGetSelectedUnitsCount },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_UStrategyUI;
UClass* UStrategyUI::GetPrivateStaticClass()
{
	using TClass = UStrategyUI;
	if (!Z_Registration_Info_UClass_UStrategyUI.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("StrategyUI"),
			Z_Registration_Info_UClass_UStrategyUI.InnerSingleton,
			StaticRegisterNativesUStrategyUI,
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
	return Z_Registration_Info_UClass_UStrategyUI.InnerSingleton;
}
UClass* Z_Construct_UClass_UStrategyUI_NoRegister()
{
	return UStrategyUI::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UStrategyUI_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  Simple UI widget for the strategy game\n *\x09Keeps track of the number of units currently selected\n */" },
#endif
		{ "IncludePath", "Variant_Strategy/StrategyUI.h" },
		{ "ModuleRelativePath", "Variant_Strategy/StrategyUI.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Simple UI widget for the strategy game\n   Keeps track of the number of units currently selected" },
#endif
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UStrategyUI_BP_UpdateUnitsCount, "BP_UpdateUnitsCount" }, // 677498334
		{ &Z_Construct_UFunction_UStrategyUI_GetSelectedUnitsCount, "GetSelectedUnitsCount" }, // 3741344939
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UStrategyUI>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UStrategyUI_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UUserWidget,
	(UObject* (*)())Z_Construct_UPackage__Script_Seshat,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UStrategyUI_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UStrategyUI_Statics::ClassParams = {
	&UStrategyUI::StaticClass,
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
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UStrategyUI_Statics::Class_MetaDataParams), Z_Construct_UClass_UStrategyUI_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UStrategyUI()
{
	if (!Z_Registration_Info_UClass_UStrategyUI.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UStrategyUI.OuterSingleton, Z_Construct_UClass_UStrategyUI_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UStrategyUI.OuterSingleton;
}
UStrategyUI::UStrategyUI(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UStrategyUI);
UStrategyUI::~UStrategyUI() {}
// ********** End Class UStrategyUI ****************************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_Strategy_StrategyUI_h__Script_Seshat_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UStrategyUI, UStrategyUI::StaticClass, TEXT("UStrategyUI"), &Z_Registration_Info_UClass_UStrategyUI, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UStrategyUI), 2688872448U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_Strategy_StrategyUI_h__Script_Seshat_3152765619(TEXT("/Script/Seshat"),
	Z_CompiledInDeferFile_FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_Strategy_StrategyUI_h__Script_Seshat_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_Strategy_StrategyUI_h__Script_Seshat_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
