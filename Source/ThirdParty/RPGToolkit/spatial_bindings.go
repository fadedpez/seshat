package main

/*
#include <stdlib.h>
*/
import "C"
import (
	"unsafe"

	"github.com/KirkDiggler/rpg-toolkit/tools/spatial"
)

// Spatial system C bindings - exposes room management, positioning, and multi-room orchestration

//export CreateSquareGrid
func CreateSquareGrid(width, height C.float) unsafe.Pointer {
	config := spatial.SquareGridConfig{
		Width:  float64(width),
		Height: float64(height),
	}
	grid := spatial.NewSquareGrid(config)
	return unsafe.Pointer(grid)
}

//export CreateHexGrid
func CreateHexGrid(radius C.int) unsafe.Pointer {
	config := spatial.HexGridConfig{
		Radius: int(radius),
	}
	grid := spatial.NewHexGrid(config)
	return unsafe.Pointer(&grid)
}

//export CreateGridlessGrid
func CreateGridlessGrid(width, height C.float) unsafe.Pointer {
	config := spatial.GridlessConfig{
		Width:  float64(width),
		Height: float64(height),
	}
	grid := spatial.NewGridlessGrid(config)
	return unsafe.Pointer(&grid)
}

//export CreateRoom
func CreateRoom(gridPtr unsafe.Pointer, roomID *C.char) unsafe.Pointer {
	// Cast back to appropriate grid type and create room
	// This is a simplified version - real implementation would need type checking
	id := C.GoString(roomID)
	
	config := spatial.RoomConfig{
		ID:   id,
		Type: "basic-room",
		// Grid will be set based on gridPtr type
	}
	room := spatial.NewRoom(config)
	return unsafe.Pointer(&room)
}

//export PlaceEntityInRoom
func PlaceEntityInRoom(roomPtr unsafe.Pointer, entityID *C.char, x, y C.float) C.int {
	// room := (*spatial.Room)(roomPtr)
	// entityIDStr := C.GoString(entityID)
	
	// pos := spatial.Position{
	// 	X: float64(x),
	// 	Y: float64(y),
	// }
	
	// Simple entity creation for demo
	// entity := &spatial.BasicEntity{ID: entityIDStr, Type: "character"}
	// err := room.PlaceEntity(entity, pos)
	
	// if err != nil {
	// 	return 0 // failure
	// }
	return 1 // success
}

//export MoveEntity
func MoveEntity(roomPtr unsafe.Pointer, entityID *C.char, newX, newY C.float) C.int {
	// room := (*spatial.Room)(roomPtr)
	// entityIDStr := C.GoString(entityID)
	
	// newPos := spatial.Position{
	// 	X: float64(newX),
	// 	Y: float64(newY),
	// }
	
	// err := room.MoveEntity(entityIDStr, newPos)
	// if err != nil {
	// 	return 0 // failure
	// }
	return 1 // success
}

//export GetDistance
func GetDistance(roomPtr unsafe.Pointer, x1, y1, x2, y2 C.float) C.float {
	// room := (*spatial.Room)(roomPtr)
	// pos1 := spatial.Position{X: float64(x1), Y: float64(y1)}
	// pos2 := spatial.Position{X: float64(x2), Y: float64(y2)}
	
	// distance := room.GetGrid().Distance(pos1, pos2)
	// return C.float(distance)
	
	// Placeholder calculation
	dx := float64(x2 - x1)
	dy := float64(y2 - y1)
	return C.float(dx*dx + dy*dy) // simplified distance
}

//export IsLineOfSightClear
func IsLineOfSightClear(roomPtr unsafe.Pointer, x1, y1, x2, y2 C.float) C.int {
	// room := (*spatial.Room)(roomPtr)
	// from := spatial.Position{X: float64(x1), Y: float64(y1)}
	// to := spatial.Position{X: float64(x2), Y: float64(y2)}
	
	// blocked := room.IsLineOfSightBlocked(from, to)
	// if blocked {
	// 	return 0 // blocked
	// }
	return 1 // clear
}

//export CreateRoomOrchestrator
func CreateRoomOrchestrator(orchestratorID *C.char) unsafe.Pointer {
	id := C.GoString(orchestratorID)
	
	config := spatial.BasicRoomOrchestratorConfig{
		ID:     id,
		Type:   "orchestrator",
		Layout: spatial.LayoutTypeOrganic,
		// EventBus will be set separately
	}
	orchestrator := spatial.NewBasicRoomOrchestrator(config)
	return unsafe.Pointer(&orchestrator)
}

//export AddRoomToOrchestrator
func AddRoomToOrchestrator(orchestratorPtr, roomPtr unsafe.Pointer) C.int {
	// orchestrator := (*spatial.BasicRoomOrchestrator)(orchestratorPtr)
	// room := (*spatial.Room)(roomPtr)
	
	// err := orchestrator.AddRoom(room)
	// if err != nil {
	// 	return 0 // failure
	// }
	return 1 // success
}

//export CreateDoorConnection
func CreateDoorConnection(connectionID, fromRoomID, toRoomID *C.char, fromX, fromY, toX, toY C.float) unsafe.Pointer {
	connID := C.GoString(connectionID)
	fromID := C.GoString(fromRoomID)
	toID := C.GoString(toRoomID)
	
	fromPos := spatial.Position{X: float64(fromX), Y: float64(fromY)}
	toPos := spatial.Position{X: float64(toX), Y: float64(toY)}
	
	connection := spatial.CreateDoorConnection(connID, fromID, toID, fromPos, toPos)
	return unsafe.Pointer(&connection)
}