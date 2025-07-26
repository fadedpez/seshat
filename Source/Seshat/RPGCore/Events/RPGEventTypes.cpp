#include "RPGEventTypes.h"

namespace RPGEventTypes
{
    FString EventTypeToString(ERPGEventType EventType)
    {
        switch (EventType)
        {
            case ERPGEventType::Unknown:                return TEXT("Unknown");
            case ERPGEventType::EntityCreated:          return TEXT("EntityCreated");
            case ERPGEventType::EntityDestroyed:        return TEXT("EntityDestroyed");
            case ERPGEventType::EntityModified:         return TEXT("EntityModified");
            case ERPGEventType::DiceRolled:             return TEXT("DiceRolled");
            case ERPGEventType::RandomSelection:        return TEXT("RandomSelection");
            case ERPGEventType::EntityMoved:            return TEXT("EntityMoved");
            case ERPGEventType::EntityPositioned:       return TEXT("EntityPositioned");
            case ERPGEventType::AreaEntered:            return TEXT("AreaEntered");
            case ERPGEventType::AreaExited:             return TEXT("AreaExited");
            case ERPGEventType::AttackInitiated:        return TEXT("AttackInitiated");
            case ERPGEventType::AttackResolved:         return TEXT("AttackResolved");
            case ERPGEventType::DamageDealt:            return TEXT("DamageDealt");
            case ERPGEventType::DamageReceived:         return TEXT("DamageReceived");
            case ERPGEventType::ConditionApplied:       return TEXT("ConditionApplied");
            case ERPGEventType::ConditionRemoved:       return TEXT("ConditionRemoved");
            case ERPGEventType::ConditionTriggered:     return TEXT("ConditionTriggered");
            case ERPGEventType::ResourceChanged:        return TEXT("ResourceChanged");
            case ERPGEventType::ResourceDepleted:       return TEXT("ResourceDepleted");
            case ERPGEventType::ResourceRestored:       return TEXT("ResourceRestored");
            case ERPGEventType::TurnStarted:            return TEXT("TurnStarted");
            case ERPGEventType::TurnEnded:              return TEXT("TurnEnded");
            case ERPGEventType::RoundStarted:           return TEXT("RoundStarted");
            case ERPGEventType::RoundEnded:             return TEXT("RoundEnded");
            case ERPGEventType::Custom:                 return TEXT("Custom");
            default:                                    return TEXT("Unknown");
        }
    }

    ERPGEventType StringToEventType(const FString& TypeString)
    {
        if (TypeString == TEXT("EntityCreated"))           return ERPGEventType::EntityCreated;
        if (TypeString == TEXT("EntityDestroyed"))         return ERPGEventType::EntityDestroyed;
        if (TypeString == TEXT("EntityModified"))          return ERPGEventType::EntityModified;
        if (TypeString == TEXT("DiceRolled"))              return ERPGEventType::DiceRolled;
        if (TypeString == TEXT("RandomSelection"))         return ERPGEventType::RandomSelection;
        if (TypeString == TEXT("EntityMoved"))             return ERPGEventType::EntityMoved;
        if (TypeString == TEXT("EntityPositioned"))        return ERPGEventType::EntityPositioned;
        if (TypeString == TEXT("AreaEntered"))             return ERPGEventType::AreaEntered;
        if (TypeString == TEXT("AreaExited"))              return ERPGEventType::AreaExited;
        if (TypeString == TEXT("AttackInitiated"))         return ERPGEventType::AttackInitiated;
        if (TypeString == TEXT("AttackResolved"))          return ERPGEventType::AttackResolved;
        if (TypeString == TEXT("DamageDealt"))             return ERPGEventType::DamageDealt;
        if (TypeString == TEXT("DamageReceived"))          return ERPGEventType::DamageReceived;
        if (TypeString == TEXT("ConditionApplied"))        return ERPGEventType::ConditionApplied;
        if (TypeString == TEXT("ConditionRemoved"))        return ERPGEventType::ConditionRemoved;
        if (TypeString == TEXT("ConditionTriggered"))      return ERPGEventType::ConditionTriggered;
        if (TypeString == TEXT("ResourceChanged"))         return ERPGEventType::ResourceChanged;
        if (TypeString == TEXT("ResourceDepleted"))        return ERPGEventType::ResourceDepleted;
        if (TypeString == TEXT("ResourceRestored"))        return ERPGEventType::ResourceRestored;
        if (TypeString == TEXT("TurnStarted"))             return ERPGEventType::TurnStarted;
        if (TypeString == TEXT("TurnEnded"))               return ERPGEventType::TurnEnded;
        if (TypeString == TEXT("RoundStarted"))            return ERPGEventType::RoundStarted;
        if (TypeString == TEXT("RoundEnded"))              return ERPGEventType::RoundEnded;
        if (TypeString == TEXT("Custom"))                  return ERPGEventType::Custom;
        
        return ERPGEventType::Unknown;
    }

