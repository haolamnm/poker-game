# Makefile for building the project

PCH = include/pch.h
PCH_OUTPUT = bin/obj/pch.pch
PCH_SRC = src/pch.cpp
MAIN_OUTPUT = bin/main
SRC_DIR = src
OBJ_DIR = bin/obj

ifeq ($(OS),Windows_NT)
	MAIN_OUTPUT = bin/main.exe
endif

# Define the compiler
CC = g++
# Define the compiler flags
CFLAGS = -Wall -g -std=c++11

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/**/*.cpp)
# Object files
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

# Create the obj directory and its subdirectories if they don't exist
$(OBJ_DIR):
	@echo "Creating obj directory and subdirectories..."
ifeq ($(OS),Windows_NT)
	if not exist $(OBJ_DIR) mkdir $(OBJ_DIR)
	if not exist $(OBJ_DIR)\gui mkdir $(OBJ_DIR)\gui
	if not exist $(OBJ_DIR)\core mkdir $(OBJ_DIR)\core
else
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)/gui
	mkdir -p $(OBJ_DIR)/core
endif
	@echo "Created obj directory and subdirectories!"

# Compile the precompiled header
$(PCH_OUTPUT): $(PCH) | $(OBJ_DIR)
	@echo "Building precompiled header..."
ifeq ($(OS),Windows_NT)
	$(CC) -Iinclude -Iinclude/SDL2 -x c++-header -o $(PCH_OUTPUT) $(PCH)
else
	$(CC) $(CFLAGS) -Iinclude -I/opt/homebrew/include/SDL2 -x c++-header -o $(PCH_OUTPUT) $(PCH)
endif

# Compile each source file into an object file
$(OBJ_DIR)/gui/%.o: $(SRC_DIR)/gui/%.cpp $(PCH_OUTPUT) | $(OBJ_DIR)/gui
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -Iinclude -I/opt/homebrew/include/SDL2 -include $(PCH) -c $< -o $@

$(OBJ_DIR)/gameplay/%.o: $(SRC_DIR)/gameplay/%.cpp $(PCH_OUTPUT) | $(OBJ_DIR)/gameplay
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -Iinclude -I/opt/homebrew/include/SDL2 -include $(PCH) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(PCH_OUTPUT) | $(OBJ_DIR)
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -Iinclude -I/opt/homebrew/include/SDL2 -include $(PCH) -c $< -o $@

# Link the object files to create the main executable
$(MAIN_OUTPUT): $(OBJS)
	@echo "Linking..."
ifeq ($(OS),Windows_NT)
	$(CC) -Llib -o $(MAIN_OUTPUT) $(OBJS) -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
else
	$(CC) $(CFLAGS) -L/opt/homebrew/lib -o $(MAIN_OUTPUT) $(OBJS) -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
endif
	@echo "Linked!"

# Default target
all: $(PCH_OUTPUT) $(MAIN_OUTPUT)
	@echo "Build successful!"

# Clean target to remove built files
clean:
	@echo "Cleaning up..."
ifeq ($(OS),Windows_NT)
	del /Q $(PCH_OUTPUT) $(OBJ_DIR)\*.o $(MAIN_OUTPUT) 2>nul || exit 0
	rmdir /S /Q $(OBJ_DIR) 2>nul || exit 0
else
	rm -f $(PCH_OUTPUT) $(OBJ_DIR)/*.o $(MAIN_OUTPUT) 2>/dev/null || true
	rm -rf $(OBJ_DIR) 2>/dev/null || true
endif
	@echo "Cleaned up!"

# Run the main executable
run: $(MAIN_OUTPUT)
	@echo "Running $(MAIN_OUTPUT)..."
ifeq ($(OS),Windows_NT)
	$(MAIN_OUTPUT)
else
	./$(MAIN_OUTPUT)
endif
	@echo "Finished running $(MAIN_OUTPUT)!"
