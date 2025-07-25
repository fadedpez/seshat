// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Seshat/Variant_Strategy/StrategyUnit.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeStrategyUnit() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_ACharacter();
ENGINE_API UClass* Z_Construct_UClass_USphereComponent_NoRegister();
SESHAT_API UClass* Z_Construct_UClass_AStrategyUnit();
SESHAT_API UClass* Z_Construct_UClass_AStrategyUnit_NoRegister();
SESHAT_API UFunction* Z_Construct_UDelegateFunction_Seshat_OnUnitMoveCompletedDelegate__DelegateSignature();
UPackage* Z_Construct_UPackage__Script_Seshat();
// ********** End Cross Module References **********************************************************

// ********** Begin Delegate FOnUnitMoveCompletedDelegate ******************************************
struct Z_Construct_UDelegateFunction_Seshat_OnUnitMoveCompletedDelegate__DelegateSignature_Statics
{
	struct _Script_Seshat_eventOnUnitMoveCompletedDelegate_Parms
	{
		AStrategyUnit* Unit;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Delegate to report that this unit has finished moving */" },
#endif
		{ "ModuleRelativePath", "Variant_Strategy/StrategyUnit.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Delegate to report that this unit has finished moving" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Unit;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FDelegateFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UDelegateFunction_Seshat_OnUnitMoveCompletedDelegate__DelegateSignature_Statics::NewProp_Unit = { "Unit", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_Seshat_eventOnUnitMoveCompletedDelegate_Parms, Unit), Z_Construct_UClass_AStrategyUnit_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_Seshat_OnUnitMoveCompletedDelegate__DelegateSignature_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_Seshat_OnUnitMoveCompletedDelegate__DelegateSignature_Statics::NewProp_Unit,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_Seshat_OnUnitMoveCompletedDelegate__DelegateSignature_Statics::PropPointers) < 2048);
const UECodeGen_Private::FDelegateFunctionParams Z_Construct_UDelegateFunction_Seshat_OnUnitMoveCompletedDelegate__DelegateSignature_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UPackage__Script_Seshat, nullptr, "OnUnitMoveCompletedDelegate__DelegateSignature", Z_Construct_UDelegateFunction_Seshat_OnUnitMoveCompletedDelegate__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_Seshat_OnUnitMoveCompletedDelegate__DelegateSignature_Statics::PropPointers), sizeof(Z_Construct_UDelegateFunction_Seshat_OnUnitMoveCompletedDelegate__DelegateSignature_Statics::_Script_Seshat_eventOnUnitMoveCompletedDelegate_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_Seshat_OnUnitMoveCompletedDelegate__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_Seshat_OnUnitMoveCompletedDelegate__DelegateSignature_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UDelegateFunction_Seshat_OnUnitMoveCompletedDelegate__DelegateSignature_Statics::_Script_Seshat_eventOnUnitMoveCompletedDelegate_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_Seshat_OnUnitMoveCompletedDelegate__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUDelegateFunction(&ReturnFunction, Z_Construct_UDelegateFunction_Seshat_OnUnitMoveCompletedDelegate__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FOnUnitMoveCompletedDelegate_DelegateWrapper(const FMulticastScriptDelegate& OnUnitMoveCompletedDelegate, AStrategyUnit* Unit)
{
	struct _Script_Seshat_eventOnUnitMoveCompletedDelegate_Parms
	{
		AStrategyUnit* Unit;
	};
	_Script_Seshat_eventOnUnitMoveCompletedDelegate_Parms Parms;
	Parms.Unit=Unit;
	OnUnitMoveCompletedDelegate.ProcessMulticastDelegate<UObject>(&Parms);
}
// ********** End Delegate FOnUnitMoveCompletedDelegate ********************************************

// ********** Begin Class AStrategyUnit Function BP_InteractionBehavior ****************************
struct StrategyUnit_eventBP_InteractionBehavior_Parms
{
	AStrategyUnit* Interactor;
};
static FName NAME_AStrategyUnit_BP_InteractionBehavior = FName(TEXT("BP_InteractionBehavior"));
void AStrategyUnit::BP_InteractionBehavior(AStrategyUnit* Interactor)
{
	StrategyUnit_eventBP_InteractionBehavior_Parms Parms;
	Parms.Interactor=Interactor;
	UFunction* Func = FindFunctionChecked(NAME_AStrategyUnit_BP_InteractionBehavior);
	ProcessEvent(Func,&Parms);
}
struct Z_Construct_UFunction_AStrategyUnit_BP_InteractionBehavior_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "NPC" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Blueprint handler for strategy game interactions */" },
#endif
		{ "DisplayName", "Interaction Behavior" },
		{ "ModuleRelativePath", "Variant_Strategy/StrategyUnit.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Blueprint handler for strategy game interactions" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Interactor;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_AStrategyUnit_BP_InteractionBehavior_Statics::NewProp_Interactor = { "Interactor", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(StrategyUnit_eventBP_InteractionBehavior_Parms, Interactor), Z_Construct_UClass_AStrategyUnit_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AStrategyUnit_BP_InteractionBehavior_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AStrategyUnit_BP_InteractionBehavior_Statics::NewProp_Interactor,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AStrategyUnit_BP_InteractionBehavior_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AStrategyUnit_BP_InteractionBehavior_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AStrategyUnit, nullptr, "BP_InteractionBehavior", Z_Construct_UFunction_AStrategyUnit_BP_InteractionBehavior_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AStrategyUnit_BP_InteractionBehavior_Statics::PropPointers), sizeof(StrategyUnit_eventBP_InteractionBehavior_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08080800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AStrategyUnit_BP_InteractionBehavior_Statics::Function_MetaDataParams), Z_Construct_UFunction_AStrategyUnit_BP_InteractionBehavior_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(StrategyUnit_eventBP_InteractionBehavior_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AStrategyUnit_BP_InteractionBehavior()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AStrategyUnit_BP_InteractionBehavior_Statics::FuncParams);
	}
	return ReturnFunction;
}
// ********** End Class AStrategyUnit Function BP_InteractionBehavior ******************************

// ********** Begin Class AStrategyUnit Function BP_UnitDeselected *********************************
static FName NAME_AStrategyUnit_BP_UnitDeselected = FName(TEXT("BP_UnitDeselected"));
void AStrategyUnit::BP_UnitDeselected()
{
	UFunction* Func = FindFunctionChecked(NAME_AStrategyUnit_BP_UnitDeselected);
	ProcessEvent(Func,NULL);
}
struct Z_Construct_UFunction_AStrategyUnit_BP_UnitDeselected_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "NPC" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Blueprint handler for strategy game deselection */" },
#endif
		{ "DisplayName", "Unit Deselected" },
		{ "ModuleRelativePath", "Variant_Strategy/StrategyUnit.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Blueprint handler for strategy game deselection" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AStrategyUnit_BP_UnitDeselected_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AStrategyUnit, nullptr, "BP_UnitDeselected", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08080800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AStrategyUnit_BP_UnitDeselected_Statics::Function_MetaDataParams), Z_Construct_UFunction_AStrategyUnit_BP_UnitDeselected_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_AStrategyUnit_BP_UnitDeselected()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AStrategyUnit_BP_UnitDeselected_Statics::FuncParams);
	}
	return ReturnFunction;
}
// ********** End Class AStrategyUnit Function BP_UnitDeselected ***********************************

