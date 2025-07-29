#include "RPGEventBusSubsystem.h"
#include "HAL/PlatformProcess.h"
#include "Misc/Paths.h"

void URPGEventBusSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
    
    UE_LOG(LogTemp, Warning, TEXT("RPGEventBusSubsystem: Initializing"));
    
    // Initialize all function pointers to nullptr
    bFunctionsLoaded = false;
    ToolkitDLLHandle = nullptr;
    
    // Initialize all function pointers
    CreateEventBusFuncPtr = nullptr;
    PublishEventFuncPtr = nullptr;
    SubscribeEventFuncPtr = nullptr;
    UnsubscribeEventFuncPtr = nullptr;
    
    GetEventBeforeAttackRollFuncPtr = nullptr;
    GetEventOnAttackRollFuncPtr = nullptr;
    GetEventAfterAttackRollFuncPtr = nullptr;
    GetEventBeforeDamageRollFuncPtr = nullptr;
    GetEventOnTakeDamageFuncPtr = nullptr;
    GetEventCalculateDamageFuncPtr = nullptr;
    GetEventAfterDamageFuncPtr = nullptr;
    GetEventEntityPlacedFuncPtr = nullptr;
    GetEventEntityMovedFuncPtr = nullptr;
    GetEventRoomCreatedFuncPtr = nullptr;
    GetEventTurnStartFuncPtr = nullptr;
    GetEventTurnEndFuncPtr = nullptr;
    GetEventRoundStartFuncPtr = nullptr;
    GetEventRoundEndFuncPtr = nullptr;
    GetEventStatusAppliedFuncPtr = nullptr;
    GetEventStatusRemovedFuncPtr = nullptr;
    GetEventStatusCheckFuncPtr = nullptr;
    
    GetContextKeyAttackerFuncPtr = nullptr;
    GetContextKeyTargetFuncPtr = nullptr;
    GetContextKeyWeaponFuncPtr = nullptr;
    GetContextKeyDamageTypeFuncPtr = nullptr;
    GetContextKeyAdvantageFuncPtr = nullptr;
    GetContextKeyRollFuncPtr = nullptr;
    GetContextKeyOldPositionFuncPtr = nullptr;
    GetContextKeyNewPositionFuncPtr = nullptr;
    GetContextKeyRoomIDFuncPtr = nullptr;
    
    CreateModifierFuncPtr = nullptr;
    CreateIntModifierFuncPtr = nullptr;
    CreateDiceModifierFuncPtr = nullptr;
    
    GetDurationPermanentFuncPtr = nullptr;
    GetDurationRoundsFuncPtr = nullptr;
    GetDurationMinutesFuncPtr = nullptr;
    GetDurationHoursFuncPtr = nullptr;
    GetDurationEncounterFuncPtr = nullptr;
    GetDurationConcentrationFuncPtr = nullptr;
    GetDurationShortRestFuncPtr = nullptr;
    GetDurationLongRestFuncPtr = nullptr;
    GetDurationUntilDamagedFuncPtr = nullptr;
    GetDurationUntilSaveFuncPtr = nullptr;
    
    FreeEventStringFuncPtr = nullptr;
    
    // Load DLL functions
    LoadDLLFunctions();
    
    if (bFunctionsLoaded)
    {
        UE_LOG(LogTemp, Warning, TEXT("RPGEventBusSubsystem: Successfully initialized"));
        
        // Create event bus instance
        if (CreateEventBusFuncPtr)
        {
            FString Result = CreateEventBus();
            UE_LOG(LogTemp, Warning, TEXT("RPGEventBusSubsystem: EventBus created: %s"), *Result);
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("RPGEventBusSubsystem: Failed to initialize - DLL functions not loaded"));
    }
}

