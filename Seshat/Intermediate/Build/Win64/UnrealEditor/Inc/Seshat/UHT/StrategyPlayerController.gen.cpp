// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Seshat/Variant_Strategy/StrategyPlayerController.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeStrategyPlayerController() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
ENGINE_API UClass* Z_Construct_UClass_APlayerController();
ENGINE_API UEnum* Z_Construct_UEnum_Engine_ETraceTypeQuery();
ENHANCEDINPUT_API UClass* Z_Construct_UClass_UInputAction_NoRegister();
ENHANCEDINPUT_API UClass* Z_Construct_UClass_UInputMappingContext_NoRegister();
SESHAT_API UClass* Z_Construct_UClass_AStrategyPlayerController();
SESHAT_API UClass* Z_Construct_UClass_AStrategyPlayerController_NoRegister();
SESHAT_API UClass* Z_Construct_UClass_AStrategyUnit_NoRegister();
SESHAT_API UEnum* Z_Construct_UEnum_Seshat_EStrategyInputMode();
UPackage* Z_Construct_UPackage__Script_Seshat();
// ********** End Cross Module References **********************************************************

// ********** Begin Enum EStrategyInputMode ********************************************************
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EStrategyInputMode;
static UEnum* EStrategyInputMode_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EStrategyInputMode.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EStrategyInputMode.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_Seshat_EStrategyInputMode, (UObject*)Z_Construct_UPackage__Script_Seshat(), TEXT("EStrategyInputMode"));
	}
	return Z_Registration_Info_UEnum_EStrategyInputMode.OuterSingleton;
}
template<> SESHAT_API UEnum* StaticEnum<EStrategyInputMode>()
{
	return EStrategyInputMode_StaticEnum();
}
struct Z_Construct_UEnum_Seshat_EStrategyInputMode_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Variant_Strategy/StrategyPlayerController.h" },
		{ "SIM_Mouse.DisplayName", "Mouse" },
		{ "SIM_Mouse.Name", "SIM_Mouse" },
		{ "SIM_Touch.DisplayName", "Touch" },
		{ "SIM_Touch.Name", "SIM_Touch" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "SIM_Mouse", (int64)SIM_Mouse },
		{ "SIM_Touch", (int64)SIM_Touch },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
};
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_Seshat_EStrategyInputMode_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_Seshat,
	nullptr,
	"EStrategyInputMode",
	"EStrategyInputMode",
	Z_Construct_UEnum_Seshat_EStrategyInputMode_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_Seshat_EStrategyInputMode_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::Regular,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_Seshat_EStrategyInputMode_Statics::Enum_MetaDataParams), Z_Construct_UEnum_Seshat_EStrategyInputMode_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_Seshat_EStrategyInputMode()
{
	if (!Z_Registration_Info_UEnum_EStrategyInputMode.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EStrategyInputMode.InnerSingleton, Z_Construct_UEnum_Seshat_EStrategyInputMode_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EStrategyInputMode.InnerSingleton;
}
// ********** End Enum EStrategyInputMode **********************************************************

// ********** Begin Class AStrategyPlayerController Function BP_CursorFeedback *********************
struct StrategyPlayerController_eventBP_CursorFeedback_Parms
{
	FVector Location;
	bool bPositive;
};
static FName NAME_AStrategyPlayerController_BP_CursorFeedback = FName(TEXT("BP_CursorFeedback"));
void AStrategyPlayerController::BP_CursorFeedback(FVector Location, bool bPositive)
{
	StrategyPlayerController_eventBP_CursorFeedback_Parms Parms;
	Parms.Location=Location;
	Parms.bPositive=bPositive ? true : false;
	UFunction* Func = FindFunctionChecked(NAME_AStrategyPlayerController_BP_CursorFeedback);
	ProcessEvent(Func,&Parms);
}
struct Z_Construct_UFunction_AStrategyPlayerController_BP_CursorFeedback_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Cursor" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Spawns the positive cursor effect */" },
#endif
		{ "DisplayName", "Cursor Feedback" },
		{ "ModuleRelativePath", "Variant_Strategy/StrategyPlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Spawns the positive cursor effect" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_Location;
	static void NewProp_bPositive_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bPositive;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_AStrategyPlayerController_BP_CursorFeedback_Statics::NewProp_Location = { "Location", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(StrategyPlayerController_eventBP_CursorFeedback_Parms, Location), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_AStrategyPlayerController_BP_CursorFeedback_Statics::NewProp_bPositive_SetBit(void* Obj)
{
	((StrategyPlayerController_eventBP_CursorFeedback_Parms*)Obj)->bPositive = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_AStrategyPlayerController_BP_CursorFeedback_Statics::NewProp_bPositive = { "bPositive", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(StrategyPlayerController_eventBP_CursorFeedback_Parms), &Z_Construct_UFunction_AStrategyPlayerController_BP_CursorFeedback_Statics::NewProp_bPositive_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AStrategyPlayerController_BP_CursorFeedback_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AStrategyPlayerController_BP_CursorFeedback_Statics::NewProp_Location,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AStrategyPlayerController_BP_CursorFeedback_Statics::NewProp_bPositive,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AStrategyPlayerController_BP_CursorFeedback_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AStrategyPlayerController_BP_CursorFeedback_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AStrategyPlayerController, nullptr, "BP_CursorFeedback", Z_Construct_UFunction_AStrategyPlayerController_BP_CursorFeedback_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AStrategyPlayerController_BP_CursorFeedback_Statics::PropPointers), sizeof(StrategyPlayerController_eventBP_CursorFeedback_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08880800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AStrategyPlayerController_BP_CursorFeedback_Statics::Function_MetaDataParams), Z_Construct_UFunction_AStrategyPlayerController_BP_CursorFeedback_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(StrategyPlayerController_eventBP_CursorFeedback_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AStrategyPlayerController_BP_CursorFeedback()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AStrategyPlayerController_BP_CursorFeedback_Statics::FuncParams);
	}
	return ReturnFunction;
}
// ********** End Class AStrategyPlayerController Function BP_CursorFeedback ***********************

// ********** Begin Class AStrategyPlayerController Function OnMoveCompleted ***********************
struct Z_Construct_UFunction_AStrategyPlayerController_OnMoveCompleted_Statics
{
	struct StrategyPlayerController_eventOnMoveCompleted_Parms
	{
		AStrategyUnit* MovedUnit;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Called when a unit move is completed */" },
#endif
		{ "ModuleRelativePath", "Variant_Strategy/StrategyPlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Called when a unit move is completed" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_MovedUnit;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_AStrategyPlayerController_OnMoveCompleted_Statics::NewProp_MovedUnit = { "MovedUnit", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(StrategyPlayerController_eventOnMoveCompleted_Parms, MovedUnit), Z_Construct_UClass_AStrategyUnit_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AStrategyPlayerController_OnMoveCompleted_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AStrategyPlayerController_OnMoveCompleted_Statics::NewProp_MovedUnit,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AStrategyPlayerController_OnMoveCompleted_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AStrategyPlayerController_OnMoveCompleted_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AStrategyPlayerController, nullptr, "OnMoveCompleted", Z_Construct_UFunction_AStrategyPlayerController_OnMoveCompleted_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AStrategyPlayerController_OnMoveCompleted_Statics::PropPointers), sizeof(Z_Construct_UFunction_AStrategyPlayerController_OnMoveCompleted_Statics::StrategyPlayerController_eventOnMoveCompleted_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AStrategyPlayerController_OnMoveCompleted_Statics::Function_MetaDataParams), Z_Construct_UFunction_AStrategyPlayerController_OnMoveCompleted_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_AStrategyPlayerController_OnMoveCompleted_Statics::StrategyPlayerController_eventOnMoveCompleted_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AStrategyPlayerController_OnMoveCompleted()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AStrategyPlayerController_OnMoveCompleted_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AStrategyPlayerController::execOnMoveCompleted)
{
	P_GET_OBJECT(AStrategyUnit,Z_Param_MovedUnit);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnMoveCompleted(Z_Param_MovedUnit);
	P_NATIVE_END;
}
// ********** End Class AStrategyPlayerController Function OnMoveCompleted *************************

// ********** Begin Class AStrategyPlayerController ************************************************
void AStrategyPlayerController::StaticRegisterNativesAStrategyPlayerController()
{
	UClass* Class = AStrategyPlayerController::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "OnMoveCompleted", &AStrategyPlayerController::execOnMoveCompleted },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_AStrategyPlayerController;
UClass* AStrategyPlayerController::GetPrivateStaticClass()
{
	using TClass = AStrategyPlayerController;
	if (!Z_Registration_Info_UClass_AStrategyPlayerController.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("StrategyPlayerController"),
			Z_Registration_Info_UClass_AStrategyPlayerController.InnerSingleton,
			StaticRegisterNativesAStrategyPlayerController,
			sizeof(TClass),
			alignof(TClass),
			TClass::StaticClassFlags,
			TClass::StaticClassCastFlags(),
			TClass::StaticConfigName(),
			(UClass::ClassConstructorType)InternalConstructor<TClass>,
			(UClass::ClassVTableHelperCtorCallerType)InternalVTableHelperCtorCaller<TClass>,
			UOBJECT_CPPCLASS_STATICFUNCTIONS_FORCLASS(TClass),
			&TClass::Super::StaticClass,
			&TClass::WithinClass::StaticClass
		);
	}
	return Z_Registration_Info_UClass_AStrategyPlayerController.InnerSingleton;
}
UClass* Z_Construct_UClass_AStrategyPlayerController_NoRegister()
{
	return AStrategyPlayerController::GetPrivateStaticClass();
}
struct Z_Construct_UClass_AStrategyPlayerController_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "HideCategories", "Collision Rendering Transformation" },
		{ "IncludePath", "Variant_Strategy/StrategyPlayerController.h" },
		{ "ModuleRelativePath", "Variant_Strategy/StrategyPlayerController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InputMode_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Determines the chosen input type */" },
#endif
		{ "ModuleRelativePath", "Variant_Strategy/StrategyPlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Determines the chosen input type" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MouseMappingContext_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Input mapping context to use with mouse input */" },
#endif
		{ "ModuleRelativePath", "Variant_Strategy/StrategyPlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Input mapping context to use with mouse input" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TouchMappingContext_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Input mapping context to use with touch input */" },
#endif
		{ "ModuleRelativePath", "Variant_Strategy/StrategyPlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Input mapping context to use with touch input" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MoveCameraAction_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Input Action for moving the camera */" },
#endif
		{ "ModuleRelativePath", "Variant_Strategy/StrategyPlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Input Action for moving the camera" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ZoomCameraAction_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Input Action for zooming the camera */" },
#endif
		{ "ModuleRelativePath", "Variant_Strategy/StrategyPlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Input Action for zooming the camera" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ResetCameraAction_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Input Action for resetting the camera to its default position */" },
#endif
		{ "ModuleRelativePath", "Variant_Strategy/StrategyPlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Input Action for resetting the camera to its default position" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SelectClickAction_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Input Action for select and click */" },
#endif
		{ "ModuleRelativePath", "Variant_Strategy/StrategyPlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Input Action for select and click" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SelectHoldAction_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Input Action for select press and hold */" },
#endif
		{ "ModuleRelativePath", "Variant_Strategy/StrategyPlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Input Action for select press and hold" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InteractClickAction_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Input Action for click interaction */" },
#endif
		{ "ModuleRelativePath", "Variant_Strategy/StrategyPlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Input Action for click interaction" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InteractHoldAction_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Input Action for interaction press and hold */" },
#endif
		{ "ModuleRelativePath", "Variant_Strategy/StrategyPlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Input Action for interaction press and hold" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SelectionModifierAction_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Input Action for modifying selection mode */" },
#endif
		{ "ModuleRelativePath", "Variant_Strategy/StrategyPlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Input Action for modifying selection mode" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TouchPrimaryTapAction_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Input Action for primary touch tap */" },
#endif
		{ "ModuleRelativePath", "Variant_Strategy/StrategyPlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Input Action for primary touch tap" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TouchPrimaryHoldAction_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Input Action for primary touch hold */" },
#endif
		{ "ModuleRelativePath", "Variant_Strategy/StrategyPlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Input Action for primary touch hold" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TouchSecondaryAction_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Input Action for secondary touch */" },
#endif
		{ "ModuleRelativePath", "Variant_Strategy/StrategyPlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Input Action for secondary touch" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TouchDoubleTapAction_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Input Action for touch double tap */" },
#endif
		{ "ModuleRelativePath", "Variant_Strategy/StrategyPlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Input Action for touch double tap" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InteractionRadius_MetaData[] = {
		{ "Category", "Input" },
		{ "ClampMax", "10000" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Max distance to look for nearby units when doing a click or touch interaction */" },
#endif
		{ "ModuleRelativePath", "Variant_Strategy/StrategyPlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Max distance to look for nearby units when doing a click or touch interaction" },
#endif
		{ "Units", "cm" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MinSecondFingerDistanceForBoxSelect_MetaData[] = {
		{ "Category", "Input" },
		{ "ClampMax", "10000" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Max distance between the starting and current position of the second touch finger to be considered a box selection */" },
#endif
		{ "ModuleRelativePath", "Variant_Strategy/StrategyPlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Max distance between the starting and current position of the second touch finger to be considered a box selection" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MinZoomLevel_MetaData[] = {
		{ "Category", "Camera" },
		{ "ClampMax", "10000" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Minimum allowed camera zoom level */" },
#endif
		{ "ModuleRelativePath", "Variant_Strategy/StrategyPlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Minimum allowed camera zoom level" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxZoomLevel_MetaData[] = {
		{ "Category", "Camera" },
		{ "ClampMax", "10000" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Maximum allowed camera zoom level */" },
#endif
		{ "ModuleRelativePath", "Variant_Strategy/StrategyPlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Maximum allowed camera zoom level" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ZoomScaling_MetaData[] = {
		{ "Category", "Camera" },
		{ "ClampMax", "1000" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Scales zoom inputs by this value */" },
#endif
		{ "ModuleRelativePath", "Variant_Strategy/StrategyPlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Scales zoom inputs by this value" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DragMultiplier_MetaData[] = {
		{ "Category", "Camera" },
		{ "ClampMax", "10000" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Affects how fast the camera moves while dragging with the mouse */" },
#endif
		{ "ModuleRelativePath", "Variant_Strategy/StrategyPlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Affects how fast the camera moves while dragging with the mouse" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SelectionTraceChannel_MetaData[] = {
		{ "Category", "Selection" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Trace channel to use for selection trace checks */" },
#endif
		{ "ModuleRelativePath", "Variant_Strategy/StrategyPlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Trace channel to use for selection trace checks" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FBytePropertyParams NewProp_InputMode;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_MouseMappingContext;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_TouchMappingContext;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_MoveCameraAction;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ZoomCameraAction;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ResetCameraAction;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SelectClickAction;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SelectHoldAction;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_InteractClickAction;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_InteractHoldAction;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SelectionModifierAction;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_TouchPrimaryTapAction;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_TouchPrimaryHoldAction;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_TouchSecondaryAction;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_TouchDoubleTapAction;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_InteractionRadius;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MinSecondFingerDistanceForBoxSelect;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MinZoomLevel;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MaxZoomLevel;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ZoomScaling;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DragMultiplier;
	static const UECodeGen_Private::FBytePropertyParams NewProp_SelectionTraceChannel;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_AStrategyPlayerController_BP_CursorFeedback, "BP_CursorFeedback" }, // 167615873
		{ &Z_Construct_UFunction_AStrategyPlayerController_OnMoveCompleted, "OnMoveCompleted" }, // 398047304
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AStrategyPlayerController>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_AStrategyPlayerController_Statics::NewProp_InputMode = { "InputMode", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AStrategyPlayerController, InputMode), Z_Construct_UEnum_Seshat_EStrategyInputMode, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InputMode_MetaData), NewProp_InputMode_MetaData) }; // 1109954810
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AStrategyPlayerController_Statics::NewProp_MouseMappingContext = { "MouseMappingContext", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AStrategyPlayerController, MouseMappingContext), Z_Construct_UClass_UInputMappingContext_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MouseMappingContext_MetaData), NewProp_MouseMappingContext_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AStrategyPlayerController_Statics::NewProp_TouchMappingContext = { "TouchMappingContext", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AStrategyPlayerController, TouchMappingContext), Z_Construct_UClass_UInputMappingContext_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TouchMappingContext_MetaData), NewProp_TouchMappingContext_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AStrategyPlayerController_Statics::NewProp_MoveCameraAction = { "MoveCameraAction", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AStrategyPlayerController, MoveCameraAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MoveCameraAction_MetaData), NewProp_MoveCameraAction_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AStrategyPlayerController_Statics::NewProp_ZoomCameraAction = { "ZoomCameraAction", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AStrategyPlayerController, ZoomCameraAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ZoomCameraAction_MetaData), NewProp_ZoomCameraAction_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AStrategyPlayerController_Statics::NewProp_ResetCameraAction = { "ResetCameraAction", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AStrategyPlayerController, ResetCameraAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ResetCameraAction_MetaData), NewProp_ResetCameraAction_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AStrategyPlayerController_Statics::NewProp_SelectClickAction = { "SelectClickAction", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AStrategyPlayerController, SelectClickAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SelectClickAction_MetaData), NewProp_SelectClickAction_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AStrategyPlayerController_Statics::NewProp_SelectHoldAction = { "SelectHoldAction", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AStrategyPlayerController, SelectHoldAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SelectHoldAction_MetaData), NewProp_SelectHoldAction_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AStrategyPlayerController_Statics::NewProp_InteractClickAction = { "InteractClickAction", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AStrategyPlayerController, InteractClickAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InteractClickAction_MetaData), NewProp_InteractClickAction_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AStrategyPlayerController_Statics::NewProp_InteractHoldAction = { "InteractHoldAction", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AStrategyPlayerController, InteractHoldAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InteractHoldAction_MetaData), NewProp_InteractHoldAction_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AStrategyPlayerController_Statics::NewProp_SelectionModifierAction = { "SelectionModifierAction", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AStrategyPlayerController, SelectionModifierAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SelectionModifierAction_MetaData), NewProp_SelectionModifierAction_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AStrategyPlayerController_Statics::NewProp_TouchPrimaryTapAction = { "TouchPrimaryTapAction", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AStrategyPlayerController, TouchPrimaryTapAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TouchPrimaryTapAction_MetaData), NewProp_TouchPrimaryTapAction_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AStrategyPlayerController_Statics::NewProp_TouchPrimaryHoldAction = { "TouchPrimaryHoldAction", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AStrategyPlayerController, TouchPrimaryHoldAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TouchPrimaryHoldAction_MetaData), NewProp_TouchPrimaryHoldAction_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AStrategyPlayerController_Statics::NewProp_TouchSecondaryAction = { "TouchSecondaryAction", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AStrategyPlayerController, TouchSecondaryAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TouchSecondaryAction_MetaData), NewProp_TouchSecondaryAction_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AStrategyPlayerController_Statics::NewProp_TouchDoubleTapAction = { "TouchDoubleTapAction", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AStrategyPlayerController, TouchDoubleTapAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TouchDoubleTapAction_MetaData), NewProp_TouchDoubleTapAction_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AStrategyPlayerController_Statics::NewProp_InteractionRadius = { "InteractionRadius", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AStrategyPlayerController, InteractionRadius), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InteractionRadius_MetaData), NewProp_InteractionRadius_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AStrategyPlayerController_Statics::NewProp_MinSecondFingerDistanceForBoxSelect = { "MinSecondFingerDistanceForBoxSelect", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AStrategyPlayerController, MinSecondFingerDistanceForBoxSelect), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MinSecondFingerDistanceForBoxSelect_MetaData), NewProp_MinSecondFingerDistanceForBoxSelect_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AStrategyPlayerController_Statics::NewProp_MinZoomLevel = { "MinZoomLevel", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AStrategyPlayerController, MinZoomLevel), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MinZoomLevel_MetaData), NewProp_MinZoomLevel_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AStrategyPlayerController_Statics::NewProp_MaxZoomLevel = { "MaxZoomLevel", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AStrategyPlayerController, MaxZoomLevel), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxZoomLevel_MetaData), NewProp_MaxZoomLevel_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AStrategyPlayerController_Statics::NewProp_ZoomScaling = { "ZoomScaling", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AStrategyPlayerController, ZoomScaling), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ZoomScaling_MetaData), NewProp_ZoomScaling_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AStrategyPlayerController_Statics::NewProp_DragMultiplier = { "DragMultiplier", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AStrategyPlayerController, DragMultiplier), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DragMultiplier_MetaData), NewProp_DragMultiplier_MetaData) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_AStrategyPlayerController_Statics::NewProp_SelectionTraceChannel = { "SelectionTraceChannel", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AStrategyPlayerController, SelectionTraceChannel), Z_Construct_UEnum_Engine_ETraceTypeQuery, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SelectionTraceChannel_MetaData), NewProp_SelectionTraceChannel_MetaData) }; // 1673313466
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AStrategyPlayerController_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AStrategyPlayerController_Statics::NewProp_InputMode,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AStrategyPlayerController_Statics::NewProp_MouseMappingContext,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AStrategyPlayerController_Statics::NewProp_TouchMappingContext,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AStrategyPlayerController_Statics::NewProp_MoveCameraAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AStrategyPlayerController_Statics::NewProp_ZoomCameraAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AStrategyPlayerController_Statics::NewProp_ResetCameraAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AStrategyPlayerController_Statics::NewProp_SelectClickAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AStrategyPlayerController_Statics::NewProp_SelectHoldAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AStrategyPlayerController_Statics::NewProp_InteractClickAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AStrategyPlayerController_Statics::NewProp_InteractHoldAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AStrategyPlayerController_Statics::NewProp_SelectionModifierAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AStrategyPlayerController_Statics::NewProp_TouchPrimaryTapAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AStrategyPlayerController_Statics::NewProp_TouchPrimaryHoldAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AStrategyPlayerController_Statics::NewProp_TouchSecondaryAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AStrategyPlayerController_Statics::NewProp_TouchDoubleTapAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AStrategyPlayerController_Statics::NewProp_InteractionRadius,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AStrategyPlayerController_Statics::NewProp_MinSecondFingerDistanceForBoxSelect,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AStrategyPlayerController_Statics::NewProp_MinZoomLevel,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AStrategyPlayerController_Statics::NewProp_MaxZoomLevel,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AStrategyPlayerController_Statics::NewProp_ZoomScaling,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AStrategyPlayerController_Statics::NewProp_DragMultiplier,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AStrategyPlayerController_Statics::NewProp_SelectionTraceChannel,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AStrategyPlayerController_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_AStrategyPlayerController_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_APlayerController,
	(UObject* (*)())Z_Construct_UPackage__Script_Seshat,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AStrategyPlayerController_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AStrategyPlayerController_Statics::ClassParams = {
	&AStrategyPlayerController::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_AStrategyPlayerController_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_AStrategyPlayerController_Statics::PropPointers),
	0,
	0x008003A5u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AStrategyPlayerController_Statics::Class_MetaDataParams), Z_Construct_UClass_AStrategyPlayerController_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AStrategyPlayerController()
{
	if (!Z_Registration_Info_UClass_AStrategyPlayerController.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AStrategyPlayerController.OuterSingleton, Z_Construct_UClass_AStrategyPlayerController_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AStrategyPlayerController.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(AStrategyPlayerController);
AStrategyPlayerController::~AStrategyPlayerController() {}
// ********** End Class AStrategyPlayerController **************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_Strategy_StrategyPlayerController_h__Script_Seshat_Statics
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ EStrategyInputMode_StaticEnum, TEXT("EStrategyInputMode"), &Z_Registration_Info_UEnum_EStrategyInputMode, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 1109954810U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AStrategyPlayerController, AStrategyPlayerController::StaticClass, TEXT("AStrategyPlayerController"), &Z_Registration_Info_UClass_AStrategyPlayerController, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AStrategyPlayerController), 2666063204U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_Strategy_StrategyPlayerController_h__Script_Seshat_1922229801(TEXT("/Script/Seshat"),
	Z_CompiledInDeferFile_FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_Strategy_StrategyPlayerController_h__Script_Seshat_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_Strategy_StrategyPlayerController_h__Script_Seshat_Statics::ClassInfo),
	nullptr, 0,
	Z_CompiledInDeferFile_FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_Strategy_StrategyPlayerController_h__Script_Seshat_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Projects_share_seshat_Seshat_Source_Seshat_Variant_Strategy_StrategyPlayerController_h__Script_Seshat_Statics::EnumInfo));
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