    FString ModifierTypeToString(ERPGEventModifier ModifierType)
    {
        switch (ModifierType)
        {
            case ERPGEventModifier::None:                   return TEXT("None");
            case ERPGEventModifier::Advantage:             return TEXT("Advantage");
            case ERPGEventModifier::Disadvantage:          return TEXT("Disadvantage");
            case ERPGEventModifier::Bonus:                 return TEXT("Bonus");
            case ERPGEventModifier::Penalty:               return TEXT("Penalty");
            case ERPGEventModifier::Multiplier:            return TEXT("Multiplier");
            case ERPGEventModifier::Conditional:           return TEXT("Conditional");
            case ERPGEventModifier::Temporary:             return TEXT("Temporary");
            case ERPGEventModifier::Persistent:            return TEXT("Persistent");
            case ERPGEventModifier::HighPriority:          return TEXT("HighPriority");
            case ERPGEventModifier::LowPriority:           return TEXT("LowPriority");
            case ERPGEventModifier::Cancelled:             return TEXT("Cancelled");
            case ERPGEventModifier::Delayed:               return TEXT("Delayed");
            case ERPGEventModifier::Repeated:              return TEXT("Repeated");
            case ERPGEventModifier::Custom:                return TEXT("Custom");
            default:                                       return TEXT("None");
        }
    }

    ERPGEventModifier StringToModifierType(const FString& ModifierString)
    {
        if (ModifierString == TEXT("Advantage"))           return ERPGEventModifier::Advantage;
        if (ModifierString == TEXT("Disadvantage"))        return ERPGEventModifier::Disadvantage;
        if (ModifierString == TEXT("Bonus"))               return ERPGEventModifier::Bonus;
        if (ModifierString == TEXT("Penalty"))             return ERPGEventModifier::Penalty;
        if (ModifierString == TEXT("Multiplier"))          return ERPGEventModifier::Multiplier;
        if (ModifierString == TEXT("Conditional"))         return ERPGEventModifier::Conditional;
        if (ModifierString == TEXT("Temporary"))           return ERPGEventModifier::Temporary;
        if (ModifierString == TEXT("Persistent"))          return ERPGEventModifier::Persistent;
        if (ModifierString == TEXT("HighPriority"))        return ERPGEventModifier::HighPriority;
        if (ModifierString == TEXT("LowPriority"))         return ERPGEventModifier::LowPriority;
        if (ModifierString == TEXT("Cancelled"))           return ERPGEventModifier::Cancelled;
        if (ModifierString == TEXT("Delayed"))             return ERPGEventModifier::Delayed;
        if (ModifierString == TEXT("Repeated"))            return ERPGEventModifier::Repeated;
        if (ModifierString == TEXT("Custom"))              return ERPGEventModifier::Custom;
        
        return ERPGEventModifier::None;
    }
}