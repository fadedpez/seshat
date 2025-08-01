#include "RPGEntitySubsystem.h"
#include "../../Seshat.h"
#include "Misc/Paths.h"

void URPGEntitySubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
    
    UE_LOG(LogTemp, Warning, TEXT("URPGEntitySubsystem: Initializing"));
    
    // Initialize toolkit integration
    LoadDLLFunctions();
    
    UE_LOG(LogTemp, Warning, TEXT("URPGEntitySubsystem: Successfully initialized"));
}

void URPGEntitySubsystem::Deinitialize()
{
    UE_LOG(LogTemp, Warning, TEXT("URPGEntitySubsystem: Deinitializing"));
    
    // Clear function pointers (don't unload DLL - let Windows handle cleanup)
    GetEntityNotFoundErrorFuncPtr = nullptr;
    GetInvalidEntityErrorFuncPtr = nullptr;
    GetDuplicateEntityErrorFuncPtr = nullptr;
    GetNilEntityErrorFuncPtr = nullptr;
    GetEmptyIDErrorFuncPtr = nullptr;
    GetInvalidTypeErrorFuncPtr = nullptr;
    ValidateEntityIDFuncPtr = nullptr;
    ValidateEntityTypeFuncPtr = nullptr;
    FreeStringFuncPtr = nullptr;
    CreateEntityErrorCompleteFuncPtr = nullptr;
    bFunctionsLoaded = false;
    ToolkitDLLHandle = nullptr;
    
    Super::Deinitialize();
}

// Core Error Constants Implementation
FString URPGEntitySubsystem::GetEntityNotFoundError() const
{
    if (!IsSafeToCallFunction() || !GetEntityNotFoundErrorFuncPtr)
    {
        return TEXT("Entity not found");
    }
    
    ANSICHAR* CStr = GetEntityNotFoundErrorFuncPtr();
    return ConvertAndFreeString(CStr);
}

FString URPGEntitySubsystem::GetInvalidEntityError() const
{
    if (!IsSafeToCallFunction() || !GetInvalidEntityErrorFuncPtr)
    {
        return TEXT("Invalid entity");
    }
    
    ANSICHAR* CStr = GetInvalidEntityErrorFuncPtr();
    return ConvertAndFreeString(CStr);
}

FString URPGEntitySubsystem::GetDuplicateEntityError() const
{
    if (!IsSafeToCallFunction() || !GetDuplicateEntityErrorFuncPtr)
    {
        return TEXT("Duplicate entity");
    }
    
    ANSICHAR* CStr = GetDuplicateEntityErrorFuncPtr();
    return ConvertAndFreeString(CStr);
}

FString URPGEntitySubsystem::GetNilEntityError() const
{
    if (!IsSafeToCallFunction() || !GetNilEntityErrorFuncPtr)
    {
        return TEXT("Nil entity");
    }
    
    ANSICHAR* CStr = GetNilEntityErrorFuncPtr();
    return ConvertAndFreeString(CStr);
}

FString URPGEntitySubsystem::GetEmptyIDError() const
{
    if (!IsSafeToCallFunction() || !GetEmptyIDErrorFuncPtr)
    {
        return TEXT("Empty entity ID");
    }
    
    ANSICHAR* CStr = GetEmptyIDErrorFuncPtr();
    return ConvertAndFreeString(CStr);
}

FString URPGEntitySubsystem::GetInvalidTypeError() const
{
    if (!IsSafeToCallFunction() || !GetInvalidTypeErrorFuncPtr)
    {
        return TEXT("Invalid entity type");
    }
    
    ANSICHAR* CStr = GetInvalidTypeErrorFuncPtr();
    return ConvertAndFreeString(CStr);
}

// Entity Validation Implementation
bool URPGEntitySubsystem::ValidateEntityID(const FString& ID) const
{
    if (!IsSafeToCallFunction() || !ValidateEntityIDFuncPtr)
    {
        return !ID.IsEmpty(); // Basic fallback validation
    }
    
    return ValidateEntityIDFuncPtr(TCHAR_TO_ANSI(*ID)) != 0;
}

bool URPGEntitySubsystem::ValidateEntityType(const FString& Type) const
{
    if (!IsSafeToCallFunction() || !ValidateEntityTypeFuncPtr)
    {
        return !Type.IsEmpty(); // Basic fallback validation
    }
    
    return ValidateEntityTypeFuncPtr(TCHAR_TO_ANSI(*Type)) != 0;
}

// Toolkit Status
bool URPGEntitySubsystem::IsToolkitLoaded() const
{
    return bFunctionsLoaded;
}

