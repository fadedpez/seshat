// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Variant_Strategy/StrategyPawn.h"

#ifdef SESHAT_StrategyPawn_generated_h
#error "StrategyPawn.generated.h already included, missing '#pragma once' in StrategyPawn.h"
#endif
#define SESHAT_StrategyPawn_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class AStrategyPawn ************************************************************
SESHAT_API UClass* Z_Construct_UClass_AStrategyPawn_NoRegister();

#define FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_Strategy_StrategyPawn_h_19_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAStrategyPawn(); \
	friend struct Z_Construct_UClass_AStrategyPawn_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend SESHAT_API UClass* Z_Construct_UClass_AStrategyPawn_NoRegister(); \
public: \
	DECLARE_CLASS2(AStrategyPawn, APawn, COMPILED_IN_FLAGS(CLASS_Abstract | CLASS_Config), CASTCLASS_None, TEXT("/Script/Seshat"), Z_Construct_UClass_AStrategyPawn_NoRegister) \
	DECLARE_SERIALIZER(AStrategyPawn)


#define FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_Strategy_StrategyPawn_h_19_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	AStrategyPawn(AStrategyPawn&&) = delete; \
	AStrategyPawn(const AStrategyPawn&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AStrategyPawn); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AStrategyPawn); \
	DEFINE_ABSTRACT_DEFAULT_CONSTRUCTOR_CALL(AStrategyPawn) \
	NO_API virtual ~AStrategyPawn();


#define FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_Strategy_StrategyPawn_h_16_PROLOG
#define FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_Strategy_StrategyPawn_h_19_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_Strategy_StrategyPawn_h_19_INCLASS_NO_PURE_DECLS \
	FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_Strategy_StrategyPawn_h_19_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class AStrategyPawn;

// ********** End Class AStrategyPawn **************************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_Strategy_StrategyPawn_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
