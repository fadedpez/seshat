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


    // Roller Interface Functions (from dice/roller.go)
    UFUNCTION(BlueprintCallable, Category = "RPG Dice")
    int32 RollerRoll(int32 Size);

    UFUNCTION(BlueprintCallable, Category = "RPG Dice")
    TArray<int32> RollerRollN(int32 Count, int32 Size);

    // Roll Struct Functions (from dice/modifier.go)  
    UFUNCTION(BlueprintCallable, Category = "RPG Dice")
    int32 CreateRoll(int32 Count, int32 Size);

    UFUNCTION(BlueprintCallable, Category = "RPG Dice")
    int32 RollGetValue(int32 RollHandle);

    UFUNCTION(BlueprintCallable, Category = "RPG Dice")
    FString RollGetDescription(int32 RollHandle);

    UFUNCTION(BlueprintCallable, Category = "RPG Dice")
    bool RollHasError(int32 RollHandle);

    UFUNCTION(BlueprintCallable, Category = "RPG Dice")
    FString RollGetError(int32 RollHandle);

    // Helper Functions (from dice/modifier.go)
    UFUNCTION(BlueprintCallable, Category = "RPG Dice")
    int32 D4(int32 Count);

    UFUNCTION(BlueprintCallable, Category = "RPG Dice")
    int32 D6(int32 Count);

    UFUNCTION(BlueprintCallable, Category = "RPG Dice")
    int32 D8(int32 Count);

    UFUNCTION(BlueprintCallable, Category = "RPG Dice")
    int32 D10(int32 Count);

    UFUNCTION(BlueprintCallable, Category = "RPG Dice")
    int32 D12(int32 Count);

    UFUNCTION(BlueprintCallable, Category = "RPG Dice")
    int32 D20(int32 Count);

    UFUNCTION(BlueprintCallable, Category = "RPG Dice")
    int32 D100(int32 Count);

    // Toolkit Status
    UFUNCTION(BlueprintCallable, Category = "RPG Dice")
    bool IsToolkitLoaded() const;

    // Legacy Functions (for backward compatibility) - implemented in .cpp as inline mapping

private:
    /** Function pointers to actual toolkit DLL functions */
    // Roller interface functions
    typedef void* (*CreateCryptoRollerFunc)();
    typedef int32 (*RollerRollFunc)(void*, int32);
    typedef int32 (*RollerRollNFunc)(void*, int32, int32, int32*);
    typedef void* (*GetDefaultRollerFunc)();
    typedef void (*SetDefaultRollerFunc)(void*);
    
    // Roll struct functions
    typedef void* (*CreateRollFunc)(int32, int32);
    typedef void* (*CreateRollWithRollerFunc)(int32, int32, void*);
    typedef int32 (*RollGetValueFunc)(void*);
    typedef ANSICHAR* (*RollGetDescriptionFunc)(void*);
    typedef int32 (*RollHasErrorFunc)(void*);
    typedef ANSICHAR* (*RollGetErrorFunc)(void*);
    
    // Helper functions
    typedef void* (*D4Func)(int32);
    typedef void* (*D6Func)(int32);
    typedef void* (*D8Func)(int32);
    typedef void* (*D10Func)(int32);
    typedef void* (*D12Func)(int32);
    typedef void* (*D20Func)(int32);
    typedef void* (*D100Func)(int32);
    
    // Legacy functions
    typedef void* (*CreateDiceRollerFunc)();
    typedef int32 (*RollDieFunc)(void*, int32);
    typedef void (*FreeStringFunc)(ANSICHAR*);
    
    // Function pointer instances
    CreateCryptoRollerFunc CreateCryptoRollerFuncPtr;
    RollerRollFunc RollerRollFuncPtr;
    RollerRollNFunc RollerRollNFuncPtr;
    GetDefaultRollerFunc GetDefaultRollerFuncPtr;
    SetDefaultRollerFunc SetDefaultRollerFuncPtr;
    
    CreateRollFunc CreateRollFuncPtr;
    CreateRollWithRollerFunc CreateRollWithRollerFuncPtr;
    RollGetValueFunc RollGetValueFuncPtr;
    RollGetDescriptionFunc RollGetDescriptionFuncPtr;
    RollHasErrorFunc RollHasErrorFuncPtr;
    RollGetErrorFunc RollGetErrorFuncPtr;
    
    D4Func D4FuncPtr;
    D6Func D6FuncPtr;
    D8Func D8FuncPtr;
    D10Func D10FuncPtr;
    D12Func D12FuncPtr;
    D20Func D20FuncPtr;
    D100Func D100FuncPtr;
    
    CreateDiceRollerFunc CreateDiceRollerFuncPtr;
    RollDieFunc RollDieFuncPtr;
    FreeStringFunc FreeStringFuncPtr;

    /** Whether the DLL functions were successfully loaded */
    bool bFunctionsLoaded;

    /** Handle to the loaded DLL */
    void* ToolkitDLLHandle;

    /** Dice roller instance from the toolkit */
    void* DiceRollerPtr;
    
    /** Roll handle management */
    TMap<int32, void*> RollHandles;
    int32 NextRollHandle = 1;

    /** Load the DLL and function pointers */
    void LoadDLLFunctions();
    
    /** Handle management helpers */
    int32 CreateRollHandle(void* RollPtr);
    void* GetRollPtr(int32 Handle);
    void ReleaseRollHandle(int32 Handle);
    
    /** Helper to convert C string and free memory */
    FString ConvertAndFreeString(ANSICHAR* CStr) const;
    
    /** Shutdown safety check (following existing pattern) */
    bool IsSafeToCallFunction() const;
    
    /** Memory management for Roll objects */
    void CleanupRollHandles();
};