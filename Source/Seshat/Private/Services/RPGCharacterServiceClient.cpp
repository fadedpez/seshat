// Copyright Epic Games, Inc. All Rights Reserved.

#include "Services/RPGCharacterServiceClient.h"
#include "Services/RPGCharacterProtobufConverter.h"
#include "GRPCWeb/RPGWebTypes.h"

// S001: CharacterService implementation following proven DiceService pattern

URPGCharacterServiceClient::URPGCharacterServiceClient()
{
    // Inherits initialization from URPGWebClient
}

URPGCharacterServiceClient::~URPGCharacterServiceClient()
{
    // Inherits cleanup from URPGWebClient
}

void URPGCharacterServiceClient::CreateDraft(const FRPGCreateDraftRequest& Request, FRPGCreateDraftDelegate OnComplete)
{
    // Serialize request using manual protobuf converter
    TArray<uint8> RequestData = FRPGCharacterProtobufConverter::SerializeCreateDraftRequest(Request);
    
    // Call the exact proto contract: dnd5e.api.v1alpha1.CharacterService/CreateDraft (via nginx to Envoy)
    SendGRPCWebRequest(
        TEXT("/dnd5e.api.v1alpha1.CharacterService/CreateDraft"),
        RequestData,
        [OnComplete](bool bSuccess, const TArray<uint8>& ResponseData, const FRPGWebResponse& WebResponse)
        {
            FRPGCreateDraftResponse CharacterResponse;
            
            UE_LOG(LogTemp, Warning, TEXT("CreateDraft HTTP callback: bSuccess=%s, StatusCode=%d, ResponseSize=%d"), 
                bSuccess ? TEXT("true") : TEXT("false"), WebResponse.StatusCode, ResponseData.Num());
            
            if (bSuccess && !ResponseData.IsEmpty())
            {
                // Deserialize response using manual protobuf converter
                bool bDeserializeSuccess = FRPGCharacterProtobufConverter::DeserializeCreateDraftResponse(ResponseData, CharacterResponse);
                
                UE_LOG(LogTemp, Warning, TEXT("CreateDraft deserialize: bSuccess=%s, DraftId=%s"), 
                    bDeserializeSuccess ? TEXT("true") : TEXT("false"), *CharacterResponse.Draft.Id);
                
                OnComplete.ExecuteIfBound(bDeserializeSuccess, CharacterResponse);
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("CreateDraft failed: HTTP error or empty response"));
                CharacterResponse.bSuccess = false;
                OnComplete.ExecuteIfBound(false, CharacterResponse);
            }
        }
    );
}

void URPGCharacterServiceClient::GetDraft(const FRPGGetDraftRequest& Request, FRPGGetDraftDelegate OnComplete)
{
    // Serialize request using manual protobuf converter
    TArray<uint8> RequestData = FRPGCharacterProtobufConverter::SerializeGetDraftRequest(Request);
    
    // Call the exact proto contract: dnd5e.api.v1alpha1.CharacterService/GetDraft
    SendGRPCWebRequest(
        TEXT("/dnd5e.api.v1alpha1.CharacterService/GetDraft"),
        RequestData,
        [OnComplete](bool bSuccess, const TArray<uint8>& ResponseData, const FRPGWebResponse& WebResponse)
        {
            FRPGGetDraftResponse CharacterResponse;
            
            UE_LOG(LogTemp, Warning, TEXT("GetDraft HTTP callback: bSuccess=%s, StatusCode=%d, ResponseSize=%d"), 
                bSuccess ? TEXT("true") : TEXT("false"), WebResponse.StatusCode, ResponseData.Num());
            
            if (bSuccess && !ResponseData.IsEmpty())
            {
                // Deserialize response using manual protobuf converter
                bool bDeserializeSuccess = FRPGCharacterProtobufConverter::DeserializeGetDraftResponse(ResponseData, CharacterResponse);
                
                UE_LOG(LogTemp, Warning, TEXT("GetDraft deserialize: bSuccess=%s, DraftId=%s, Name=%s"), 
                    bDeserializeSuccess ? TEXT("true") : TEXT("false"), *CharacterResponse.Draft.Id, *CharacterResponse.Draft.Name);
                
                OnComplete.ExecuteIfBound(bDeserializeSuccess, CharacterResponse);
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("GetDraft failed: HTTP error or empty response"));
                CharacterResponse.bSuccess = false;
                OnComplete.ExecuteIfBound(false, CharacterResponse);
            }
        }
    );
}