void URPGEventBusSubsystem::Deinitialize()
{
    UE_LOG(LogTemp, Warning, TEXT("RPGEventBusSubsystem: Deinitializing"));
    
    // Clear all function pointers
    CreateEventBusFuncPtr = nullptr;
    PublishEventFuncPtr = nullptr;
    SubscribeEventFuncPtr = nullptr;
    UnsubscribeEventFuncPtr = nullptr;
    
    GetEventBeforeAttackRollFuncPtr = nullptr;
    GetEventOnAttackRollFuncPtr = nullptr;
    GetEventAfterAttackRollFuncPtr = nullptr;
    GetEventBeforeDamageRollFuncPtr = nullptr;
    GetEventOnTakeDamageFuncPtr = nullptr;
    GetEventCalculateDamageFuncPtr = nullptr;
    GetEventAfterDamageFuncPtr = nullptr;
    GetEventEntityPlacedFuncPtr = nullptr;
    GetEventEntityMovedFuncPtr = nullptr;
    GetEventRoomCreatedFuncPtr = nullptr;
    GetEventTurnStartFuncPtr = nullptr;
    GetEventTurnEndFuncPtr = nullptr;
    GetEventRoundStartFuncPtr = nullptr;
    GetEventRoundEndFuncPtr = nullptr;
    GetEventStatusAppliedFuncPtr = nullptr;
    GetEventStatusRemovedFuncPtr = nullptr;
    GetEventStatusCheckFuncPtr = nullptr;
    
    GetContextKeyAttackerFuncPtr = nullptr;
    GetContextKeyTargetFuncPtr = nullptr;
    GetContextKeyWeaponFuncPtr = nullptr;
    GetContextKeyDamageTypeFuncPtr = nullptr;
    GetContextKeyAdvantageFuncPtr = nullptr;
    GetContextKeyRollFuncPtr = nullptr;
    GetContextKeyOldPositionFuncPtr = nullptr;
    GetContextKeyNewPositionFuncPtr = nullptr;
    GetContextKeyRoomIDFuncPtr = nullptr;
    
    CreateModifierFuncPtr = nullptr;
    CreateIntModifierFuncPtr = nullptr;
    CreateDiceModifierFuncPtr = nullptr;
    
    GetDurationPermanentFuncPtr = nullptr;
    GetDurationRoundsFuncPtr = nullptr;
    GetDurationMinutesFuncPtr = nullptr;
    GetDurationHoursFuncPtr = nullptr;
    GetDurationEncounterFuncPtr = nullptr;
    GetDurationConcentrationFuncPtr = nullptr;
    GetDurationShortRestFuncPtr = nullptr;
    GetDurationLongRestFuncPtr = nullptr;
    GetDurationUntilDamagedFuncPtr = nullptr;
    GetDurationUntilSaveFuncPtr = nullptr;
    
    FreeEventStringFuncPtr = nullptr;
    
    bFunctionsLoaded = false;
    ToolkitDLLHandle = nullptr;
    
    Super::Deinitialize();
}

// EventBus Management Functions Implementation
FString URPGEventBusSubsystem::CreateEventBus()
{
    if (!IsSafeToCallFunction() || !CreateEventBusFuncPtr)
    {
        return TEXT("ERROR: Function not available");
    }
    
    ANSICHAR* CStr = CreateEventBusFuncPtr();
    return ConvertAndFreeString(CStr);
}

bool URPGEventBusSubsystem::PublishEvent(const FString& EventType, const FString& SourceID, const FString& TargetID, const FString& ContextData)
{
    if (!IsSafeToCallFunction() || !PublishEventFuncPtr)
    {
        return false;
    }
    
    return PublishEventFuncPtr(TCHAR_TO_ANSI(*EventType), TCHAR_TO_ANSI(*SourceID), TCHAR_TO_ANSI(*TargetID), TCHAR_TO_ANSI(*ContextData)) != 0;
}

FString URPGEventBusSubsystem::SubscribeEvent(const FString& EventType, int32 Priority)
{
    if (!IsSafeToCallFunction() || !SubscribeEventFuncPtr)
    {
        return TEXT("");
    }
    
    ANSICHAR* CStr = SubscribeEventFuncPtr(TCHAR_TO_ANSI(*EventType), Priority);
    return ConvertAndFreeString(CStr);
}

