# S001 gRPC-Web HTTP Integration - Complete API Reference

## Overview

Complete UE integration for **rpg-api** services using the proven S001 pattern: gRPC-Web HTTP transport with manual protobuf serialization. This enables RPG game mechanics and D&D 5e character management directly from Unreal Engine Blueprint and C++.

**Integrated Services:**
- **DiceService**: Dice rolling mechanics and session management
- **CharacterService**: D&D 5e character creation and management

## Architecture

```
UE Blueprint/C++ → URPGCharacterServiceClient → HTTP POST → nginx:80 → envoy:8080 → rpg-api:50051
                                              ↓
                                    Manual Protobuf Wire Format
                                              ↓  
                                    No C++ protobuf dependency
```

**Key Components:**
- **URPGCharacterServiceClient**: Main service client (extends URPGWebClient)
- **FRPGCharacterProtobufConverter**: Manual protobuf serialization (no C++ protobuf library)
- **RPGCharacterTypes.h**: UE USTRUCT types mirroring proto messages exactly
- **S001 Pattern**: HTTP transport + protobuf wire format + nginx/envoy routing

# Proto Contract Endpoints

## DiceService - `dice.api.v1alpha1.DiceService`

**Base Path**: `/dice.api.v1alpha1.DiceService/{MethodName}`
**Client**: `URPGDiceServiceClient`

### CreateSession
**Purpose**: Create a new dice rolling session with unique identifier
**Request**: `FRPGCreateSessionRequest`
- `session_name` (string, optional): Human-readable session name

**Response**: `FRPGCreateSessionResponse`
- `session_id` (string): Unique session identifier
- `session_name` (string): Resolved session name
- `success` (bool): Operation success status

### Roll
**Purpose**: Roll dice with standard notation (e.g., "2d20", "1d6+3")  
**Request**: `FRPGRollRequest`
- `session_id` (string): Session identifier for grouping rolls
- `dice_notation` (string): Dice notation (2d20, 1d6+3, 4d6kh3, etc.)
- `description` (string, optional): Human-readable description of the roll

**Response**: `FRPGRollResponse`
- `roll_id` (string): Unique roll identifier
- `dice_notation` (string): Original dice notation
- `description` (string): Roll description
- `individual_rolls` (Array<int32>): Individual die results
- `total` (int32): Final calculated total
- `session_id` (string): Associated session
- `success` (bool): Operation success status

**Supported Dice Notation:**
- Basic: `2d20`, `1d6`, `3d8`  
- Modifiers: `1d20+5`, `2d6-1`
- Keep Highest: `4d6kh3` (roll 4d6, keep highest 3)
- Keep Lowest: `4d6kl3` (roll 4d6, keep lowest 3)
- Exploding: `1d6!` (reroll max values)

### ListRolls
**Purpose**: Get roll history for a session
**Request**: `FRPGListRollsRequest`
- `session_id` (string): Session to retrieve rolls from
- `page_size` (int32, optional): Number of rolls per page (default: 50)
- `page_token` (string, optional): Pagination token

**Response**: `FRPGListRollsResponse`
- `rolls` (Array<Roll>): Roll history with full details
- `next_page_token` (string): Token for next page (if more rolls exist)
- `total_size` (int32): Total number of rolls in session
- `success` (bool): Operation success status

---

## CharacterService - `dnd5e.api.v1alpha1.CharacterService`

**Base Path**: `/dnd5e.api.v1alpha1.CharacterService/{MethodName}`  
**Client**: `URPGCharacterServiceClient`

### 1. Draft Management

#### CreateDraft
**Purpose**: Create a new character draft for step-by-step character creation
**Request**: `FRPGCreateDraftRequest`
- `player_id` (string): Player identifier 
- `session_id` (string, optional): Game session identifier

**Response**: `FRPGCreateDraftResponse`
- `draft` (CharacterDraft): New draft with unique ID and default values
- `success` (bool): Operation success status

#### GetDraft  
**Purpose**: Retrieve an existing character draft by ID
**Request**: `FRPGGetDraftRequest`
- `draft_id` (string): Draft identifier to retrieve

**Response**: `FRPGGetDraftResponse` 
- `draft` (CharacterDraft): Complete draft with all current values
- `success` (bool): Operation success status

### 2. Character Customization

#### UpdateName
**Purpose**: Set the character's name
**Request**: `FRPGUpdateNameRequest`
- `draft_id` (string): Target draft identifier
- `name` (string): Character name

**Response**: `FRPGUpdateNameResponse`
- `draft` (CharacterDraft): Updated draft with new name
- `success` (bool): Operation success status

