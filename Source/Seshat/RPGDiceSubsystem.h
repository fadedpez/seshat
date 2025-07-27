#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UObject/ScriptInterface.h"
#include "RPGCore/Entity/RPGEntity.h"
#include "RPGCore/Events/RPGEventTypes.h"
#include "RPGCore/Events/RPGEventContext.h"
#include "RPGDiceSubsystem.generated.h"

// Forward declarations
class URPGEventBusSubsystem;

/**
 * Subsystem that provides dice rolling functionality using the rpg-toolkit
 */
UCLASS()
class SESHAT_API URPGDiceSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    // Begin USubsystem
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;
    // End USubsystem

    /**
     * Roll a single die with the specified number of sides
     * @param Sides Number of sides on the die (must be > 0)
     * @return The roll result (1 to Sides), or -1 on error
     */
    UFUNCTION(BlueprintCallable, Category = "RPG Dice")
    int32 Roll(int32 Sides);

    /**
     * Roll a die with advantage (roll twice, take higher)
     * @param Sides Number of sides on the die
     * @return The higher of two rolls
     */
    UFUNCTION(BlueprintCallable, Category = "RPG Dice")
    int32 RollWithAdvantage(int32 Sides);

    /**
     * Roll a die with disadvantage (roll twice, take lower)
     * @param Sides Number of sides on the die
     * @return The lower of two rolls
     */
    UFUNCTION(BlueprintCallable, Category = "RPG Dice")
    int32 RollWithDisadvantage(int32 Sides);

    /**
     * Roll multiple dice and return individual results
     * @param Count Number of dice to roll
     * @param Sides Number of sides on each die
     * @return Array of individual roll results
     */
    UFUNCTION(BlueprintCallable, Category = "RPG Dice")
    TArray<int32> RollMultiple(int32 Count, int32 Sides);

    /**
     * Check if the dice toolkit is properly loaded and functional
     */
    UFUNCTION(BlueprintCallable, Category = "RPG Dice")
    bool IsToolkitLoaded() const;

    // Entity-aware dice rolling methods (prepares for event system integration)
    
    /**
     * Roll a die for a specific entity (future: will include entity modifiers)
     * @param Sides Number of sides on the die
     * @param Entity The entity performing the roll
     * @return Roll result
     */
    UFUNCTION(BlueprintCallable, Category = "RPG Dice")
    int32 RollForEntity(int32 Sides, TScriptInterface<IRPGEntityInterface> Entity);

    /**
     * Roll with advantage for a specific entity
     * @param Sides Number of sides on the die
     * @param Entity The entity performing the roll
     * @return The higher of two rolls
     */
    UFUNCTION(BlueprintCallable, Category = "RPG Dice")
    int32 RollWithAdvantageForEntity(int32 Sides, TScriptInterface<IRPGEntityInterface> Entity);

    // Event integration methods
    
    /**
     * Enable or disable event publishing for dice rolls
     * @param bEnabled Whether to publish events for dice rolls
     */
    UFUNCTION(BlueprintCallable, Category = "RPG Dice")
    void SetEventPublishingEnabled(bool bEnabled) { bPublishEvents = bEnabled; }

    /**
     * Check if event publishing is enabled
     */
    UFUNCTION(BlueprintCallable, Category = "RPG Dice")
    bool IsEventPublishingEnabled() const { return bPublishEvents; }

private:
    /** Function pointers to actual toolkit DLL functions */
    typedef void* (*CreateDiceRollerFunc)();
    typedef int32 (*RollDieFunc)(void*, int32);
    typedef ANSICHAR* (*GetVersionFunc)();
    typedef int32 (*InitializeFunc)();

    CreateDiceRollerFunc CreateDiceRollerFuncPtr;
    RollDieFunc RollDieFuncPtr;
    GetVersionFunc GetVersionFuncPtr;
    InitializeFunc InitializeFuncPtr;

    /** Whether the DLL functions were successfully loaded */
    bool bFunctionsLoaded;

    /** Handle to the loaded DLL */
    void* ToolkitDLLHandle;

    /** Dice roller instance from the toolkit */
    void* DiceRollerPtr;

    /** Whether to publish events for dice rolls */
    bool bPublishEvents = true;

    /** Load the DLL and function pointers */
    void LoadDLLFunctions();

    /** Event publishing helpers */
    void PublishDiceRollEvent(int32 Sides, int32 Result, TScriptInterface<IRPGEntityInterface> Entity = nullptr);
    URPGEventBusSubsystem* GetEventBusSubsystem() const;
};