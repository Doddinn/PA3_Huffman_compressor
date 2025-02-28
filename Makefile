# Makefile for a simple C++ project using C++11

# Compiler and flags
CXX      = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2

# Target name
TARGET   = myprogram

# Source files
SRCS     = main.cpp compressor.cpp

# Object files (same as SRCS but with .o extension)
OBJS     = $(SRCS:.cpp=.o)

# Default rule: build the target
all: $(TARGET)

# Link step: create the final executable from object files
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

# Compile each .cpp into a .o
%.o: %.cpp header.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule: remove object files and the executable
clean:
	rm -f $(OBJS) $(TARGET)

# PHONY targets
.PHONY: all clean
