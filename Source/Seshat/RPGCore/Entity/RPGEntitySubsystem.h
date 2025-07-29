#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "HAL/PlatformProcess.h"
#include "RPGEntitySubsystem.generated.h"

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
    
    GetEntityNotFoundErrorFunc GetEntityNotFoundErrorFuncPtr;
    GetInvalidEntityErrorFunc GetInvalidEntityErrorFuncPtr;
    GetDuplicateEntityErrorFunc GetDuplicateEntityErrorFuncPtr;
    GetNilEntityErrorFunc GetNilEntityErrorFuncPtr;
    GetEmptyIDErrorFunc GetEmptyIDErrorFuncPtr;
    GetInvalidTypeErrorFunc GetInvalidTypeErrorFuncPtr;
    ValidateEntityIDFunc ValidateEntityIDFuncPtr;
    ValidateEntityTypeFunc ValidateEntityTypeFuncPtr;
    FreeStringFunc FreeStringFuncPtr;
    
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