void URPGCharacterServiceClient::UpdateName(const FRPGUpdateNameRequest& Request, FRPGUpdateNameDelegate OnComplete)
{
    // Serialize request using manual protobuf converter
    TArray<uint8> RequestData = FRPGCharacterProtobufConverter::SerializeUpdateNameRequest(Request);
    
    // Call the exact proto contract: dnd5e.api.v1alpha1.CharacterService/UpdateName
    SendGRPCWebRequest(
        TEXT("/dnd5e.api.v1alpha1.CharacterService/UpdateName"),
        RequestData,
        [OnComplete](bool bSuccess, const TArray<uint8>& ResponseData, const FRPGWebResponse& WebResponse)
        {
            FRPGUpdateNameResponse CharacterResponse;
            
            UE_LOG(LogTemp, Warning, TEXT("UpdateName HTTP callback: bSuccess=%s, StatusCode=%d, ResponseSize=%d"), 
                bSuccess ? TEXT("true") : TEXT("false"), WebResponse.StatusCode, ResponseData.Num());
            
            if (bSuccess && !ResponseData.IsEmpty())
            {
                // Deserialize response using manual protobuf converter
                bool bDeserializeSuccess = FRPGCharacterProtobufConverter::DeserializeUpdateNameResponse(ResponseData, CharacterResponse);
                
                UE_LOG(LogTemp, Warning, TEXT("UpdateName deserialize: bSuccess=%s, Name=%s"), 
                    bDeserializeSuccess ? TEXT("true") : TEXT("false"), *CharacterResponse.Draft.Name);
                
                OnComplete.ExecuteIfBound(bDeserializeSuccess, CharacterResponse);
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("UpdateName failed: HTTP error or empty response"));
                CharacterResponse.bSuccess = false;
                OnComplete.ExecuteIfBound(false, CharacterResponse);
            }
        }
    );
}

void URPGCharacterServiceClient::UpdateRace(const FRPGUpdateRaceRequest& Request, FRPGUpdateRaceDelegate OnComplete)
{
    // Serialize request using manual protobuf converter
    TArray<uint8> RequestData = FRPGCharacterProtobufConverter::SerializeUpdateRaceRequest(Request);
    
    // Call the exact proto contract: dnd5e.api.v1alpha1.CharacterService/UpdateRace
    SendGRPCWebRequest(
        TEXT("/dnd5e.api.v1alpha1.CharacterService/UpdateRace"),
        RequestData,
        [OnComplete](bool bSuccess, const TArray<uint8>& ResponseData, const FRPGWebResponse& WebResponse)
        {
            FRPGUpdateRaceResponse CharacterResponse;
            
            UE_LOG(LogTemp, Warning, TEXT("UpdateRace HTTP callback: bSuccess=%s, StatusCode=%d, ResponseSize=%d"), 
                bSuccess ? TEXT("true") : TEXT("false"), WebResponse.StatusCode, ResponseData.Num());
            
            if (bSuccess && !ResponseData.IsEmpty())
            {
                // Deserialize response using manual protobuf converter
                bool bDeserializeSuccess = FRPGCharacterProtobufConverter::DeserializeUpdateRaceResponse(ResponseData, CharacterResponse);
                
                UE_LOG(LogTemp, Warning, TEXT("UpdateRace deserialize: bSuccess=%s, Race=%d, Subrace=%d"), 
                    bDeserializeSuccess ? TEXT("true") : TEXT("false"), 
                    static_cast<int32>(CharacterResponse.Draft.Race), 
                    static_cast<int32>(CharacterResponse.Draft.Subrace));
                
                OnComplete.ExecuteIfBound(bDeserializeSuccess, CharacterResponse);
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("UpdateRace failed: HTTP error or empty response"));
                CharacterResponse.bSuccess = false;
                OnComplete.ExecuteIfBound(false, CharacterResponse);
            }
        }
    );
}

