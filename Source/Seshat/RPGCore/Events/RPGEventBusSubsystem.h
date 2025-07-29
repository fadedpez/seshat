#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "HAL/PlatformProcess.h"
#include "RPGEventBusSubsystem.generated.h"

/**
 * Core toolkit integration subsystem for RPG events
 * Exposes the actual rpg-toolkit events package functions
 * NO custom event management - just raw toolkit exposure
 * Swiss Army Knife Standard: 1:1 mapping of toolkit API
 */
UCLASS()
class SESHAT_API URPGEventBusSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    // Begin USubsystem
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;
    // End USubsystem

    // EventBus Management Functions (from events/eventbus.go)
    UFUNCTION(BlueprintCallable, Category = "RPG Events")
    FString CreateEventBus();
    
    UFUNCTION(BlueprintCallable, Category = "RPG Events")
    bool PublishEvent(const FString& EventType, const FString& SourceID, const FString& TargetID, const FString& ContextData);
    
    UFUNCTION(BlueprintCallable, Category = "RPG Events")
    FString SubscribeEvent(const FString& EventType, int32 Priority);
    
    UFUNCTION(BlueprintCallable, Category = "RPG Events")
    bool UnsubscribeEvent(const FString& SubscriptionID);

    // Event Type Constants (from events/types.go)
    UFUNCTION(BlueprintCallable, Category = "RPG Events")
    FString GetEventBeforeAttackRoll() const;
    
    UFUNCTION(BlueprintCallable, Category = "RPG Events")
    FString GetEventOnAttackRoll() const;
    
    UFUNCTION(BlueprintCallable, Category = "RPG Events")
    FString GetEventAfterAttackRoll() const;
    
    UFUNCTION(BlueprintCallable, Category = "RPG Events")
    FString GetEventBeforeDamageRoll() const;
    
    UFUNCTION(BlueprintCallable, Category = "RPG Events")
    FString GetEventOnTakeDamage() const;
    
    UFUNCTION(BlueprintCallable, Category = "RPG Events")
    FString GetEventCalculateDamage() const;
    
    UFUNCTION(BlueprintCallable, Category = "RPG Events")
    FString GetEventAfterDamage() const;
    
    UFUNCTION(BlueprintCallable, Category = "RPG Events")
    FString GetEventEntityPlaced() const;
    
    UFUNCTION(BlueprintCallable, Category = "RPG Events")
    FString GetEventEntityMoved() const;
    
    UFUNCTION(BlueprintCallable, Category = "RPG Events")
    FString GetEventRoomCreated() const;
    
    UFUNCTION(BlueprintCallable, Category = "RPG Events")
    FString GetEventTurnStart() const;
    
    UFUNCTION(BlueprintCallable, Category = "RPG Events")
    FString GetEventTurnEnd() const;
    
    UFUNCTION(BlueprintCallable, Category = "RPG Events")
    FString GetEventRoundStart() const;
    
    UFUNCTION(BlueprintCallable, Category = "RPG Events")
    FString GetEventRoundEnd() const;
    
    UFUNCTION(BlueprintCallable, Category = "RPG Events")
    FString GetEventStatusApplied() const;
    
    UFUNCTION(BlueprintCallable, Category = "RPG Events")
    FString GetEventStatusRemoved() const;
    
    UFUNCTION(BlueprintCallable, Category = "RPG Events")
    FString GetEventStatusCheck() const;

    // Context Key Constants (from events/context.go)
    UFUNCTION(BlueprintCallable, Category = "RPG Events")
    FString GetContextKeyAttacker() const;
    
    UFUNCTION(BlueprintCallable, Category = "RPG Events")
    FString GetContextKeyTarget() const;
    
    UFUNCTION(BlueprintCallable, Category = "RPG Events")
    FString GetContextKeyWeapon() const;
    
    UFUNCTION(BlueprintCallable, Category = "RPG Events")
    FString GetContextKeyDamageType() const;
    
    UFUNCTION(BlueprintCallable, Category = "RPG Events")
    FString GetContextKeyAdvantage() const;
    
    UFUNCTION(BlueprintCallable, Category = "RPG Events")
    FString GetContextKeyRoll() const;
    
    UFUNCTION(BlueprintCallable, Category = "RPG Events")
    FString GetContextKeyOldPosition() const;
    
    UFUNCTION(BlueprintCallable, Category = "RPG Events")
    FString GetContextKeyNewPosition() const;
    
    UFUNCTION(BlueprintCallable, Category = "RPG Events")
    FString GetContextKeyRoomID() const;

    // Modifier Creation Functions (from events/modifier.go)
    UFUNCTION(BlueprintCallable, Category = "RPG Events")
    FString CreateModifier(const FString& Source, const FString& ModifierType, int32 Value, int32 Priority);
    
    UFUNCTION(BlueprintCallable, Category = "RPG Events")
    FString CreateIntModifier(const FString& Source, const FString& ModifierType, int32 Value);
    
    UFUNCTION(BlueprintCallable, Category = "RPG Events")
    FString CreateDiceModifier(const FString& Source, const FString& ModifierType, const FString& DiceExpression);

    // Duration Constants (from events/duration.go)
    UFUNCTION(BlueprintCallable, Category = "RPG Events")
    FString GetDurationPermanent() const;
    
    UFUNCTION(BlueprintCallable, Category = "RPG Events")
    FString GetDurationRounds() const;
    
    UFUNCTION(BlueprintCallable, Category = "RPG Events")
    FString GetDurationMinutes() const;
    
    UFUNCTION(BlueprintCallable, Category = "RPG Events")
    FString GetDurationHours() const;
    
    UFUNCTION(BlueprintCallable, Category = "RPG Events")
    FString GetDurationEncounter() const;
    
    UFUNCTION(BlueprintCallable, Category = "RPG Events")
    FString GetDurationConcentration() const;
    
    UFUNCTION(BlueprintCallable, Category = "RPG Events")
    FString GetDurationShortRest() const;
    
    UFUNCTION(BlueprintCallable, Category = "RPG Events")
    FString GetDurationLongRest() const;
    
    UFUNCTION(BlueprintCallable, Category = "RPG Events")
    FString GetDurationUntilDamaged() const;
    
    UFUNCTION(BlueprintCallable, Category = "RPG Events")
    FString GetDurationUntilSave() const;

    // Toolkit Status
    UFUNCTION(BlueprintCallable, Category = "RPG Events")
    bool IsToolkitLoaded() const;

