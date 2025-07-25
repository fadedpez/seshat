// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSeshat_init() {}
	SESHAT_API UFunction* Z_Construct_UDelegateFunction_Seshat_OnUnitMoveCompletedDelegate__DelegateSignature();
	static FPackageRegistrationInfo Z_Registration_Info_UPackage__Script_Seshat;
	FORCENOINLINE UPackage* Z_Construct_UPackage__Script_Seshat()
	{
		if (!Z_Registration_Info_UPackage__Script_Seshat.OuterSingleton)
		{
			static UObject* (*const SingletonFuncArray[])() = {
				(UObject* (*)())Z_Construct_UDelegateFunction_Seshat_OnUnitMoveCompletedDelegate__DelegateSignature,
			};
			static const UECodeGen_Private::FPackageParams PackageParams = {
				"/Script/Seshat",
				SingletonFuncArray,
				UE_ARRAY_COUNT(SingletonFuncArray),
				PKG_CompiledIn | 0x00000000,
				0x66ABC53C,
				0x7E4AECCC,
				METADATA_PARAMS(0, nullptr)
			};
			UECodeGen_Private::ConstructUPackage(Z_Registration_Info_UPackage__Script_Seshat.OuterSingleton, PackageParams);
		}
		return Z_Registration_Info_UPackage__Script_Seshat.OuterSingleton;
	}
	static FRegisterCompiledInInfo Z_CompiledInDeferPackage_UPackage__Script_Seshat(Z_Construct_UPackage__Script_Seshat, TEXT("/Script/Seshat"), Z_Registration_Info_UPackage__Script_Seshat, CONSTRUCT_RELOAD_VERSION_INFO(FPackageReloadVersionInfo, 0x66ABC53C, 0x7E4AECCC));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
