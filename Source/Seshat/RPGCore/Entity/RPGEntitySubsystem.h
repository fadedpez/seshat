#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UObject/ScriptInterface.h"
#include "../RPGCoreTypes.h"
#include "HAL/PlatformProcess.h"
#include "RPGEntitySubsystem.generated.h"

// Forward declarations
class IRPGEntityInterface;

/**
 * Delegate for entity lifecycle events
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEntityRegistered, const FString&, EntityID, const FString&, EntityType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEntityUnregistered, const FString&, EntityID, const FString&, EntityType);

/**
 * Central entity management system for RPG entities
 * Provides registry, validation, and lifecycle management
 * Bridges UE entities with Go toolkit entities
 */
UCLASS()
class SESHAT_API URPGEntitySubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    // USubsystem interface
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;

    // Entity registration and management
    UFUNCTION(BlueprintCallable, Category = "RPG Entity")
    FRPGEntityValidationResult RegisterEntity(TScriptInterface<IRPGEntityInterface> Entity);

    UFUNCTION(BlueprintCallable, Category = "RPG Entity")
    bool UnregisterEntity(const FString& EntityID, const FString& EntityType);

    UFUNCTION(BlueprintCallable, Category = "RPG Entity")
    TScriptInterface<IRPGEntityInterface> GetEntity(const FString& EntityID, const FString& EntityType);

    UFUNCTION(BlueprintCallable, Category = "RPG Entity")
    TArray<TScriptInterface<IRPGEntityInterface>> GetEntitiesByType(const FString& EntityType);

    UFUNCTION(BlueprintCallable, Category = "RPG Entity")
    TArray<FString> GetAllEntityTypes() const;

    UFUNCTION(BlueprintCallable, Category = "RPG Entity")
    int32 GetEntityCount() const;

    UFUNCTION(BlueprintCallable, Category = "RPG Entity")
    int32 GetEntityCountByType(const FString& EntityType) const;

    // Entity validation
    UFUNCTION(BlueprintCallable, Category = "RPG Entity")
    FRPGEntityValidationResult ValidateEntity(TScriptInterface<IRPGEntityInterface> Entity);

    UFUNCTION(BlueprintCallable, Category = "RPG Entity")
    bool IsEntityRegistered(const FString& EntityID, const FString& EntityType) const;

    // Entity queries
    UFUNCTION(BlueprintCallable, Category = "RPG Entity")
    bool DoesEntityExist(const FString& EntityID, const FString& EntityType) const;

    UFUNCTION(BlueprintCallable, Category = "RPG Entity")
    TScriptInterface<IRPGEntityInterface> FindEntityByID(const FString& EntityID) const;

    // Toolkit integration
    UFUNCTION(BlueprintCallable, Category = "RPG Entity")
    bool IsToolkitLoaded() const { return bToolkitLoaded; }

    UFUNCTION(BlueprintCallable, Category = "RPG Entity")
    int32 SyncEntityWithToolkit(TScriptInterface<IRPGEntityInterface> Entity);

    // Events
    UPROPERTY(BlueprintAssignable, Category = "RPG Entity")
    FOnEntityRegistered OnEntityRegistered;

    UPROPERTY(BlueprintAssignable, Category = "RPG Entity")
    FOnEntityUnregistered OnEntityUnregistered;

    // Debug and utilities
    UFUNCTION(BlueprintCallable, Category = "RPG Entity", CallInEditor = true)
    void DumpEntityRegistry() const;

    UFUNCTION(BlueprintCallable, Category = "RPG Entity")
    void ClearEntityRegistry();

protected:
    // DLL loading and toolkit integration
    void LoadToolkitDLL();
    void LoadDLLFunctions();
    bool InitializeToolkit();

    // Validation helpers
    bool IsValidEntityID(const FString& EntityID) const;
    bool IsValidEntityType(const FString& EntityType) const;
    FRPGEntityError CreateEntityError(ERPGEntityError ErrorType, const FString& EntityID,
                                     const FString& EntityType, const FString& Operation,
                                     const FString& Message = TEXT("")) const;

private:
    // Entity registry: EntityType -> EntityID -> Entity
    TMap<FString, TMap<FString, TScriptInterface<IRPGEntityInterface>>> EntityRegistry;

    // Toolkit DLL integration
    void* ToolkitDLLHandle = nullptr;
    bool bToolkitLoaded = false;

    // DLL function pointers (extending existing pattern)
    typedef int32(*CreateEntityFunc)(const char* entityType, const char* entityID);
    typedef int32(*ValidateEntityFunc)(const char* entityType, const char* entityID);
    typedef char*(*GetEntityTypeFunc)(int32 entityHandle);
    typedef char*(*GetEntityIDFunc)(int32 entityHandle);
    typedef void(*DestroyEntityFunc)(int32 entityHandle);
    typedef int32(*GetEntityCountFunc)();
    typedef int32(*EntityExistsFunc)(const char* entityType, const char* entityID);

    CreateEntityFunc CreateEntityFuncPtr = nullptr;
    ValidateEntityFunc ValidateEntityFuncPtr = nullptr;
    GetEntityTypeFunc GetEntityTypeFuncPtr = nullptr;
    GetEntityIDFunc GetEntityIDFuncPtr = nullptr;
    DestroyEntityFunc DestroyEntityFuncPtr = nullptr;
    GetEntityCountFunc GetEntityCountFuncPtr = nullptr;
    EntityExistsFunc EntityExistsFuncPtr = nullptr;

    // Entity handle mapping (UE Entity <-> Go toolkit handle)
    TMap<FString, int32> EntityToHandleMap; // "EntityType:EntityID" -> toolkit handle
    TMap<int32, FString> HandleToEntityMap; // toolkit handle -> "EntityType:EntityID"

    // Thread safety
    mutable FCriticalSection EntityRegistryLock;

    // Helper methods
    FString GetEntityKey(const FString& EntityID, const FString& EntityType) const;
    bool LoadCoreFunctions();
};