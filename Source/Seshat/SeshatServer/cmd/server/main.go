package main

import (
	"log"
	"net"

	"google.golang.org/grpc"
	"google.golang.org/grpc/reflection"

	"github.com/seshat/server/internal/services"
	pb "github.com/seshat/server/generated/seshat"
)

func main() {
	// Create gRPC server
	s := grpc.NewServer()

	// Register all services
	diceService := services.NewDiceService()
	pb.RegisterDiceServiceServer(s, diceService)

	eventsService := services.NewEventsService()
	pb.RegisterEventServiceServer(s, eventsService)

	spatialService := services.NewSpatialService()
	pb.RegisterSpatialServiceServer(s, spatialService)

	environmentsService := services.NewEnvironmentsService()
	pb.RegisterEnvironmentServiceServer(s, environmentsService)

	selectablesService := services.NewSelectablesService()
	pb.RegisterSelectablesServiceServer(s, selectablesService)

	conditionsService := services.NewConditionsService()
	pb.RegisterConditionsServiceServer(s, conditionsService)

	resourcesService := services.NewResourcesService()
	pb.RegisterResourceServiceServer(s, resourcesService)

	spellsService := services.NewSpellsService()
	pb.RegisterSpellServiceServer(s, spellsService)

	spawnService := services.NewSpawnService()
	pb.RegisterSpawnServiceServer(s, spawnService)

	// Enable reflection for debugging
	reflection.Register(s)

	// Start server
	lis, err := net.Listen("tcp", ":9090")
	if err != nil {
		log.Fatalf("Failed to listen: %v", err)
	}

	log.Println("🎲 Seshat RPG Toolkit Server starting on :9090")
	log.Println("📜 Services available:")
	log.Println("  • DiceService      - Roll dice, test fairness")
	log.Println("  • EventService     - Event bus with streaming")
	log.Println("  • SpatialService   - Rooms, positioning, pathfinding")
	log.Println("  • EnvironmentService - Room generation, walls, themes")
	log.Println("  • SelectablesService - Weighted selection tables")
	log.Println("  • ConditionsService  - Status effects and relationships")
	log.Println("  • ResourceService    - Resource pools and management")
	log.Println("  • SpellService       - Complete spell system")
	log.Println("  • SpawnService       - Entity spawning and patterns")
	log.Println("")
	log.Println("🔧 Development server - all experimental features enabled!")

	if err := s.Serve(lis); err != nil {
		log.Fatalf("Failed to serve: %v", err)
	}
}