// Private Implementation
void URPGEntitySubsystem::LoadDLLFunctions()
{
    // Use proper UE binary directory (following RPGDiceSubsystem pattern)
    FString BinariesDir = FPaths::Combine(FPaths::ProjectDir(), TEXT("Binaries"), FPlatformProcess::GetBinariesSubdirectory());
    FString LibraryPath = FPaths::Combine(BinariesDir, TEXT("rpg_toolkit.dll"));
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
    
    // Load error constant functions
    GetEntityNotFoundErrorFuncPtr = (GetEntityNotFoundErrorFunc)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("GetEntityNotFoundError"));
    GetInvalidEntityErrorFuncPtr = (GetInvalidEntityErrorFunc)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("GetInvalidEntityError"));
    GetDuplicateEntityErrorFuncPtr = (GetDuplicateEntityErrorFunc)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("GetDuplicateEntityError"));
    GetNilEntityErrorFuncPtr = (GetNilEntityErrorFunc)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("GetNilEntityError"));
    GetEmptyIDErrorFuncPtr = (GetEmptyIDErrorFunc)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("GetEmptyIDError"));
    GetInvalidTypeErrorFuncPtr = (GetInvalidTypeErrorFunc)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("GetInvalidTypeError"));
    
    // Load validation functions
    ValidateEntityIDFuncPtr = (ValidateEntityIDFunc)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("ValidateEntityID"));
    ValidateEntityTypeFuncPtr = (ValidateEntityTypeFunc)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("ValidateEntityType"));
    
    // Load string management function
    FreeStringFuncPtr = (FreeStringFunc)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("FreeString"));
    
    // Load automatic cleanup function
    CreateEntityErrorCompleteFuncPtr = (CreateEntityErrorCompleteFunc)FPlatformProcess::GetDllExport(ToolkitDLLHandle, TEXT("CreateEntityErrorComplete"));
    
    // Check if functions were loaded
    bool bAllFunctionsLoaded = (GetEntityNotFoundErrorFuncPtr != nullptr) && 
                              (GetInvalidEntityErrorFuncPtr != nullptr) && 
                              (GetDuplicateEntityErrorFuncPtr != nullptr) &&
                              (GetNilEntityErrorFuncPtr != nullptr) &&
                              (GetEmptyIDErrorFuncPtr != nullptr) &&
                              (GetInvalidTypeErrorFuncPtr != nullptr) &&
                              (ValidateEntityIDFuncPtr != nullptr) &&
                              (ValidateEntityTypeFuncPtr != nullptr) &&
                              (FreeStringFuncPtr != nullptr) &&
                              (CreateEntityErrorCompleteFuncPtr != nullptr);
    
    if (bAllFunctionsLoaded)
    {
        bFunctionsLoaded = true;
        UE_LOG(LogTemp, Warning, TEXT("URPGEntitySubsystem: All core toolkit functions loaded successfully"));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("URPGEntitySubsystem: Failed to load some core toolkit functions"));
        UE_LOG(LogTemp, Error, TEXT("  GetEntityNotFoundError: %s"), GetEntityNotFoundErrorFuncPtr ? TEXT("OK") : TEXT("FAILED"));
        UE_LOG(LogTemp, Error, TEXT("  GetInvalidEntityError: %s"), GetInvalidEntityErrorFuncPtr ? TEXT("OK") : TEXT("FAILED"));
        UE_LOG(LogTemp, Error, TEXT("  GetDuplicateEntityError: %s"), GetDuplicateEntityErrorFuncPtr ? TEXT("OK") : TEXT("FAILED"));
        UE_LOG(LogTemp, Error, TEXT("  GetNilEntityError: %s"), GetNilEntityErrorFuncPtr ? TEXT("OK") : TEXT("FAILED"));
        UE_LOG(LogTemp, Error, TEXT("  GetEmptyIDError: %s"), GetEmptyIDErrorFuncPtr ? TEXT("OK") : TEXT("FAILED"));
        UE_LOG(LogTemp, Error, TEXT("  GetInvalidTypeError: %s"), GetInvalidTypeErrorFuncPtr ? TEXT("OK") : TEXT("FAILED"));
        UE_LOG(LogTemp, Error, TEXT("  ValidateEntityID: %s"), ValidateEntityIDFuncPtr ? TEXT("OK") : TEXT("FAILED"));
        UE_LOG(LogTemp, Error, TEXT("  ValidateEntityType: %s"), ValidateEntityTypeFuncPtr ? TEXT("OK") : TEXT("FAILED"));
        UE_LOG(LogTemp, Error, TEXT("  FreeString: %s"), FreeStringFuncPtr ? TEXT("OK") : TEXT("FAILED"));
        UE_LOG(LogTemp, Error, TEXT("  CreateEntityErrorComplete: %s"), CreateEntityErrorCompleteFuncPtr ? TEXT("OK") : TEXT("FAILED"));
    }
}

FString URPGEntitySubsystem::ConvertAndFreeString(ANSICHAR* CStr) const
{
    if (!CStr)
    {
        return FString();
    }
    
    FString Result = FString(ANSI_TO_TCHAR(CStr));
    
    // Free the C string memory
    if (FreeStringFuncPtr)
    {
        FreeStringFuncPtr(CStr);
    }
    
    return Result;
}

bool URPGEntitySubsystem::IsSafeToCallFunction() const
{
    // Following RPGDiceSubsystem pattern for shutdown safety
    return bFunctionsLoaded && ToolkitDLLHandle != nullptr;
}

// Automatic Cleanup Entity Error Implementation
FEntityErrorResult URPGEntitySubsystem::CreateEntityError(const FString& Operation, const FString& EntityType, const FString& EntityID, const FString& Message)
{
    if (!IsSafeToCallFunction() || !CreateEntityErrorCompleteFuncPtr)
    {
        return FEntityErrorResult(); // Invalid result
    }
    
    // Convert FString to ANSICHAR*
    FTCHARToUTF8 OpConverter(*Operation);
    FTCHARToUTF8 TypeConverter(*EntityType);
    FTCHARToUTF8 IDConverter(*EntityID);
    FTCHARToUTF8 MsgConverter(*Message);
    
    ANSICHAR* outOp;
    ANSICHAR* outType;
    ANSICHAR* outID;
    ANSICHAR* outMessage;
    
    int32 success = CreateEntityErrorCompleteFuncPtr(
        OpConverter.Get(),
        TypeConverter.Get(),
        IDConverter.Get(),
        MsgConverter.Get(),
        &outOp, &outType, &outID, &outMessage
    );
    
    if (success)
    {
        FEntityErrorResult Result(
            ConvertAndFreeString(outOp),
            ConvertAndFreeString(outType),
            ConvertAndFreeString(outID),
            ConvertAndFreeString(outMessage)
        );
        return Result;
    }
    
    return FEntityErrorResult(); // Invalid result
}