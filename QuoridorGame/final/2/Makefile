# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -std=c++20 -fPIE -fopenmp -O3 -ljsoncpp

# Linker flags
LDFLAGS = -L/usr/local/lib -fPIE -std=c++20

# Directories
SRC_DIR = .
OBJ_DIR = obj
BIN_DIR = bin

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# Object files
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# Executable name
TARGET = $(BIN_DIR)/quoridor

# Libraries to link
LIBS = -lboost_system -lboost_json -lboost_thread -lboost_filesystem

# Default target
all: $(TARGET)

# Create bin and obj directories if they don't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Rule to build the executable
$(TARGET): $(OBJ_DIR) $(BIN_DIR) $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) $(LDFLAGS) $(LIBS) -o $@

# Rule to build object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean
