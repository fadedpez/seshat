#include "RPGEntitySubsystem.h"
#include "RPGEntity.h"
#include "../../Seshat.h"
#include "Misc/Paths.h"

void URPGEntitySubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
    
    UE_LOG(LogTemp, Warning, TEXT("URPGEntitySubsystem: Initializing"));
    
    // Initialize toolkit integration
    LoadToolkitDLL();
    
    UE_LOG(LogTemp, Warning, TEXT("URPGEntitySubsystem: Successfully initialized"));
}

void URPGEntitySubsystem::Deinitialize()
{
    UE_LOG(LogTemp, Warning, TEXT("URPGEntitySubsystem: Deinitializing"));
    
    // Clear entity registry
    {
        FScopeLock Lock(&EntityRegistryLock);
        EntityRegistry.Empty();
        EntityToHandleMap.Empty();
        HandleToEntityMap.Empty();
    }
    
    // Clear function pointers (don't unload DLL - let Windows handle cleanup)
    CreateEntityFuncPtr = nullptr;
    ValidateEntityFuncPtr = nullptr;
    GetEntityTypeFuncPtr = nullptr;
    GetEntityIDFuncPtr = nullptr;
    DestroyEntityFuncPtr = nullptr;
    GetEntityCountFuncPtr = nullptr;
    EntityExistsFuncPtr = nullptr;
    bToolkitLoaded = false;
    ToolkitDLLHandle = nullptr;
    
    Super::Deinitialize();
}

FRPGEntityValidationResult URPGEntitySubsystem::RegisterEntity(TScriptInterface<IRPGEntityInterface> Entity)
{
    if (!Entity.GetInterface())
    {
        return FRPGEntityValidationResult(false, 
            CreateEntityError(ERPGEntityError::NilEntity, TEXT(""), TEXT(""), TEXT("RegisterEntity")));
    }
    
    // Validate entity first
    FRPGEntityValidationResult ValidationResult = ValidateEntity(Entity);
    if (!ValidationResult.bIsValid)
    {
        return ValidationResult;
    }
    
    FString EntityID = Entity->GetID();
    FString EntityType = Entity->GetType();
    
    FScopeLock Lock(&EntityRegistryLock);
    
    // Check for duplicates
    if (EntityRegistry.Contains(EntityType))
    {
        if (EntityRegistry[EntityType].Contains(EntityID))
        {
            return FRPGEntityValidationResult(false,
                CreateEntityError(ERPGEntityError::Duplicate, EntityID, EntityType, TEXT("RegisterEntity")));
        }
    }
    else
    {
        EntityRegistry.Add(EntityType, TMap<FString, TScriptInterface<IRPGEntityInterface>>());
    }
    
    // Register entity
    EntityRegistry[EntityType].Add(EntityID, Entity);
    
    // Sync with toolkit if available
    if (bToolkitLoaded)
    {
        int32 ToolkitHandle = SyncEntityWithToolkit(Entity);
        if (ToolkitHandle > 0)
        {
            FString EntityKey = GetEntityKey(EntityID, EntityType);
            EntityToHandleMap.Add(EntityKey, ToolkitHandle);
            HandleToEntityMap.Add(ToolkitHandle, EntityKey);
        }
    }
    
    // Broadcast event
    OnEntityRegistered.Broadcast(EntityID, EntityType);
    
    UE_LOG(LogTemp, Log, TEXT("URPGEntitySubsystem::RegisterEntity: Successfully registered entity %s:%s"), 
           *EntityType, *EntityID);
    
    return FRPGEntityValidationResult(true);
}

bool URPGEntitySubsystem::UnregisterEntity(const FString& EntityID, const FString& EntityType)
{
    FScopeLock Lock(&EntityRegistryLock);
    
    if (!EntityRegistry.Contains(EntityType))
    {
        UE_LOG(LogTemp, Warning, TEXT("URPGEntitySubsystem::UnregisterEntity: EntityType %s not found"), 
               *EntityType);
        return false;
    }
    
    if (!EntityRegistry[EntityType].Contains(EntityID))
    {
        UE_LOG(LogTemp, Warning, TEXT("URPGEntitySubsystem::UnregisterEntity: EntityID %s not found"), 
               *EntityID);
        return false;
    }
    
    // Remove from registry
    EntityRegistry[EntityType].Remove(EntityID);
    
    // Clean up empty type entries
    if (EntityRegistry[EntityType].Num() == 0)
    {
        EntityRegistry.Remove(EntityType);
    }
    
    // Clean up toolkit mapping
    FString EntityKey = GetEntityKey(EntityID, EntityType);
    if (EntityToHandleMap.Contains(EntityKey))
    {
        int32 ToolkitHandle = EntityToHandleMap[EntityKey];
        
        // Destroy entity in toolkit
        if (bToolkitLoaded && DestroyEntityFuncPtr)
        {
            DestroyEntityFuncPtr(ToolkitHandle);
        }
        
        EntityToHandleMap.Remove(EntityKey);
        HandleToEntityMap.Remove(ToolkitHandle);
    }
    
    // Broadcast event
    OnEntityUnregistered.Broadcast(EntityID, EntityType);
    
    UE_LOG(LogTemp, Log, TEXT("URPGEntitySubsystem::UnregisterEntity: Successfully unregistered entity %s:%s"), 
           *EntityType, *EntityID);
    
    return true;
}

