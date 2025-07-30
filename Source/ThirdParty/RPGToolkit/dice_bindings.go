package main

/*
#include <stdlib.h>
*/
import "C"
import (
	"sync"
	"unsafe"

	"github.com/KirkDiggler/rpg-toolkit/dice"
)

// CGO Memory Registry - Global object registry to prevent GC
// Follows runtime/cgo.Handle pattern (industry standard)
var (
	objectRegistry = make(map[uintptr]interface{})
	registryMutex  sync.RWMutex
	nextID         uintptr = 1 // Platform-native sizing
)

// Registry management functions (industry standard pattern)
func registerObject(obj interface{}) uintptr {
	registryMutex.Lock()
	defer registryMutex.Unlock()

	id := nextID
	nextID++
	objectRegistry[id] = obj
	return id
}

func getObject(handle uintptr) (interface{}, bool) {
	registryMutex.RLock()
	defer registryMutex.RUnlock()

	obj, exists := objectRegistry[handle]
	return obj, exists
}

func cleanupObject(handle uintptr) {
	registryMutex.Lock()
	defer registryMutex.Unlock()
	delete(objectRegistry, handle)
}

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
func RollGetValue(handle C.uintptr_t) C.int {
	obj, exists := getObject(uintptr(handle))
	if !exists {
		return -1 // Error: invalid handle
	}

	roll, ok := obj.(*dice.Roll)
	if !ok {
		return -1 // Error: wrong type
	}

	return C.int(roll.GetValue())
}

//export RollGetDescription
func RollGetDescription(handle C.uintptr_t) *C.char {
	obj, exists := getObject(uintptr(handle))
	if !exists {
		return C.CString("ERROR: Invalid handle") // Caller must free
	}

	roll, ok := obj.(*dice.Roll)
	if !ok {
		return C.CString("ERROR: Wrong type") // Caller must free
	}

	return C.CString(roll.GetDescription()) // Caller must free
}

//export RollHasError
func RollHasError(handle C.uintptr_t) C.int {
	obj, exists := getObject(uintptr(handle))
	if !exists {
		return 1 // Assume error if can't check
	}

	roll, ok := obj.(*dice.Roll)
	if !ok {
		return 1 // Wrong type is an error
	}

	if roll.Err() != nil {
		return 1 // Has error
	}
	return 0 // No error
}

//export RollGetError
func RollGetError(handle C.uintptr_t) *C.char {
	obj, exists := getObject(uintptr(handle))
	if !exists {
		return C.CString("ERROR: Invalid handle") // Caller must free
	}

	roll, ok := obj.(*dice.Roll)
	if !ok {
		return C.CString("ERROR: Wrong type") // Caller must free
	}

	err := roll.Err()
	if err != nil {
		return C.CString(err.Error()) // Caller must free
	}
	return C.CString("") // Caller must free (empty string)
}

// Automatic Cleanup Helper Functions
// These extract all values immediately and handle memory cleanup automatically

//export D4Complete
func D4Complete(count C.int, outValue *C.int, outDesc **C.char, outError **C.char) C.int {
	roll := dice.D4(int(count))
	
	*outValue = C.int(roll.GetValue())
	*outDesc = C.CString(roll.GetDescription())
	
	if roll.Err() != nil {
		*outError = C.CString(roll.Err().Error())
		return 0 // Has error
	} else {
		*outError = C.CString("")
		return 1 // Success
	}
	// roll goes out of scope and gets GC'd naturally - no registry needed!
}

//export D6Complete
func D6Complete(count C.int, outValue *C.int, outDesc **C.char, outError **C.char) C.int {
	roll := dice.D6(int(count))
	
	*outValue = C.int(roll.GetValue())
	*outDesc = C.CString(roll.GetDescription())
	
	if roll.Err() != nil {
		*outError = C.CString(roll.Err().Error())
		return 0 // Has error
	} else {
		*outError = C.CString("")
		return 1 // Success
	}
}

//export D8Complete
func D8Complete(count C.int, outValue *C.int, outDesc **C.char, outError **C.char) C.int {
	roll := dice.D8(int(count))
	
	*outValue = C.int(roll.GetValue())
	*outDesc = C.CString(roll.GetDescription())
	
	if roll.Err() != nil {
		*outError = C.CString(roll.Err().Error())
		return 0 // Has error
	} else {
		*outError = C.CString("")
		return 1 // Success
	}
}

//export D10Complete
func D10Complete(count C.int, outValue *C.int, outDesc **C.char, outError **C.char) C.int {
	roll := dice.D10(int(count))
	
	*outValue = C.int(roll.GetValue())
	*outDesc = C.CString(roll.GetDescription())
	
	if roll.Err() != nil {
		*outError = C.CString(roll.Err().Error())
		return 0 // Has error
	} else {
		*outError = C.CString("")
		return 1 // Success
	}
}

//export D12Complete
func D12Complete(count C.int, outValue *C.int, outDesc **C.char, outError **C.char) C.int {
	roll := dice.D12(int(count))
	
	*outValue = C.int(roll.GetValue())
	*outDesc = C.CString(roll.GetDescription())
	
	if roll.Err() != nil {
		*outError = C.CString(roll.Err().Error())
		return 0 // Has error
	} else {
		*outError = C.CString("")
		return 1 // Success
	}
}

//export D20Complete
func D20Complete(count C.int, outValue *C.int, outDesc **C.char, outError **C.char) C.int {
	roll := dice.D20(int(count))
	
	*outValue = C.int(roll.GetValue())
	*outDesc = C.CString(roll.GetDescription())
	
	if roll.Err() != nil {
		*outError = C.CString(roll.Err().Error())
		return 0 // Has error
	} else {
		*outError = C.CString("")
		return 1 // Success
	}
}

//export D100Complete
func D100Complete(count C.int, outValue *C.int, outDesc **C.char, outError **C.char) C.int {
	roll := dice.D100(int(count))
	
	*outValue = C.int(roll.GetValue())
	*outDesc = C.CString(roll.GetDescription())
	
	if roll.Err() != nil {
		*outError = C.CString(roll.Err().Error())
		return 0 // Has error
	} else {
		*outError = C.CString("")
		return 1 // Success
	}
}

// Memory Management Functions

//export RollCleanup
func RollCleanup(handle C.uintptr_t) {
	cleanupObject(uintptr(handle))
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