# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++11 -Wall

# Directories
SRC_DIR := src
BUILD_DIR := build
INCLUDE_DIR := include
DATA_DIR := data
RESULTS_DIR := $(DATA_DIR)/results

# Source files
SRCS := $(wildcard $(SRC_DIR)/**/*.cpp $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

# Include directories
INC_DIRS := -I$(INCLUDE_DIR)

# Executable
TARGET := my_program

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INC_DIRS) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INC_DIRS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

run: $(TARGET)
	./$(TARGET)

# Add additional dependencies here if needed

# Example: Dependency for CSVReader.cpp
$(BUILD_DIR)/service/CSVReader.o: $(INCLUDE_DIR)/service/CSVReader.h

# Example: Dependency for NewMatchingEngine.cpp
$(BUILD_DIR)/service/NewMatchingEngine.o: $(INCLUDE_DIR)/service/NewMatchingEngine.h

# Add more dependencies as needed
