// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "RpgToolkit/RpgDiceRoller.h"

#ifdef SESHAT_RpgDiceRoller_generated_h
#error "RpgDiceRoller.generated.h already included, missing '#pragma once' in RpgDiceRoller.h"
#endif
#define SESHAT_RpgDiceRoller_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class URpgDiceRoller ***********************************************************
#define FID_Projects_share_seshat_Seshat_Source_Seshat_RpgToolkit_RpgDiceRoller_h_17_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execTestConnection); \
	DECLARE_FUNCTION(execSetServerUrl); \
	DECLARE_FUNCTION(execGetRollHistory); \
	DECLARE_FUNCTION(execTestDiceFairness); \
	DECLARE_FUNCTION(execRollWithContext); \
	DECLARE_FUNCTION(execRollMultipleDice); \
	DECLARE_FUNCTION(execRollDice); \
	DECLARE_FUNCTION(execRollD20);


SESHAT_API UClass* Z_Construct_UClass_URpgDiceRoller_NoRegister();

#define FID_Projects_share_seshat_Seshat_Source_Seshat_RpgToolkit_RpgDiceRoller_h_17_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesURpgDiceRoller(); \
	friend struct Z_Construct_UClass_URpgDiceRoller_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend SESHAT_API UClass* Z_Construct_UClass_URpgDiceRoller_NoRegister(); \
public: \
	DECLARE_CLASS2(URpgDiceRoller, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/Seshat"), Z_Construct_UClass_URpgDiceRoller_NoRegister) \
	DECLARE_SERIALIZER(URpgDiceRoller)


#define FID_Projects_share_seshat_Seshat_Source_Seshat_RpgToolkit_RpgDiceRoller_h_17_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	URpgDiceRoller(URpgDiceRoller&&) = delete; \
	URpgDiceRoller(const URpgDiceRoller&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, URpgDiceRoller); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(URpgDiceRoller); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(URpgDiceRoller) \
	NO_API virtual ~URpgDiceRoller();


#define FID_Projects_share_seshat_Seshat_Source_Seshat_RpgToolkit_RpgDiceRoller_h_14_PROLOG
#define FID_Projects_share_seshat_Seshat_Source_Seshat_RpgToolkit_RpgDiceRoller_h_17_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Projects_share_seshat_Seshat_Source_Seshat_RpgToolkit_RpgDiceRoller_h_17_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Projects_share_seshat_Seshat_Source_Seshat_RpgToolkit_RpgDiceRoller_h_17_INCLASS_NO_PURE_DECLS \
	FID_Projects_share_seshat_Seshat_Source_Seshat_RpgToolkit_RpgDiceRoller_h_17_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class URpgDiceRoller;

// ********** End Class URpgDiceRoller *************************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Projects_share_seshat_Seshat_Source_Seshat_RpgToolkit_RpgDiceRoller_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
