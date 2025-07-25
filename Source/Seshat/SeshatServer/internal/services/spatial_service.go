package services

import (
	"context"

	pb "github.com/seshat/server/generated/seshat"
)

// SpatialService implements the gRPC SpatialService interface
type SpatialService struct {
	pb.UnimplementedSpatialServiceServer
}

// NewSpatialService creates a new spatial service instance
func NewSpatialService() *SpatialService {
	return &SpatialService{}
}

// CreateRoom creates a new room
func (s *SpatialService) CreateRoom(ctx context.Context, req *pb.CreateRoomRequest) (*pb.CreateRoomResponse, error) {
	// TODO: Implement with rpg-toolkit spatial module
	return &pb.CreateRoomResponse{
		Status: &pb.Result{
			Success: false,
			Error: &pb.ErrorDetails{
				Code:    "NOT_IMPLEMENTED",
				Message: "SpatialService implementation coming next!",
			},
		},
	}, nil
}

// Stub implementations for all other methods
func (s *SpatialService) GetRoom(ctx context.Context, req *pb.GetRoomRequest) (*pb.GetRoomResponse, error) {
	return &pb.GetRoomResponse{Status: &pb.Result{Success: false, Error: &pb.ErrorDetails{Code: "NOT_IMPLEMENTED", Message: "Coming soon!"}}}, nil
}

func (s *SpatialService) ListRooms(ctx context.Context, req *pb.ListRoomsRequest) (*pb.ListRoomsResponse, error) {
	return &pb.ListRoomsResponse{Status: &pb.Result{Success: false, Error: &pb.ErrorDetails{Code: "NOT_IMPLEMENTED", Message: "Coming soon!"}}}, nil
}

func (s *SpatialService) DeleteRoom(ctx context.Context, req *pb.DeleteRoomRequest) (*pb.DeleteRoomResponse, error) {
	return &pb.DeleteRoomResponse{Status: &pb.Result{Success: false, Error: &pb.ErrorDetails{Code: "NOT_IMPLEMENTED", Message: "Coming soon!"}}}, nil
}

func (s *SpatialService) PlaceEntity(ctx context.Context, req *pb.PlaceEntityRequest) (*pb.PlaceEntityResponse, error) {
	return &pb.PlaceEntityResponse{Status: &pb.Result{Success: false, Error: &pb.ErrorDetails{Code: "NOT_IMPLEMENTED", Message: "Coming soon!"}}}, nil
}

func (s *SpatialService) MoveEntity(ctx context.Context, req *pb.MoveEntityRequest) (*pb.MoveEntityResponse, error) {
	return &pb.MoveEntityResponse{Status: &pb.Result{Success: false, Error: &pb.ErrorDetails{Code: "NOT_IMPLEMENTED", Message: "Coming soon!"}}}, nil
}

func (s *SpatialService) RemoveEntity(ctx context.Context, req *pb.RemoveEntityRequest) (*pb.RemoveEntityResponse, error) {
	return &pb.RemoveEntityResponse{Status: &pb.Result{Success: false, Error: &pb.ErrorDetails{Code: "NOT_IMPLEMENTED", Message: "Coming soon!"}}}, nil
}

func (s *SpatialService) GetEntityPosition(ctx context.Context, req *pb.GetEntityPositionRequest) (*pb.GetEntityPositionResponse, error) {
	return &pb.GetEntityPositionResponse{Status: &pb.Result{Success: false, Error: &pb.ErrorDetails{Code: "NOT_IMPLEMENTED", Message: "Coming soon!"}}}, nil
}

func (s *SpatialService) GetEntitiesAt(ctx context.Context, req *pb.GetEntitiesAtRequest) (*pb.GetEntitiesAtResponse, error) {
	return &pb.GetEntitiesAtResponse{Status: &pb.Result{Success: false, Error: &pb.ErrorDetails{Code: "NOT_IMPLEMENTED", Message: "Coming soon!"}}}, nil
}

