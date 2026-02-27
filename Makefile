CC := clang
CXX := clang++
CFLAGS := -Wall -Wextra -std=c11 -O2
CXXFLAGS := -Wall -Wextra -std=c++17 -O2

SRC_DIR := src
OBJ_DIR := obj
INC_DIR := include
BIN_DIR := bin

# Source files
C_SRCS := $(wildcard $(SRC_DIR)/*.c)
CXX_SRCS := $(wildcard $(SRC_DIR)/*.cpp)

# Object files
C_OBJS := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(C_SRCS))
CXX_OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(CXX_SRCS))
OBJS := $(C_OBJS) $(CXX_OBJS)

TARGET := $(BIN_DIR)/anomaly_detection

.PHONY: all clean run test help

all: $(TARGET)

$(TARGET): $(OBJS) | $(BIN_DIR)
	@echo "Linking $(TARGET)..."
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@ -lm
	@echo "Build complete: $(TARGET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@echo "Compiling $<..."
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	@echo "Compiling $<..."
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

clean:
	@echo "Cleaning build artifacts..."
	rm -rf $(OBJ_DIR) $(BIN_DIR)
	@echo "Clean complete."

run: $(TARGET)
	@echo "Running anomaly detection with sample data..."
	@./$(TARGET) -i examples/sample_data.csv -v

test: $(TARGET)
	@echo "Running tests..."
	@echo "Test 1: Basic stdin input"
	@echo "1,2,3,4,5,100" | ./$(TARGET)
	@echo ""
	@echo "Test 2: File input with IQR method"
	@./$(TARGET) -i examples/sample_data.csv -m iqr
	@echo ""
	@echo "Test 3: JSON output"
	@./$(TARGET) -i examples/sample_data.csv -f json -o test_output.json
	@echo ""
	@echo "Test 4: MAD method with verbose"
	@./$(TARGET) -i examples/sample_data.csv -m mad -v

help:
	@echo "Anomaly Detection - Makefile Help"
	@echo ""
	@echo "Available targets:"
	@echo "  all     - Build the project (default)"
	@echo "  clean   - Remove build artifacts"
	@echo "  run     - Build and run with sample data"
	@echo "  test    - Run test suite"
	@echo "  help    - Show this help message"
	@echo ""
	@echo "Usage examples:"
	@echo "  make              # Build the project"
	@echo "  make clean        # Clean build files"
	@echo "  make run          # Run with sample data"
	@echo "  make test         # Run tests"
