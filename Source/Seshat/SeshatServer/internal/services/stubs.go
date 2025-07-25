package services

import (
	"context"

	pb "github.com/seshat/server/generated/seshat"
)

// Stub implementations for all remaining services
// These return "NOT_IMPLEMENTED" errors but allow the server to compile and run

// EnvironmentsService stub
type EnvironmentsService struct {
	pb.UnimplementedEnvironmentServiceServer
}

func NewEnvironmentsService() *EnvironmentsService {
	return &EnvironmentsService{}
}

func (e *EnvironmentsService) GenerateRoom(ctx context.Context, req *pb.GenerateRoomRequest) (*pb.GenerateRoomResponse, error) {
	return &pb.GenerateRoomResponse{Status: &pb.Result{Success: false, Error: &pb.ErrorDetails{Code: "NOT_IMPLEMENTED", Message: "EnvironmentsService implementation coming soon!"}}}, nil
}

func (e *EnvironmentsService) GenerateRoomWithTemplate(ctx context.Context, req *pb.GenerateRoomTemplateRequest) (*pb.GenerateRoomTemplateResponse, error) {
	return &pb.GenerateRoomTemplateResponse{Status: &pb.Result{Success: false, Error: &pb.ErrorDetails{Code: "NOT_IMPLEMENTED", Message: "Coming soon!"}}}, nil
}

func (e *EnvironmentsService) GenerateWalls(ctx context.Context, req *pb.GenerateWallsRequest) (*pb.GenerateWallsResponse, error) {
	return &pb.GenerateWallsResponse{Status: &pb.Result{Success: false, Error: &pb.ErrorDetails{Code: "NOT_IMPLEMENTED", Message: "Coming soon!"}}}, nil
}

func (e *EnvironmentsService) DestroyWall(ctx context.Context, req *pb.DestroyWallRequest) (*pb.DestroyWallResponse, error) {
	return &pb.DestroyWallResponse{Status: &pb.Result{Success: false, Error: &pb.ErrorDetails{Code: "NOT_IMPLEMENTED", Message: "Coming soon!"}}}, nil
}

func (e *EnvironmentsService) GetWallInfo(ctx context.Context, req *pb.GetWallInfoRequest) (*pb.GetWallInfoResponse, error) {
	return &pb.GetWallInfoResponse{Status: &pb.Result{Success: false, Error: &pb.ErrorDetails{Code: "NOT_IMPLEMENTED", Message: "Coming soon!"}}}, nil
}

func (e *EnvironmentsService) GetThemes(ctx context.Context, req *pb.GetThemesRequest) (*pb.GetThemesResponse, error) {
	return &pb.GetThemesResponse{Status: &pb.Result{Success: false, Error: &pb.ErrorDetails{Code: "NOT_IMPLEMENTED", Message: "Coming soon!"}}}, nil
}

func (e *EnvironmentsService) ApplyTheme(ctx context.Context, req *pb.ApplyThemeRequest) (*pb.ApplyThemeResponse, error) {
	return &pb.ApplyThemeResponse{Status: &pb.Result{Success: false, Error: &pb.ErrorDetails{Code: "NOT_IMPLEMENTED", Message: "Coming soon!"}}}, nil
}

func (e *EnvironmentsService) GetShapeTemplates(ctx context.Context, req *pb.GetShapeTemplatesRequest) (*pb.GetShapeTemplatesResponse, error) {
	return &pb.GetShapeTemplatesResponse{Status: &pb.Result{Success: false, Error: &pb.ErrorDetails{Code: "NOT_IMPLEMENTED", Message: "Coming soon!"}}}, nil
}

func (e *EnvironmentsService) CreateCustomShape(ctx context.Context, req *pb.CreateCustomShapeRequest) (*pb.CreateCustomShapeResponse, error) {
	return &pb.CreateCustomShapeResponse{Status: &pb.Result{Success: false, Error: &pb.ErrorDetails{Code: "NOT_IMPLEMENTED", Message: "Coming soon!"}}}, nil
}