TScriptInterface<IRPGEntityInterface> URPGEntitySubsystem::GetEntity(const FString& EntityID, const FString& EntityType)
{
    FScopeLock Lock(&EntityRegistryLock);
    
    if (EntityRegistry.Contains(EntityType) && EntityRegistry[EntityType].Contains(EntityID))
    {
        return EntityRegistry[EntityType][EntityID];
    }
    
    return TScriptInterface<IRPGEntityInterface>();
}

TArray<TScriptInterface<IRPGEntityInterface>> URPGEntitySubsystem::GetEntitiesByType(const FString& EntityType)
{
    TArray<TScriptInterface<IRPGEntityInterface>> Result;
    
    FScopeLock Lock(&EntityRegistryLock);
    
    if (EntityRegistry.Contains(EntityType))
    {
        for (auto& EntityPair : EntityRegistry[EntityType])
        {
            Result.Add(EntityPair.Value);
        }
    }
    
    return Result;
}

TArray<FString> URPGEntitySubsystem::GetAllEntityTypes() const
{
    TArray<FString> Result;
    
    FScopeLock Lock(&EntityRegistryLock);
    EntityRegistry.GetKeys(Result);
    
    return Result;
}

int32 URPGEntitySubsystem::GetEntityCount() const
{
    FScopeLock Lock(&EntityRegistryLock);
    
    int32 TotalCount = 0;
    for (auto& TypePair : EntityRegistry)
    {
        TotalCount += TypePair.Value.Num();
    }
    
    return TotalCount;
}

int32 URPGEntitySubsystem::GetEntityCountByType(const FString& EntityType) const
{
    FScopeLock Lock(&EntityRegistryLock);
    
    if (EntityRegistry.Contains(EntityType))
    {
        return EntityRegistry[EntityType].Num();
    }
    
    return 0;
}

FRPGEntityValidationResult URPGEntitySubsystem::ValidateEntity(TScriptInterface<IRPGEntityInterface> Entity)
{
    if (!Entity.GetInterface())
    {
        return FRPGEntityValidationResult(false, 
            CreateEntityError(ERPGEntityError::NilEntity, TEXT(""), TEXT(""), TEXT("ValidateEntity")));
    }
    
    FString EntityID = Entity->GetID();
    FString EntityType = Entity->GetType();
    
    if (!IsValidEntityID(EntityID))
    {
        return FRPGEntityValidationResult(false,
            CreateEntityError(ERPGEntityError::EmptyID, EntityID, EntityType, TEXT("ValidateEntity")));
    }
    
    if (!IsValidEntityType(EntityType))
    {
        return FRPGEntityValidationResult(false,
            CreateEntityError(ERPGEntityError::InvalidType, EntityID, EntityType, TEXT("ValidateEntity")));
    }
    
    // Additional validation using toolkit if available
    if (bToolkitLoaded && ValidateEntityFuncPtr)
    {
        int32 ValidationResult = ValidateEntityFuncPtr(TCHAR_TO_ANSI(*EntityType), TCHAR_TO_ANSI(*EntityID));
        if (ValidationResult != 0)
        {
            ERPGEntityError ErrorType = static_cast<ERPGEntityError>(ValidationResult);
            return FRPGEntityValidationResult(false,
                CreateEntityError(ErrorType, EntityID, EntityType, TEXT("ValidateEntity"), TEXT("Toolkit validation failed")));
        }
    }
    
    return FRPGEntityValidationResult(true);
}

bool URPGEntitySubsystem::IsEntityRegistered(const FString& EntityID, const FString& EntityType) const
{
    FScopeLock Lock(&EntityRegistryLock);
    
    return EntityRegistry.Contains(EntityType) && EntityRegistry[EntityType].Contains(EntityID);
}

bool URPGEntitySubsystem::DoesEntityExist(const FString& EntityID, const FString& EntityType) const
{
    return IsEntityRegistered(EntityID, EntityType);
}