#### UpdateRace  
**Purpose**: Set the character's race and subrace
**Request**: `FRPGUpdateRaceRequest`
- `draft_id` (string): Target draft identifier
- `race` (ERPGRace): D&D 5e race enum (Human, Elf, Dwarf, etc.)
- `subrace` (ERPGSubrace, optional): D&D 5e subrace enum (High Elf, Hill Dwarf, etc.)

**Response**: `FRPGUpdateRaceResponse`
- `draft` (CharacterDraft): Updated draft with race/subrace applied
- `success` (bool): Operation success status

#### UpdateClass
**Purpose**: Set the character's class  
**Request**: `FRPGUpdateClassRequest`
- `draft_id` (string): Target draft identifier
- `class` (ERPGClass): D&D 5e class enum (Fighter, Wizard, Rogue, etc.)

**Response**: `FRPGUpdateClassResponse`
- `draft` (CharacterDraft): Updated draft with class applied
- `success` (bool): Operation success status

### 3. Ability Score System

#### RollAbilityScores
**Purpose**: Server-side rolling of 6 sets of 4d6 (drop lowest) for ability score assignment
**Request**: `FRPGRollAbilityScoresRequest`
- `draft_id` (string): Target draft identifier

**Response**: `FRPGRollAbilityScoresResponse`
- `rolls` (Array<AbilityScoreRoll>): 6 rolls with IDs, dice breakdown, and totals
- `expires_at` (int64): When these rolls expire (server-side validation)
- `success` (bool): Operation success status

**AbilityScoreRoll Structure:**
- `roll_id` (string): Unique server-generated roll identifier
- `dice` (Array<int32>): Individual dice values (e.g., [6, 4, 3, 1] → drops 1)
- `total` (int32): Final ability score value (sum of best 3 dice)

#### UpdateAbilityScores
**Purpose**: Assign ability scores to character (supports two methods)
**Request**: `FRPGUpdateAbilityScoresRequest`
- `draft_id` (string): Target draft identifier
- **Method 1 (Preferred)**: `roll_assignments` (RollAssignments) - Roll IDs from RollAbilityScores
- **Method 2 (Legacy)**: `ability_scores` (AbilityScores) - Raw values (limited validation)
- `use_roll_assignments` (bool): Flag indicating which method to use

**Response**: `FRPGUpdateAbilityScoresResponse`
- `draft` (CharacterDraft): Updated draft with ability scores applied
- `success` (bool): Operation success status

**RollAssignments Structure (Preferred Method):**
- `strength_roll_id` (string): Roll ID to assign to Strength
- `dexterity_roll_id` (string): Roll ID to assign to Dexterity  
- `constitution_roll_id` (string): Roll ID to assign to Constitution
- `intelligence_roll_id` (string): Roll ID to assign to Intelligence
- `wisdom_roll_id` (string): Roll ID to assign to Wisdom
- `charisma_roll_id` (string): Roll ID to assign to Charisma

### 4. Data Loading

#### ListRaces
**Purpose**: Get all available D&D 5e races for character creation
**Request**: `FRPGListRacesRequest`
- `page_size` (int32): Number of races per page (default: 20)
- `page_token` (string): Pagination token for next page
- `include_subraces` (bool): Include subrace information (default: true)

**Response**: `FRPGListRacesResponse`
- `races` (Array<RaceInfo>): Available races with details
- `next_page_token` (string): Token for next page (if more races exist)
- `total_size` (int32): Total number of races available
- `success` (bool): Operation success status

#### ListClasses
**Purpose**: Get all available D&D 5e classes for character creation
**Request**: `FRPGListClassesRequest`
- `page_size` (int32): Number of classes per page (default: 20)
- `page_token` (string): Pagination token for next page

**Response**: `FRPGListClassesResponse`
- `classes` (Array<ClassInfo>): Available classes with details  
- `next_page_token` (string): Token for next page (if more classes exist)
- `total_size` (int32): Total number of classes available
- `success` (bool): Operation success status

## Character Creation Workflow

**Recommended 7-Step Process** (following rpg-dnd5e-web pattern):

1. **CreateDraft**: Create new character draft
2. **ListRaces**: Get available races for selection
3. **UpdateRace**: Select race/subrace (e.g., Human)
4. **ListClasses**: Get available classes for selection  
5. **UpdateClass**: Select class (e.g., Fighter)
6. **RollAbilityScores**: Server rolls 6 ability scores
7. **UpdateAbilityScores**: Assign roll IDs to ability scores