bool URPGEventBusSubsystem::UnsubscribeEvent(const FString& SubscriptionID)
{
    if (!IsSafeToCallFunction() || !UnsubscribeEventFuncPtr)
    {
        return false;
    }
    
    return UnsubscribeEventFuncPtr(TCHAR_TO_ANSI(*SubscriptionID)) != 0;
}

// Event Type Constants Implementation
FString URPGEventBusSubsystem::GetEventBeforeAttackRoll() const
{
    if (!IsSafeToCallFunction() || !GetEventBeforeAttackRollFuncPtr)
    {
        return TEXT("before_attack_roll");
    }
    
    ANSICHAR* CStr = GetEventBeforeAttackRollFuncPtr();
    return ConvertAndFreeString(CStr);
}

FString URPGEventBusSubsystem::GetEventOnAttackRoll() const
{
    if (!IsSafeToCallFunction() || !GetEventOnAttackRollFuncPtr)
    {
        return TEXT("on_attack_roll");
    }
    
    ANSICHAR* CStr = GetEventOnAttackRollFuncPtr();
    return ConvertAndFreeString(CStr);
}

FString URPGEventBusSubsystem::GetEventAfterAttackRoll() const
{
    if (!IsSafeToCallFunction() || !GetEventAfterAttackRollFuncPtr)
    {
        return TEXT("after_attack_roll");
    }
    
    ANSICHAR* CStr = GetEventAfterAttackRollFuncPtr();
    return ConvertAndFreeString(CStr);
}

FString URPGEventBusSubsystem::GetEventBeforeDamageRoll() const
{
    if (!IsSafeToCallFunction() || !GetEventBeforeDamageRollFuncPtr)
    {
        return TEXT("before_damage_roll");
    }
    
    ANSICHAR* CStr = GetEventBeforeDamageRollFuncPtr();
    return ConvertAndFreeString(CStr);
}

FString URPGEventBusSubsystem::GetEventOnTakeDamage() const
{
    if (!IsSafeToCallFunction() || !GetEventOnTakeDamageFuncPtr)
    {
        return TEXT("on_take_damage");
    }
    
    ANSICHAR* CStr = GetEventOnTakeDamageFuncPtr();
    return ConvertAndFreeString(CStr);
}

FString URPGEventBusSubsystem::GetEventCalculateDamage() const
{
    if (!IsSafeToCallFunction() || !GetEventCalculateDamageFuncPtr)
    {
        return TEXT("calculate_damage");
    }
    
    ANSICHAR* CStr = GetEventCalculateDamageFuncPtr();
    return ConvertAndFreeString(CStr);
}

FString URPGEventBusSubsystem::GetEventAfterDamage() const
{
    if (!IsSafeToCallFunction() || !GetEventAfterDamageFuncPtr)
    {
        return TEXT("after_damage");
    }
    
    ANSICHAR* CStr = GetEventAfterDamageFuncPtr();
    return ConvertAndFreeString(CStr);
}

FString URPGEventBusSubsystem::GetEventEntityPlaced() const
{
    if (!IsSafeToCallFunction() || !GetEventEntityPlacedFuncPtr)
    {
        return TEXT("spatial.entity.placed");
    }
    
    ANSICHAR* CStr = GetEventEntityPlacedFuncPtr();
    return ConvertAndFreeString(CStr);
}

FString URPGEventBusSubsystem::GetEventEntityMoved() const
{
    if (!IsSafeToCallFunction() || !GetEventEntityMovedFuncPtr)
    {
        return TEXT("spatial.entity.moved");
    }
    
    ANSICHAR* CStr = GetEventEntityMovedFuncPtr();
    return ConvertAndFreeString(CStr);
}

FString URPGEventBusSubsystem::GetEventRoomCreated() const
{
    if (!IsSafeToCallFunction() || !GetEventRoomCreatedFuncPtr)
    {
        return TEXT("spatial.room.created");
    }
    
    ANSICHAR* CStr = GetEventRoomCreatedFuncPtr();
    return ConvertAndFreeString(CStr);
}