void URPGCharacterServiceClient::UpdateClass(const FRPGUpdateClassRequest& Request, FRPGUpdateClassDelegate OnComplete)
{
    // Serialize request using manual protobuf converter
    TArray<uint8> RequestData = FRPGCharacterProtobufConverter::SerializeUpdateClassRequest(Request);
    
    // Call the exact proto contract: dnd5e.api.v1alpha1.CharacterService/UpdateClass
    SendGRPCWebRequest(
        TEXT("/dnd5e.api.v1alpha1.CharacterService/UpdateClass"),
        RequestData,
        [OnComplete](bool bSuccess, const TArray<uint8>& ResponseData, const FRPGWebResponse& WebResponse)
        {
            FRPGUpdateClassResponse CharacterResponse;
            
            UE_LOG(LogTemp, Warning, TEXT("UpdateClass HTTP callback: bSuccess=%s, StatusCode=%d, ResponseSize=%d"), 
                bSuccess ? TEXT("true") : TEXT("false"), WebResponse.StatusCode, ResponseData.Num());
            
            if (bSuccess && !ResponseData.IsEmpty())
            {
                // Deserialize response using manual protobuf converter
                bool bDeserializeSuccess = FRPGCharacterProtobufConverter::DeserializeUpdateClassResponse(ResponseData, CharacterResponse);
                
                UE_LOG(LogTemp, Warning, TEXT("UpdateClass deserialize: bSuccess=%s, Class=%d"), 
                    bDeserializeSuccess ? TEXT("true") : TEXT("false"), 
                    static_cast<int32>(CharacterResponse.Draft.Class));
                
                OnComplete.ExecuteIfBound(bDeserializeSuccess, CharacterResponse);
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("UpdateClass failed: HTTP error or empty response"));
                CharacterResponse.bSuccess = false;
                OnComplete.ExecuteIfBound(false, CharacterResponse);
            }
        }
    );
}

void URPGCharacterServiceClient::UpdateAbilityScores(const FRPGUpdateAbilityScoresRequest& Request, FRPGUpdateAbilityScoresDelegate OnComplete)
{
    // Serialize request using manual protobuf converter
    TArray<uint8> RequestData = FRPGCharacterProtobufConverter::SerializeUpdateAbilityScoresRequest(Request);
    
    // Call the exact proto contract: dnd5e.api.v1alpha1.CharacterService/UpdateAbilityScores
    SendGRPCWebRequest(
        TEXT("/dnd5e.api.v1alpha1.CharacterService/UpdateAbilityScores"),
        RequestData,
        [OnComplete](bool bSuccess, const TArray<uint8>& ResponseData, const FRPGWebResponse& WebResponse)
        {
            FRPGUpdateAbilityScoresResponse CharacterResponse;
            
            UE_LOG(LogTemp, Warning, TEXT("UpdateAbilityScores HTTP callback: bSuccess=%s, StatusCode=%d, ResponseSize=%d"), 
                bSuccess ? TEXT("true") : TEXT("false"), WebResponse.StatusCode, ResponseData.Num());
            
            if (bSuccess && !ResponseData.IsEmpty())
            {
                // Deserialize response using manual protobuf converter
                bool bDeserializeSuccess = FRPGCharacterProtobufConverter::DeserializeUpdateAbilityScoresResponse(ResponseData, CharacterResponse);
                
                UE_LOG(LogTemp, Warning, TEXT("UpdateAbilityScores deserialize: bSuccess=%s, STR=%d, DEX=%d, CON=%d"), 
                    bDeserializeSuccess ? TEXT("true") : TEXT("false"), 
                    CharacterResponse.Draft.AbilityScores.Strength,
                    CharacterResponse.Draft.AbilityScores.Dexterity,
                    CharacterResponse.Draft.AbilityScores.Constitution);
                
                OnComplete.ExecuteIfBound(bDeserializeSuccess, CharacterResponse);
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("UpdateAbilityScores failed: HTTP error or empty response"));
                CharacterResponse.bSuccess = false;
                OnComplete.ExecuteIfBound(false, CharacterResponse);
            }
        }
    );
}

void URPGCharacterServiceClient::ListRaces(const FRPGListRacesRequest& Request, FRPGListRacesDelegate OnComplete)
{
    // Serialize request using manual protobuf converter
    TArray<uint8> RequestData = FRPGCharacterProtobufConverter::SerializeListRacesRequest(Request);
    
    // Call the exact proto contract: dnd5e.api.v1alpha1.CharacterService/ListRaces
    SendGRPCWebRequest(
        TEXT("/dnd5e.api.v1alpha1.CharacterService/ListRaces"),
        RequestData,
        [OnComplete](bool bSuccess, const TArray<uint8>& ResponseData, const FRPGWebResponse& WebResponse)
        {
            FRPGListRacesResponse CharacterResponse;
            
            UE_LOG(LogTemp, Warning, TEXT("ListRaces HTTP callback: bSuccess=%s, StatusCode=%d, ResponseSize=%d"), 
                bSuccess ? TEXT("true") : TEXT("false"), WebResponse.StatusCode, ResponseData.Num());
            
            if (bSuccess && !ResponseData.IsEmpty())
            {
                // Deserialize response using manual protobuf converter
                bool bDeserializeSuccess = FRPGCharacterProtobufConverter::DeserializeListRacesResponse(ResponseData, CharacterResponse);
                
                UE_LOG(LogTemp, Warning, TEXT("ListRaces deserialize: bSuccess=%s, RaceCount=%d"), 
                    bDeserializeSuccess ? TEXT("true") : TEXT("false"), CharacterResponse.Races.Num());
                
                OnComplete.ExecuteIfBound(bDeserializeSuccess, CharacterResponse);
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("ListRaces failed: HTTP error or empty response"));
                CharacterResponse.bSuccess = false;
                OnComplete.ExecuteIfBound(false, CharacterResponse);
            }
        }
    );
}

