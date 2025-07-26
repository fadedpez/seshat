#pragma once

#include "CoreMinimal.h"
#include "Engine/Engine.h"
#include "RPGCoreTypes.generated.h"

/**
 * Entity error types matching rpg-toolkit's core error system
 */
UENUM(BlueprintType)
enum class ERPGEntityError : uint8
{
    None            UMETA(DisplayName = "No Error"),
    NotFound        UMETA(DisplayName = "Entity Not Found"),
    Invalid         UMETA(DisplayName = "Invalid Entity"),
    Duplicate       UMETA(DisplayName = "Duplicate Entity"),
    NilEntity       UMETA(DisplayName = "Nil Entity"),
    EmptyID         UMETA(DisplayName = "Empty ID"),
    InvalidType     UMETA(DisplayName = "Invalid Type"),
    RegistrationFailed UMETA(DisplayName = "Registration Failed"),
    AlreadyRegistered UMETA(DisplayName = "Already Registered")
};

/**
 * Structured entity error information
 */
USTRUCT(BlueprintType)
struct SESHAT_API FRPGEntityError
{
    GENERATED_BODY()

    FRPGEntityError()
        : ErrorType(ERPGEntityError::None)
    {}

    FRPGEntityError(ERPGEntityError InErrorType, const FString& InEntityID = TEXT(""), 
                   const FString& InEntityType = TEXT(""), const FString& InOperation = TEXT(""),
                   const FString& InMessage = TEXT(""))
        : EntityID(InEntityID)
        , EntityType(InEntityType)
        , Operation(InOperation)
        , ErrorType(InErrorType)
        , ErrorMessage(InMessage)
    {}

    UPROPERTY(BlueprintReadOnly, Category = "RPG Entity Error")
    FString EntityID;

    UPROPERTY(BlueprintReadOnly, Category = "RPG Entity Error")
    FString EntityType;

    UPROPERTY(BlueprintReadOnly, Category = "RPG Entity Error")
    FString Operation;

    UPROPERTY(BlueprintReadOnly, Category = "RPG Entity Error")
    ERPGEntityError ErrorType;

    UPROPERTY(BlueprintReadOnly, Category = "RPG Entity Error")
    FString ErrorMessage;

    // Utility methods
    bool IsValid() const { return ErrorType == ERPGEntityError::None; }

    FString GetFormattedMessage() const;
};

/**
 * Entity validation result
 */
USTRUCT(BlueprintType)
struct SESHAT_API FRPGEntityValidationResult
{
    GENERATED_BODY()

    FRPGEntityValidationResult()
        : bIsValid(false)
    {}

    FRPGEntityValidationResult(bool bValid, const FRPGEntityError& Error = FRPGEntityError())
        : bIsValid(bValid)
        , Error(Error)
    {}

    UPROPERTY(BlueprintReadOnly, Category = "RPG Entity Validation")
    bool bIsValid;

    UPROPERTY(BlueprintReadOnly, Category = "RPG Entity Validation")
    FRPGEntityError Error;
};

// Common entity types as constants
namespace RPGEntityTypes
{
    const FString Character = TEXT("character");
    const FString Item = TEXT("item");
    const FString Location = TEXT("location");
    const FString Room = TEXT("room");
    const FString Condition = TEXT("condition");
    const FString Effect = TEXT("effect");
    const FString Spell = TEXT("spell");
    const FString Weapon = TEXT("weapon");
    const FString Armor = TEXT("armor");
}