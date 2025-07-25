// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Variant_TwinStick/AI/TwinStickNPC.h"

#ifdef SESHAT_TwinStickNPC_generated_h
#error "TwinStickNPC.generated.h already included, missing '#pragma once' in TwinStickNPC.h"
#endif
#define SESHAT_TwinStickNPC_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class ATwinStickNPC ************************************************************
SESHAT_API UClass* Z_Construct_UClass_ATwinStickNPC_NoRegister();

#define FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_TwinStick_AI_TwinStickNPC_h_20_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesATwinStickNPC(); \
	friend struct Z_Construct_UClass_ATwinStickNPC_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend SESHAT_API UClass* Z_Construct_UClass_ATwinStickNPC_NoRegister(); \
public: \
	DECLARE_CLASS2(ATwinStickNPC, ACharacter, COMPILED_IN_FLAGS(CLASS_Abstract | CLASS_Config), CASTCLASS_None, TEXT("/Script/Seshat"), Z_Construct_UClass_ATwinStickNPC_NoRegister) \
	DECLARE_SERIALIZER(ATwinStickNPC)


#define FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_TwinStick_AI_TwinStickNPC_h_20_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	ATwinStickNPC(ATwinStickNPC&&) = delete; \
	ATwinStickNPC(const ATwinStickNPC&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ATwinStickNPC); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ATwinStickNPC); \
	DEFINE_ABSTRACT_DEFAULT_CONSTRUCTOR_CALL(ATwinStickNPC) \
	NO_API virtual ~ATwinStickNPC();


#define FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_TwinStick_AI_TwinStickNPC_h_17_PROLOG
#define FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_TwinStick_AI_TwinStickNPC_h_20_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_TwinStick_AI_TwinStickNPC_h_20_INCLASS_NO_PURE_DECLS \
	FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_TwinStick_AI_TwinStickNPC_h_20_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class ATwinStickNPC;

// ********** End Class ATwinStickNPC **************************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_TwinStick_AI_TwinStickNPC_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
