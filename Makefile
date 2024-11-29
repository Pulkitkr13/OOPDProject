# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
LDFLAGS = -L.  # Add the current directory (.) to library search path
BUILD_DIR = build
SRC_DIR = src
INCLUDE_DIR = include
EXECUTABLE = WifiSimulator
STATIC_LIB = libwifisimulator.a
DYNAMIC_LIB = libwifisimulator.so

# Source and object files
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
HEADERS = $(wildcard $(INCLUDE_DIR)/*.h)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SOURCES))

# Default target
all: $(BUILD_DIR)/$(EXECUTABLE) $(STATIC_LIB) $(DYNAMIC_LIB)

# Link object files into the executable
$(BUILD_DIR)/$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS) -lwifisimulator

# Compile source files into object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Build Static Library (.a)
$(STATIC_LIB): $(OBJECTS)
	ar rcs $@ $(OBJECTS)

# Build Dynamic Library (.so)
$(DYNAMIC_LIB): $(OBJECTS)
	$(CXX) -shared -o $@ $(OBJECTS)

# Clean build files
clean:
ifeq ($(OS),Windows_NT)
	del /q $(BUILD_DIR)\*
else
	rm -rf $(BUILD_DIR)/*
endif

# Debug build
debug: CXXFLAGS += -g
debug: clean all

# Optimized build
optimized: CXXFLAGS += -O3
optimized: clean all

.PHONY: all clean debug optimized
