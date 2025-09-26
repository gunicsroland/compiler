# Project settings
TARGET := mycc
CXX := g++
CXXFLAGS := -std=c++20 -Wall -Wextra -Wpedantic -Iinclude
LDFLAGS :=

# Directories
SRC_DIR := src
OBJ_DIR := build/$(BUILD)
BIN_DIR := bin

# Sources and objects
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

# Default target
all: $(BIN_DIR)/$(TARGET)

# Link step
$(BIN_DIR)/$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

# Compile step
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run clang-tidy on all sources
tidy:
	clang-tidy $(SRCS) -p .

# Utility targets
clean:
	rm -rf build bin

rebuild: clean all

.PHONY: all clean rebuild tidy