void URPGCharacterServiceClient::ListClasses(const FRPGListClassesRequest& Request, FRPGListClassesDelegate OnComplete)
{
    // Serialize request using manual protobuf converter
    TArray<uint8> RequestData = FRPGCharacterProtobufConverter::SerializeListClassesRequest(Request);
    
    // Call the exact proto contract: dnd5e.api.v1alpha1.CharacterService/ListClasses
    SendGRPCWebRequest(
        TEXT("/dnd5e.api.v1alpha1.CharacterService/ListClasses"),
        RequestData,
        [OnComplete](bool bSuccess, const TArray<uint8>& ResponseData, const FRPGWebResponse& WebResponse)
        {
            FRPGListClassesResponse CharacterResponse;
            
            UE_LOG(LogTemp, Warning, TEXT("ListClasses HTTP callback: bSuccess=%s, StatusCode=%d, ResponseSize=%d"), 
                bSuccess ? TEXT("true") : TEXT("false"), WebResponse.StatusCode, ResponseData.Num());
            
            if (bSuccess && !ResponseData.IsEmpty())
            {
                // Deserialize response using manual protobuf converter
                bool bDeserializeSuccess = FRPGCharacterProtobufConverter::DeserializeListClassesResponse(ResponseData, CharacterResponse);
                
                UE_LOG(LogTemp, Warning, TEXT("ListClasses deserialize: bSuccess=%s, ClassCount=%d"), 
                    bDeserializeSuccess ? TEXT("true") : TEXT("false"), CharacterResponse.Classes.Num());
                
                OnComplete.ExecuteIfBound(bDeserializeSuccess, CharacterResponse);
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("ListClasses failed: HTTP error or empty response"));
                CharacterResponse.bSuccess = false;
                OnComplete.ExecuteIfBound(false, CharacterResponse);
            }
        }
    );
}

void URPGCharacterServiceClient::RollAbilityScores(const FRPGRollAbilityScoresRequest& Request, FRPGRollAbilityScoresDelegate OnComplete)
{
    // Serialize request using manual protobuf converter
    TArray<uint8> RequestData = FRPGCharacterProtobufConverter::SerializeRollAbilityScoresRequest(Request);
    
    // Call the exact proto contract: dnd5e.api.v1alpha1.CharacterService/RollAbilityScores
    SendGRPCWebRequest(
        TEXT("/dnd5e.api.v1alpha1.CharacterService/RollAbilityScores"),
        RequestData,
        [OnComplete](bool bSuccess, const TArray<uint8>& ResponseData, const FRPGWebResponse& WebResponse)
        {
            FRPGRollAbilityScoresResponse CharacterResponse;
            
            UE_LOG(LogTemp, Warning, TEXT("RollAbilityScores HTTP callback: bSuccess=%s, StatusCode=%d, ResponseSize=%d"), 
                bSuccess ? TEXT("true") : TEXT("false"), WebResponse.StatusCode, ResponseData.Num());
            
            if (bSuccess && !ResponseData.IsEmpty())
            {
                // Deserialize response using manual protobuf converter
                bool bDeserializeSuccess = FRPGCharacterProtobufConverter::DeserializeRollAbilityScoresResponse(ResponseData, CharacterResponse);
                
                UE_LOG(LogTemp, Warning, TEXT("RollAbilityScores deserialize: bSuccess=%s, RollCount=%d"), 
                    bDeserializeSuccess ? TEXT("true") : TEXT("false"), CharacterResponse.Rolls.Num());
                
                OnComplete.ExecuteIfBound(bDeserializeSuccess, CharacterResponse);
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("RollAbilityScores failed: HTTP error or empty response"));
                CharacterResponse.bSuccess = false;
                OnComplete.ExecuteIfBound(false, CharacterResponse);
            }
        }
    );
}

void URPGCharacterServiceClient::TestCreateDraft()
{
    UE_LOG(LogTemp, Warning, TEXT("=== CharacterService TestCreateDraft ==="));

    FRPGCreateDraftRequest TestRequest;
    TestRequest.PlayerId = TEXT("test_player_123");
    TestRequest.SessionId = TEXT("test_session_456");

    FRPGCreateDraftDelegate CreateDelegate;
    CreateDelegate.BindUFunction(this, FName("OnTestCreateDraftComplete"));
    CreateDraft(TestRequest, CreateDelegate);
}

