#pragma once

#include "CoreMinimal.h"
#include "RPGEventTypes.h"
#include "../Entity/RPGEntity.h"
#include "../RPGCoreTypes.h"
#include "RPGEventContext.generated.h"

/**
 * Event context data structure that carries information about an event
 * This is the primary data container for all RPG events
 */
USTRUCT(BlueprintType)
struct SESHAT_API FRPGEventContext
{
    GENERATED_BODY()

    FRPGEventContext()
        : EventType(ERPGEventType::Unknown)
        , Priority(ERPGEventPriority::Normal)
        , Timestamp(0.0f)
        , bCancelled(false)
        , bHandled(false)
    {
    }

    FRPGEventContext(ERPGEventType InEventType, TScriptInterface<IRPGEntityInterface> InSource = nullptr)
        : EventType(InEventType)
        , SourceEntity(InSource)
        , Priority(ERPGEventPriority::Normal)
        , Timestamp(FApp::GetCurrentTime())
        , bCancelled(false)
        , bHandled(false)
    {
        EventID = FGuid::NewGuid().ToString();
    }

    // Core event identification
    UPROPERTY(BlueprintReadOnly, Category = "RPG Event Context")
    FString EventID;

    UPROPERTY(BlueprintReadOnly, Category = "RPG Event Context")
    ERPGEventType EventType;

    UPROPERTY(BlueprintReadOnly, Category = "RPG Event Context")
    FString EventName;

    // Entity references
    UPROPERTY(BlueprintReadOnly, Category = "RPG Event Context")
    TScriptInterface<IRPGEntityInterface> SourceEntity;

    UPROPERTY(BlueprintReadOnly, Category = "RPG Event Context")
    TScriptInterface<IRPGEntityInterface> TargetEntity;

    UPROPERTY(BlueprintReadOnly, Category = "RPG Event Context")
    TArray<TScriptInterface<IRPGEntityInterface>> AdditionalEntities;

    // Event processing info
    UPROPERTY(BlueprintReadOnly, Category = "RPG Event Context")
    ERPGEventPriority Priority;

    UPROPERTY(BlueprintReadOnly, Category = "RPG Event Context")
    double Timestamp;

    UPROPERTY(BlueprintReadWrite, Category = "RPG Event Context")
    bool bCancelled;

    UPROPERTY(BlueprintReadWrite, Category = "RPG Event Context")
    bool bHandled;

    // Event modifiers
    UPROPERTY(BlueprintReadWrite, Category = "RPG Event Context")
    TArray<ERPGEventModifier> Modifiers;

    // Generic data storage using key-value pairs
    UPROPERTY(BlueprintReadWrite, Category = "RPG Event Context")
    TMap<FString, FString> StringData;

    UPROPERTY(BlueprintReadWrite, Category = "RPG Event Context")
    TMap<FString, int32> IntData;

    UPROPERTY(BlueprintReadWrite, Category = "RPG Event Context")
    TMap<FString, float> FloatData;

    UPROPERTY(BlueprintReadWrite, Category = "RPG Event Context")
    TMap<FString, bool> BoolData;

    // Custom payload data (for complex data structures)
    UPROPERTY(BlueprintReadWrite, Category = "RPG Event Context")
    TMap<FString, UObject*> ObjectData;

    // Utility methods for data access (regular C++ methods only in USTRUCT)
    void SetStringData(const FString& Key, const FString& Value)
    {
        StringData.Add(Key, Value);
    }

    FString GetStringData(const FString& Key, const FString& DefaultValue = TEXT("")) const
    {
        if (const FString* Value = StringData.Find(Key))
        {
            return *Value;
        }
        return DefaultValue;
    }

    void SetIntData(const FString& Key, int32 Value)
    {
        IntData.Add(Key, Value);
    }

    int32 GetIntData(const FString& Key, int32 DefaultValue = 0) const
    {
        if (const int32* Value = IntData.Find(Key))
        {
            return *Value;
        }
        return DefaultValue;
    }

    void SetFloatData(const FString& Key, float Value)
    {
        FloatData.Add(Key, Value);
    }

