package main

/*
#include <stdlib.h>
*/
import "C"
import (
	"unsafe"

	"github.com/KirkDiggler/rpg-toolkit/mechanics/conditions"
)

// Conditions system C bindings - exposes status effects, relationships, and condition management

//export CreateConditionManager
func CreateConditionManager(managerID *C.char) unsafe.Pointer {
	id := C.GoString(managerID)
	
	config := conditions.ManagerConfig{
		ID:   id,
		Type: "condition-manager",
		// EventBus will be set separately if needed
	}
	manager := conditions.NewManager(config)
	return unsafe.Pointer(&manager)
}

//export CreateSimpleCondition
func CreateSimpleCondition(conditionID, conditionType, name, description *C.char, duration C.int) unsafe.Pointer {
	id := C.GoString(conditionID)
	cType := C.GoString(conditionType)
	nameStr := C.GoString(name)
	descStr := C.GoString(description)
	
	config := conditions.SimpleConditionConfig{
		ID:          id,
		Type:        cType,
		Name:        nameStr,
		Description: descStr,
		Duration:    int(duration),
	}
	
	condition := conditions.NewSimpleCondition(config)
	return unsafe.Pointer(&condition)
}

//export ApplyCondition
func ApplyCondition(managerPtr, conditionPtr unsafe.Pointer, targetID *C.char) C.int {
	manager := (*conditions.Manager)(managerPtr)
	condition := (*conditions.SimpleCondition)(conditionPtr)
	target := C.GoString(targetID)
	
	err := manager.ApplyCondition(target, condition)
	if err != nil {
		return 0 // failure
	}
	return 1 // success
}

//export RemoveCondition
func RemoveCondition(managerPtr unsafe.Pointer, targetID, conditionID *C.char) C.int {
	manager := (*conditions.Manager)(managerPtr)
	target := C.GoString(targetID)
	condID := C.GoString(conditionID)
	
	err := manager.RemoveCondition(target, condID)
	if err != nil {
		return 0 // failure
	}
	return 1 // success
}

//export HasCondition
func HasCondition(managerPtr unsafe.Pointer, targetID, conditionID *C.char) C.int {
	manager := (*conditions.Manager)(managerPtr)
	target := C.GoString(targetID)
	condID := C.GoString(conditionID)
	
	hasCondition := manager.HasCondition(target, condID)
	if hasCondition {
		return 1 // has condition
	}
	return 0 // doesn't have condition
}

//export GetConditionDuration
func GetConditionDuration(managerPtr unsafe.Pointer, targetID, conditionID *C.char) C.int {
	manager := (*conditions.Manager)(managerPtr)
	target := C.GoString(targetID)
	condID := C.GoString(conditionID)
	
	condition := manager.GetCondition(target, condID)
	if condition == nil {
		return -1 // condition not found
	}
	
	// Get duration from condition (simplified)
	return C.int(0) // placeholder
}

//export UpdateConditionDurations
func UpdateConditionDurations(managerPtr unsafe.Pointer, elapsedTime C.int) C.int {
	manager := (*conditions.Manager)(managerPtr)
	
	// Update all condition durations
	err := manager.UpdateDurations(int(elapsedTime))
	if err != nil {
		return 0 // failure
	}
	return 1 // success
}

//export CreateConditionRelationship
func CreateConditionRelationship(relationshipID, sourceID, targetID *C.char, relationshipType C.int) unsafe.Pointer {
	id := C.GoString(relationshipID)
	source := C.GoString(sourceID)
	target := C.GoString(targetID)
	
	var relType conditions.RelationshipType
	switch relationshipType {
	case 0:
		relType = conditions.RelationshipTypeMutuallyExclusive
	case 1:
		relType = conditions.RelationshipTypeSupersedes
	case 2:
		relType = conditions.RelationshipTypeRequires
	default:
		relType = conditions.RelationshipTypeMutuallyExclusive
	}
	
	config := conditions.RelationshipConfig{
		ID:     id,
		Source: source,
		Target: target,
		Type:   relType,
	}
	
	relationship := conditions.NewRelationship(config)
	return unsafe.Pointer(&relationship)
}

//export AddConditionRelationship
func AddConditionRelationship(managerPtr, relationshipPtr unsafe.Pointer) C.int {
	manager := (*conditions.Manager)(managerPtr)
	relationship := (*conditions.Relationship)(relationshipPtr)
	
	err := manager.AddRelationship(relationship)
	if err != nil {
		return 0 // failure
	}
	return 1 // success
}

//export GetActiveConditions
func GetActiveConditions(managerPtr unsafe.Pointer, targetID *C.char, conditionIDs **C.char, maxCount C.int) C.int {
	manager := (*conditions.Manager)(managerPtr)
	target := C.GoString(targetID)
	
	conditions := manager.GetActiveConditions(target)
	
	// Convert to C string array (simplified)
	count := len(conditions)
	if count > int(maxCount) {
		count = int(maxCount)
	}
	
	// In real implementation, we'd properly populate the C string array
	// For now, just return the count
	return C.int(count)
}