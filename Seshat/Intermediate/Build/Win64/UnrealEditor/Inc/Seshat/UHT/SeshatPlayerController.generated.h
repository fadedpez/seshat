// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "SeshatPlayerController.h"

#ifdef SESHAT_SeshatPlayerController_generated_h
#error "SeshatPlayerController.generated.h already included, missing '#pragma once' in SeshatPlayerController.h"
#endif
#define SESHAT_SeshatPlayerController_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class ASeshatPlayerController **************************************************
SESHAT_API UClass* Z_Construct_UClass_ASeshatPlayerController_NoRegister();

#define FID_Projects_share_seshat_Seshat_Source_Seshat_SeshatPlayerController_h_23_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesASeshatPlayerController(); \
	friend struct Z_Construct_UClass_ASeshatPlayerController_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend SESHAT_API UClass* Z_Construct_UClass_ASeshatPlayerController_NoRegister(); \
public: \
	DECLARE_CLASS2(ASeshatPlayerController, APlayerController, COMPILED_IN_FLAGS(CLASS_Abstract | CLASS_Config), CASTCLASS_None, TEXT("/Script/Seshat"), Z_Construct_UClass_ASeshatPlayerController_NoRegister) \
	DECLARE_SERIALIZER(ASeshatPlayerController)


#define FID_Projects_share_seshat_Seshat_Source_Seshat_SeshatPlayerController_h_23_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	ASeshatPlayerController(ASeshatPlayerController&&) = delete; \
	ASeshatPlayerController(const ASeshatPlayerController&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ASeshatPlayerController); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ASeshatPlayerController); \
	DEFINE_ABSTRACT_DEFAULT_CONSTRUCTOR_CALL(ASeshatPlayerController) \
	NO_API virtual ~ASeshatPlayerController();


#define FID_Projects_share_seshat_Seshat_Source_Seshat_SeshatPlayerController_h_20_PROLOG
#define FID_Projects_share_seshat_Seshat_Source_Seshat_SeshatPlayerController_h_23_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Projects_share_seshat_Seshat_Source_Seshat_SeshatPlayerController_h_23_INCLASS_NO_PURE_DECLS \
	FID_Projects_share_seshat_Seshat_Source_Seshat_SeshatPlayerController_h_23_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class ASeshatPlayerController;

// ********** End Class ASeshatPlayerController ****************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Projects_share_seshat_Seshat_Source_Seshat_SeshatPlayerController_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