func (s *SpatialService) GetEntitiesInRange(ctx context.Context, req *pb.GetEntitiesInRangeRequest) (*pb.GetEntitiesInRangeResponse, error) {
	return &pb.GetEntitiesInRangeResponse{Status: &pb.Result{Success: false, Error: &pb.ErrorDetails{Code: "NOT_IMPLEMENTED", Message: "Coming soon!"}}}, nil
}

func (s *SpatialService) GetEntitiesInArea(ctx context.Context, req *pb.GetEntitiesInAreaRequest) (*pb.GetEntitiesInAreaResponse, error) {
	return &pb.GetEntitiesInAreaResponse{Status: &pb.Result{Success: false, Error: &pb.ErrorDetails{Code: "NOT_IMPLEMENTED", Message: "Coming soon!"}}}, nil
}

func (s *SpatialService) GetEntitiesInLine(ctx context.Context, req *pb.GetEntitiesInLineRequest) (*pb.GetEntitiesInLineResponse, error) {
	return &pb.GetEntitiesInLineResponse{Status: &pb.Result{Success: false, Error: &pb.ErrorDetails{Code: "NOT_IMPLEMENTED", Message: "Coming soon!"}}}, nil
}

func (s *SpatialService) FindPath(ctx context.Context, req *pb.FindPathRequest) (*pb.FindPathResponse, error) {
	return &pb.FindPathResponse{Status: &pb.Result{Success: false, Error: &pb.ErrorDetails{Code: "NOT_IMPLEMENTED", Message: "Coming soon!"}}}, nil
}

func (s *SpatialService) GetDistance(ctx context.Context, req *pb.GetDistanceRequest) (*pb.GetDistanceResponse, error) {
	return &pb.GetDistanceResponse{Status: &pb.Result{Success: false, Error: &pb.ErrorDetails{Code: "NOT_IMPLEMENTED", Message: "Coming soon!"}}}, nil
}

func (s *SpatialService) CheckLineOfSight(ctx context.Context, req *pb.LineOfSightRequest) (*pb.LineOfSightResponse, error) {
	return &pb.LineOfSightResponse{Status: &pb.Result{Success: false, Error: &pb.ErrorDetails{Code: "NOT_IMPLEMENTED", Message: "Coming soon!"}}}, nil
}

func (s *SpatialService) CreateConnection(ctx context.Context, req *pb.CreateConnectionRequest) (*pb.CreateConnectionResponse, error) {
	return &pb.CreateConnectionResponse{Status: &pb.Result{Success: false, Error: &pb.ErrorDetails{Code: "NOT_IMPLEMENTED", Message: "Coming soon!"}}}, nil
}

func (s *SpatialService) GetConnections(ctx context.Context, req *pb.GetConnectionsRequest) (*pb.GetConnectionsResponse, error) {
	return &pb.GetConnectionsResponse{Status: &pb.Result{Success: false, Error: &pb.ErrorDetails{Code: "NOT_IMPLEMENTED", Message: "Coming soon!"}}}, nil
}

func (s *SpatialService) MoveEntityBetweenRooms(ctx context.Context, req *pb.MoveEntityBetweenRoomsRequest) (*pb.MoveEntityBetweenRoomsResponse, error) {
	return &pb.MoveEntityBetweenRoomsResponse{Status: &pb.Result{Success: false, Error: &pb.ErrorDetails{Code: "NOT_IMPLEMENTED", Message: "Coming soon!"}}}, nil
}

func (s *SpatialService) GetValidPositions(ctx context.Context, req *pb.GetValidPositionsRequest) (*pb.GetValidPositionsResponse, error) {
	return &pb.GetValidPositionsResponse{Status: &pb.Result{Success: false, Error: &pb.ErrorDetails{Code: "NOT_IMPLEMENTED", Message: "Coming soon!"}}}, nil
}

func (s *SpatialService) IsValidPosition(ctx context.Context, req *pb.IsValidPositionRequest) (*pb.IsValidPositionResponse, error) {
	return &pb.IsValidPositionResponse{Status: &pb.Result{Success: false, Error: &pb.ErrorDetails{Code: "NOT_IMPLEMENTED", Message: "Coming soon!"}}}, nil
}