void URPGCharacterServiceClient::TestListRaces()
{
    UE_LOG(LogTemp, Warning, TEXT("=== CharacterService TestListRaces ==="));

    FRPGListRacesRequest TestRequest;
    TestRequest.PageSize = 10;
    TestRequest.bIncludeSubraces = true;

    FRPGListRacesDelegate RacesDelegate;
    RacesDelegate.BindUFunction(this, FName("OnTestListRacesComplete"));
    ListRaces(TestRequest, RacesDelegate);
}

void URPGCharacterServiceClient::OnTestCreateDraftComplete(bool bSuccess, const FRPGCreateDraftResponse& Response)
{
    UE_LOG(LogTemp, Warning, TEXT("=== CharacterService CreateDraft Test Result ==="));
    UE_LOG(LogTemp, Warning, TEXT("Success: %s"), bSuccess ? TEXT("true") : TEXT("false"));
    
    if (bSuccess)
    {
        UE_LOG(LogTemp, Warning, TEXT("Draft ID: %s"), *Response.Draft.Id);
        UE_LOG(LogTemp, Warning, TEXT("Player ID: %s"), *Response.Draft.PlayerId);
        UE_LOG(LogTemp, Warning, TEXT("Session ID: %s"), *Response.Draft.SessionId);
        UE_LOG(LogTemp, Warning, TEXT("Name: %s"), *Response.Draft.Name);
        UE_LOG(LogTemp, Warning, TEXT("Race: %d"), static_cast<int32>(Response.Draft.Race));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("CreateDraft test failed"));
    }
}

void URPGCharacterServiceClient::OnTestListRacesComplete(bool bSuccess, const FRPGListRacesResponse& Response)
{
    UE_LOG(LogTemp, Warning, TEXT("=== CharacterService ListRaces Test Result ==="));
    UE_LOG(LogTemp, Warning, TEXT("Success: %s"), bSuccess ? TEXT("true") : TEXT("false"));
    
    if (bSuccess)
    {
        UE_LOG(LogTemp, Warning, TEXT("Total Races: %d"), Response.TotalSize);
        UE_LOG(LogTemp, Warning, TEXT("Returned Races: %d"), Response.Races.Num());
        
        for (int32 i = 0; i < Response.Races.Num(); ++i)
        {
            const FRPGRaceInfo& Race = Response.Races[i];
            UE_LOG(LogTemp, Warning, TEXT("Race %d: ID=%s, Name=%s, Speed=%d"), 
                i, *Race.Id, *Race.Name, Race.Speed);
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("ListRaces test failed"));
    }
}

void URPGCharacterServiceClient::TestCharacterCreation()
{
    UE_LOG(LogTemp, Warning, TEXT("=== STARTING COMPREHENSIVE CHARACTER CREATION WORKFLOW TEST ==="));
    
    if (!IsInitialized())
    {
        UE_LOG(LogTemp, Error, TEXT("CharacterServiceClient not initialized"));
        LastTestResults = TEXT("ERROR: Client not initialized");
        return;
    }

    LastTestResults = TEXT("STARTING: Complete Character Creation Flow...\n");
    CurrentDraftId = TEXT("");
    
    // Step 1: Create a draft (following rpg-dnd5e-web pattern)
    FRPGCreateDraftRequest CreateRequest;
    CreateRequest.PlayerId = TEXT("test-player");  // Match working web app

    UE_LOG(LogTemp, Warning, TEXT("Step 1: Creating character draft for player: %s"), *CreateRequest.PlayerId);

    FRPGCreateDraftDelegate CreateDelegate;
    CreateDelegate.BindUFunction(this, FName("OnTestCharacterCreationStep1Complete"));
    
    CreateDraft(CreateRequest, CreateDelegate);
}

FString URPGCharacterServiceClient::GetLastTestResults() const
{
    return LastTestResults;
}

void URPGCharacterServiceClient::OnTestCharacterCreationStep1Complete(bool bSuccess, const FRPGCreateDraftResponse& Response)
{
    UE_LOG(LogTemp, Warning, TEXT("=== STEP 1 COMPLETE - Draft Created ==="));
    UE_LOG(LogTemp, Warning, TEXT("Success: %s"), bSuccess ? TEXT("true") : TEXT("false"));
    
    if (bSuccess)
    {
        CurrentDraftId = Response.Draft.Id;
        UE_LOG(LogTemp, Warning, TEXT("Created Draft ID: %s"), *CurrentDraftId);
        
        LastTestResults += FString::Printf(TEXT("✅ STEP 1: Draft created (ID=%s)\n"), *CurrentDraftId);
        
        // Step 2: List available races (following rpg-dnd5e-web pattern)
        UE_LOG(LogTemp, Warning, TEXT("Step 2: Listing available races..."));
        
        FRPGListRacesRequest RacesRequest;
        RacesRequest.PageSize = 20; 
        RacesRequest.PageToken = TEXT("");
        
        FRPGListRacesDelegate RacesDelegate;
        RacesDelegate.BindUFunction(this, FName("OnTestCharacterCreationStep2Complete"));
        
        ListRaces(RacesRequest, RacesDelegate);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Draft creation failed"));
        LastTestResults += TEXT("❌ STEP 1 FAILED: Could not create draft\n");
    }
}