func (e *EnvironmentsService) AnalyzeCapacity(ctx context.Context, req *pb.AnalyzeCapacityRequest) (*pb.AnalyzeCapacityResponse, error) {
	return &pb.AnalyzeCapacityResponse{Status: &pb.Result{Success: false, Error: &pb.ErrorDetails{Code: "NOT_IMPLEMENTED", Message: "Coming soon!"}}}, nil
}

func (e *EnvironmentsService) GetOptimalSize(ctx context.Context, req *pb.GetOptimalSizeRequest) (*pb.GetOptimalSizeResponse, error) {
	return &pb.GetOptimalSizeResponse{Status: &pb.Result{Success: false, Error: &pb.ErrorDetails{Code: "NOT_IMPLEMENTED", Message: "Coming soon!"}}}, nil
}

// SelectablesService stub
type SelectablesService struct {
	pb.UnimplementedSelectablesServiceServer
}

func NewSelectablesService() *SelectablesService {
	return &SelectablesService{}
}

func (s *SelectablesService) CreateTable(ctx context.Context, req *pb.CreateTableRequest) (*pb.CreateTableResponse, error) {
	return &pb.CreateTableResponse{Status: &pb.Result{Success: false, Error: &pb.ErrorDetails{Code: "NOT_IMPLEMENTED", Message: "SelectablesService implementation coming soon!"}}}, nil
}

func (s *SelectablesService) AddItem(ctx context.Context, req *pb.AddItemRequest) (*pb.AddItemResponse, error) {
	return &pb.AddItemResponse{Status: &pb.Result{Success: false, Error: &pb.ErrorDetails{Code: "NOT_IMPLEMENTED", Message: "Coming soon!"}}}, nil
}

func (s *SelectablesService) RemoveItem(ctx context.Context, req *pb.RemoveItemRequest) (*pb.RemoveItemResponse, error) {
	return &pb.RemoveItemResponse{Status: &pb.Result{Success: false, Error: &pb.ErrorDetails{Code: "NOT_IMPLEMENTED", Message: "Coming soon!"}}}, nil
}

func (s *SelectablesService) UpdateWeight(ctx context.Context, req *pb.UpdateWeightRequest) (*pb.UpdateWeightResponse, error) {
	return &pb.UpdateWeightResponse{Status: &pb.Result{Success: false, Error: &pb.ErrorDetails{Code: "NOT_IMPLEMENTED", Message: "Coming soon!"}}}, nil
}

func (s *SelectablesService) Select(ctx context.Context, req *pb.SelectRequest) (*pb.SelectResponse, error) {
	return &pb.SelectResponse{Status: &pb.Result{Success: false, Error: &pb.ErrorDetails{Code: "NOT_IMPLEMENTED", Message: "Coming soon!"}}}, nil
}

func (s *SelectablesService) SelectMultiple(ctx context.Context, req *pb.SelectMultipleRequest) (*pb.SelectMultipleResponse, error) {
	return &pb.SelectMultipleResponse{Status: &pb.Result{Success: false, Error: &pb.ErrorDetails{Code: "NOT_IMPLEMENTED", Message: "Coming soon!"}}}, nil
}

func (s *SelectablesService) SelectWithContext(ctx context.Context, req *pb.SelectWithContextRequest) (*pb.SelectWithContextResponse, error) {
	return &pb.SelectWithContextResponse{Status: &pb.Result{Success: false, Error: &pb.ErrorDetails{Code: "NOT_IMPLEMENTED", Message: "Coming soon!"}}}, nil
}

func (s *SelectablesService) GetTable(ctx context.Context, req *pb.GetTableRequest) (*pb.GetTableResponse, error) {
	return &pb.GetTableResponse{Status: &pb.Result{Success: false, Error: &pb.ErrorDetails{Code: "NOT_IMPLEMENTED", Message: "Coming soon!"}}}, nil
}

func (s *SelectablesService) ListTables(ctx context.Context, req *pb.ListTablesRequest) (*pb.ListTablesResponse, error) {
	return &pb.ListTablesResponse{Status: &pb.Result{Success: false, Error: &pb.ErrorDetails{Code: "NOT_IMPLEMENTED", Message: "Coming soon!"}}}, nil
}

