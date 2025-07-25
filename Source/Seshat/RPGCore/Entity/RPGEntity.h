#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "../RPGCoreTypes.h"
#include "RPGEntity.generated.h"

/**
 * Universal entity interface matching rpg-toolkit's core.Entity
 * Pure identity contract - only ID and Type
 */
UINTERFACE(MinimalAPI, Blueprintable)
class URPGEntityInterface : public UInterface
{
    GENERATED_BODY()
};

class SESHAT_API IRPGEntityInterface
{
    GENERATED_BODY()

public:
    // C++ interface for direct access
    virtual FString GetID() const = 0;
    virtual FString GetType() const = 0;
};

/**
 * Base implementation of RPG Entity for UE Actors
 * Provides foundation for all game entities that need spatial representation
 */
UCLASS(Abstract, BlueprintType, Blueprintable)
class SESHAT_API ARPGEntity : public AActor, public IRPGEntityInterface
{
    GENERATED_BODY()

public:
    ARPGEntity();

    // IRPGEntityInterface implementation
    virtual FString GetID() const override;
    virtual FString GetType() const override;

    // Blueprint-accessible versions
    UFUNCTION(BlueprintCallable, Category = "RPG Entity")
    FString GetEntityID() const { return GetID(); }

    UFUNCTION(BlueprintCallable, Category = "RPG Entity")
    FString GetEntityType() const { return GetType(); }

    // Entity lifecycle
    UFUNCTION(BlueprintCallable, Category = "RPG Entity")
    bool IsValidEntity() const;

    UFUNCTION(BlueprintCallable, Category = "RPG Entity")
    void RegisterWithSubsystem();

    UFUNCTION(BlueprintCallable, Category = "RPG Entity")
    void UnregisterFromSubsystem();

protected:
    // Called when entity is first created to set up ID/Type
    virtual void InitializeEntity();

    // Override in subclasses to provide specific entity types
    virtual FString GetDefaultEntityType() const { return TEXT("entity"); }

    // Override in subclasses to provide custom ID generation
    virtual FString GenerateEntityID() const;

    // UE Actor lifecycle integration
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RPG Entity", 
              meta = (ToolTip = "Unique identifier for this entity"))
    FString EntityID;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RPG Entity",
              meta = (ToolTip = "Entity type categorization"))
    FString EntityType;

private:
    bool bEntityInitialized = false;
    bool bRegisteredWithSubsystem = false;
};

/**
 * Non-Actor entity implementation for objects that don't need spatial representation
 * Examples: items in inventory, abstract conditions, temporary effects
 */
UCLASS(BlueprintType, Blueprintable)
class SESHAT_API URPGEntityObject : public UObject, public IRPGEntityInterface
{
    GENERATED_BODY()

public:
    URPGEntityObject();

    // IRPGEntityInterface implementation
    virtual FString GetID() const override;
    virtual FString GetType() const override;

    // Blueprint-accessible versions
    UFUNCTION(BlueprintCallable, Category = "RPG Entity")
    FString GetEntityID() const { return GetID(); }

    UFUNCTION(BlueprintCallable, Category = "RPG Entity")
    FString GetEntityType() const { return GetType(); }

    // Factory method for creating entities
    UFUNCTION(BlueprintCallable, Category = "RPG Entity", CallInEditor = true)
    static URPGEntityObject* CreateEntity(UObject* Outer, const FString& EntityType, 
                                         const FString& EntityID = TEXT(""));

protected:
    virtual void InitializeEntity(const FString& Type, const FString& ID = TEXT(""));

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RPG Entity")
    FString EntityID;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RPG Entity")
    FString EntityType;
};