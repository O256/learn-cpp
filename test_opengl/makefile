# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -Wall

# Include directories
INCLUDES = -I./glad/include -I./glfw/include

# Library directories
LDFLAGS = -L./glfw/lib-mingw-w64

# Libraries
LIBS = -lglfw3 -lopengl32 -lgdi32 -lmingwex -lglu32

# Source files
SRCS = main.cpp glad/src/glad.c

# Object files
OBJS = main.o glad.o

# Executable name
EXEC = test_opengl.exe

# Default target
all: $(EXEC)

# Build executable
$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)

# Compile source files into object files
main.o: main.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

glad.o: glad/src/glad.c
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Clean up
clean:
	rm -f $(OBJS) $(EXEC)

# Phony targets
.PHONY: all clean
