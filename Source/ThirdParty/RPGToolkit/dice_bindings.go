package main

/*
#include <stdlib.h>
*/
import "C"
import (
	"unsafe"
	
	"github.com/KirkDiggler/rpg-toolkit/dice"
)

// Dice system C bindings - exposes dice rolling using the actual toolkit API

//export CreateDiceRoller
func CreateDiceRoller() unsafe.Pointer {
	// Just return a success marker - we'll use the default roller
	marker := C.CString("roller_created")
	return unsafe.Pointer(marker)
}

//export RollDie
func RollDie(rollerPtr unsafe.Pointer, sides C.int) C.int {
	// Create a new roll with the specified number of sides using the toolkit
	roll, err := dice.NewRoll(1, int(sides))
	if err != nil {
		return C.int(-1)
	}
	
	// Get the rolled value
	result := roll.GetValue()
	return C.int(result)
}