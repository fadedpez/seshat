// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Variant_TwinStick/TwinStickGameMode.h"

#ifdef SESHAT_TwinStickGameMode_generated_h
#error "TwinStickGameMode.generated.h already included, missing '#pragma once' in TwinStickGameMode.h"
#endif
#define SESHAT_TwinStickGameMode_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class ATwinStickGameMode *******************************************************
SESHAT_API UClass* Z_Construct_UClass_ATwinStickGameMode_NoRegister();

#define FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_TwinStick_TwinStickGameMode_h_18_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesATwinStickGameMode(); \
	friend struct Z_Construct_UClass_ATwinStickGameMode_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend SESHAT_API UClass* Z_Construct_UClass_ATwinStickGameMode_NoRegister(); \
public: \
	DECLARE_CLASS2(ATwinStickGameMode, AGameModeBase, COMPILED_IN_FLAGS(CLASS_Abstract | CLASS_Transient | CLASS_Config), CASTCLASS_None, TEXT("/Script/Seshat"), Z_Construct_UClass_ATwinStickGameMode_NoRegister) \
	DECLARE_SERIALIZER(ATwinStickGameMode)


#define FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_TwinStick_TwinStickGameMode_h_18_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ATwinStickGameMode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	ATwinStickGameMode(ATwinStickGameMode&&) = delete; \
	ATwinStickGameMode(const ATwinStickGameMode&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ATwinStickGameMode); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ATwinStickGameMode); \
	DEFINE_ABSTRACT_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ATwinStickGameMode) \
	NO_API virtual ~ATwinStickGameMode();


#define FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_TwinStick_TwinStickGameMode_h_15_PROLOG
#define FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_TwinStick_TwinStickGameMode_h_18_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_TwinStick_TwinStickGameMode_h_18_INCLASS_NO_PURE_DECLS \
	FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_TwinStick_TwinStickGameMode_h_18_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class ATwinStickGameMode;

// ********** End Class ATwinStickGameMode *********************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_TwinStick_TwinStickGameMode_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