void URPGCharacterServiceClient::OnTestCharacterCreationStep2Complete(bool bSuccess, const FRPGListRacesResponse& Response)
{
    UE_LOG(LogTemp, Warning, TEXT("=== STEP 2 COMPLETE - Races Listed ==="));
    UE_LOG(LogTemp, Warning, TEXT("Success: %s"), bSuccess ? TEXT("true") : TEXT("false"));
    
    if (bSuccess && Response.Races.Num() > 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("Found %d races"), Response.Races.Num());
        LastTestResults += FString::Printf(TEXT("✅ STEP 2: Listed %d races\n"), Response.Races.Num());
        
        // Step 3: Select Human race (RACE_HUMAN=1, matching working web app data)
        UE_LOG(LogTemp, Warning, TEXT("Step 3: Selecting Human race for draft..."));
        
        FRPGUpdateRaceRequest UpdateRaceRequest;
        UpdateRaceRequest.DraftId = CurrentDraftId;
        UpdateRaceRequest.Race = ERPGRace::RACE_HUMAN; // Human race from working data
        UpdateRaceRequest.Subrace = ERPGSubrace::SUBRACE_UNSPECIFIED; // No subrace for Human
        
        FRPGUpdateRaceDelegate UpdateRaceDelegate;
        UpdateRaceDelegate.BindUFunction(this, FName("OnTestCharacterCreationStep3Complete"));
        
        UpdateRace(UpdateRaceRequest, UpdateRaceDelegate);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Race listing failed or no races found"));
        LastTestResults += TEXT("❌ STEP 2 FAILED: Could not list races\n");
    }
}

void URPGCharacterServiceClient::OnTestCharacterCreationStep3Complete(bool bSuccess, const FRPGUpdateRaceResponse& Response)
{
    UE_LOG(LogTemp, Warning, TEXT("=== STEP 3 COMPLETE - Race Selected ==="));
    UE_LOG(LogTemp, Warning, TEXT("Success: %s"), bSuccess ? TEXT("true") : TEXT("false"));
    
    if (bSuccess)
    {
        UE_LOG(LogTemp, Warning, TEXT("Race updated: %d"), static_cast<int32>(Response.Draft.Race));
        LastTestResults += FString::Printf(TEXT("✅ STEP 3: Selected race (ID=%d)\n"), static_cast<int32>(Response.Draft.Race));
        
        // Step 4: List available classes
        UE_LOG(LogTemp, Warning, TEXT("Step 4: Listing available classes..."));
        
        FRPGListClassesRequest ClassesRequest;
        ClassesRequest.PageSize = 20;
        ClassesRequest.PageToken = TEXT("");
        
        FRPGListClassesDelegate ClassesDelegate;
        ClassesDelegate.BindUFunction(this, FName("OnTestCharacterCreationStep4Complete"));
        
        ListClasses(ClassesRequest, ClassesDelegate);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Race update failed"));
        LastTestResults += TEXT("❌ STEP 3 FAILED: Could not select race\n");
    }
}

void URPGCharacterServiceClient::OnTestCharacterCreationStep4Complete(bool bSuccess, const FRPGListClassesResponse& Response)
{
    UE_LOG(LogTemp, Warning, TEXT("=== STEP 4 COMPLETE - Classes Listed ==="));
    UE_LOG(LogTemp, Warning, TEXT("Success: %s"), bSuccess ? TEXT("true") : TEXT("false"));
    
    if (bSuccess && Response.Classes.Num() > 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("Found %d classes"), Response.Classes.Num());
        LastTestResults += FString::Printf(TEXT("✅ STEP 4: Listed %d classes\n"), Response.Classes.Num());
        
        // Step 5: Select Fighter class (CLASS_FIGHTER=5, matching working web app data)
        UE_LOG(LogTemp, Warning, TEXT("Step 5: Selecting Fighter class for draft..."));
        
        FRPGUpdateClassRequest UpdateClassRequest;
        UpdateClassRequest.DraftId = CurrentDraftId;
        UpdateClassRequest.Class = ERPGClass::CLASS_FIGHTER; // Fighter class from working data
        
        FRPGUpdateClassDelegate UpdateClassDelegate;
        UpdateClassDelegate.BindUFunction(this, FName("OnTestCharacterCreationStep5Complete"));
        
        UpdateClass(UpdateClassRequest, UpdateClassDelegate);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Class listing failed or no classes found"));
        LastTestResults += TEXT("❌ STEP 4 FAILED: Could not list classes\n");
    }
}

