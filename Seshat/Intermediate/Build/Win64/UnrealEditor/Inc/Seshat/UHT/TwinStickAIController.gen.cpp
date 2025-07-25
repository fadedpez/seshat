// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Seshat/Variant_TwinStick/AI/TwinStickAIController.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeTwinStickAIController() {}

// ********** Begin Cross Module References ********************************************************
AIMODULE_API UClass* Z_Construct_UClass_AAIController();
GAMEPLAYSTATETREEMODULE_API UClass* Z_Construct_UClass_UStateTreeAIComponent_NoRegister();
SESHAT_API UClass* Z_Construct_UClass_ATwinStickAIController();
SESHAT_API UClass* Z_Construct_UClass_ATwinStickAIController_NoRegister();
UPackage* Z_Construct_UPackage__Script_Seshat();
// ********** End Cross Module References **********************************************************

// ********** Begin Class ATwinStickAIController ***************************************************
void ATwinStickAIController::StaticRegisterNativesATwinStickAIController()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_ATwinStickAIController;
UClass* ATwinStickAIController::GetPrivateStaticClass()
{
	using TClass = ATwinStickAIController;
	if (!Z_Registration_Info_UClass_ATwinStickAIController.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("TwinStickAIController"),
			Z_Registration_Info_UClass_ATwinStickAIController.InnerSingleton,
			StaticRegisterNativesATwinStickAIController,
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
	return Z_Registration_Info_UClass_ATwinStickAIController.InnerSingleton;
}
UClass* Z_Construct_UClass_ATwinStickAIController_NoRegister()
{
	return ATwinStickAIController::GetPrivateStaticClass();
}
struct Z_Construct_UClass_ATwinStickAIController_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  A StateTree-Enabled AI Controller for a Twin Stick Shooter game\n *  Runs NPC logic through a StateTree\n */" },
#endif
		{ "HideCategories", "Collision Rendering Transformation" },
		{ "IncludePath", "Variant_TwinStick/AI/TwinStickAIController.h" },
		{ "ModuleRelativePath", "Variant_TwinStick/AI/TwinStickAIController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "A StateTree-Enabled AI Controller for a Twin Stick Shooter game\nRuns NPC logic through a StateTree" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StateTreeAI_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "AI" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** StateTree Component */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Variant_TwinStick/AI/TwinStickAIController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "StateTree Component" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_StateTreeAI;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ATwinStickAIController>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ATwinStickAIController_Statics::NewProp_StateTreeAI = { "StateTreeAI", nullptr, (EPropertyFlags)0x00400000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ATwinStickAIController, StateTreeAI), Z_Construct_UClass_UStateTreeAIComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StateTreeAI_MetaData), NewProp_StateTreeAI_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ATwinStickAIController_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATwinStickAIController_Statics::NewProp_StateTreeAI,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ATwinStickAIController_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_ATwinStickAIController_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AAIController,
	(UObject* (*)())Z_Construct_UPackage__Script_Seshat,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ATwinStickAIController_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ATwinStickAIController_Statics::ClassParams = {
	&ATwinStickAIController::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_ATwinStickAIController_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_ATwinStickAIController_Statics::PropPointers),
	0,
	0x008003A5u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ATwinStickAIController_Statics::Class_MetaDataParams), Z_Construct_UClass_ATwinStickAIController_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_ATwinStickAIController()
{
	if (!Z_Registration_Info_UClass_ATwinStickAIController.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ATwinStickAIController.OuterSingleton, Z_Construct_UClass_ATwinStickAIController_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ATwinStickAIController.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(ATwinStickAIController);
ATwinStickAIController::~ATwinStickAIController() {}
// ********** End Class ATwinStickAIController *****************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_TwinStick_AI_TwinStickAIController_h__Script_Seshat_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ATwinStickAIController, ATwinStickAIController::StaticClass, TEXT("ATwinStickAIController"), &Z_Registration_Info_UClass_ATwinStickAIController, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ATwinStickAIController), 891486493U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_TwinStick_AI_TwinStickAIController_h__Script_Seshat_3523578120(TEXT("/Script/Seshat"),
	Z_CompiledInDeferFile_FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_TwinStick_AI_TwinStickAIController_h__Script_Seshat_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_TwinStick_AI_TwinStickAIController_h__Script_Seshat_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