TScriptInterface<IRPGEntityInterface> URPGEntitySubsystem::FindEntityByID(const FString& EntityID) const
{
    FScopeLock Lock(&EntityRegistryLock);
    
    // Search across all entity types
    for (auto& TypePair : EntityRegistry)
    {
        if (TypePair.Value.Contains(EntityID))
        {
            return TypePair.Value[EntityID];
        }
    }
    
    return TScriptInterface<IRPGEntityInterface>();
}

int32 URPGEntitySubsystem::SyncEntityWithToolkit(TScriptInterface<IRPGEntityInterface> Entity)
{
    if (!bToolkitLoaded || !CreateEntityFuncPtr || !Entity.GetInterface())
    {
        return -1;
    }
    
    FString EntityID = Entity->GetID();
    FString EntityType = Entity->GetType();
    
    int32 ToolkitHandle = CreateEntityFuncPtr(TCHAR_TO_ANSI(*EntityType), TCHAR_TO_ANSI(*EntityID));
    
    if (ToolkitHandle > 0)
    {
        UE_LOG(LogTemp, Log, TEXT("URPGEntitySubsystem::SyncEntityWithToolkit: Created toolkit entity %s:%s with handle %d"), 
               *EntityType, *EntityID, ToolkitHandle);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("URPGEntitySubsystem::SyncEntityWithToolkit: Failed to create toolkit entity %s:%s"), 
               *EntityType, *EntityID);
    }
    
    return ToolkitHandle;
}

void URPGEntitySubsystem::DumpEntityRegistry() const
{
    FScopeLock Lock(&EntityRegistryLock);
    
    UE_LOG(LogTemp, Warning, TEXT("=== Entity Registry Dump ==="));
    UE_LOG(LogTemp, Warning, TEXT("Total entity types: %d"), EntityRegistry.Num());
    
    for (auto& TypePair : EntityRegistry)
    {
        FString EntityType = TypePair.Key;
        int32 EntityCount = TypePair.Value.Num();
        
        UE_LOG(LogTemp, Warning, TEXT("Type: %s (%d entities)"), *EntityType, EntityCount);
        
        for (auto& EntityPair : TypePair.Value)
        {
            FString EntityID = EntityPair.Key;
            UE_LOG(LogTemp, Warning, TEXT("  - %s"), *EntityID);
        }
    }
    
    UE_LOG(LogTemp, Warning, TEXT("========================"));
}

void URPGEntitySubsystem::ClearEntityRegistry()
{
    FScopeLock Lock(&EntityRegistryLock);
    
    int32 TotalCount = GetEntityCount();
    
    // Clean up toolkit entities
    if (bToolkitLoaded && DestroyEntityFuncPtr)
    {
        for (auto& HandlePair : HandleToEntityMap)
        {
            DestroyEntityFuncPtr(HandlePair.Key);
        }
    }
    
    EntityRegistry.Empty();
    EntityToHandleMap.Empty();
    HandleToEntityMap.Empty();
    
    UE_LOG(LogTemp, Warning, TEXT("URPGEntitySubsystem::ClearEntityRegistry: Cleared %d entities"), TotalCount);
}

void URPGEntitySubsystem::LoadToolkitDLL()
{
    // Construct the path to our DLL (following existing dice subsystem pattern)
    FString BaseDir = FPaths::ProjectDir();
    FString LibraryPath = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/RPGToolkit/rpg_toolkit.dll"));
    LibraryPath = FPaths::ConvertRelativePathToFull(LibraryPath);

    UE_LOG(LogTemp, Warning, TEXT("URPGEntitySubsystem: Attempting to load DLL from: %s"), *LibraryPath);

    // Check if the DLL exists
    if (!FPaths::FileExists(LibraryPath))
    {
        UE_LOG(LogTemp, Error, TEXT("URPGEntitySubsystem: DLL not found at path: %s"), *LibraryPath);
        return;
    }

    // Load the DLL
    ToolkitDLLHandle = FPlatformProcess::GetDllHandle(*LibraryPath);
    if (!ToolkitDLLHandle)
    {
        UE_LOG(LogTemp, Error, TEXT("URPGEntitySubsystem: Failed to load DLL"));
        return;
    }

    UE_LOG(LogTemp, Warning, TEXT("URPGEntitySubsystem: Successfully loaded DLL"));
    
    // Load function pointers
    LoadDLLFunctions();
}

