// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Seshat/Variant_TwinStick/TwinStickPickup.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeTwinStickPickup() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_AActor();
ENGINE_API UClass* Z_Construct_UClass_USphereComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UStaticMeshComponent_NoRegister();
SESHAT_API UClass* Z_Construct_UClass_ATwinStickPickup();
SESHAT_API UClass* Z_Construct_UClass_ATwinStickPickup_NoRegister();
UPackage* Z_Construct_UPackage__Script_Seshat();
// ********** End Cross Module References **********************************************************

// ********** Begin Class ATwinStickPickup *********************************************************
void ATwinStickPickup::StaticRegisterNativesATwinStickPickup()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_ATwinStickPickup;
UClass* ATwinStickPickup::GetPrivateStaticClass()
{
	using TClass = ATwinStickPickup;
	if (!Z_Registration_Info_UClass_ATwinStickPickup.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("TwinStickPickup"),
			Z_Registration_Info_UClass_ATwinStickPickup.InnerSingleton,
			StaticRegisterNativesATwinStickPickup,
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
	return Z_Registration_Info_UClass_ATwinStickPickup.InnerSingleton;
}
UClass* Z_Construct_UClass_ATwinStickPickup_NoRegister()
{
	return ATwinStickPickup::GetPrivateStaticClass();
}
struct Z_Construct_UClass_ATwinStickPickup_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  A simple pickup for a Twin Stick Shooter game\n */" },
#endif
		{ "IncludePath", "Variant_TwinStick/TwinStickPickup.h" },
		{ "ModuleRelativePath", "Variant_TwinStick/TwinStickPickup.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "A simple pickup for a Twin Stick Shooter game" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CollisionSphere_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Components" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Pickup collision sphere */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Variant_TwinStick/TwinStickPickup.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Pickup collision sphere" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Mesh_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Components" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Provides visual representation for the pickup */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Variant_TwinStick/TwinStickPickup.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Provides visual representation for the pickup" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_CollisionSphere;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Mesh;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ATwinStickPickup>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ATwinStickPickup_Statics::NewProp_CollisionSphere = { "CollisionSphere", nullptr, (EPropertyFlags)0x00400000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ATwinStickPickup, CollisionSphere), Z_Construct_UClass_USphereComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CollisionSphere_MetaData), NewProp_CollisionSphere_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ATwinStickPickup_Statics::NewProp_Mesh = { "Mesh", nullptr, (EPropertyFlags)0x00400000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ATwinStickPickup, Mesh), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Mesh_MetaData), NewProp_Mesh_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ATwinStickPickup_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATwinStickPickup_Statics::NewProp_CollisionSphere,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATwinStickPickup_Statics::NewProp_Mesh,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ATwinStickPickup_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_ATwinStickPickup_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AActor,
	(UObject* (*)())Z_Construct_UPackage__Script_Seshat,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ATwinStickPickup_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ATwinStickPickup_Statics::ClassParams = {
	&ATwinStickPickup::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_ATwinStickPickup_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_ATwinStickPickup_Statics::PropPointers),
	0,
	0x008001A5u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ATwinStickPickup_Statics::Class_MetaDataParams), Z_Construct_UClass_ATwinStickPickup_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_ATwinStickPickup()
{
	if (!Z_Registration_Info_UClass_ATwinStickPickup.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ATwinStickPickup.OuterSingleton, Z_Construct_UClass_ATwinStickPickup_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ATwinStickPickup.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(ATwinStickPickup);
ATwinStickPickup::~ATwinStickPickup() {}
// ********** End Class ATwinStickPickup ***********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_TwinStick_TwinStickPickup_h__Script_Seshat_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ATwinStickPickup, ATwinStickPickup::StaticClass, TEXT("ATwinStickPickup"), &Z_Registration_Info_UClass_ATwinStickPickup, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ATwinStickPickup), 30943609U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_TwinStick_TwinStickPickup_h__Script_Seshat_2104198002(TEXT("/Script/Seshat"),
	Z_CompiledInDeferFile_FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_TwinStick_TwinStickPickup_h__Script_Seshat_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_TwinStick_TwinStickPickup_h__Script_Seshat_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