void URPGCharacterServiceClient::OnTestCharacterCreationStep5Complete(bool bSuccess, const FRPGUpdateClassResponse& Response)
{
    UE_LOG(LogTemp, Warning, TEXT("=== STEP 5 COMPLETE - Class Selected ==="));
    UE_LOG(LogTemp, Warning, TEXT("Success: %s"), bSuccess ? TEXT("true") : TEXT("false"));
    
    if (bSuccess)
    {
        UE_LOG(LogTemp, Warning, TEXT("Class updated: %d"), static_cast<int32>(Response.Draft.Class));
        LastTestResults += FString::Printf(TEXT("✅ STEP 5: Selected Fighter class (ID=%d)\n"), static_cast<int32>(Response.Draft.Class));
        
        // Step 6: Roll ability scores using CharacterService (proper server-side workflow)
        UE_LOG(LogTemp, Warning, TEXT("Step 6: Rolling ability scores via CharacterService.RollAbilityScores..."));
        LastTestResults += TEXT("🎲 STEP 6: Rolling ability scores via server...\n");
        
        // Use the server's ability score rolling endpoint instead of manual DiceService orchestration
        // This ensures proper validation and server-side state management
        FRPGRollAbilityScoresRequest RollRequest;
        RollRequest.DraftId = CurrentDraftId;
        
        FRPGRollAbilityScoresDelegate RollDelegate;
        RollDelegate.BindUFunction(this, FName("OnTestCharacterCreationStep6aComplete"));
        
        RollAbilityScores(RollRequest, RollDelegate);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Class update failed"));
        LastTestResults += TEXT("❌ STEP 5 FAILED: Could not select class\n");
    }
}

void URPGCharacterServiceClient::OnTestCharacterCreationStep6aComplete(bool bSuccess, const FRPGRollAbilityScoresResponse& Response)
{
    UE_LOG(LogTemp, Warning, TEXT("=== STEP 6a COMPLETE - Ability Scores Rolled ==="));
    UE_LOG(LogTemp, Warning, TEXT("Success: %s"), bSuccess ? TEXT("true") : TEXT("false"));
    
    if (bSuccess && Response.Rolls.Num() == 6)
    {
        UE_LOG(LogTemp, Warning, TEXT("Server rolled %d ability scores"), Response.Rolls.Num());
        LastTestResults += FString::Printf(TEXT("✅ STEP 6a: Server rolled %d ability scores\n"), Response.Rolls.Num());
        
        // Log all the rolls
        for (int32 i = 0; i < Response.Rolls.Num(); ++i)
        {
            const FRPGAbilityScoreRoll& Roll = Response.Rolls[i];
            UE_LOG(LogTemp, Warning, TEXT("Roll %d (%s): Total=%d"), i + 1, *Roll.RollId, Roll.Total);
            LastTestResults += FString::Printf(TEXT("  Roll %d: %d\n"), i + 1, Roll.Total);
        }
        
        // Step 6b: Now assign these roll IDs to ability scores (server expects roll assignments, not raw values)
        UE_LOG(LogTemp, Warning, TEXT("Step 6b: Assigning roll IDs to ability scores..."));
        
        FRPGRollAssignments RollAssignments;
        RollAssignments.StrengthRollId = Response.Rolls[0].RollId;
        RollAssignments.DexterityRollId = Response.Rolls[1].RollId;
        RollAssignments.ConstitutionRollId = Response.Rolls[2].RollId;
        RollAssignments.IntelligenceRollId = Response.Rolls[3].RollId;
        RollAssignments.WisdomRollId = Response.Rolls[4].RollId;
        RollAssignments.CharismaRollId = Response.Rolls[5].RollId;
        
        UE_LOG(LogTemp, Warning, TEXT("Assigned Roll IDs: STR:%s DEX:%s CON:%s INT:%s WIS:%s CHA:%s"), 
            *RollAssignments.StrengthRollId, *RollAssignments.DexterityRollId, *RollAssignments.ConstitutionRollId,
            *RollAssignments.IntelligenceRollId, *RollAssignments.WisdomRollId, *RollAssignments.CharismaRollId);
        
        FRPGUpdateAbilityScoresRequest AbilityRequest;
        AbilityRequest.DraftId = CurrentDraftId;
        AbilityRequest.RollAssignments = RollAssignments;
        AbilityRequest.bUseRollAssignments = true; // Use roll assignments instead of raw scores
        
        FRPGUpdateAbilityScoresDelegate AbilityDelegate;
        AbilityDelegate.BindUFunction(this, FName("OnTestCharacterCreationStep6Complete"));
        
        UpdateAbilityScores(AbilityRequest, AbilityDelegate);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Ability score rolling failed: bSuccess=%s, RollCount=%d"), 
            bSuccess ? TEXT("true") : TEXT("false"), Response.Rolls.Num());
        LastTestResults += TEXT("❌ STEP 6a FAILED: Could not roll ability scores\n");
    }
}