void URPGEntitySubsystem::LoadDLLFunctions()
{
    if (!ToolkitDLLHandle)
    {
        return;
    }
    
    // Load core entity functions
    CreateEntityFuncPtr = (CreateEntityFunc)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("CreateEntity"));
    ValidateEntityFuncPtr = (ValidateEntityFunc)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("ValidateEntity"));
    GetEntityTypeFuncPtr = (GetEntityTypeFunc)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("GetEntityType"));
    GetEntityIDFuncPtr = (GetEntityIDFunc)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("GetEntityID"));
    DestroyEntityFuncPtr = (DestroyEntityFunc)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("DestroyEntity"));
    GetEntityCountFuncPtr = (GetEntityCountFunc)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("GetEntityCount"));
    EntityExistsFuncPtr = (EntityExistsFunc)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("EntityExists"));
    
    // Check if functions were loaded
    bool bAllFunctionsLoaded = (CreateEntityFuncPtr != nullptr) && 
                              (ValidateEntityFuncPtr != nullptr) && 
                              (GetEntityTypeFuncPtr != nullptr) &&
                              (GetEntityIDFuncPtr != nullptr) &&
                              (DestroyEntityFuncPtr != nullptr) &&
                              (GetEntityCountFuncPtr != nullptr) &&
                              (EntityExistsFuncPtr != nullptr);
    
    if (bAllFunctionsLoaded)
    {
        bToolkitLoaded = true;
        UE_LOG(LogTemp, Warning, TEXT("URPGEntitySubsystem: All core entity functions loaded successfully"));
        
        // Initialize toolkit
        InitializeToolkit();
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("URPGEntitySubsystem: Failed to load some core entity functions"));
        UE_LOG(LogTemp, Error, TEXT("  CreateEntity: %s"), CreateEntityFuncPtr ? TEXT("OK") : TEXT("FAILED"));
        UE_LOG(LogTemp, Error, TEXT("  ValidateEntity: %s"), ValidateEntityFuncPtr ? TEXT("OK") : TEXT("FAILED"));
        UE_LOG(LogTemp, Error, TEXT("  GetEntityType: %s"), GetEntityTypeFuncPtr ? TEXT("OK") : TEXT("FAILED"));
        UE_LOG(LogTemp, Error, TEXT("  GetEntityID: %s"), GetEntityIDFuncPtr ? TEXT("OK") : TEXT("FAILED"));
        UE_LOG(LogTemp, Error, TEXT("  DestroyEntity: %s"), DestroyEntityFuncPtr ? TEXT("OK") : TEXT("FAILED"));
        UE_LOG(LogTemp, Error, TEXT("  GetEntityCount: %s"), GetEntityCountFuncPtr ? TEXT("OK") : TEXT("FAILED"));
        UE_LOG(LogTemp, Error, TEXT("  EntityExists: %s"), EntityExistsFuncPtr ? TEXT("OK") : TEXT("FAILED"));
    }
}

bool URPGEntitySubsystem::InitializeToolkit()
{
    if (!bToolkitLoaded)
    {
        return false;
    }
    
    UE_LOG(LogTemp, Warning, TEXT("URPGEntitySubsystem: Toolkit core entity system initialized"));
    return true;
}

bool URPGEntitySubsystem::IsValidEntityID(const FString& EntityID) const
{
    return !EntityID.IsEmpty() && EntityID.Len() > 0;
}

bool URPGEntitySubsystem::IsValidEntityType(const FString& EntityType) const
{
    return !EntityType.IsEmpty() && EntityType.Len() > 0;
}

FRPGEntityError URPGEntitySubsystem::CreateEntityError(ERPGEntityError ErrorType, const FString& EntityID,
                                                      const FString& EntityType, const FString& Operation,
                                                      const FString& Message) const
{
    FString ErrorMessage = Message;
    if (ErrorMessage.IsEmpty())
    {
        // Provide default messages based on error type
        switch (ErrorType)
        {
        case ERPGEntityError::NotFound:
            ErrorMessage = TEXT("Entity not found");
            break;
        case ERPGEntityError::Invalid:
            ErrorMessage = TEXT("Entity is invalid");
            break;
        case ERPGEntityError::Duplicate:
            ErrorMessage = TEXT("Entity already exists");
            break;
        case ERPGEntityError::NilEntity:
            ErrorMessage = TEXT("Entity is null");
            break;
        case ERPGEntityError::EmptyID:
            ErrorMessage = TEXT("Entity ID is empty");
            break;
        case ERPGEntityError::InvalidType:
            ErrorMessage = TEXT("Entity type is invalid");
            break;
        default:
            ErrorMessage = TEXT("Unknown error");
            break;
        }
    }
    
    return FRPGEntityError(ErrorType, EntityID, EntityType, Operation, ErrorMessage);
}

FString URPGEntitySubsystem::GetEntityKey(const FString& EntityID, const FString& EntityType) const
{
    return FString::Printf(TEXT("%s:%s"), *EntityType, *EntityID);
}