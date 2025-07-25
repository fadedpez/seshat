package main

/*
#include <stdlib.h>
*/
import "C"
import (
	"github.com/KirkDiggler/rpg-toolkit/dice"
	"github.com/KirkDiggler/rpg-toolkit/tools/spatial"
)

// Simple C bindings for basic rpg-toolkit functionality

//export CreateSquareGrid
func CreateSquareGrid(width, height C.float) *C.char {
	config := spatial.SquareGridConfig{
		Width:  float64(width),
		Height: float64(height),
	}
	grid := spatial.NewSquareGrid(config)
	
	// For demo, just return a success message
	_ = grid
	return C.CString("square_grid_created")
}

//export RollDice
func RollDice(sides C.int) C.int {
	roller := &dice.CryptoRoller{}
	result, err := roller.Roll(int(sides))
	if err != nil {
		return -1 // error
	}
	return C.int(result)
}

//export CalculateDistance
func CalculateDistance(x1, y1, x2, y2 C.float) C.float {
	pos1 := spatial.Position{X: float64(x1), Y: float64(y1)}
	pos2 := spatial.Position{X: float64(x2), Y: float64(y2)}
	
	// Create a simple grid to calculate distance
	config := spatial.SquareGridConfig{Width: 100, Height: 100}
	grid := spatial.NewSquareGrid(config)
	
	distance := grid.Distance(pos1, pos2)
	return C.float(distance)
}

//export IsValidPosition
func IsValidPosition(gridWidth, gridHeight, x, y C.float) C.int {
	config := spatial.SquareGridConfig{
		Width:  float64(gridWidth),
		Height: float64(gridHeight),
	}
	grid := spatial.NewSquareGrid(config)
	
	pos := spatial.Position{X: float64(x), Y: float64(y)}
	valid := grid.IsValidPosition(pos)
	
	if valid {
		return 1
	}
	return 0
}