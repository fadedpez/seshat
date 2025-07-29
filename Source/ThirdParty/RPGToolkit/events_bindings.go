package main

/*
#include <stdlib.h>
*/
import "C"
import (
	"context"
	"unsafe"

	"github.com/KirkDiggler/rpg-toolkit/events"
)

// Swiss Army Knife Event Bindings - 1:1 mapping of rpg-toolkit/events package

// EventBus instance management
var globalEventBus events.EventBus

//export CreateEventBus
func CreateEventBus() *C.char {
	globalEventBus = events.NewBus()
	if globalEventBus != nil {
		return C.CString("OK")
	}
	return C.CString("FAILED")
}

//export PublishEvent
func PublishEvent(eventType *C.char, sourceID *C.char, targetID *C.char, contextData *C.char) C.int {
	if globalEventBus == nil {
		return 0
	}

	eventTypeStr := C.GoString(eventType)
	
	// Create new game event with correct signature: (eventType string, source, target core.Entity)
	event := events.NewGameEvent(eventTypeStr, nil, nil)
	if event == nil {
		return 0
	}
	
	err := globalEventBus.Publish(context.Background(), event)
	if err != nil {
		return 0
	}
	return 1
}

//export SubscribeEvent
func SubscribeEvent(eventType *C.char, priority C.int) *C.char {
	if globalEventBus == nil {
		return C.CString("")
	}

	eventTypeStr := C.GoString(eventType)
	
	// Create handler function with correct signature: func(context.Context, Event) error
	handlerFunc := events.HandlerFunc(func(ctx context.Context, event events.Event) error {
		// Handler implementation managed by UE subsystem callback
		return nil
	})
	
	// Call SubscribeFunc with correct signature: (eventType string, priority int, fn HandlerFunc)  
	subscriptionID := globalEventBus.SubscribeFunc(eventTypeStr, int(priority), handlerFunc)
	return C.CString(subscriptionID)
}

//export UnsubscribeEvent
func UnsubscribeEvent(subscriptionID *C.char) C.int {
	if globalEventBus == nil {
		return 0
	}

	subscriptionIDStr := C.GoString(subscriptionID)
	err := globalEventBus.Unsubscribe(subscriptionIDStr)
	if err != nil {
		return 0
	}
	return 1
}

// Event Type Constants - Direct exposure of toolkit constants
//export GetEventBeforeAttackRoll
func GetEventBeforeAttackRoll() *C.char {
	return C.CString("before_attack_roll")
}

//export GetEventOnAttackRoll
func GetEventOnAttackRoll() *C.char {
	return C.CString("on_attack_roll")
}

//export GetEventAfterAttackRoll
func GetEventAfterAttackRoll() *C.char {
	return C.CString("after_attack_roll")
}

//export GetEventBeforeDamageRoll
func GetEventBeforeDamageRoll() *C.char {
	return C.CString("before_damage_roll")
}

//export GetEventOnTakeDamage
func GetEventOnTakeDamage() *C.char {
	return C.CString("on_take_damage")
}

//export GetEventCalculateDamage
func GetEventCalculateDamage() *C.char {
	return C.CString("calculate_damage")
}

//export GetEventAfterDamage
func GetEventAfterDamage() *C.char {
	return C.CString("after_damage")
}

//export GetEventEntityPlaced
func GetEventEntityPlaced() *C.char {
	return C.CString("spatial.entity.placed")
}

//export GetEventEntityMoved
func GetEventEntityMoved() *C.char {
	return C.CString("spatial.entity.moved")
}

//export GetEventRoomCreated
func GetEventRoomCreated() *C.char {
	return C.CString("spatial.room.created")
}

//export GetEventTurnStart
func GetEventTurnStart() *C.char {
	return C.CString("turn_start")
}

//export GetEventTurnEnd
func GetEventTurnEnd() *C.char {
	return C.CString("turn_end")
}

//export GetEventRoundStart
func GetEventRoundStart() *C.char {
	return C.CString("round_start")
}

//export GetEventRoundEnd
func GetEventRoundEnd() *C.char {
	return C.CString("round_end")
}

//export GetEventStatusApplied
func GetEventStatusApplied() *C.char {
	return C.CString("status_applied")
}

//export GetEventStatusRemoved
func GetEventStatusRemoved() *C.char {
	return C.CString("status_removed")
}

//export GetEventStatusCheck
func GetEventStatusCheck() *C.char {
	return C.CString("status_check")
}

// Context Key Constants - Direct exposure of toolkit constants
//export GetContextKeyAttacker
func GetContextKeyAttacker() *C.char {
	return C.CString("attacker")
}

//export GetContextKeyTarget
func GetContextKeyTarget() *C.char {
	return C.CString("target")
}

//export GetContextKeyWeapon
func GetContextKeyWeapon() *C.char {
	return C.CString("weapon")
}

//export GetContextKeyDamageType
func GetContextKeyDamageType() *C.char {
	return C.CString("damage_type")
}

//export GetContextKeyAdvantage
func GetContextKeyAdvantage() *C.char {
	return C.CString("advantage")
}

//export GetContextKeyRoll
func GetContextKeyRoll() *C.char {
	return C.CString("roll")
}

//export GetContextKeyOldPosition
func GetContextKeyOldPosition() *C.char {
	return C.CString("old_position")
}

//export GetContextKeyNewPosition
func GetContextKeyNewPosition() *C.char {
	return C.CString("new_position")
}

//export GetContextKeyRoomID
func GetContextKeyRoomID() *C.char {
	return C.CString("room_id")
}

// Modifier Creation Functions - Direct exposure of toolkit factories
//export CreateModifier
func CreateModifier(source *C.char, modifierType *C.char, value C.int, priority C.int) *C.char {
	// This would create a modifier using events.NewModifier()
	// Return handle or ID for the modifier
	return C.CString("modifier_handle_placeholder")
}

//export CreateIntModifier
func CreateIntModifier(source *C.char, modifierType *C.char, value C.int) *C.char {
	// This would create an integer modifier using events.NewIntModifier()
	return C.CString("int_modifier_handle_placeholder")
}

//export CreateDiceModifier
func CreateDiceModifier(source *C.char, modifierType *C.char, diceExpression *C.char) *C.char {
	// This would create a dice modifier using events.NewDiceValue()
	return C.CString("dice_modifier_handle_placeholder")
}

// Duration Constants - Direct exposure of toolkit duration types
//export GetDurationPermanent
func GetDurationPermanent() *C.char {
	return C.CString("permanent")
}

//export GetDurationRounds
func GetDurationRounds() *C.char {
	return C.CString("rounds")
}

//export GetDurationMinutes
func GetDurationMinutes() *C.char {
	return C.CString("minutes")
}

//export GetDurationHours
func GetDurationHours() *C.char {
	return C.CString("hours")
}

//export GetDurationEncounter
func GetDurationEncounter() *C.char {
	return C.CString("encounter")
}

//export GetDurationConcentration
func GetDurationConcentration() *C.char {
	return C.CString("concentration")
}

//export GetDurationShortRest
func GetDurationShortRest() *C.char {
	return C.CString("short_rest")
}

//export GetDurationLongRest
func GetDurationLongRest() *C.char {
	return C.CString("long_rest")
}

//export GetDurationUntilDamaged
func GetDurationUntilDamaged() *C.char {
	return C.CString("until_damaged")
}

//export GetDurationUntilSave
func GetDurationUntilSave() *C.char {
	return C.CString("until_save")
}

// Memory management
//export FreeEventString
func FreeEventString(str *C.char) {
	C.free(unsafe.Pointer(str))
}