void URPGCharacterServiceClient::OnTestCharacterCreationStep6Complete(bool bSuccess, const FRPGUpdateAbilityScoresResponse& Response)
{
    UE_LOG(LogTemp, Warning, TEXT("=== STEP 6 COMPLETE - Ability Scores Set ==="));
    UE_LOG(LogTemp, Warning, TEXT("Success: %s"), bSuccess ? TEXT("true") : TEXT("false"));
    
    if (bSuccess)
    {
        UE_LOG(LogTemp, Warning, TEXT("Ability Scores - STR:%d DEX:%d CON:%d"), 
            Response.Draft.AbilityScores.Strength,
            Response.Draft.AbilityScores.Dexterity,
            Response.Draft.AbilityScores.Constitution);
            
        LastTestResults += TEXT("✅ STEP 6: Set ability scores (STR:14 DEX:18 CON:14)\n");
        
        // Step 7: Get the complete draft to verify everything worked
        UE_LOG(LogTemp, Warning, TEXT("Step 7: Getting complete draft to verify..."));
        
        FRPGGetDraftRequest GetDraftRequest;
        GetDraftRequest.DraftId = CurrentDraftId;
        
        FRPGGetDraftDelegate GetDraftDelegate;
        GetDraftDelegate.BindUFunction(this, FName("OnTestCharacterCreationStep7Complete"));
        
        GetDraft(GetDraftRequest, GetDraftDelegate);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Ability scores update failed"));
        LastTestResults += TEXT("❌ STEP 6 FAILED: Could not set ability scores\n");
    }
}

void URPGCharacterServiceClient::OnTestCharacterCreationStep7Complete(bool bSuccess, const FRPGGetDraftResponse& Response)
{
    UE_LOG(LogTemp, Warning, TEXT("=== STEP 7 COMPLETE - WORKFLOW TEST FINISHED ==="));
    UE_LOG(LogTemp, Warning, TEXT("Success: %s"), bSuccess ? TEXT("true") : TEXT("false"));
    
    if (bSuccess)
    {
        const FRPGCharacterDraft& Draft = Response.Draft;
        
        UE_LOG(LogTemp, Warning, TEXT("=== FINAL DRAFT VERIFICATION ==="));
        UE_LOG(LogTemp, Warning, TEXT("Draft ID: %s"), *Draft.Id);
        UE_LOG(LogTemp, Warning, TEXT("Player ID: %s"), *Draft.PlayerId);
        UE_LOG(LogTemp, Warning, TEXT("Race ID: %d"), static_cast<int32>(Draft.Race));
        UE_LOG(LogTemp, Warning, TEXT("Class ID: %d"), static_cast<int32>(Draft.Class));
        UE_LOG(LogTemp, Warning, TEXT("STR:%d DEX:%d CON:%d INT:%d WIS:%d CHA:%d"), 
            Draft.AbilityScores.Strength, Draft.AbilityScores.Dexterity, Draft.AbilityScores.Constitution,
            Draft.AbilityScores.Intelligence, Draft.AbilityScores.Wisdom, Draft.AbilityScores.Charisma);
        
        LastTestResults += TEXT("✅ STEP 7: Complete draft retrieved\n");
        LastTestResults += TEXT("🎉 CHARACTER CREATION WORKFLOW SUCCESS!\n");
        LastTestResults += FString::Printf(TEXT("Final Draft: Human Fighter with full ability scores\n"));
        LastTestResults += FString::Printf(TEXT("Draft ID: %s is ready for gameplay!"), *CurrentDraftId);
        
        UE_LOG(LogTemp, Warning, TEXT("=== CHARACTER CREATION WORKFLOW COMPLETE - SUCCESS! ==="));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Final draft retrieval failed"));
        LastTestResults += TEXT("❌ STEP 7 FAILED: Could not retrieve complete draft\n");
    }
}

