// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "RpgToolkit/RpgToolkitSubsystem.h"

#ifdef SESHAT_RpgToolkitSubsystem_generated_h
#error "RpgToolkitSubsystem.generated.h already included, missing '#pragma once' in RpgToolkitSubsystem.h"
#endif
#define SESHAT_RpgToolkitSubsystem_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

class URpgDiceRoller;

// ********** Begin Class URpgToolkitSubsystem *****************************************************
#define FID_Projects_share_seshat_Seshat_Source_Seshat_RpgToolkit_RpgToolkitSubsystem_h_18_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execGetToolkitStatus); \
	DECLARE_FUNCTION(execRunDiagnostics); \
	DECLARE_FUNCTION(execInitializeServer); \
	DECLARE_FUNCTION(execQuickRollMultiple); \
	DECLARE_FUNCTION(execQuickRoll); \
	DECLARE_FUNCTION(execQuickRollD20); \
	DECLARE_FUNCTION(execGetDiceRoller);


SESHAT_API UClass* Z_Construct_UClass_URpgToolkitSubsystem_NoRegister();

#define FID_Projects_share_seshat_Seshat_Source_Seshat_RpgToolkit_RpgToolkitSubsystem_h_18_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesURpgToolkitSubsystem(); \
	friend struct Z_Construct_UClass_URpgToolkitSubsystem_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend SESHAT_API UClass* Z_Construct_UClass_URpgToolkitSubsystem_NoRegister(); \
public: \
	DECLARE_CLASS2(URpgToolkitSubsystem, UGameInstanceSubsystem, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/Seshat"), Z_Construct_UClass_URpgToolkitSubsystem_NoRegister) \
	DECLARE_SERIALIZER(URpgToolkitSubsystem)


#define FID_Projects_share_seshat_Seshat_Source_Seshat_RpgToolkit_RpgToolkitSubsystem_h_18_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API URpgToolkitSubsystem(); \
	/** Deleted move- and copy-constructors, should never be used */ \
	URpgToolkitSubsystem(URpgToolkitSubsystem&&) = delete; \
	URpgToolkitSubsystem(const URpgToolkitSubsystem&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, URpgToolkitSubsystem); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(URpgToolkitSubsystem); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(URpgToolkitSubsystem) \
	NO_API virtual ~URpgToolkitSubsystem();


#define FID_Projects_share_seshat_Seshat_Source_Seshat_RpgToolkit_RpgToolkitSubsystem_h_15_PROLOG
#define FID_Projects_share_seshat_Seshat_Source_Seshat_RpgToolkit_RpgToolkitSubsystem_h_18_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Projects_share_seshat_Seshat_Source_Seshat_RpgToolkit_RpgToolkitSubsystem_h_18_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Projects_share_seshat_Seshat_Source_Seshat_RpgToolkit_RpgToolkitSubsystem_h_18_INCLASS_NO_PURE_DECLS \
	FID_Projects_share_seshat_Seshat_Source_Seshat_RpgToolkit_RpgToolkitSubsystem_h_18_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class URpgToolkitSubsystem;

// ********** End Class URpgToolkitSubsystem *******************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Projects_share_seshat_Seshat_Source_Seshat_RpgToolkit_RpgToolkitSubsystem_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