// ********** Begin Class AStrategyUnit Function BP_UnitSelected ***********************************
static FName NAME_AStrategyUnit_BP_UnitSelected = FName(TEXT("BP_UnitSelected"));
void AStrategyUnit::BP_UnitSelected()
{
	UFunction* Func = FindFunctionChecked(NAME_AStrategyUnit_BP_UnitSelected);
	ProcessEvent(Func,NULL);
}
struct Z_Construct_UFunction_AStrategyUnit_BP_UnitSelected_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "NPC" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Blueprint handler for strategy game selection */" },
#endif
		{ "DisplayName", "Unit Selected" },
		{ "ModuleRelativePath", "Variant_Strategy/StrategyUnit.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Blueprint handler for strategy game selection" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AStrategyUnit_BP_UnitSelected_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AStrategyUnit, nullptr, "BP_UnitSelected", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08080800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AStrategyUnit_BP_UnitSelected_Statics::Function_MetaDataParams), Z_Construct_UFunction_AStrategyUnit_BP_UnitSelected_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_AStrategyUnit_BP_UnitSelected()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AStrategyUnit_BP_UnitSelected_Statics::FuncParams);
	}
	return ReturnFunction;
}
// ********** End Class AStrategyUnit Function BP_UnitSelected *************************************

// ********** Begin Class AStrategyUnit ************************************************************
void AStrategyUnit::StaticRegisterNativesAStrategyUnit()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_AStrategyUnit;
UClass* AStrategyUnit::GetPrivateStaticClass()
{
	using TClass = AStrategyUnit;
	if (!Z_Registration_Info_UClass_AStrategyUnit.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("StrategyUnit"),
			Z_Registration_Info_UClass_AStrategyUnit.InnerSingleton,
			StaticRegisterNativesAStrategyUnit,
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
	return Z_Registration_Info_UClass_AStrategyUnit.InnerSingleton;
}
UClass* Z_Construct_UClass_AStrategyUnit_NoRegister()
{
	return AStrategyUnit::GetPrivateStaticClass();
}
struct Z_Construct_UClass_AStrategyUnit_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  A simple strategy game unit\n *  Rather than react to inputs, it's controlled indirectly by the Strategy Player Controller\n */" },
#endif
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "Variant_Strategy/StrategyUnit.h" },
		{ "ModuleRelativePath", "Variant_Strategy/StrategyUnit.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "A simple strategy game unit\nRather than react to inputs, it's controlled indirectly by the Strategy Player Controller" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InteractionRange_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Components" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Interaction range sphere */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Variant_Strategy/StrategyUnit.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Interaction range sphere" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_InteractionRange;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_AStrategyUnit_BP_InteractionBehavior, "BP_InteractionBehavior" }, // 2523288698
		{ &Z_Construct_UFunction_AStrategyUnit_BP_UnitDeselected, "BP_UnitDeselected" }, // 271370798
		{ &Z_Construct_UFunction_AStrategyUnit_BP_UnitSelected, "BP_UnitSelected" }, // 3916570923
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AStrategyUnit>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AStrategyUnit_Statics::NewProp_InteractionRange = { "InteractionRange", nullptr, (EPropertyFlags)0x00400000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AStrategyUnit, InteractionRange), Z_Construct_UClass_USphereComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InteractionRange_MetaData), NewProp_InteractionRange_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AStrategyUnit_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AStrategyUnit_Statics::NewProp_InteractionRange,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AStrategyUnit_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_AStrategyUnit_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_ACharacter,
	(UObject* (*)())Z_Construct_UPackage__Script_Seshat,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AStrategyUnit_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AStrategyUnit_Statics::ClassParams = {
	&AStrategyUnit::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_AStrategyUnit_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_AStrategyUnit_Statics::PropPointers),
	0,
	0x008001A5u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AStrategyUnit_Statics::Class_MetaDataParams), Z_Construct_UClass_AStrategyUnit_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AStrategyUnit()
{
	if (!Z_Registration_Info_UClass_AStrategyUnit.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AStrategyUnit.OuterSingleton, Z_Construct_UClass_AStrategyUnit_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AStrategyUnit.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(AStrategyUnit);
AStrategyUnit::~AStrategyUnit() {}
// ********** End Class AStrategyUnit **************************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_Strategy_StrategyUnit_h__Script_Seshat_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AStrategyUnit, AStrategyUnit::StaticClass, TEXT("AStrategyUnit"), &Z_Registration_Info_UClass_AStrategyUnit, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AStrategyUnit), 337515214U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_Strategy_StrategyUnit_h__Script_Seshat_89518004(TEXT("/Script/Seshat"),
	Z_CompiledInDeferFile_FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_Strategy_StrategyUnit_h__Script_Seshat_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_Strategy_StrategyUnit_h__Script_Seshat_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
