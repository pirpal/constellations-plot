# C compiler
#CC = gcc
CC = clang

# Flags
CFLAGS = -g -Wall -Wextra --std=c11 -pedantic

# Directories
BIN_DIR      = bin
OBJ_DIR      = obj
SRC_DIR      = src
TEST_DIR     = tests
TEST_BIN_DIR = $(TEST_DIR)/bin

# SDL2 links
SDL_LIBS     = $(shell pkg-config --libs sdl2)
SDL_FLAGS    = $(shell pkg-config --cflags sdl2)

# Test framework link
CRITERION = -lcriterion

# Math library link
MATH = -lm

# Executable
BIN = $(BIN_DIR)/CONSTELLATIONS

# Source files
SRC = $(wildcard $(SRC_DIR)/*.c)

# Object files
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

# Tests source files
TESTS = $(wildcard $(TEST_DIR)/*.c)

# Tests object files (exclude main.c from test objects)
TEST_OBJ = $(subst $(OBJ_DIR)/main.o,,$(OBJ))

# Tests executables
TEST_BIN = $(patsubst $(TEST_DIR)/%.c, $(TEST_BIN_DIR)/%, $(TESTS))

# COMMANDS -------------------------- 
# [make] General compilation command
all: $(BIN)

# Executable linkage from object files
$(BIN): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

# Objects separated compilation
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Tests executables linkage
$(TEST_BIN_DIR)/%: $(TEST_DIR)/%.c
	$(CC) $(CFLAGS) $< $(TEST_OBJ) -o $@ $(CRITERION)

# [make test] Compile and run tests
test: $(TEST_BIN)
	for test in $(TEST_BIN) ; do ./$$test ; done

# [make clean] Remove objects files and executables
clean:
	rm -f $(OBJ_DIR)/*.o $(BIN_DIR)/* $(TEST_BIN_DIR)/*

