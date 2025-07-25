// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Variant_TwinStick/TwinStickPlayerController.h"

#ifdef SESHAT_TwinStickPlayerController_generated_h
#error "TwinStickPlayerController.generated.h already included, missing '#pragma once' in TwinStickPlayerController.h"
#endif
#define SESHAT_TwinStickPlayerController_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

class AActor;

// ********** Begin Class ATwinStickPlayerController ***********************************************
#define FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_TwinStick_TwinStickPlayerController_h_20_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execOnPawnDestroyed);


SESHAT_API UClass* Z_Construct_UClass_ATwinStickPlayerController_NoRegister();

#define FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_TwinStick_TwinStickPlayerController_h_20_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesATwinStickPlayerController(); \
	friend struct Z_Construct_UClass_ATwinStickPlayerController_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend SESHAT_API UClass* Z_Construct_UClass_ATwinStickPlayerController_NoRegister(); \
public: \
	DECLARE_CLASS2(ATwinStickPlayerController, APlayerController, COMPILED_IN_FLAGS(CLASS_Abstract | CLASS_Config), CASTCLASS_None, TEXT("/Script/Seshat"), Z_Construct_UClass_ATwinStickPlayerController_NoRegister) \
	DECLARE_SERIALIZER(ATwinStickPlayerController)


#define FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_TwinStick_TwinStickPlayerController_h_20_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ATwinStickPlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	ATwinStickPlayerController(ATwinStickPlayerController&&) = delete; \
	ATwinStickPlayerController(const ATwinStickPlayerController&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ATwinStickPlayerController); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ATwinStickPlayerController); \
	DEFINE_ABSTRACT_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ATwinStickPlayerController) \
	NO_API virtual ~ATwinStickPlayerController();


#define FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_TwinStick_TwinStickPlayerController_h_17_PROLOG
#define FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_TwinStick_TwinStickPlayerController_h_20_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_TwinStick_TwinStickPlayerController_h_20_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_TwinStick_TwinStickPlayerController_h_20_INCLASS_NO_PURE_DECLS \
	FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_TwinStick_TwinStickPlayerController_h_20_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class ATwinStickPlayerController;

// ********** End Class ATwinStickPlayerController *************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_TwinStick_TwinStickPlayerController_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
