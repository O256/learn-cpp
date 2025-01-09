# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++17 -Wall

# Directories
DEPS_DIR = deps
SRC_DIR = src
INCLUDE_DIR = include
SHADER_DIR = shaders
BUILD_DIR = build

# Include directories
INCLUDES = -I$(DEPS_DIR)/glad/include \
          -I$(DEPS_DIR)/glfw/include \
          -I$(DEPS_DIR) \
          -I$(INCLUDE_DIR)

# Library directories
LDFLAGS = -L$(DEPS_DIR)/glfw/lib-mingw-w64

# Libraries
LIBS = -lglfw3 -lopengl32 -lgdi32 -lmingwex -lglu32

# Source files
SRCS = $(SRC_DIR)/main.cpp \
       $(DEPS_DIR)/glad/src/glad.c

# Object files (in build directory)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
OBJS := $(OBJS:$(DEPS_DIR)/%.c=$(BUILD_DIR)/%.o)

# Shader files
SHADERS = $(SHADER_DIR)/basic.vert $(SHADER_DIR)/basic.frag

# Executable name
EXEC = $(BUILD_DIR)/test_opengl.exe

# Create necessary directories
$(shell if not exist "$(BUILD_DIR)" mkdir "$(BUILD_DIR)")
$(shell if not exist "$(BUILD_DIR)\glad\src" mkdir "$(BUILD_DIR)\glad\src")

# Default target
all: $(EXEC) copy_shaders

# Build executable
$(EXEC): $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) -o $@ $(LIBS)

# Compile C++ source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | create_dirs
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Compile C source files (for glad)
$(BUILD_DIR)/glad/src/%.o: $(DEPS_DIR)/glad/src/%.c | create_dirs
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Create necessary directories
create_dirs:
	@if not exist "$(BUILD_DIR)" mkdir "$(BUILD_DIR)"
	@if not exist "$(BUILD_DIR)\glad\src" mkdir "$(BUILD_DIR)\glad\src"

# Copy shader files to build directory
copy_shaders: | create_dirs
	@if not exist "$(BUILD_DIR)\$(SHADER_DIR)" mkdir "$(BUILD_DIR)\$(SHADER_DIR)"
	@copy /Y "$(SHADER_DIR)\*.vert" "$(BUILD_DIR)\$(SHADER_DIR)" >nul 2>&1
	@copy /Y "$(SHADER_DIR)\*.frag" "$(BUILD_DIR)\$(SHADER_DIR)" >nul 2>&1

# Print variables for debugging
debug:
	@echo "Source files: $(SRCS)"
	@echo "Object files: $(OBJS)"
	@echo "Include paths: $(INCLUDES)"

# Run the program
run: $(EXEC)
	@cd $(BUILD_DIR) && .\test_opengl.exe

# Clean up
clean:
	@if exist "$(BUILD_DIR)" rd /s /q "$(BUILD_DIR)"

# Phony targets
.PHONY: all clean run copy_shaders create_dirs debug
