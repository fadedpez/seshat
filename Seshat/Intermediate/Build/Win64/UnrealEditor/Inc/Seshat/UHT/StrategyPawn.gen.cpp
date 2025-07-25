// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Seshat/Variant_Strategy/StrategyPawn.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeStrategyPawn() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_APawn();
ENGINE_API UClass* Z_Construct_UClass_UCameraComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UFloatingPawnMovement_NoRegister();
SESHAT_API UClass* Z_Construct_UClass_AStrategyPawn();
SESHAT_API UClass* Z_Construct_UClass_AStrategyPawn_NoRegister();
UPackage* Z_Construct_UPackage__Script_Seshat();
// ********** End Cross Module References **********************************************************

// ********** Begin Class AStrategyPawn ************************************************************
void AStrategyPawn::StaticRegisterNativesAStrategyPawn()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_AStrategyPawn;
UClass* AStrategyPawn::GetPrivateStaticClass()
{
	using TClass = AStrategyPawn;
	if (!Z_Registration_Info_UClass_AStrategyPawn.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("StrategyPawn"),
			Z_Registration_Info_UClass_AStrategyPawn.InnerSingleton,
			StaticRegisterNativesAStrategyPawn,
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
	return Z_Registration_Info_UClass_AStrategyPawn.InnerSingleton;
}
UClass* Z_Construct_UClass_AStrategyPawn_NoRegister()
{
	return AStrategyPawn::GetPrivateStaticClass();
}
struct Z_Construct_UClass_AStrategyPawn_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  Simple pawn that implements a top-down camera perspective for a strategy game.\n *  Units are indirectly controlled by other means.\n */" },
#endif
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "Variant_Strategy/StrategyPawn.h" },
		{ "ModuleRelativePath", "Variant_Strategy/StrategyPawn.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Simple pawn that implements a top-down camera perspective for a strategy game.\nUnits are indirectly controlled by other means." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Camera_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Components" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Camera */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Variant_Strategy/StrategyPawn.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Camera" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FloatingPawnMovement_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Camera" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Movement Component */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Variant_Strategy/StrategyPawn.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Movement Component" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Camera;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_FloatingPawnMovement;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AStrategyPawn>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AStrategyPawn_Statics::NewProp_Camera = { "Camera", nullptr, (EPropertyFlags)0x00400000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AStrategyPawn, Camera), Z_Construct_UClass_UCameraComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Camera_MetaData), NewProp_Camera_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AStrategyPawn_Statics::NewProp_FloatingPawnMovement = { "FloatingPawnMovement", nullptr, (EPropertyFlags)0x00400000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AStrategyPawn, FloatingPawnMovement), Z_Construct_UClass_UFloatingPawnMovement_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FloatingPawnMovement_MetaData), NewProp_FloatingPawnMovement_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AStrategyPawn_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AStrategyPawn_Statics::NewProp_Camera,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AStrategyPawn_Statics::NewProp_FloatingPawnMovement,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AStrategyPawn_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_AStrategyPawn_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_APawn,
	(UObject* (*)())Z_Construct_UPackage__Script_Seshat,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AStrategyPawn_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AStrategyPawn_Statics::ClassParams = {
	&AStrategyPawn::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_AStrategyPawn_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_AStrategyPawn_Statics::PropPointers),
	0,
	0x008001A5u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AStrategyPawn_Statics::Class_MetaDataParams), Z_Construct_UClass_AStrategyPawn_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AStrategyPawn()
{
	if (!Z_Registration_Info_UClass_AStrategyPawn.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AStrategyPawn.OuterSingleton, Z_Construct_UClass_AStrategyPawn_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AStrategyPawn.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(AStrategyPawn);
AStrategyPawn::~AStrategyPawn() {}
// ********** End Class AStrategyPawn **************************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_Strategy_StrategyPawn_h__Script_Seshat_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AStrategyPawn, AStrategyPawn::StaticClass, TEXT("AStrategyPawn"), &Z_Registration_Info_UClass_AStrategyPawn, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AStrategyPawn), 225639093U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_Strategy_StrategyPawn_h__Script_Seshat_1601450832(TEXT("/Script/Seshat"),
	Z_CompiledInDeferFile_FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_Strategy_StrategyPawn_h__Script_Seshat_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_Strategy_StrategyPawn_h__Script_Seshat_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