private:
    /** Function pointers to actual toolkit DLL functions */
    typedef ANSICHAR* (*CreateEventBusFunc)();
    typedef int32 (*PublishEventFunc)(const ANSICHAR*, const ANSICHAR*, const ANSICHAR*, const ANSICHAR*);
    typedef ANSICHAR* (*SubscribeEventFunc)(const ANSICHAR*, int32);
    typedef int32 (*UnsubscribeEventFunc)(const ANSICHAR*);
    
    // Event type constant functions
    typedef ANSICHAR* (*GetEventBeforeAttackRollFunc)();
    typedef ANSICHAR* (*GetEventOnAttackRollFunc)();
    typedef ANSICHAR* (*GetEventAfterAttackRollFunc)();
    typedef ANSICHAR* (*GetEventBeforeDamageRollFunc)();
    typedef ANSICHAR* (*GetEventOnTakeDamageFunc)();
    typedef ANSICHAR* (*GetEventCalculateDamageFunc)();
    typedef ANSICHAR* (*GetEventAfterDamageFunc)();
    typedef ANSICHAR* (*GetEventEntityPlacedFunc)();
    typedef ANSICHAR* (*GetEventEntityMovedFunc)();
    typedef ANSICHAR* (*GetEventRoomCreatedFunc)();
    typedef ANSICHAR* (*GetEventTurnStartFunc)();
    typedef ANSICHAR* (*GetEventTurnEndFunc)();
    typedef ANSICHAR* (*GetEventRoundStartFunc)();
    typedef ANSICHAR* (*GetEventRoundEndFunc)();
    typedef ANSICHAR* (*GetEventStatusAppliedFunc)();
    typedef ANSICHAR* (*GetEventStatusRemovedFunc)();
    typedef ANSICHAR* (*GetEventStatusCheckFunc)();
    
    // Context key constant functions
    typedef ANSICHAR* (*GetContextKeyAttackerFunc)();
    typedef ANSICHAR* (*GetContextKeyTargetFunc)();
    typedef ANSICHAR* (*GetContextKeyWeaponFunc)();
    typedef ANSICHAR* (*GetContextKeyDamageTypeFunc)();
    typedef ANSICHAR* (*GetContextKeyAdvantageFunc)();
    typedef ANSICHAR* (*GetContextKeyRollFunc)();
    typedef ANSICHAR* (*GetContextKeyOldPositionFunc)();
    typedef ANSICHAR* (*GetContextKeyNewPositionFunc)();
    typedef ANSICHAR* (*GetContextKeyRoomIDFunc)();
    
    // Modifier creation functions
    typedef ANSICHAR* (*CreateModifierFunc)(const ANSICHAR*, const ANSICHAR*, int32, int32);
    typedef ANSICHAR* (*CreateIntModifierFunc)(const ANSICHAR*, const ANSICHAR*, int32);
    typedef ANSICHAR* (*CreateDiceModifierFunc)(const ANSICHAR*, const ANSICHAR*, const ANSICHAR*);
    
    // Duration constant functions
    typedef ANSICHAR* (*GetDurationPermanentFunc)();
    typedef ANSICHAR* (*GetDurationRoundsFunc)();
    typedef ANSICHAR* (*GetDurationMinutesFunc)();
    typedef ANSICHAR* (*GetDurationHoursFunc)();
    typedef ANSICHAR* (*GetDurationEncounterFunc)();
    typedef ANSICHAR* (*GetDurationConcentrationFunc)();
    typedef ANSICHAR* (*GetDurationShortRestFunc)();
    typedef ANSICHAR* (*GetDurationLongRestFunc)();
    typedef ANSICHAR* (*GetDurationUntilDamagedFunc)();
    typedef ANSICHAR* (*GetDurationUntilSaveFunc)();
    
    typedef void (*FreeEventStringFunc)(ANSICHAR*);
    
    // Function pointer instances
    CreateEventBusFunc CreateEventBusFuncPtr;
    PublishEventFunc PublishEventFuncPtr;
    SubscribeEventFunc SubscribeEventFuncPtr;
    UnsubscribeEventFunc UnsubscribeEventFuncPtr;
    
    GetEventBeforeAttackRollFunc GetEventBeforeAttackRollFuncPtr;
    GetEventOnAttackRollFunc GetEventOnAttackRollFuncPtr;
    GetEventAfterAttackRollFunc GetEventAfterAttackRollFuncPtr;
    GetEventBeforeDamageRollFunc GetEventBeforeDamageRollFuncPtr;
    GetEventOnTakeDamageFunc GetEventOnTakeDamageFuncPtr;
    GetEventCalculateDamageFunc GetEventCalculateDamageFuncPtr;
    GetEventAfterDamageFunc GetEventAfterDamageFuncPtr;
    GetEventEntityPlacedFunc GetEventEntityPlacedFuncPtr;
    GetEventEntityMovedFunc GetEventEntityMovedFuncPtr;
    GetEventRoomCreatedFunc GetEventRoomCreatedFuncPtr;
    GetEventTurnStartFunc GetEventTurnStartFuncPtr;
    GetEventTurnEndFunc GetEventTurnEndFuncPtr;
    GetEventRoundStartFunc GetEventRoundStartFuncPtr;
    GetEventRoundEndFunc GetEventRoundEndFuncPtr;
    GetEventStatusAppliedFunc GetEventStatusAppliedFuncPtr;
    GetEventStatusRemovedFunc GetEventStatusRemovedFuncPtr;
    GetEventStatusCheckFunc GetEventStatusCheckFuncPtr;
    
    GetContextKeyAttackerFunc GetContextKeyAttackerFuncPtr;
    GetContextKeyTargetFunc GetContextKeyTargetFuncPtr;
    GetContextKeyWeaponFunc GetContextKeyWeaponFuncPtr;
    GetContextKeyDamageTypeFunc GetContextKeyDamageTypeFuncPtr;
    GetContextKeyAdvantageFunc GetContextKeyAdvantageFuncPtr;
    GetContextKeyRollFunc GetContextKeyRollFuncPtr;
    GetContextKeyOldPositionFunc GetContextKeyOldPositionFuncPtr;
    GetContextKeyNewPositionFunc GetContextKeyNewPositionFuncPtr;
    GetContextKeyRoomIDFunc GetContextKeyRoomIDFuncPtr;
    
    CreateModifierFunc CreateModifierFuncPtr;
    CreateIntModifierFunc CreateIntModifierFuncPtr;
    CreateDiceModifierFunc CreateDiceModifierFuncPtr;
    
    GetDurationPermanentFunc GetDurationPermanentFuncPtr;
    GetDurationRoundsFunc GetDurationRoundsFuncPtr;
    GetDurationMinutesFunc GetDurationMinutesFuncPtr;
    GetDurationHoursFunc GetDurationHoursFuncPtr;
    GetDurationEncounterFunc GetDurationEncounterFuncPtr;
    GetDurationConcentrationFunc GetDurationConcentrationFuncPtr;
    GetDurationShortRestFunc GetDurationShortRestFuncPtr;
    GetDurationLongRestFunc GetDurationLongRestFuncPtr;
    GetDurationUntilDamagedFunc GetDurationUntilDamagedFuncPtr;
    GetDurationUntilSaveFunc GetDurationUntilSaveFuncPtr;
    
    FreeEventStringFunc FreeEventStringFuncPtr;
    
    /** Whether the DLL functions were successfully loaded */
    bool bFunctionsLoaded;
    
    /** Handle to the loaded DLL */
    void* ToolkitDLLHandle;
    
    /** Load the DLL and function pointers */
    void LoadDLLFunctions();
    
    /** Helper to convert C string and free memory */
    FString ConvertAndFreeString(ANSICHAR* CStr) const;
    
    /** Shutdown safety check (following established pattern) */
    bool IsSafeToCallFunction() const;
};