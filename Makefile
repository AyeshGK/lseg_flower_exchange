# Directories
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build
DATA_DIR = data

# Compiler flags for C++
CXXFLAGS = -std=c++11 -Wall

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/dao/*.cpp) $(wildcard $(SRC_DIR)/service/*.cpp) $(wildcard $(SRC_DIR)/model/*.cpp) $(wildcard $(SRC_DIR)/factory/*.cpp)

# Header files
INCLUDES = -I$(INCLUDE_DIR)

# Object files
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

# Targets
all: $(BUILD_DIR)/final

$(BUILD_DIR)/final: $(OBJS)
	@echo "Linking and producing executable..."
	g++ $(CXXFLAGS) -o $@ $^

# Create necessary directories before compiling
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	@echo "Compiling $<..."
	g++ $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Clean up
clean:
	@echo "Cleaning up..."
	rm -rf $(BUILD_DIR)/*

.PHONY: all clean

run: $(BUILD_DIR)/final
	@echo "Running final executable..."
	./$<
