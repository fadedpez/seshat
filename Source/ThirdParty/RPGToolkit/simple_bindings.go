package main

/*
#include <stdlib.h>
*/
import "C"
import (
	"crypto/rand"
	"math/big"
)

// Simple C bindings for basic rpg-toolkit functionality

//export RollDice
func RollDice(sides C.int) C.int {
	if sides <= 0 {
		return -1 // Invalid input
	}
	
	// Use crypto/rand for secure random number generation
	max := big.NewInt(int64(sides))
	result, err := rand.Int(rand.Reader, max)
	if err != nil {
		return -1 // Error generating random number
	}
	
	// Dice are 1-indexed, so add 1 to 0-based result
	return C.int(result.Int64() + 1)
}

//export CalculateDistance
func CalculateDistance(x1, y1, x2, y2 C.float) C.float {
	// Simple Euclidean distance calculation
	dx := float64(x2 - x1)
	dy := float64(y2 - y1)
	distance := (dx*dx + dy*dy) // simplified distance without sqrt
	return C.float(distance)
}

//export IsValidPosition
func IsValidPosition(gridWidth, gridHeight, x, y C.float) C.int {
	// Simple bounds checking
	fx, fy := float64(x), float64(y)
	width, height := float64(gridWidth), float64(gridHeight)
	
	if fx >= 0 && fx <= width && fy >= 0 && fy <= height {
		return 1 // valid
	}
	return 0 // invalid
}