FString URPGEventBusSubsystem::GetEventTurnStart() const
{
    if (!IsSafeToCallFunction() || !GetEventTurnStartFuncPtr)
    {
        return TEXT("turn_start");
    }
    
    ANSICHAR* CStr = GetEventTurnStartFuncPtr();
    return ConvertAndFreeString(CStr);
}

FString URPGEventBusSubsystem::GetEventTurnEnd() const
{
    if (!IsSafeToCallFunction() || !GetEventTurnEndFuncPtr)
    {
        return TEXT("turn_end");
    }
    
    ANSICHAR* CStr = GetEventTurnEndFuncPtr();
    return ConvertAndFreeString(CStr);
}

FString URPGEventBusSubsystem::GetEventRoundStart() const
{
    if (!IsSafeToCallFunction() || !GetEventRoundStartFuncPtr)
    {
        return TEXT("round_start");
    }
    
    ANSICHAR* CStr = GetEventRoundStartFuncPtr();
    return ConvertAndFreeString(CStr);
}

FString URPGEventBusSubsystem::GetEventRoundEnd() const
{
    if (!IsSafeToCallFunction() || !GetEventRoundEndFuncPtr)
    {
        return TEXT("round_end");
    }
    
    ANSICHAR* CStr = GetEventRoundEndFuncPtr();
    return ConvertAndFreeString(CStr);
}

FString URPGEventBusSubsystem::GetEventStatusApplied() const
{
    if (!IsSafeToCallFunction() || !GetEventStatusAppliedFuncPtr)
    {
        return TEXT("status_applied");
    }
    
    ANSICHAR* CStr = GetEventStatusAppliedFuncPtr();
    return ConvertAndFreeString(CStr);
}

FString URPGEventBusSubsystem::GetEventStatusRemoved() const
{
    if (!IsSafeToCallFunction() || !GetEventStatusRemovedFuncPtr)
    {
        return TEXT("status_removed");
    }
    
    ANSICHAR* CStr = GetEventStatusRemovedFuncPtr();
    return ConvertAndFreeString(CStr);
}

FString URPGEventBusSubsystem::GetEventStatusCheck() const
{
    if (!IsSafeToCallFunction() || !GetEventStatusCheckFuncPtr)
    {
        return TEXT("status_check");
    }
    
    ANSICHAR* CStr = GetEventStatusCheckFuncPtr();
    return ConvertAndFreeString(CStr);
}

// Context Key Constants Implementation
FString URPGEventBusSubsystem::GetContextKeyAttacker() const
{
    if (!IsSafeToCallFunction() || !GetContextKeyAttackerFuncPtr)
    {
        return TEXT("attacker");
    }
    
    ANSICHAR* CStr = GetContextKeyAttackerFuncPtr();
    return ConvertAndFreeString(CStr);
}

FString URPGEventBusSubsystem::GetContextKeyTarget() const
{
    if (!IsSafeToCallFunction() || !GetContextKeyTargetFuncPtr)
    {
        return TEXT("target");
    }
    
    ANSICHAR* CStr = GetContextKeyTargetFuncPtr();
    return ConvertAndFreeString(CStr);
}

FString URPGEventBusSubsystem::GetContextKeyWeapon() const
{
    if (!IsSafeToCallFunction() || !GetContextKeyWeaponFuncPtr)
    {
        return TEXT("weapon");
    }
    
    ANSICHAR* CStr = GetContextKeyWeaponFuncPtr();
    return ConvertAndFreeString(CStr);
}

FString URPGEventBusSubsystem::GetContextKeyDamageType() const
{
    if (!IsSafeToCallFunction() || !GetContextKeyDamageTypeFuncPtr)
    {
        return TEXT("damage_type");
    }
    
    ANSICHAR* CStr = GetContextKeyDamageTypeFuncPtr();
    return ConvertAndFreeString(CStr);
}

