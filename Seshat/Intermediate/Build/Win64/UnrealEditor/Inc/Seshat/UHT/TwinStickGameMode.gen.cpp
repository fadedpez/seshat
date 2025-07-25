// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Seshat/Variant_TwinStick/TwinStickGameMode.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeTwinStickGameMode() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
SESHAT_API UClass* Z_Construct_UClass_ATwinStickGameMode();
SESHAT_API UClass* Z_Construct_UClass_ATwinStickGameMode_NoRegister();
SESHAT_API UClass* Z_Construct_UClass_UTwinStickUI_NoRegister();
UPackage* Z_Construct_UPackage__Script_Seshat();
// ********** End Cross Module References **********************************************************

// ********** Begin Class ATwinStickGameMode *******************************************************
void ATwinStickGameMode::StaticRegisterNativesATwinStickGameMode()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_ATwinStickGameMode;
UClass* ATwinStickGameMode::GetPrivateStaticClass()
{
	using TClass = ATwinStickGameMode;
	if (!Z_Registration_Info_UClass_ATwinStickGameMode.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("TwinStickGameMode"),
			Z_Registration_Info_UClass_ATwinStickGameMode.InnerSingleton,
			StaticRegisterNativesATwinStickGameMode,
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
	return Z_Registration_Info_UClass_ATwinStickGameMode.InnerSingleton;
}
UClass* Z_Construct_UClass_ATwinStickGameMode_NoRegister()
{
	return ATwinStickGameMode::GetPrivateStaticClass();
}
struct Z_Construct_UClass_ATwinStickGameMode_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  Simple Game Mode for a Twin Stick Shooter game.\n *  Manages the score and UI\n */" },
#endif
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "Variant_TwinStick/TwinStickGameMode.h" },
		{ "ModuleRelativePath", "Variant_TwinStick/TwinStickGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Simple Game Mode for a Twin Stick Shooter game.\nManages the score and UI" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_UIWidgetClass_MetaData[] = {
		{ "Category", "Twin Stick" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Type of UI Widget to spawn */" },
#endif
		{ "ModuleRelativePath", "Variant_TwinStick/TwinStickGameMode.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Type of UI Widget to spawn" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ComboIncrementMax_MetaData[] = {
		{ "Category", "Twin Stick" },
		{ "ClampMax", "10" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Number of combo hits to process before incrementing the combo multiplier */" },
#endif
		{ "ModuleRelativePath", "Variant_TwinStick/TwinStickGameMode.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Number of combo hits to process before incrementing the combo multiplier" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ComboCap_MetaData[] = {
		{ "Category", "Twin Stick" },
		{ "ClampMax", "10" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Maximum allowed combo multiplier value */" },
#endif
		{ "ModuleRelativePath", "Variant_TwinStick/TwinStickGameMode.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Maximum allowed combo multiplier value" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ComboCooldown_MetaData[] = {
		{ "Category", "Twin Stick" },
		{ "ClampMax", "10" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Max time between kills before the combo multiplier resets */" },
#endif
		{ "ModuleRelativePath", "Variant_TwinStick/TwinStickGameMode.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Max time between kills before the combo multiplier resets" },
#endif
		{ "Units", "s" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NPCCap_MetaData[] = {
		{ "Category", "Twin Stick" },
		{ "ClampMax", "100" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Max number of NPCs to allow in the level at once */" },
#endif
		{ "ModuleRelativePath", "Variant_TwinStick/TwinStickGameMode.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Max number of NPCs to allow in the level at once" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FClassPropertyParams NewProp_UIWidgetClass;
	static const UECodeGen_Private::FIntPropertyParams NewProp_ComboIncrementMax;
	static const UECodeGen_Private::FIntPropertyParams NewProp_ComboCap;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ComboCooldown;
	static const UECodeGen_Private::FIntPropertyParams NewProp_NPCCap;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ATwinStickGameMode>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_ATwinStickGameMode_Statics::NewProp_UIWidgetClass = { "UIWidgetClass", nullptr, (EPropertyFlags)0x0024080000000001, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ATwinStickGameMode, UIWidgetClass), Z_Construct_UClass_UClass, Z_Construct_UClass_UTwinStickUI_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_UIWidgetClass_MetaData), NewProp_UIWidgetClass_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_ATwinStickGameMode_Statics::NewProp_ComboIncrementMax = { "ComboIncrementMax", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ATwinStickGameMode, ComboIncrementMax), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ComboIncrementMax_MetaData), NewProp_ComboIncrementMax_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_ATwinStickGameMode_Statics::NewProp_ComboCap = { "ComboCap", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ATwinStickGameMode, ComboCap), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ComboCap_MetaData), NewProp_ComboCap_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ATwinStickGameMode_Statics::NewProp_ComboCooldown = { "ComboCooldown", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ATwinStickGameMode, ComboCooldown), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ComboCooldown_MetaData), NewProp_ComboCooldown_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_ATwinStickGameMode_Statics::NewProp_NPCCap = { "NPCCap", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ATwinStickGameMode, NPCCap), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NPCCap_MetaData), NewProp_NPCCap_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ATwinStickGameMode_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATwinStickGameMode_Statics::NewProp_UIWidgetClass,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATwinStickGameMode_Statics::NewProp_ComboIncrementMax,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATwinStickGameMode_Statics::NewProp_ComboCap,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATwinStickGameMode_Statics::NewProp_ComboCooldown,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATwinStickGameMode_Statics::NewProp_NPCCap,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ATwinStickGameMode_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_ATwinStickGameMode_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AGameModeBase,
	(UObject* (*)())Z_Construct_UPackage__Script_Seshat,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ATwinStickGameMode_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ATwinStickGameMode_Statics::ClassParams = {
	&ATwinStickGameMode::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_ATwinStickGameMode_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_ATwinStickGameMode_Statics::PropPointers),
	0,
	0x008003ADu,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ATwinStickGameMode_Statics::Class_MetaDataParams), Z_Construct_UClass_ATwinStickGameMode_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_ATwinStickGameMode()
{
	if (!Z_Registration_Info_UClass_ATwinStickGameMode.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ATwinStickGameMode.OuterSingleton, Z_Construct_UClass_ATwinStickGameMode_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ATwinStickGameMode.OuterSingleton;
}
ATwinStickGameMode::ATwinStickGameMode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(ATwinStickGameMode);
ATwinStickGameMode::~ATwinStickGameMode() {}
// ********** End Class ATwinStickGameMode *********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_TwinStick_TwinStickGameMode_h__Script_Seshat_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ATwinStickGameMode, ATwinStickGameMode::StaticClass, TEXT("ATwinStickGameMode"), &Z_Registration_Info_UClass_ATwinStickGameMode, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ATwinStickGameMode), 1131057831U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_TwinStick_TwinStickGameMode_h__Script_Seshat_2538528097(TEXT("/Script/Seshat"),
	Z_CompiledInDeferFile_FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_TwinStick_TwinStickGameMode_h__Script_Seshat_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_TwinStick_TwinStickGameMode_h__Script_Seshat_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