    float GetFloatData(const FString& Key, float DefaultValue = 0.0f) const
    {
        if (const float* Value = FloatData.Find(Key))
        {
            return *Value;
        }
        return DefaultValue;
    }

    void SetBoolData(const FString& Key, bool Value)
    {
        BoolData.Add(Key, Value);
    }

    bool GetBoolData(const FString& Key, bool DefaultValue = false) const
    {
        if (const bool* Value = BoolData.Find(Key))
        {
            return *Value;
        }
        return DefaultValue;
    }

    void SetObjectData(const FString& Key, UObject* Value)
    {
        ObjectData.Add(Key, Value);
    }

    UObject* GetObjectData(const FString& Key) const
    {
        if (UObject* const* Value = ObjectData.Find(Key))
        {
            return *Value;
        }
        return nullptr;
    }

    // Modifier management
    void AddModifier(ERPGEventModifier Modifier)
    {
        Modifiers.AddUnique(Modifier);
    }

    void RemoveModifier(ERPGEventModifier Modifier)
    {
        Modifiers.Remove(Modifier);
    }

    bool HasModifier(ERPGEventModifier Modifier) const
    {
        return Modifiers.Contains(Modifier);
    }

    void ClearModifiers()
    {
        Modifiers.Empty();
    }

    // Entity management helpers
    void AddAdditionalEntity(TScriptInterface<IRPGEntityInterface> Entity)
    {
        if (Entity.GetInterface())
        {
            AdditionalEntities.AddUnique(Entity);
        }
    }

    bool HasEntity(TScriptInterface<IRPGEntityInterface> Entity) const
    {
        if (!Entity.GetInterface())
        {
            return false;
        }

        FString EntityID = Entity->GetID();
        FString EntityType = Entity->GetType();

        // Check source entity
        if (SourceEntity.GetInterface() && 
            SourceEntity->GetID() == EntityID && 
            SourceEntity->GetType() == EntityType)
        {
            return true;
        }

        // Check target entity
        if (TargetEntity.GetInterface() && 
            TargetEntity->GetID() == EntityID && 
            TargetEntity->GetType() == EntityType)
        {
            return true;
        }

        // Check additional entities
        for (const auto& AdditionalEntity : AdditionalEntities)
        {
            if (AdditionalEntity.GetInterface() && 
                AdditionalEntity->GetID() == EntityID && 
                AdditionalEntity->GetType() == EntityType)
            {
                return true;
            }
        }

        return false;
    }

    // Validation and utility
    bool IsValid() const
    {
        return EventType != ERPGEventType::Unknown && !EventID.IsEmpty();
    }

    FString ToString() const
    {
        FString Result = FString::Printf(TEXT("Event[%s]: %s"), 
            *EventID, 
            *RPGEventTypes::EventTypeToString(EventType));
        
        if (SourceEntity.GetInterface())
        {
            Result += FString::Printf(TEXT(" Source=%s:%s"), 
                *SourceEntity->GetType(), 
                *SourceEntity->GetID());
        }
        
        if (TargetEntity.GetInterface())
        {
            Result += FString::Printf(TEXT(" Target=%s:%s"), 
                *TargetEntity->GetType(), 
                *TargetEntity->GetID());
        }
        
        if (bCancelled)
        {
            Result += TEXT(" [CANCELLED]");
        }
        
        if (bHandled)
        {
            Result += TEXT(" [HANDLED]");
        }
        
        return Result;
    }

    // Reset context for reuse
    void Reset()
    {
        EventID = FGuid::NewGuid().ToString();
        EventType = ERPGEventType::Unknown;
        EventName.Empty();
        SourceEntity = nullptr;
        TargetEntity = nullptr;
        AdditionalEntities.Empty();
        Priority = ERPGEventPriority::Normal;
        Timestamp = FApp::GetCurrentTime();
        bCancelled = false;
        bHandled = false;
        Modifiers.Empty();
        StringData.Empty();
        IntData.Empty();
        FloatData.Empty();
        BoolData.Empty();
        ObjectData.Empty();
    }
};