func (s *SelectablesService) DeleteTable(ctx context.Context, req *pb.DeleteTableRequest) (*pb.DeleteTableResponse, error) {
	return &pb.DeleteTableResponse{Status: &pb.Result{Success: false, Error: &pb.ErrorDetails{Code: "NOT_IMPLEMENTED", Message: "Coming soon!"}}}, nil
}

func (s *SelectablesService) CloneTable(ctx context.Context, req *pb.CloneTableRequest) (*pb.CloneTableResponse, error) {
	return &pb.CloneTableResponse{Status: &pb.Result{Success: false, Error: &pb.ErrorDetails{Code: "NOT_IMPLEMENTED", Message: "Coming soon!"}}}, nil
}

func (s *SelectablesService) GetProbabilities(ctx context.Context, req *pb.GetProbabilitiesRequest) (*pb.GetProbabilitiesResponse, error) {
	return &pb.GetProbabilitiesResponse{Status: &pb.Result{Success: false, Error: &pb.ErrorDetails{Code: "NOT_IMPLEMENTED", Message: "Coming soon!"}}}, nil
}

func (s *SelectablesService) TestDistribution(ctx context.Context, req *pb.TestDistributionRequest) (*pb.TestDistributionResponse, error) {
	return &pb.TestDistributionResponse{Status: &pb.Result{Success: false, Error: &pb.ErrorDetails{Code: "NOT_IMPLEMENTED", Message: "Coming soon!"}}}, nil
}

func (s *SelectablesService) MergeTables(ctx context.Context, req *pb.MergeTablesRequest) (*pb.MergeTablesResponse, error) {
	return &pb.MergeTablesResponse{Status: &pb.Result{Success: false, Error: &pb.ErrorDetails{Code: "NOT_IMPLEMENTED", Message: "Coming soon!"}}}, nil
}

// ConditionsService stub  
type ConditionsService struct {
	pb.UnimplementedConditionsServiceServer
}

func NewConditionsService() *ConditionsService {
	return &ConditionsService{}
}

func (c *ConditionsService) ApplyCondition(ctx context.Context, req *pb.ApplyConditionRequest) (*pb.ApplyConditionResponse, error) {
	return &pb.ApplyConditionResponse{Status: &pb.Result{Success: false, Error: &pb.ErrorDetails{Code: "NOT_IMPLEMENTED", Message: "ConditionsService implementation coming soon!"}}}, nil
}

// ResourcesService stub
type ResourcesService struct {
	pb.UnimplementedResourceServiceServer
}

func NewResourcesService() *ResourcesService {
	return &ResourcesService{}
}

func (r *ResourcesService) CreateResourcePool(ctx context.Context, req *pb.CreateResourcePoolRequest) (*pb.CreateResourcePoolResponse, error) {
	return &pb.CreateResourcePoolResponse{Status: &pb.Result{Success: false, Error: &pb.ErrorDetails{Code: "NOT_IMPLEMENTED", Message: "ResourcesService implementation coming soon!"}}}, nil
}

// SpellsService stub
type SpellsService struct {
	pb.UnimplementedSpellServiceServer
}

func NewSpellsService() *SpellsService {
	return &SpellsService{}
}

func (s *SpellsService) GetSpell(ctx context.Context, req *pb.GetSpellRequest) (*pb.GetSpellResponse, error) {
	return &pb.GetSpellResponse{Status: &pb.Result{Success: false, Error: &pb.ErrorDetails{Code: "NOT_IMPLEMENTED", Message: "SpellsService implementation coming soon!"}}}, nil
}

// SpawnService stub
type SpawnService struct {
	pb.UnimplementedSpawnServiceServer
}

func NewSpawnService() *SpawnService {
	return &SpawnService{}
}

func (s *SpawnService) CreateSpawnEngine(ctx context.Context, req *pb.CreateSpawnEngineRequest) (*pb.CreateSpawnEngineResponse, error) {
	return &pb.CreateSpawnEngineResponse{Status: &pb.Result{Success: false, Error: &pb.ErrorDetails{Code: "NOT_IMPLEMENTED", Message: "SpawnService implementation coming soon!"}}}, nil
}