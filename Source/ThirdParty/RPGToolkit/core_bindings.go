package main

import "C"
import (
	"sync"

	"github.com/google/uuid"
)

// Entity represents a game entity in the toolkit
type Entity struct {
	ID   string
	Type string
}

// GetID implements core.Entity interface
func (e *Entity) GetID() string {
	return e.ID
}

// GetType implements core.Entity interface
func (e *Entity) GetType() string {
	return e.Type
}

// Global entity storage for the binding layer
var (
	entities    = make(map[int32]*Entity)
	entityMutex = sync.RWMutex{}
	nextHandle  = int32(1)
)

// Helper function to get next entity handle
func getNextHandle() int32 {
	entityMutex.Lock()
	defer entityMutex.Unlock()
	handle := nextHandle
	nextHandle++
	return handle
}

//export CreateEntity
func CreateEntity(entityType *C.char, entityID *C.char) C.int {
	goType := C.GoString(entityType)
	goID := C.GoString(entityID)

	// Generate ID if not provided
	if goID == "" {
		goID = uuid.New().String()
	}

	// Validate entity type
	if goType == "" {
		return -1 // Invalid entity type
	}

	// Create entity
	entity := &Entity{
		ID:   goID,
		Type: goType,
	}

	// Store entity and return handle
	handle := getNextHandle()
	entityMutex.Lock()
	entities[handle] = entity
	entityMutex.Unlock()

	// TODO: Integrate with actual toolkit core package when available
	// For now, just store in our binding layer

	return C.int(handle)
}

//export ValidateEntity
func ValidateEntity(entityType *C.char, entityID *C.char) C.int {
	goType := C.GoString(entityType)
	goID := C.GoString(entityID)

	// Basic validation rules
	if goType == "" {
		return 6 // InvalidType error (matches ERPGEntityError enum)
	}

	if goID == "" {
		return 5 // EmptyID error (matches ERPGEntityError enum)
	}

	// Additional validation can be added here
	// TODO: Use actual toolkit validation when core package is integrated

	return 0 // No error
}

//export GetEntityType
func GetEntityType(entityHandle C.int) *C.char {
	handle := int32(entityHandle)

	entityMutex.RLock()
	entity, exists := entities[handle]
	entityMutex.RUnlock()

	if !exists {
		return C.CString("") // Entity not found
	}

	return C.CString(entity.Type)
}

//export GetEntityID
func GetEntityID(entityHandle C.int) *C.char {
	handle := int32(entityHandle)

	entityMutex.RLock()
	entity, exists := entities[handle]
	entityMutex.RUnlock()

	if !exists {
		return C.CString("") // Entity not found
	}

	return C.CString(entity.ID)
}

//export DestroyEntity
func DestroyEntity(entityHandle C.int) {
	handle := int32(entityHandle)

	entityMutex.Lock()
	delete(entities, handle)
	entityMutex.Unlock()
}

//export GetEntityCount
func GetEntityCount() C.int {
	entityMutex.RLock()
	count := len(entities)
	entityMutex.RUnlock()

	return C.int(count)
}

//export EntityExists
func EntityExists(entityType *C.char, entityID *C.char) C.int {
	goType := C.GoString(entityType)
	goID := C.GoString(entityID)

	entityMutex.RLock()
	defer entityMutex.RUnlock()

	for _, entity := range entities {
		if entity.Type == goType && entity.ID == goID {
			return 1 // Found
		}
	}

	return 0 // Not found
}