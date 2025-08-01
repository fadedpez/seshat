package main

import (
	"C"
	"encoding/json"
	"fmt"
	"strings"
	"sync/atomic"
	"time"

	"github.com/KirkDiggler/rpg-toolkit/rulebooks/dnd5e/character"
	"github.com/KirkDiggler/rpg-toolkit/rulebooks/dnd5e/class"
	"github.com/KirkDiggler/rpg-toolkit/rulebooks/dnd5e/constants"
	"github.com/KirkDiggler/rpg-toolkit/rulebooks/dnd5e/race"
	"github.com/KirkDiggler/rpg-toolkit/rulebooks/dnd5e/shared"
)

var characterCounter int64

// generateCharacterID creates unique character IDs using timestamp + counter
func generateCharacterID() string {
	timestamp := time.Now().Unix()
	counter := atomic.AddInt64(&characterCounter, 1)
	return fmt.Sprintf("char_%d_%d", timestamp, counter)
}

// createAbilityScores creates AbilityScores using the published toolkit API
func createAbilityScores(str, dex, con, intel, wis, cha int) (shared.AbilityScores, error) {
	config := &shared.AbilityScoreConfig{
		STR: str,
		DEX: dex,
		CON: con,
		INT: intel,
		WIS: wis,
		CHA: cha,
	}
	return shared.NewAbilityScores(config)
}

//export CreateCharacterComplete
func CreateCharacterComplete(
	// Input parameters (10 total)
	raceDataJSON *C.char,           // 1
	classDataJSON *C.char,          // 2
	backgroundDataJSON *C.char,     // 3
	characterName *C.char,          // 4
	str, dex, con, intel, wis, cha C.int, // 5,6,7,8,9,10

	// Output parameters - Core identity (4 total)
	outID **C.char,                 // 11
	outName **C.char,               // 12
	outLevel *C.int,                // 13
	outProficiencyBonus *C.int,     // 14

	// Output parameters - References (3 total)
	outRaceID **C.char,             // 15
	outClassID **C.char,            // 16
	outBackgroundID **C.char,       // 17

	// Output parameters - Ability scores (6 total)
	outStr, outDex, outCon, outInt, outWis, outCha *C.int, // 18,19,20,21,22,23

	// Output parameters - Physical (2 total)
	outSize **C.char,               // 24
	outSpeed *C.int,                // 25

	// Output parameters - Combat (4 total)
	outHP, outMaxHP, outAC, outInitiative *C.int, // 26,27,28,29

	// Output parameters - Arrays (2 total)
	outLanguages **C.char,          // 30 (concatenated string)
	outFeatures **C.char,           // 31 (concatenated string)

	// Output parameters - Error handling (1 total)
	outError **C.char, // 32
) C.int {
	// Parse input JSON data
	var raceData race.Data
	if err := json.Unmarshal([]byte(C.GoString(raceDataJSON)), &raceData); err != nil {
		*outError = C.CString(fmt.Sprintf("failed to parse race data: %v", err))
		return 0
	}

	var classData class.Data
	if err := json.Unmarshal([]byte(C.GoString(classDataJSON)), &classData); err != nil {
		*outError = C.CString(fmt.Sprintf("failed to parse class data: %v", err))
		return 0
	}

	var backgroundData shared.Background
	if err := json.Unmarshal([]byte(C.GoString(backgroundDataJSON)), &backgroundData); err != nil {
		*outError = C.CString(fmt.Sprintf("failed to parse background data: %v", err))
		return 0
	}

	// Build base ability scores using toolkit API
	baseAbilityScores, err := createAbilityScores(int(str), int(dex), int(con), int(intel), int(wis), int(cha))
	if err != nil {
		*outError = C.CString(fmt.Sprintf("invalid ability scores: %v", err))
		return 0
	}

	// Note: Racial bonuses will be applied by the toolkit during character creation
	finalAbilityScores := baseAbilityScores

	// Create character using toolkit
	characterID := generateCharacterID()
	char, err := character.NewFromCreationData(character.CreationData{
		ID:             characterID,
		Name:           C.GoString(characterName),
		RaceData:       &raceData,
		SubraceID:      "", // MVP: No subrace support yet
		ClassData:      &classData,
		BackgroundData: &backgroundData,
		AbilityScores:  finalAbilityScores,
		Choices:        make(map[string]any), // MVP: No choices yet
	})

	if err != nil {
		*outError = C.CString(fmt.Sprintf("character creation failed: %v", err))
		return 0
	}

	// Extract ALL values immediately (automatic cleanup pattern)
	charData := char.ToData()

	// Core identity
	*outID = C.CString(charData.ID)
	*outName = C.CString(charData.Name)
	*outLevel = C.int(charData.Level)
	
	// Calculate proficiency bonus from level (D&D 5e formula)
	proficiencyBonus := 2 + ((charData.Level - 1) / 4)
	*outProficiencyBonus = C.int(proficiencyBonus)

	// References (convert constant types to strings)
	*outRaceID = C.CString(string(charData.RaceID))
	*outClassID = C.CString(string(charData.ClassID))
	*outBackgroundID = C.CString(string(charData.BackgroundID))

	// Ability scores (final values after racial bonuses)
	*outStr = C.int(charData.AbilityScores[constants.STR])
	*outDex = C.int(charData.AbilityScores[constants.DEX])
	*outCon = C.int(charData.AbilityScores[constants.CON])
	*outInt = C.int(charData.AbilityScores[constants.INT])
	*outWis = C.int(charData.AbilityScores[constants.WIS])
	*outCha = C.int(charData.AbilityScores[constants.CHA])

	// Physical characteristics
	*outSize = C.CString(charData.Size)
	*outSpeed = C.int(charData.Speed)

	// Combat stats
	*outHP = C.int(charData.HitPoints)
	*outMaxHP = C.int(charData.MaxHitPoints)
	
	// Calculate basic AC (10 + Dex modifier) - equipment will modify this later
	dexMod := charData.AbilityScores.Modifier(constants.DEX)
	basicAC := 10 + dexMod
	*outAC = C.int(basicAC)
	
	// Initiative is Dex modifier
	*outInitiative = C.int(dexMod)

	// Arrays (concatenated strings for MVP)
	*outLanguages = C.CString(strings.Join(charData.Languages, ","))
	
	// Features not directly available - use empty string for MVP
	*outFeatures = C.CString("")

	// Success - no error
	*outError = C.CString("")
	return 1

	// char goes out of scope and gets GC'd naturally - no registry needed!
}

// No main function needed - this is a library