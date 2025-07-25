// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Variant_TwinStick/TwinStickCharacter.h"

#ifdef SESHAT_TwinStickCharacter_generated_h
#error "TwinStickCharacter.generated.h already included, missing '#pragma once' in TwinStickCharacter.h"
#endif
#define SESHAT_TwinStickCharacter_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class ATwinStickCharacter ******************************************************
#define FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_TwinStick_TwinStickCharacter_h_26_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execDoAoEAttack); \
	DECLARE_FUNCTION(execDoShoot); \
	DECLARE_FUNCTION(execDoDash); \
	DECLARE_FUNCTION(execDoAim); \
	DECLARE_FUNCTION(execDoMove);


#define FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_TwinStick_TwinStickCharacter_h_26_CALLBACK_WRAPPERS
SESHAT_API UClass* Z_Construct_UClass_ATwinStickCharacter_NoRegister();

#define FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_TwinStick_TwinStickCharacter_h_26_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesATwinStickCharacter(); \
	friend struct Z_Construct_UClass_ATwinStickCharacter_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend SESHAT_API UClass* Z_Construct_UClass_ATwinStickCharacter_NoRegister(); \
public: \
	DECLARE_CLASS2(ATwinStickCharacter, ACharacter, COMPILED_IN_FLAGS(CLASS_Abstract | CLASS_Config), CASTCLASS_None, TEXT("/Script/Seshat"), Z_Construct_UClass_ATwinStickCharacter_NoRegister) \
	DECLARE_SERIALIZER(ATwinStickCharacter)


#define FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_TwinStick_TwinStickCharacter_h_26_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	ATwinStickCharacter(ATwinStickCharacter&&) = delete; \
	ATwinStickCharacter(const ATwinStickCharacter&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ATwinStickCharacter); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ATwinStickCharacter); \
	DEFINE_ABSTRACT_DEFAULT_CONSTRUCTOR_CALL(ATwinStickCharacter) \
	NO_API virtual ~ATwinStickCharacter();


#define FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_TwinStick_TwinStickCharacter_h_23_PROLOG
#define FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_TwinStick_TwinStickCharacter_h_26_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_TwinStick_TwinStickCharacter_h_26_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_TwinStick_TwinStickCharacter_h_26_CALLBACK_WRAPPERS \
	FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_TwinStick_TwinStickCharacter_h_26_INCLASS_NO_PURE_DECLS \
	FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_TwinStick_TwinStickCharacter_h_26_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class ATwinStickCharacter;

// ********** End Class ATwinStickCharacter ********************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_TwinStick_TwinStickCharacter_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
