// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "SeshatCharacter.h"

#ifdef SESHAT_SeshatCharacter_generated_h
#error "SeshatCharacter.generated.h already included, missing '#pragma once' in SeshatCharacter.h"
#endif
#define SESHAT_SeshatCharacter_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class ASeshatCharacter *********************************************************
SESHAT_API UClass* Z_Construct_UClass_ASeshatCharacter_NoRegister();

#define FID_Projects_share_seshat_Seshat_Source_Seshat_SeshatCharacter_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesASeshatCharacter(); \
	friend struct Z_Construct_UClass_ASeshatCharacter_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend SESHAT_API UClass* Z_Construct_UClass_ASeshatCharacter_NoRegister(); \
public: \
	DECLARE_CLASS2(ASeshatCharacter, ACharacter, COMPILED_IN_FLAGS(CLASS_Abstract | CLASS_Config), CASTCLASS_None, TEXT("/Script/Seshat"), Z_Construct_UClass_ASeshatCharacter_NoRegister) \
	DECLARE_SERIALIZER(ASeshatCharacter)


#define FID_Projects_share_seshat_Seshat_Source_Seshat_SeshatCharacter_h_15_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	ASeshatCharacter(ASeshatCharacter&&) = delete; \
	ASeshatCharacter(const ASeshatCharacter&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ASeshatCharacter); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ASeshatCharacter); \
	DEFINE_ABSTRACT_DEFAULT_CONSTRUCTOR_CALL(ASeshatCharacter) \
	NO_API virtual ~ASeshatCharacter();


#define FID_Projects_share_seshat_Seshat_Source_Seshat_SeshatCharacter_h_12_PROLOG
#define FID_Projects_share_seshat_Seshat_Source_Seshat_SeshatCharacter_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Projects_share_seshat_Seshat_Source_Seshat_SeshatCharacter_h_15_INCLASS_NO_PURE_DECLS \
	FID_Projects_share_seshat_Seshat_Source_Seshat_SeshatCharacter_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class ASeshatCharacter;

// ********** End Class ASeshatCharacter ***********************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Projects_share_seshat_Seshat_Source_Seshat_SeshatCharacter_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
