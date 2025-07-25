// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Seshat/Variant_TwinStick/TwinStickAoEAttack.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeTwinStickAoEAttack() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_AActor();
ENGINE_API UClass* Z_Construct_UClass_USphereComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UStaticMeshComponent_NoRegister();
SESHAT_API UClass* Z_Construct_UClass_ATwinStickAoEAttack();
SESHAT_API UClass* Z_Construct_UClass_ATwinStickAoEAttack_NoRegister();
UPackage* Z_Construct_UPackage__Script_Seshat();
// ********** End Cross Module References **********************************************************

// ********** Begin Class ATwinStickAoEAttack Function BP_AoEFinished ******************************
static FName NAME_ATwinStickAoEAttack_BP_AoEFinished = FName(TEXT("BP_AoEFinished"));
void ATwinStickAoEAttack::BP_AoEFinished()
{
	UFunction* Func = FindFunctionChecked(NAME_ATwinStickAoEAttack_BP_AoEFinished);
	ProcessEvent(Func,NULL);
}
struct Z_Construct_UFunction_ATwinStickAoEAttack_BP_AoEFinished_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "AoE Attack" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Allows Blueprint handling of AoE fade out effects. NOTE: Call Destroy Actor at the end of this! */" },
#endif
		{ "ModuleRelativePath", "Variant_TwinStick/TwinStickAoEAttack.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Allows Blueprint handling of AoE fade out effects. NOTE: Call Destroy Actor at the end of this!" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ATwinStickAoEAttack_BP_AoEFinished_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_ATwinStickAoEAttack, nullptr, "BP_AoEFinished", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08080800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ATwinStickAoEAttack_BP_AoEFinished_Statics::Function_MetaDataParams), Z_Construct_UFunction_ATwinStickAoEAttack_BP_AoEFinished_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_ATwinStickAoEAttack_BP_AoEFinished()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ATwinStickAoEAttack_BP_AoEFinished_Statics::FuncParams);
	}
	return ReturnFunction;
}
// ********** End Class ATwinStickAoEAttack Function BP_AoEFinished ********************************

// ********** Begin Class ATwinStickAoEAttack ******************************************************
void ATwinStickAoEAttack::StaticRegisterNativesATwinStickAoEAttack()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_ATwinStickAoEAttack;
UClass* ATwinStickAoEAttack::GetPrivateStaticClass()
{
	using TClass = ATwinStickAoEAttack;
	if (!Z_Registration_Info_UClass_ATwinStickAoEAttack.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("TwinStickAoEAttack"),
			Z_Registration_Info_UClass_ATwinStickAoEAttack.InnerSingleton,
			StaticRegisterNativesATwinStickAoEAttack,
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
	return Z_Registration_Info_UClass_ATwinStickAoEAttack.InnerSingleton;
}
UClass* Z_Construct_UClass_ATwinStickAoEAttack_NoRegister()
{
	return ATwinStickAoEAttack::GetPrivateStaticClass();
}
struct Z_Construct_UClass_ATwinStickAoEAttack_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  A simple persistent AoE attack.\n *  Damages characters that enter for as long as it's active\n */" },
#endif
		{ "IncludePath", "Variant_TwinStick/TwinStickAoEAttack.h" },
		{ "ModuleRelativePath", "Variant_TwinStick/TwinStickAoEAttack.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "A simple persistent AoE attack.\nDamages characters that enter for as long as it's active" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SphereVisual_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Components" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Provides the visual representation for the AoE attack */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Variant_TwinStick/TwinStickAoEAttack.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Provides the visual representation for the AoE attack" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CollisionSphere_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Components" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Provides the collision volume for the AoE attack */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Variant_TwinStick/TwinStickAoEAttack.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Provides the collision volume for the AoE attack" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TickAoETime_MetaData[] = {
		{ "Category", "AoE Attack" },
		{ "ClampMax", "5" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Time to wait between AoE damage ticks */" },
#endif
		{ "ModuleRelativePath", "Variant_TwinStick/TwinStickAoEAttack.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Time to wait between AoE damage ticks" },
#endif
		{ "Units", "s" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StopAoETime_MetaData[] = {
		{ "Category", "AoE Attack" },
		{ "ClampMax", "5" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Time to wait before stopping AoE damage checks */" },
#endif
		{ "ModuleRelativePath", "Variant_TwinStick/TwinStickAoEAttack.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Time to wait before stopping AoE damage checks" },
#endif
		{ "Units", "s" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SphereVisual;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_CollisionSphere;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_TickAoETime;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_StopAoETime;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_ATwinStickAoEAttack_BP_AoEFinished, "BP_AoEFinished" }, // 3843957182
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ATwinStickAoEAttack>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ATwinStickAoEAttack_Statics::NewProp_SphereVisual = { "SphereVisual", nullptr, (EPropertyFlags)0x00400000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ATwinStickAoEAttack, SphereVisual), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SphereVisual_MetaData), NewProp_SphereVisual_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ATwinStickAoEAttack_Statics::NewProp_CollisionSphere = { "CollisionSphere", nullptr, (EPropertyFlags)0x00400000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ATwinStickAoEAttack, CollisionSphere), Z_Construct_UClass_USphereComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CollisionSphere_MetaData), NewProp_CollisionSphere_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ATwinStickAoEAttack_Statics::NewProp_TickAoETime = { "TickAoETime", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ATwinStickAoEAttack, TickAoETime), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TickAoETime_MetaData), NewProp_TickAoETime_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ATwinStickAoEAttack_Statics::NewProp_StopAoETime = { "StopAoETime", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ATwinStickAoEAttack, StopAoETime), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StopAoETime_MetaData), NewProp_StopAoETime_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ATwinStickAoEAttack_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATwinStickAoEAttack_Statics::NewProp_SphereVisual,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATwinStickAoEAttack_Statics::NewProp_CollisionSphere,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATwinStickAoEAttack_Statics::NewProp_TickAoETime,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATwinStickAoEAttack_Statics::NewProp_StopAoETime,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ATwinStickAoEAttack_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_ATwinStickAoEAttack_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AActor,
	(UObject* (*)())Z_Construct_UPackage__Script_Seshat,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ATwinStickAoEAttack_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ATwinStickAoEAttack_Statics::ClassParams = {
	&ATwinStickAoEAttack::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_ATwinStickAoEAttack_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_ATwinStickAoEAttack_Statics::PropPointers),
	0,
	0x008001A5u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ATwinStickAoEAttack_Statics::Class_MetaDataParams), Z_Construct_UClass_ATwinStickAoEAttack_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_ATwinStickAoEAttack()
{
	if (!Z_Registration_Info_UClass_ATwinStickAoEAttack.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ATwinStickAoEAttack.OuterSingleton, Z_Construct_UClass_ATwinStickAoEAttack_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ATwinStickAoEAttack.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(ATwinStickAoEAttack);
ATwinStickAoEAttack::~ATwinStickAoEAttack() {}
// ********** End Class ATwinStickAoEAttack ********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_TwinStick_TwinStickAoEAttack_h__Script_Seshat_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ATwinStickAoEAttack, ATwinStickAoEAttack::StaticClass, TEXT("ATwinStickAoEAttack"), &Z_Registration_Info_UClass_ATwinStickAoEAttack, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ATwinStickAoEAttack), 1785581878U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_TwinStick_TwinStickAoEAttack_h__Script_Seshat_3551808441(TEXT("/Script/Seshat"),
	Z_CompiledInDeferFile_FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_TwinStick_TwinStickAoEAttack_h__Script_Seshat_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_TwinStick_TwinStickAoEAttack_h__Script_Seshat_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
