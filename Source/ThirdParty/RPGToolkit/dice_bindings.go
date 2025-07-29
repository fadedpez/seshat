package main

/*
#include <stdlib.h>
*/
import "C"
import (
	"unsafe"

	"github.com/KirkDiggler/rpg-toolkit/dice"
)

// Dice Package Complete Exposure - C bindings for the actual toolkit dice package

// Roller Interface Functions
// These expose the actual dice.Roller interface from dice/roller.go

//export CreateCryptoRoller
func CreateCryptoRoller() unsafe.Pointer {
	roller := &dice.CryptoRoller{}
	return unsafe.Pointer(roller)
}

//export RollerRoll
func RollerRoll(rollerPtr unsafe.Pointer, size C.int) C.int {
	roller := (*dice.CryptoRoller)(rollerPtr)
	result, err := roller.Roll(int(size))
	if err != nil {
		return -1 // Error indicator
	}
	return C.int(result)
}

//export RollerRollN
func RollerRollN(rollerPtr unsafe.Pointer, count, size C.int, results *C.int) C.int {
	roller := (*dice.CryptoRoller)(rollerPtr)
	rolls, err := roller.RollN(int(count), int(size))
	if err != nil {
		return -1 // Error indicator
	}

	// Copy results to C array
	resultsSlice := (*[1 << 30]C.int)(unsafe.Pointer(results))[:count:count]
	for i, roll := range rolls {
		resultsSlice[i] = C.int(roll)
	}
	return C.int(len(rolls))
}

//export GetDefaultRoller
func GetDefaultRoller() unsafe.Pointer {
	return unsafe.Pointer(&dice.DefaultRoller)
}

//export SetDefaultRoller
func SetDefaultRoller(rollerPtr unsafe.Pointer) {
	roller := (*dice.Roller)(rollerPtr)
	dice.SetDefaultRoller(*roller)
}

// Roll Struct Functions
// These expose the actual dice.Roll struct from dice/modifier.go

//export CreateRoll
func CreateRoll(count, size C.int) unsafe.Pointer {
	roll, err := dice.NewRoll(int(count), int(size))
	if err != nil {
		return nil
	}
	return unsafe.Pointer(roll)
}

//export CreateRollWithRoller
func CreateRollWithRoller(count, size C.int, rollerPtr unsafe.Pointer) unsafe.Pointer {
	roller := (*dice.Roller)(rollerPtr)
	roll, err := dice.NewRollWithRoller(int(count), int(size), *roller)
	if err != nil {
		return nil
	}
	return unsafe.Pointer(roll)
}

//export RollGetValue
func RollGetValue(rollPtr unsafe.Pointer) C.int {
	roll := (*dice.Roll)(rollPtr)
	return C.int(roll.GetValue())
}

//export RollGetDescription
func RollGetDescription(rollPtr unsafe.Pointer) *C.char {
	roll := (*dice.Roll)(rollPtr)
	return C.CString(roll.GetDescription())
}

//export RollHasError
func RollHasError(rollPtr unsafe.Pointer) C.int {
	roll := (*dice.Roll)(rollPtr)
	if roll.Err() != nil {
		return 1 // true
	}
	return 0 // false
}

//export RollGetError
func RollGetError(rollPtr unsafe.Pointer) *C.char {
	roll := (*dice.Roll)(rollPtr)
	err := roll.Err()
	if err != nil {
		return C.CString(err.Error())
	}
	return nil
}

// Helper Functions Complete Exposure
// These expose all the helper functions from dice/modifier.go

//export D4
func D4(count C.int) unsafe.Pointer {
	roll := dice.D4(int(count))
	return unsafe.Pointer(roll)
}

//export D6
func D6(count C.int) unsafe.Pointer {
	roll := dice.D6(int(count))
	return unsafe.Pointer(roll)
}

//export D8
func D8(count C.int) unsafe.Pointer {
	roll := dice.D8(int(count))
	return unsafe.Pointer(roll)
}

//export D10
func D10(count C.int) unsafe.Pointer {
	roll := dice.D10(int(count))
	return unsafe.Pointer(roll)
}

//export D12
func D12(count C.int) unsafe.Pointer {
	roll := dice.D12(int(count))
	return unsafe.Pointer(roll)
}

//export D20
func D20(count C.int) unsafe.Pointer {
	roll := dice.D20(int(count))
	return unsafe.Pointer(roll)
}

//export D100
func D100(count C.int) unsafe.Pointer {
	roll := dice.D100(int(count))
	return unsafe.Pointer(roll)
}

// Legacy Functions (for compatibility with existing URPGDiceSubsystem)
// These will be replaced when we update the subsystem

//export CreateDiceRoller
func CreateDiceRoller() unsafe.Pointer {
	// Return actual CryptoRoller instead of fake string
	return CreateCryptoRoller()
}

//export RollDie
func RollDie(rollerPtr unsafe.Pointer, sides C.int) C.int {
	// Use actual Roller.Roll instead of creating new Roll
	return RollerRoll(rollerPtr, sides)
}