FString URPGEventBusSubsystem::GetContextKeyAdvantage() const
{
    if (!IsSafeToCallFunction() || !GetContextKeyAdvantageFuncPtr)
    {
        return TEXT("advantage");
    }
    
    ANSICHAR* CStr = GetContextKeyAdvantageFuncPtr();
    return ConvertAndFreeString(CStr);
}

FString URPGEventBusSubsystem::GetContextKeyRoll() const
{
    if (!IsSafeToCallFunction() || !GetContextKeyRollFuncPtr)
    {
        return TEXT("roll");
    }
    
    ANSICHAR* CStr = GetContextKeyRollFuncPtr();
    return ConvertAndFreeString(CStr);
}

FString URPGEventBusSubsystem::GetContextKeyOldPosition() const
{
    if (!IsSafeToCallFunction() || !GetContextKeyOldPositionFuncPtr)
    {
        return TEXT("old_position");
    }
    
    ANSICHAR* CStr = GetContextKeyOldPositionFuncPtr();
    return ConvertAndFreeString(CStr);
}

FString URPGEventBusSubsystem::GetContextKeyNewPosition() const
{
    if (!IsSafeToCallFunction() || !GetContextKeyNewPositionFuncPtr)
    {
        return TEXT("new_position");
    }
    
    ANSICHAR* CStr = GetContextKeyNewPositionFuncPtr();
    return ConvertAndFreeString(CStr);
}

FString URPGEventBusSubsystem::GetContextKeyRoomID() const
{
    if (!IsSafeToCallFunction() || !GetContextKeyRoomIDFuncPtr)
    {
        return TEXT("room_id");
    }
    
    ANSICHAR* CStr = GetContextKeyRoomIDFuncPtr();
    return ConvertAndFreeString(CStr);
}

// Modifier Creation Functions Implementation
FString URPGEventBusSubsystem::CreateModifier(const FString& Source, const FString& ModifierType, int32 Value, int32 Priority)
{
    if (!IsSafeToCallFunction() || !CreateModifierFuncPtr)
    {
        return TEXT("ERROR: Function not available");
    }
    
    ANSICHAR* CStr = CreateModifierFuncPtr(TCHAR_TO_ANSI(*Source), TCHAR_TO_ANSI(*ModifierType), Value, Priority);
    return ConvertAndFreeString(CStr);
}

FString URPGEventBusSubsystem::CreateIntModifier(const FString& Source, const FString& ModifierType, int32 Value)
{
    if (!IsSafeToCallFunction() || !CreateIntModifierFuncPtr)
    {
        return TEXT("ERROR: Function not available");
    }
    
    ANSICHAR* CStr = CreateIntModifierFuncPtr(TCHAR_TO_ANSI(*Source), TCHAR_TO_ANSI(*ModifierType), Value);
    return ConvertAndFreeString(CStr);
}

FString URPGEventBusSubsystem::CreateDiceModifier(const FString& Source, const FString& ModifierType, const FString& DiceExpression)
{
    if (!IsSafeToCallFunction() || !CreateDiceModifierFuncPtr)
    {
        return TEXT("ERROR: Function not available");
    }
    
    ANSICHAR* CStr = CreateDiceModifierFuncPtr(TCHAR_TO_ANSI(*Source), TCHAR_TO_ANSI(*ModifierType), TCHAR_TO_ANSI(*DiceExpression));
    return ConvertAndFreeString(CStr);
}

// Duration Constants Implementation
FString URPGEventBusSubsystem::GetDurationPermanent() const
{
    if (!IsSafeToCallFunction() || !GetDurationPermanentFuncPtr)
    {
        return TEXT("permanent");
    }
    
    ANSICHAR* CStr = GetDurationPermanentFuncPtr();
    return ConvertAndFreeString(CStr);
}

FString URPGEventBusSubsystem::GetDurationRounds() const
{
    if (!IsSafeToCallFunction() || !GetDurationRoundsFuncPtr)
    {
        return TEXT("rounds");
    }
    
    ANSICHAR* CStr = GetDurationRoundsFuncPtr();
    return ConvertAndFreeString(CStr);
}

