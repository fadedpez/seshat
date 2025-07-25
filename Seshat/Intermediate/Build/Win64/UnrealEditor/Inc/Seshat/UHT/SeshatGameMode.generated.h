// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "SeshatGameMode.h"

#ifdef SESHAT_SeshatGameMode_generated_h
#error "SeshatGameMode.generated.h already included, missing '#pragma once' in SeshatGameMode.h"
#endif
#define SESHAT_SeshatGameMode_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class ASeshatGameMode **********************************************************
SESHAT_API UClass* Z_Construct_UClass_ASeshatGameMode_NoRegister();

#define FID_Projects_share_seshat_Seshat_Source_Seshat_SeshatGameMode_h_17_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesASeshatGameMode(); \
	friend struct Z_Construct_UClass_ASeshatGameMode_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend SESHAT_API UClass* Z_Construct_UClass_ASeshatGameMode_NoRegister(); \
public: \
	DECLARE_CLASS2(ASeshatGameMode, AGameModeBase, COMPILED_IN_FLAGS(CLASS_Abstract | CLASS_Transient | CLASS_Config), CASTCLASS_None, TEXT("/Script/Seshat"), Z_Construct_UClass_ASeshatGameMode_NoRegister) \
	DECLARE_SERIALIZER(ASeshatGameMode)


#define FID_Projects_share_seshat_Seshat_Source_Seshat_SeshatGameMode_h_17_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	ASeshatGameMode(ASeshatGameMode&&) = delete; \
	ASeshatGameMode(const ASeshatGameMode&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ASeshatGameMode); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ASeshatGameMode); \
	DEFINE_ABSTRACT_DEFAULT_CONSTRUCTOR_CALL(ASeshatGameMode) \
	NO_API virtual ~ASeshatGameMode();


#define FID_Projects_share_seshat_Seshat_Source_Seshat_SeshatGameMode_h_14_PROLOG
#define FID_Projects_share_seshat_Seshat_Source_Seshat_SeshatGameMode_h_17_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Projects_share_seshat_Seshat_Source_Seshat_SeshatGameMode_h_17_INCLASS_NO_PURE_DECLS \
	FID_Projects_share_seshat_Seshat_Source_Seshat_SeshatGameMode_h_17_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class ASeshatGameMode;

// ********** End Class ASeshatGameMode ************************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Projects_share_seshat_Seshat_Source_Seshat_SeshatGameMode_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
