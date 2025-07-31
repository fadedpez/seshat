#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UObject/ScriptInterface.h"
#include "RPGCore/Entity/RPGEntity.h"
#include "RPGCore/Events/RPGEventTypes.h"
#include "RPGCore/Events/RPGEventContext.h"
#include "RPGDiceSubsystem.generated.h"

/**
 * Blueprint-friendly dice roll result with automatic memory management
 */
USTRUCT(BlueprintType)
struct SESHAT_API FRollResult
{
    GENERATED_BODY()

    /** The numeric result of the dice roll */
    UPROPERTY(BlueprintReadOnly, Category = "Roll Result")
    int32 Value = -1;

    /** Human-readable description (e.g., "+d20[15]=15") */
    UPROPERTY(BlueprintReadOnly, Category = "Roll Result")
    FString Description;

    /** Whether this roll had an error */
    UPROPERTY(BlueprintReadOnly, Category = "Roll Result")
    bool HasError = false;

    /** Error message if HasError is true */
    UPROPERTY(BlueprintReadOnly, Category = "Roll Result")
    FString ErrorMessage;

    /** Default constructor */
    FRollResult()
        : Value(-1), HasError(false)
    {
    }

    /** Constructor for successful roll */
    FRollResult(int32 InValue, const FString& InDescription)
        : Value(InValue), Description(InDescription), HasError(false)
    {
    }

    /** Constructor for failed roll */
    FRollResult(const FString& InErrorMessage)
        : Value(-1), HasError(true), ErrorMessage(InErrorMessage)
    {
    }
};

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

    // Legacy Roll Struct Functions (deprecated - use FRollResult functions)
    // These remain for backward compatibility but should not be used in new code

    // Automatic Cleanup Helper Functions (from dice/modifier.go)
    UFUNCTION(BlueprintCallable, Category = "RPG Dice")
    FRollResult D4(int32 Count = 1);

    UFUNCTION(BlueprintCallable, Category = "RPG Dice")
    FRollResult D6(int32 Count = 1);

    UFUNCTION(BlueprintCallable, Category = "RPG Dice")
    FRollResult D8(int32 Count = 1);

    UFUNCTION(BlueprintCallable, Category = "RPG Dice")
    FRollResult D10(int32 Count = 1);

    UFUNCTION(BlueprintCallable, Category = "RPG Dice")
    FRollResult D12(int32 Count = 1);

    UFUNCTION(BlueprintCallable, Category = "RPG Dice")
    FRollResult D20(int32 Count = 1);

    UFUNCTION(BlueprintCallable, Category = "RPG Dice")
    FRollResult D100(int32 Count = 1);

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
    typedef int32 (*RollGetValueFunc)(uintptr_t);
    typedef ANSICHAR* (*RollGetDescriptionFunc)(uintptr_t);
    typedef int32 (*RollHasErrorFunc)(uintptr_t);
    typedef ANSICHAR* (*RollGetErrorFunc)(uintptr_t);
    
    // Automatic cleanup helper functions
    typedef int32 (*D4CompleteFunc)(int32, int32*, ANSICHAR**, ANSICHAR**);
    typedef int32 (*D6CompleteFunc)(int32, int32*, ANSICHAR**, ANSICHAR**);
    typedef int32 (*D8CompleteFunc)(int32, int32*, ANSICHAR**, ANSICHAR**);
    typedef int32 (*D10CompleteFunc)(int32, int32*, ANSICHAR**, ANSICHAR**);
    typedef int32 (*D12CompleteFunc)(int32, int32*, ANSICHAR**, ANSICHAR**);
    typedef int32 (*D20CompleteFunc)(int32, int32*, ANSICHAR**, ANSICHAR**);
    typedef int32 (*D100CompleteFunc)(int32, int32*, ANSICHAR**, ANSICHAR**);
    
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
    
    D4CompleteFunc D4CompleteFuncPtr;
    D6CompleteFunc D6CompleteFuncPtr;
    D8CompleteFunc D8CompleteFuncPtr;
    D10CompleteFunc D10CompleteFuncPtr;
    D12CompleteFunc D12CompleteFuncPtr;
    D20CompleteFunc D20CompleteFuncPtr;
    D100CompleteFunc D100CompleteFuncPtr;
    
    CreateDiceRollerFunc CreateDiceRollerFuncPtr;
    RollDieFunc RollDieFuncPtr;
    FreeStringFunc FreeStringFuncPtr;

    /** Whether the DLL functions were successfully loaded */
    bool bFunctionsLoaded;

    /** Handle to the loaded DLL */
    void* ToolkitDLLHandle;

    /** Dice roller instance from the toolkit */
    void* DiceRollerPtr;
    

    /** Load the DLL and function pointers */
    void LoadDLLFunctions();
    
    
    /** Helper to convert C string and free memory */
    FString ConvertAndFreeString(ANSICHAR* CStr) const;
    
    /** Shutdown safety check (following existing pattern) */
    bool IsSafeToCallFunction() const;
    
};