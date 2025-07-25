// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Seshat/Variant_TwinStick/TwinStickNPCDestruction.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeTwinStickNPCDestruction() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_AActor();
SESHAT_API UClass* Z_Construct_UClass_ATwinStickNPCDestruction();
SESHAT_API UClass* Z_Construct_UClass_ATwinStickNPCDestruction_NoRegister();
UPackage* Z_Construct_UPackage__Script_Seshat();
// ********** End Cross Module References **********************************************************

// ********** Begin Class ATwinStickNPCDestruction *************************************************
void ATwinStickNPCDestruction::StaticRegisterNativesATwinStickNPCDestruction()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_ATwinStickNPCDestruction;
UClass* ATwinStickNPCDestruction::GetPrivateStaticClass()
{
	using TClass = ATwinStickNPCDestruction;
	if (!Z_Registration_Info_UClass_ATwinStickNPCDestruction.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("TwinStickNPCDestruction"),
			Z_Registration_Info_UClass_ATwinStickNPCDestruction.InnerSingleton,
			StaticRegisterNativesATwinStickNPCDestruction,
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
	return Z_Registration_Info_UClass_ATwinStickNPCDestruction.InnerSingleton;
}
UClass* Z_Construct_UClass_ATwinStickNPCDestruction_NoRegister()
{
	return ATwinStickNPCDestruction::GetPrivateStaticClass();
}
struct Z_Construct_UClass_ATwinStickNPCDestruction_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  A NPC destruction proxy for a Twin Stick Shooter game\n *  Replaces the NPC when it is destroyed,\n *  allowing it to play effects without affecting gameplay \n */" },
#endif
		{ "IncludePath", "Variant_TwinStick/TwinStickNPCDestruction.h" },
		{ "ModuleRelativePath", "Variant_TwinStick/TwinStickNPCDestruction.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "A NPC destruction proxy for a Twin Stick Shooter game\nReplaces the NPC when it is destroyed,\nallowing it to play effects without affecting gameplay" },
#endif
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ATwinStickNPCDestruction>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_ATwinStickNPCDestruction_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AActor,
	(UObject* (*)())Z_Construct_UPackage__Script_Seshat,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ATwinStickNPCDestruction_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ATwinStickNPCDestruction_Statics::ClassParams = {
	&ATwinStickNPCDestruction::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x008001A5u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ATwinStickNPCDestruction_Statics::Class_MetaDataParams), Z_Construct_UClass_ATwinStickNPCDestruction_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_ATwinStickNPCDestruction()
{
	if (!Z_Registration_Info_UClass_ATwinStickNPCDestruction.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ATwinStickNPCDestruction.OuterSingleton, Z_Construct_UClass_ATwinStickNPCDestruction_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ATwinStickNPCDestruction.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(ATwinStickNPCDestruction);
ATwinStickNPCDestruction::~ATwinStickNPCDestruction() {}
// ********** End Class ATwinStickNPCDestruction ***************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_TwinStick_TwinStickNPCDestruction_h__Script_Seshat_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ATwinStickNPCDestruction, ATwinStickNPCDestruction::StaticClass, TEXT("ATwinStickNPCDestruction"), &Z_Registration_Info_UClass_ATwinStickNPCDestruction, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ATwinStickNPCDestruction), 1974165292U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_TwinStick_TwinStickNPCDestruction_h__Script_Seshat_4234874783(TEXT("/Script/Seshat"),
	Z_CompiledInDeferFile_FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_TwinStick_TwinStickNPCDestruction_h__Script_Seshat_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_TwinStick_TwinStickNPCDestruction_h__Script_Seshat_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
