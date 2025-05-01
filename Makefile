# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++20 -g -Wall -I./include -I./include/raylib -I./include/raygui -O3 -MMD

# Linker flags
LDFLAGS := -lraylib

# Directories
SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

# Source and object files
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))
DEPS := $(OBJS:.o=.d)

# Target executable
EXECUTABLE_NAME := vissort
TARGET := $(BIN_DIR)/$(EXECUTABLE_NAME)

# Detect OS
ifeq ($(OS), Windows_NT)
	DETECTED_OS := Windows
else
	DETECTED_OS := $(shell uname)
endif

# Add additional linking flags for Windows
ifeq ($(DETECTED_OS), Windows)
	LDFLAGS += -L./lib/windows_x64 -lwinmm -lgdi32
endif

# Add additional linking flags for Linux
ifeq ($(DETECTED_OS), Linux)
	LDFLAGS += -L./lib/linux_x64
endif

# Default rule
all: $(TARGET)

# Link object files into final executable
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

-include $(DEPS)

$(BIN_DIR) $(OBJ_DIR):
	mkdir $@

PHONY: clean run

# Delete executable
clean:
ifeq ($(DETECTED_OS), Windows)
	rmdir /s /q $(OBJ_DIR) $(BIN_DIR)
endif
ifeq ($(DETECTED_OS), Linux)
	rm -rf $(OBJ_DIR) $(BIN_DIR)
endif

# Build and run executable
run: $(TARGET)
#	cp -r assets/ bin/assets/   Copies assets into the bin directory. Might not be ideal. 
ifeq ($(DETECTED_OS), Windows)
	cd bin && $(EXECUTABLE_NAME)
else ifeq ($(DETECTED_OS), Linux)
	cd bin && ./$(EXECUTABLE_NAME)
endif