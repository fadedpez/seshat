#include "RPGEntity.h"
#include "../../Seshat.h"
#include "RPGEntitySubsystem.h"
#include "Misc/Guid.h"

ARPGEntity::ARPGEntity()
{
    PrimaryActorTick.bCanEverTick = false;
    
    // Initialize with empty values - will be set up in InitializeEntity
    EntityID = TEXT("");
    EntityType = TEXT("");
    
    bEntityInitialized = false;
    bRegisteredWithSubsystem = false;
}

FString ARPGEntity::GetID() const
{
    return EntityID;
}

FString ARPGEntity::GetType() const
{
    return EntityType;
}

bool ARPGEntity::IsValidEntity() const
{
    return !EntityID.IsEmpty() && !EntityType.IsEmpty();
}

void ARPGEntity::RegisterWithSubsystem()
{
    if (bRegisteredWithSubsystem)
    {
        UE_LOG(LogTemp, Warning, TEXT("ARPGEntity::RegisterWithSubsystem: Entity %s:%s already registered"), 
               *EntityType, *EntityID);
        return;
    }

    URPGEntitySubsystem* EntitySubsystem = GetGameInstance()->GetSubsystem<URPGEntitySubsystem>();
    if (EntitySubsystem)
    {
        // Use raw toolkit validation functions - no custom registration system
        bool bValidID = EntitySubsystem->ValidateEntityID(EntityID);
        bool bValidType = EntitySubsystem->ValidateEntityType(EntityType);
        
        if (bValidID && bValidType)
        {
            bRegisteredWithSubsystem = true;
            UE_LOG(LogTemp, Log, TEXT("ARPGEntity::RegisterWithSubsystem: Successfully validated entity %s:%s"), 
                   *EntityType, *EntityID);
        }
        else
        {
            FString ErrorMessage;
            if (!bValidID)
            {
                ErrorMessage += FString::Printf(TEXT("Invalid ID: %s. "), *EntitySubsystem->GetInvalidEntityError());
            }
            if (!bValidType)
            {
                ErrorMessage += FString::Printf(TEXT("Invalid Type: %s. "), *EntitySubsystem->GetInvalidTypeError());
            }
            
            UE_LOG(LogTemp, Error, TEXT("ARPGEntity::RegisterWithSubsystem: Failed to validate entity %s:%s - %s"), 
                   *EntityType, *EntityID, *ErrorMessage);
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("ARPGEntity::RegisterWithSubsystem: EntitySubsystem not found"));
    }
}

void ARPGEntity::UnregisterFromSubsystem()
{
    if (!bRegisteredWithSubsystem)
    {
        return;
    }

    // Swiss Army Knife Standard: No custom unregister system in toolkit
    // Just mark as unregistered - toolkit doesn't track entity state
    bRegisteredWithSubsystem = false;
    UE_LOG(LogTemp, Log, TEXT("ARPGEntity::UnregisterFromSubsystem: Entity %s:%s marked as unregistered"), 
           *EntityType, *EntityID);
}

void ARPGEntity::InitializeEntity()
{
    if (bEntityInitialized)
    {
        return;
    }

    // Generate ID if not set
    if (EntityID.IsEmpty())
    {
        EntityID = GenerateEntityID();
    }

    // Set type if not set
    if (EntityType.IsEmpty())
    {
        EntityType = GetDefaultEntityType();
    }

    bEntityInitialized = true;
    
    UE_LOG(LogTemp, Log, TEXT("ARPGEntity::InitializeEntity: Initialized entity %s:%s"), 
           *EntityType, *EntityID);
}

FString ARPGEntity::GenerateEntityID() const
{
    // Generate a unique ID using UE's GUID system
    FGuid NewGuid = FGuid::NewGuid();
    return NewGuid.ToString();
}

void ARPGEntity::BeginPlay()
{
    Super::BeginPlay();
    
    // Initialize entity if not already done
    if (!bEntityInitialized)
    {
        InitializeEntity();
    }
    
    // Register with subsystem
    RegisterWithSubsystem();
}

void ARPGEntity::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    // Unregister from subsystem
    UnregisterFromSubsystem();
    
    Super::EndPlay(EndPlayReason);
}

// URPGEntityObject implementation

URPGEntityObject::URPGEntityObject()
{
    EntityID = TEXT("");
    EntityType = TEXT("");
}

FString URPGEntityObject::GetID() const
{
    return EntityID;
}

FString URPGEntityObject::GetType() const
{
    return EntityType;
}

URPGEntityObject* URPGEntityObject::CreateEntity(UObject* Outer, const FString& EntityType, const FString& EntityID)
{
    if (!Outer)
    {
        UE_LOG(LogTemp, Error, TEXT("URPGEntityObject::CreateEntity: Invalid outer object"));
        return nullptr;
    }

    if (EntityType.IsEmpty())
    {
        UE_LOG(LogTemp, Error, TEXT("URPGEntityObject::CreateEntity: EntityType cannot be empty"));
        return nullptr;
    }

    URPGEntityObject* NewEntity = NewObject<URPGEntityObject>(Outer);
    if (NewEntity)
    {
        NewEntity->InitializeEntity(EntityType, EntityID);
        UE_LOG(LogTemp, Log, TEXT("URPGEntityObject::CreateEntity: Created entity %s:%s"), 
               *EntityType, *NewEntity->GetID());
    }

    return NewEntity;
}

void URPGEntityObject::InitializeEntity(const FString& Type, const FString& ID)
{
    EntityType = Type;
    
    if (ID.IsEmpty())
    {
        // Generate unique ID
        FGuid NewGuid = FGuid::NewGuid();
        EntityID = NewGuid.ToString();
    }
    else
    {
        EntityID = ID;
    }
}