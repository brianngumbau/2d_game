# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -I./include -I./SDL2/include

# Linker flags for SDL2 (add SDL2main for Windows)
LIBS = -L./SDL2/lib -lmingw32 -lSDL2main -lSDL2


# Source and output directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Output executable
TARGET = $(BIN_DIR)/2d_maze_game

# List of source files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# Object files corresponding to source files
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# Rule to build the final executable
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(OBJS) $(LIBS) -o $(TARGET)

# Rule to build object files from source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build artifacts
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Run the game
run: $(TARGET)
	./$(TARGET)

.PHONY: clean run