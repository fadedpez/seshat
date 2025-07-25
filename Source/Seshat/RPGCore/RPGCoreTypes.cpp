#include "RPGCoreTypes.h"

FString FRPGEntityError::GetFormattedMessage() const
{
    if (ErrorType == ERPGEntityError::None)
    {
        return TEXT("No Error");
    }

    FString FormattedMessage = FString::Printf(TEXT("[%s] %s"), 
        *Operation, 
        ErrorMessage.IsEmpty() ? TEXT("Unknown error") : *ErrorMessage);

    if (!EntityID.IsEmpty() && !EntityType.IsEmpty())
    {
        FormattedMessage += FString::Printf(TEXT(" (Entity: %s:%s)"), *EntityType, *EntityID);
    }
    else if (!EntityType.IsEmpty())
    {
        FormattedMessage += FString::Printf(TEXT(" (Type: %s)"), *EntityType);
    }
    else if (!EntityID.IsEmpty())
    {
        FormattedMessage += FString::Printf(TEXT(" (ID: %s)"), *EntityID);
    }

    return FormattedMessage;
}