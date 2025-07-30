package main

/*
#include <stdlib.h>
*/
import "C"
import (
	"errors"
	"unsafe"

	"github.com/KirkDiggler/rpg-toolkit/core"
)

// Core Error Constants Exposure
// These expose the actual toolkit error constants from core/errors.go

//export GetEntityNotFoundError
func GetEntityNotFoundError() *C.char {
	return C.CString(core.ErrEntityNotFound.Error())
}

//export GetInvalidEntityError
func GetInvalidEntityError() *C.char {
	return C.CString(core.ErrInvalidEntity.Error())
}

//export GetDuplicateEntityError
func GetDuplicateEntityError() *C.char {
	return C.CString(core.ErrDuplicateEntity.Error())
}

//export GetNilEntityError
func GetNilEntityError() *C.char {
	return C.CString(core.ErrNilEntity.Error())
}

//export GetEmptyIDError
func GetEmptyIDError() *C.char {
	return C.CString(core.ErrEmptyID.Error())
}

//export GetInvalidTypeError
func GetInvalidTypeError() *C.char {
	return C.CString(core.ErrInvalidType.Error())
}

// EntityError Struct Handling
// These expose the actual toolkit EntityError struct from core/errors.go

//export CreateEntityError
func CreateEntityError(op, entityType, entityID, errMsg *C.char) unsafe.Pointer {
	opStr := C.GoString(op)
	typeStr := C.GoString(entityType)
	idStr := C.GoString(entityID)
	errStr := C.GoString(errMsg)

	baseErr := errors.New(errStr)
	entityErr := core.NewEntityError(opStr, typeStr, idStr, baseErr)

	return unsafe.Pointer(entityErr)
}

//export GetEntityErrorMessage
func GetEntityErrorMessage(errPtr unsafe.Pointer) *C.char {
	entityErr := (*core.EntityError)(errPtr)
	return C.CString(entityErr.Error())
}

//export GetEntityErrorID
func GetEntityErrorID(errPtr unsafe.Pointer) *C.char {
	entityErr := (*core.EntityError)(errPtr)
	return C.CString(entityErr.EntityID)
}

//export GetEntityErrorType
func GetEntityErrorType(errPtr unsafe.Pointer) *C.char {
	entityErr := (*core.EntityError)(errPtr)
	return C.CString(entityErr.EntityType)
}

//export GetEntityErrorOp
func GetEntityErrorOp(errPtr unsafe.Pointer) *C.char {
	entityErr := (*core.EntityError)(errPtr)
	return C.CString(entityErr.Op)
}

// Automatic Cleanup Entity Error Function
// Extracts all values immediately and handles memory cleanup automatically

//export CreateEntityErrorComplete
func CreateEntityErrorComplete(op, entityType, entityID, errMsg *C.char, 
                              outOp, outType, outID, outMessage **C.char) C.int {
	// Create EntityError object
	opStr := C.GoString(op)
	typeStr := C.GoString(entityType)
	idStr := C.GoString(entityID)
	errStr := C.GoString(errMsg)

	baseErr := errors.New(errStr)
	entityErr := core.NewEntityError(opStr, typeStr, idStr, baseErr)
	
	// Extract all values immediately
	*outOp = C.CString(entityErr.Op)
	*outType = C.CString(entityErr.EntityType)
	*outID = C.CString(entityErr.EntityID)
	*outMessage = C.CString(entityErr.Error())
	
	return 1 // Success
	// entityErr goes out of scope and gets GC'd naturally - no registry needed!
}

// Entity Interface Validation
// These provide validation functions for Entity interface compliance

//export ValidateEntityID
func ValidateEntityID(id *C.char) C.int {
	idStr := C.GoString(id)
	if idStr == "" {
		return 0 // false
	}
	return 1 // true
}

//export ValidateEntityType
func ValidateEntityType(entityType *C.char) C.int {
	typeStr := C.GoString(entityType)
	if typeStr == "" {
		return 0 // false
	}
	return 1 // true
}

// Memory Management
// String cleanup function for C interop

//export FreeString
func FreeString(str *C.char) {
	C.free(unsafe.Pointer(str))
}