// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Variant_Strategy/StrategyHUD.h"

#ifdef SESHAT_StrategyHUD_generated_h
#error "StrategyHUD.generated.h already included, missing '#pragma once' in StrategyHUD.h"
#endif
#define SESHAT_StrategyHUD_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class AStrategyHUD *************************************************************
SESHAT_API UClass* Z_Construct_UClass_AStrategyHUD_NoRegister();

#define FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_Strategy_StrategyHUD_h_18_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAStrategyHUD(); \
	friend struct Z_Construct_UClass_AStrategyHUD_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend SESHAT_API UClass* Z_Construct_UClass_AStrategyHUD_NoRegister(); \
public: \
	DECLARE_CLASS2(AStrategyHUD, AHUD, COMPILED_IN_FLAGS(CLASS_Abstract | CLASS_Transient | CLASS_Config), CASTCLASS_None, TEXT("/Script/Seshat"), Z_Construct_UClass_AStrategyHUD_NoRegister) \
	DECLARE_SERIALIZER(AStrategyHUD)


#define FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_Strategy_StrategyHUD_h_18_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AStrategyHUD(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	AStrategyHUD(AStrategyHUD&&) = delete; \
	AStrategyHUD(const AStrategyHUD&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AStrategyHUD); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AStrategyHUD); \
	DEFINE_ABSTRACT_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AStrategyHUD) \
	NO_API virtual ~AStrategyHUD();


#define FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_Strategy_StrategyHUD_h_15_PROLOG
#define FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_Strategy_StrategyHUD_h_18_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_Strategy_StrategyHUD_h_18_INCLASS_NO_PURE_DECLS \
	FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_Strategy_StrategyHUD_h_18_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class AStrategyHUD;

// ********** End Class AStrategyHUD ***************************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_Strategy_StrategyHUD_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