FString URPGEventBusSubsystem::GetDurationMinutes() const
{
    if (!IsSafeToCallFunction() || !GetDurationMinutesFuncPtr)
    {
        return TEXT("minutes");
    }
    
    ANSICHAR* CStr = GetDurationMinutesFuncPtr();
    return ConvertAndFreeString(CStr);
}

FString URPGEventBusSubsystem::GetDurationHours() const
{
    if (!IsSafeToCallFunction() || !GetDurationHoursFuncPtr)
    {
        return TEXT("hours");
    }
    
    ANSICHAR* CStr = GetDurationHoursFuncPtr();
    return ConvertAndFreeString(CStr);
}

FString URPGEventBusSubsystem::GetDurationEncounter() const
{
    if (!IsSafeToCallFunction() || !GetDurationEncounterFuncPtr)
    {
        return TEXT("encounter");
    }
    
    ANSICHAR* CStr = GetDurationEncounterFuncPtr();
    return ConvertAndFreeString(CStr);
}

FString URPGEventBusSubsystem::GetDurationConcentration() const
{
    if (!IsSafeToCallFunction() || !GetDurationConcentrationFuncPtr)
    {
        return TEXT("concentration");
    }
    
    ANSICHAR* CStr = GetDurationConcentrationFuncPtr();
    return ConvertAndFreeString(CStr);
}

FString URPGEventBusSubsystem::GetDurationShortRest() const
{
    if (!IsSafeToCallFunction() || !GetDurationShortRestFuncPtr)
    {
        return TEXT("short_rest");
    }
    
    ANSICHAR* CStr = GetDurationShortRestFuncPtr();
    return ConvertAndFreeString(CStr);
}

FString URPGEventBusSubsystem::GetDurationLongRest() const
{
    if (!IsSafeToCallFunction() || !GetDurationLongRestFuncPtr)
    {
        return TEXT("long_rest");
    }
    
    ANSICHAR* CStr = GetDurationLongRestFuncPtr();
    return ConvertAndFreeString(CStr);
}

FString URPGEventBusSubsystem::GetDurationUntilDamaged() const
{
    if (!IsSafeToCallFunction() || !GetDurationUntilDamagedFuncPtr)
    {
        return TEXT("until_damaged");
    }
    
    ANSICHAR* CStr = GetDurationUntilDamagedFuncPtr();
    return ConvertAndFreeString(CStr);
}

FString URPGEventBusSubsystem::GetDurationUntilSave() const
{
    if (!IsSafeToCallFunction() || !GetDurationUntilSaveFuncPtr)
    {
        return TEXT("until_save");
    }
    
    ANSICHAR* CStr = GetDurationUntilSaveFuncPtr();
    return ConvertAndFreeString(CStr);
}

// Toolkit Status
bool URPGEventBusSubsystem::IsToolkitLoaded() const
{
    return bFunctionsLoaded;
}

