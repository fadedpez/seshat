package main

/*
#include <stdlib.h>
*/
import "C"
import (
	"unsafe"

	"github.com/KirkDiggler/rpg-toolkit/dice"
)

// Dice system C bindings - exposes dice rolling, modifiers, and fairness testing

//export CreateDiceRoller
func CreateDiceRoller() unsafe.Pointer {
	roller := dice.NewRoller()
	return unsafe.Pointer(&roller)
}

//export RollDie
func RollDie(rollerPtr unsafe.Pointer, sides C.int) C.int {
	roller := (*dice.Roller)(rollerPtr)
	result := roller.Roll(int(sides))
	return C.int(result)
}

//export RollMultipleDice
func RollMultipleDice(rollerPtr unsafe.Pointer, count, sides C.int, results *C.int) C.int {
	roller := (*dice.Roller)(rollerPtr)
	
	// Convert C array to Go slice for results
	resultsSlice := (*[1000]C.int)(unsafe.Pointer(results))[:count:count]
	
	total := 0
	for i := 0; i < int(count); i++ {
		roll := roller.Roll(int(sides))
		resultsSlice[i] = C.int(roll)
		total += roll
	}
	
	return C.int(total)
}

//export CreateModifier
func CreateModifier(name *C.char, value C.int, modType C.int) unsafe.Pointer {
	nameStr := C.GoString(name)
	
	var modifier dice.Modifier
	switch modType {
	case 0: // Flat modifier
		modifier = dice.NewFlatModifier(nameStr, int(value))
	case 1: // Multiplier modifier  
		modifier = dice.NewMultiplierModifier(nameStr, float64(value))
	default:
		modifier = dice.NewFlatModifier(nameStr, int(value))
	}
	
	return unsafe.Pointer(&modifier)
}

//export ApplyModifier
func ApplyModifier(rollerPtr, modifierPtr unsafe.Pointer, baseValue C.int) C.int {
	// modifier := (*dice.Modifier)(modifierPtr)
	
	// In real implementation, we'd apply the modifier to the roll
	// For now, just return the base value plus a simple modifier
	return baseValue + 1
}

//export RollWithAdvantage
func RollWithAdvantage(rollerPtr unsafe.Pointer, sides C.int) C.int {
	roller := (*dice.Roller)(rollerPtr)
	
	roll1 := roller.Roll(int(sides))
	roll2 := roller.Roll(int(sides))
	
	if roll1 > roll2 {
		return C.int(roll1)
	}
	return C.int(roll2)
}

//export RollWithDisadvantage
func RollWithDisadvantage(rollerPtr unsafe.Pointer, sides C.int) C.int {
	roller := (*dice.Roller)(rollerPtr)
	
	roll1 := roller.Roll(int(sides))
	roll2 := roller.Roll(int(sides))
	
	if roll1 < roll2 {
		return C.int(roll1)
	}
	return C.int(roll2)
}

//export TestDiceFairness
func TestDiceFairness(rollerPtr unsafe.Pointer, sides, sampleSize C.int) C.float {
	roller := (*dice.Roller)(rollerPtr)
	
	// Perform fairness test by rolling many times and calculating variance
	rolls := make([]int, sampleSize)
	for i := 0; i < int(sampleSize); i++ {
		rolls[i] = roller.Roll(int(sides))
	}
	
	// Simple fairness calculation (chi-squared would be better)
	expected := float64(sampleSize) / float64(sides)
	distribution := make([]int, sides)
	
	for _, roll := range rolls {
		distribution[roll-1]++ // Convert to 0-based index
	}
	
	chiSquared := 0.0
	for _, observed := range distribution {
		diff := float64(observed) - expected
		chiSquared += (diff * diff) / expected
	}
	
	return C.float(chiSquared)
}