**Complete Example:**
```cpp
// Step 1: Create Draft
FRPGCreateDraftRequest CreateRequest;
CreateRequest.PlayerId = TEXT("player-123");
CharacterService->CreateDraft(CreateRequest, CreateDelegate);

// Step 6: Roll Ability Scores  
FRPGRollAbilityScoresRequest RollRequest;
RollRequest.DraftId = DraftId;
CharacterService->RollAbilityScores(RollRequest, RollDelegate);

// Step 7: Assign Rolls (Preferred Method)
FRPGUpdateAbilityScoresRequest AbilityRequest;
AbilityRequest.DraftId = DraftId;
AbilityRequest.RollAssignments.StrengthRollId = Response.Rolls[0].RollId;
AbilityRequest.RollAssignments.DexterityRollId = Response.Rolls[1].RollId;
// ... assign remaining roll IDs
AbilityRequest.bUseRollAssignments = true;
CharacterService->UpdateAbilityScores(AbilityRequest, AbilityDelegate);
```

## Core Data Structures

### CharacterDraft
**Complete character state during creation process**
- `id` (string): Unique draft identifier
- `player_id` (string): Owner player identifier
- `session_id` (string): Associated game session
- `name` (string): Character name
- `race` (ERPGRace): Selected race
- `subrace` (ERPGSubrace): Selected subrace  
- `class` (ERPGClass): Selected class
- `background` (ERPGBackground): Selected background
- `alignment` (ERPGAlignment): Selected alignment
- `ability_scores` (AbilityScores): Final ability scores
- `expires_at` (int64): Draft expiration timestamp
- `created_at` (int64): Creation timestamp
- `updated_at` (int64): Last modification timestamp

### AbilityScores
**D&D 5e six core ability scores**
- `strength` (int32): Strength score (3-18, default: 10)
- `dexterity` (int32): Dexterity score (3-18, default: 10)  
- `constitution` (int32): Constitution score (3-18, default: 10)
- `intelligence` (int32): Intelligence score (3-18, default: 10)
- `wisdom` (int32): Wisdom score (3-18, default: 10)
- `charisma` (int32): Charisma score (3-18, default: 10)

# Service Client Classes

## URPGDiceServiceClient
**Inherits**: URPGWebClient  
**Purpose**: Dice rolling and session management

**Blueprint Methods:**
- `CreateSession(Request, Delegate)`: Create new dice session
- `Roll(Request, Delegate)`: Roll dice with notation
- `ListRolls(Request, Delegate)`: Get roll history
- `TestRollDice()`: Simple test function
- `TestCreateSession()`: Session creation test

**C++ Integration:**
```cpp
UPROPERTY()
URPGDiceServiceClient* DiceService;

void RollInitiative()
{
    FRPGRollRequest Request;
    Request.SessionId = CurrentSessionId;
    Request.DiceNotation = TEXT("1d20+3");
    Request.Description = TEXT("Initiative Roll");
    
    FRPGRollDelegate Delegate;
    Delegate.BindUFunction(this, FName("OnInitiativeRolled"));
    DiceService->Roll(Request, Delegate);
}
```

## URPGCharacterServiceClient  
**Inherits**: URPGWebClient
**Purpose**: D&D 5e character creation and management

**Blueprint Methods:**
- `CreateDraft(Request, Delegate)`: Create character draft
- `GetDraft(Request, Delegate)`: Retrieve existing draft
- `UpdateName/Race/Class(Request, Delegate)`: Character customization
- `RollAbilityScores(Request, Delegate)`: Server-side ability score rolling
- `UpdateAbilityScores(Request, Delegate)`: Assign ability scores
- `ListRaces/Classes(Request, Delegate)`: Get D&D 5e data
- `TestCharacterCreation()`: Complete workflow test

# Integration Patterns

## Blueprint Integration
All methods are `UFUNCTION(BlueprintCallable)` and can be used directly in Blueprint:

```
Get Character Service Client → Create Draft → (Success) → List Races → ...
```

### C++ Integration
```cpp
UCLASS()
class SESHAT_API AMyCharacterCreator : public AActor
{
    UPROPERTY()
    URPGCharacterServiceClient* CharacterService;
    
    void CreateNewCharacter()
    {
        if (!CharacterService) return;
        
        FRPGCreateDraftRequest Request;
        Request.PlayerId = GetPlayerID();
        
        FRPGCreateDraftDelegate Delegate;
        Delegate.BindUFunction(this, FName("OnDraftCreated"));
        
        CharacterService->CreateDraft(Request, Delegate);
    }
    
    UFUNCTION()
    void OnDraftCreated(bool bSuccess, const FRPGCreateDraftResponse& Response)
    {
        if (bSuccess)
        {
            CurrentDraftId = Response.Draft.Id;
            // Continue workflow...
        }
    }
};
```

