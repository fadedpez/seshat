.PHONY: generate build run clean test

# Generate protobuf code
generate:
	cd ../Protos && buf generate

# Build the server
build: generate
	go build -o bin/seshat-server ./cmd/server

# Run the server
run: build
	./bin/seshat-server

# Run with live reload (requires air: go install github.com/cosmtrek/air@latest)
dev:
	air -c .air.toml

# Clean generated files and binaries
clean:
	rm -rf generated/
	rm -rf bin/
	cd ../Protos && rm -rf generated/

# Run tests
test: generate
	go test ./...

# Install dependencies
deps:
	go mod download
	go mod tidy

# Install development tools
install-tools:
	go install github.com/cosmtrek/air@latest
	go install github.com/bufbuild/buf/cmd/buf@latest