// Private Implementation
void URPGEventBusSubsystem::LoadDLLFunctions()
{
    // Use proper UE binary directory (following established pattern)
    FString BinariesDir = FPaths::Combine(FPaths::ProjectDir(), TEXT("Binaries"), FPlatformProcess::GetBinariesSubdirectory());
    FString LibraryPath = FPaths::Combine(BinariesDir, TEXT("rpg_toolkit.dll"));
    LibraryPath = FPaths::ConvertRelativePathToFull(LibraryPath);

    UE_LOG(LogTemp, Warning, TEXT("RPGEventBusSubsystem: Attempting to load DLL from: %s"), *LibraryPath);

    // Check if the DLL exists
    if (!FPaths::FileExists(LibraryPath))
    {
        UE_LOG(LogTemp, Error, TEXT("RPGEventBusSubsystem: DLL not found at path: %s"), *LibraryPath);
        return;
    }

    // Load the DLL
    ToolkitDLLHandle = FPlatformProcess::GetDllHandle(*LibraryPath);
    if (!ToolkitDLLHandle)
    {
        UE_LOG(LogTemp, Error, TEXT("RPGEventBusSubsystem: Failed to load DLL"));
        return;
    }

    UE_LOG(LogTemp, Warning, TEXT("RPGEventBusSubsystem: Successfully loaded DLL"));
    
    // Load EventBus management functions
    CreateEventBusFuncPtr = (CreateEventBusFunc)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("CreateEventBus"));
    PublishEventFuncPtr = (PublishEventFunc)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("PublishEvent"));
    SubscribeEventFuncPtr = (SubscribeEventFunc)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("SubscribeEvent"));
    UnsubscribeEventFuncPtr = (UnsubscribeEventFunc)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("UnsubscribeEvent"));
    
    // Load Event type constant functions
    GetEventBeforeAttackRollFuncPtr = (GetEventBeforeAttackRollFunc)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("GetEventBeforeAttackRoll"));
    GetEventOnAttackRollFuncPtr = (GetEventOnAttackRollFunc)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("GetEventOnAttackRoll"));
    GetEventAfterAttackRollFuncPtr = (GetEventAfterAttackRollFunc)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("GetEventAfterAttackRoll"));
    GetEventBeforeDamageRollFuncPtr = (GetEventBeforeDamageRollFunc)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("GetEventBeforeDamageRoll"));
    GetEventOnTakeDamageFuncPtr = (GetEventOnTakeDamageFunc)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("GetEventOnTakeDamage"));
    GetEventCalculateDamageFuncPtr = (GetEventCalculateDamageFunc)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("GetEventCalculateDamage"));
    GetEventAfterDamageFuncPtr = (GetEventAfterDamageFunc)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("GetEventAfterDamage"));
    GetEventEntityPlacedFuncPtr = (GetEventEntityPlacedFunc)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("GetEventEntityPlaced"));
    GetEventEntityMovedFuncPtr = (GetEventEntityMovedFunc)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("GetEventEntityMoved"));
    GetEventRoomCreatedFuncPtr = (GetEventRoomCreatedFunc)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("GetEventRoomCreated"));
    GetEventTurnStartFuncPtr = (GetEventTurnStartFunc)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("GetEventTurnStart"));
    GetEventTurnEndFuncPtr = (GetEventTurnEndFunc)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("GetEventTurnEnd"));
    GetEventRoundStartFuncPtr = (GetEventRoundStartFunc)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("GetEventRoundStart"));
    GetEventRoundEndFuncPtr = (GetEventRoundEndFunc)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("GetEventRoundEnd"));
    GetEventStatusAppliedFuncPtr = (GetEventStatusAppliedFunc)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("GetEventStatusApplied"));
    GetEventStatusRemovedFuncPtr = (GetEventStatusRemovedFunc)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("GetEventStatusRemoved"));
    GetEventStatusCheckFuncPtr = (GetEventStatusCheckFunc)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("GetEventStatusCheck"));
    
    // Load Context key constant functions
    GetContextKeyAttackerFuncPtr = (GetContextKeyAttackerFunc)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("GetContextKeyAttacker"));
    GetContextKeyTargetFuncPtr = (GetContextKeyTargetFunc)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("GetContextKeyTarget"));
    GetContextKeyWeaponFuncPtr = (GetContextKeyWeaponFunc)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("GetContextKeyWeapon"));
    GetContextKeyDamageTypeFuncPtr = (GetContextKeyDamageTypeFunc)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("GetContextKeyDamageType"));
    GetContextKeyAdvantageFuncPtr = (GetContextKeyAdvantageFunc)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("GetContextKeyAdvantage"));
    GetContextKeyRollFuncPtr = (GetContextKeyRollFunc)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("GetContextKeyRoll"));
    GetContextKeyOldPositionFuncPtr = (GetContextKeyOldPositionFunc)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("GetContextKeyOldPosition"));
    GetContextKeyNewPositionFuncPtr = (GetContextKeyNewPositionFunc)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("GetContextKeyNewPosition"));
    GetContextKeyRoomIDFuncPtr = (GetContextKeyRoomIDFunc)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("GetContextKeyRoomID"));
    
    // Load Modifier creation functions
    CreateModifierFuncPtr = (CreateModifierFunc)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("CreateModifier"));
    CreateIntModifierFuncPtr = (CreateIntModifierFunc)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("CreateIntModifier"));
    CreateDiceModifierFuncPtr = (CreateDiceModifierFunc)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("CreateDiceModifier"));
    
    // Load Duration constant functions
    GetDurationPermanentFuncPtr = (GetDurationPermanentFunc)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("GetDurationPermanent"));
    GetDurationRoundsFuncPtr = (GetDurationRoundsFunc)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("GetDurationRounds"));
    GetDurationMinutesFuncPtr = (GetDurationMinutesFunc)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("GetDurationMinutes"));
    GetDurationHoursFuncPtr = (GetDurationHoursFunc)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("GetDurationHours"));
    GetDurationEncounterFuncPtr = (GetDurationEncounterFunc)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("GetDurationEncounter"));
    GetDurationConcentrationFuncPtr = (GetDurationConcentrationFunc)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("GetDurationConcentration"));
    GetDurationShortRestFuncPtr = (GetDurationShortRestFunc)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("GetDurationShortRest"));
    GetDurationLongRestFuncPtr = (GetDurationLongRestFunc)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("GetDurationLongRest"));
    GetDurationUntilDamagedFuncPtr = (GetDurationUntilDamagedFunc)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("GetDurationUntilDamaged"));
    GetDurationUntilSaveFuncPtr = (GetDurationUntilSaveFunc)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("GetDurationUntilSave"));
    
    // Load memory management function
    FreeEventStringFuncPtr = (FreeEventStringFunc)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("FreeEventString"));
    
    // Check if critical functions were loaded
    bool bCriticalFunctionsLoaded = (CreateEventBusFuncPtr != nullptr) && 
                                   (PublishEventFuncPtr != nullptr) && 
                                   (FreeEventStringFuncPtr != nullptr);
    
    if (bCriticalFunctionsLoaded)
    {
        bFunctionsLoaded = true;
        UE_LOG(LogTemp, Warning, TEXT("RPGEventBusSubsystem: All critical event functions loaded successfully"));
        
        // Log status of all functions
        UE_LOG(LogTemp, Log, TEXT("=== Event Function Loading Status ==="));
        UE_LOG(LogTemp, Log, TEXT("EventBus Functions:"));
        UE_LOG(LogTemp, Log, TEXT("  CreateEventBus: %s"), CreateEventBusFuncPtr ? TEXT("OK") : TEXT("FAILED"));
        UE_LOG(LogTemp, Log, TEXT("  PublishEvent: %s"), PublishEventFuncPtr ? TEXT("OK") : TEXT("FAILED"));
        UE_LOG(LogTemp, Log, TEXT("  SubscribeEvent: %s"), SubscribeEventFuncPtr ? TEXT("OK") : TEXT("FAILED"));
        UE_LOG(LogTemp, Log, TEXT("  UnsubscribeEvent: %s"), UnsubscribeEventFuncPtr ? TEXT("OK") : TEXT("FAILED"));
        UE_LOG(LogTemp, Log, TEXT("================================"));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("RPGEventBusSubsystem: Failed to load critical event functions"));
    }
}

FString URPGEventBusSubsystem::ConvertAndFreeString(ANSICHAR* CStr) const
{
    if (!CStr)
    {
        return FString();
    }
    
    FString Result = FString(ANSI_TO_TCHAR(CStr));
    
    // Free the C string memory
    if (FreeEventStringFuncPtr)
    {
        FreeEventStringFuncPtr(CStr);
    }
    
    return Result;
}

bool URPGEventBusSubsystem::IsSafeToCallFunction() const
{
    // Following established pattern for shutdown safety
    return bFunctionsLoaded && ToolkitDLLHandle != nullptr;
}