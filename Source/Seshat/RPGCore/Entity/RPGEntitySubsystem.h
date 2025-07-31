#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "HAL/PlatformProcess.h"
#include "RPGEntitySubsystem.generated.h"

/**
 * Blueprint-friendly entity error result with automatic memory management
 */
USTRUCT(BlueprintType)
struct SESHAT_API FEntityErrorResult
{
    GENERATED_BODY()

    /** The error operation that failed */
    UPROPERTY(BlueprintReadOnly, Category = "Entity Error")
    FString Operation;

    /** The type of entity involved */
    UPROPERTY(BlueprintReadOnly, Category = "Entity Error")
    FString EntityType;

    /** The ID of the entity involved */
    UPROPERTY(BlueprintReadOnly, Category = "Entity Error")
    FString EntityID;

    /** The error message */
    UPROPERTY(BlueprintReadOnly, Category = "Entity Error")
    FString Message;

    /** Whether this represents a valid error */
    UPROPERTY(BlueprintReadOnly, Category = "Entity Error")
    bool IsValid = false;

    /** Default constructor */
    FEntityErrorResult()
        : IsValid(false)
    {
    }

    /** Constructor for valid error */
    FEntityErrorResult(const FString& InOp, const FString& InType, const FString& InID, const FString& InMessage)
        : Operation(InOp), EntityType(InType), EntityID(InID), Message(InMessage), IsValid(true)
    {
    }

    /** Constructor for invalid error */
    FEntityErrorResult(bool bInvalid)
        : IsValid(false)
    {
    }
};

/**
 * Core toolkit integration subsystem for RPG entities
 * Exposes the actual rpg-toolkit core package functions
 * NO custom entity management - just raw toolkit exposure
 */
UCLASS()
class SESHAT_API URPGEntitySubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    // Begin USubsystem
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;
    // End USubsystem

    // Core Error Constants (from core/errors.go)
    UFUNCTION(BlueprintCallable, Category = "RPG Core")
    FString GetEntityNotFoundError() const;
    
    UFUNCTION(BlueprintCallable, Category = "RPG Core")
    FString GetInvalidEntityError() const;
    
    UFUNCTION(BlueprintCallable, Category = "RPG Core")
    FString GetDuplicateEntityError() const;
    
    UFUNCTION(BlueprintCallable, Category = "RPG Core")
    FString GetNilEntityError() const;
    
    UFUNCTION(BlueprintCallable, Category = "RPG Core")
    FString GetEmptyIDError() const;
    
    UFUNCTION(BlueprintCallable, Category = "RPG Core")
    FString GetInvalidTypeError() const;

    // Entity Validation Functions (from core/entity.go interface)
    UFUNCTION(BlueprintCallable, Category = "RPG Core")
    bool ValidateEntityID(const FString& ID) const;
    
    UFUNCTION(BlueprintCallable, Category = "RPG Core")
    bool ValidateEntityType(const FString& Type) const;

    // Automatic Cleanup Entity Error Functions
    UFUNCTION(BlueprintCallable, Category = "RPG Core")
    FEntityErrorResult CreateEntityError(const FString& Operation, const FString& EntityType, const FString& EntityID, const FString& Message);

    // Toolkit Status
    UFUNCTION(BlueprintCallable, Category = "RPG Core")
    bool IsToolkitLoaded() const;

private:
    /** Function pointers to actual toolkit DLL functions */
    typedef ANSICHAR* (*GetEntityNotFoundErrorFunc)();
    typedef ANSICHAR* (*GetInvalidEntityErrorFunc)();
    typedef ANSICHAR* (*GetDuplicateEntityErrorFunc)();
    typedef ANSICHAR* (*GetNilEntityErrorFunc)();
    typedef ANSICHAR* (*GetEmptyIDErrorFunc)();
    typedef ANSICHAR* (*GetInvalidTypeErrorFunc)();
    typedef int32 (*ValidateEntityIDFunc)(const ANSICHAR*);
    typedef int32 (*ValidateEntityTypeFunc)(const ANSICHAR*);
    typedef void (*FreeStringFunc)(ANSICHAR*);
    
    // Automatic cleanup function
    typedef int32 (*CreateEntityErrorCompleteFunc)(const ANSICHAR*, const ANSICHAR*, const ANSICHAR*, const ANSICHAR*, ANSICHAR**, ANSICHAR**, ANSICHAR**, ANSICHAR**);
    
    GetEntityNotFoundErrorFunc GetEntityNotFoundErrorFuncPtr;
    GetInvalidEntityErrorFunc GetInvalidEntityErrorFuncPtr;
    GetDuplicateEntityErrorFunc GetDuplicateEntityErrorFuncPtr;
    GetNilEntityErrorFunc GetNilEntityErrorFuncPtr;
    GetEmptyIDErrorFunc GetEmptyIDErrorFuncPtr;
    GetInvalidTypeErrorFunc GetInvalidTypeErrorFuncPtr;
    ValidateEntityIDFunc ValidateEntityIDFuncPtr;
    ValidateEntityTypeFunc ValidateEntityTypeFuncPtr;
    FreeStringFunc FreeStringFuncPtr;
    CreateEntityErrorCompleteFunc CreateEntityErrorCompleteFuncPtr;
    
    /** Whether the DLL functions were successfully loaded */
    bool bFunctionsLoaded;
    
    /** Handle to the loaded DLL */
    void* ToolkitDLLHandle;
    
    /** Load the DLL and function pointers */
    void LoadDLLFunctions();
    
    /** Helper to convert C string and free memory */
    FString ConvertAndFreeString(ANSICHAR* CStr) const;
    
    /** Shutdown safety check (following RPGDiceSubsystem pattern) */
    bool IsSafeToCallFunction() const;
};