# Quick Reference - All Available Methods

## DiceService Methods (3 endpoints)
| Method | Purpose | Request Type | Response Type |
|--------|---------|--------------|---------------|
| `CreateSession` | Create dice session | `FRPGCreateSessionRequest` | `FRPGCreateSessionResponse` |
| `Roll` | Roll dice with notation | `FRPGRollRequest` | `FRPGRollResponse` |  
| `ListRolls` | Get roll history | `FRPGListRollsRequest` | `FRPGListRollsResponse` |

## CharacterService Methods (8 endpoints)
| Method | Purpose | Request Type | Response Type |
|--------|---------|--------------|---------------|
| `CreateDraft` | Create character draft | `FRPGCreateDraftRequest` | `FRPGCreateDraftResponse` |
| `GetDraft` | Retrieve existing draft | `FRPGGetDraftRequest` | `FRPGGetDraftResponse` |
| `UpdateName` | Set character name | `FRPGUpdateNameRequest` | `FRPGUpdateNameResponse` |
| `UpdateRace` | Set race/subrace | `FRPGUpdateRaceRequest` | `FRPGUpdateRaceResponse` |
| `UpdateClass` | Set character class | `FRPGUpdateClassRequest` | `FRPGUpdateClassResponse` |
| `UpdateAbilityScores` | Set ability scores | `FRPGUpdateAbilityScoresRequest` | `FRPGUpdateAbilityScoresResponse` |
| `RollAbilityScores` | Server-side ability rolling | `FRPGRollAbilityScoresRequest` | `FRPGRollAbilityScoresResponse` |
| `ListRaces` | Get available races | `FRPGListRacesRequest` | `FRPGListRacesResponse` |
| `ListClasses` | Get available classes | `FRPGListClassesRequest` | `FRPGListClassesResponse` |

## Testing Functions
**DiceService Tests:**
- `TestRollDice()`: Simple dice roll test
- `TestCreateSession()`: Session creation test

**CharacterService Tests:**
- `TestCreateDraft()`: Simple draft creation test
- `TestListRaces()`: Simple race listing test  
- `TestCharacterCreation()`: Complete 7-step workflow test
- `GetLastTestResults()`: Get formatted test results for UI display

## Total Integration Summary
- **11 Proto Endpoints**: 3 DiceService + 8 CharacterService
- **2 Service Clients**: Full Blueprint and C++ integration
- **Manual Protobuf**: No external dependencies, UE-optimized
- **Production Ready**: Tested end-to-end workflows
- **S001 Pattern**: Proven architecture from DiceService

## Error Handling

All methods use consistent error handling:
- **HTTP-level errors**: Network issues, server unavailable
- **Protobuf-level errors**: Malformed requests/responses
- **Business-level errors**: Invalid draft IDs, expired rolls, validation failures

**Response Pattern:**
```cpp
if (bSuccess && !ResponseData.IsEmpty())
{
    bool bDeserializeSuccess = Converter::DeserializeResponse(ResponseData, Response);
    OnComplete.ExecuteIfBound(bDeserializeSuccess, Response);
}
else
{
    Response.bSuccess = false;
    OnComplete.ExecuteIfBound(false, Response);
}
```

## Implementation Notes

### Manual Protobuf Serialization
- **No C++ protobuf dependency**: Uses custom wire format implementation
- **Binary compatible**: Produces identical output to official protobuf libraries
- **UE-optimized**: Uses TArray<uint8>, FString, UE memory patterns
- **Proven pattern**: Same approach as working DiceService integration

### Roll ID Security
- **Server-side validation**: Roll IDs prevent score injection attacks
- **Expiration system**: Rolls expire after set time to prevent reuse
- **Audit trail**: Server tracks which rolls were used for which abilities
- **Flexibility**: Players can assign high rolls to preferred abilities

### Performance Characteristics
- **Lightweight**: No external dependencies beyond UE and HTTP
- **Fast serialization**: Manual implementation optimized for common cases
- **Efficient networking**: Binary protobuf format minimizes bandwidth
- **Blueprint-friendly**: All operations async with delegate callbacks

## Development Status

✅ **COMPLETE AND TESTED** - All endpoints implemented and working  
✅ **End-to-end workflow** - 7-step character creation fully functional  
✅ **Production ready** - Following proven S001 patterns from DiceService  
✅ **Blueprint accessible** - Full UE integration with proper delegates  

**Next Phase**: Character Creation Subsystem - Higher-level orchestration and UI integration