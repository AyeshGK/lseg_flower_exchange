# Directories
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build

# Compiler flags for C++
CXXFLAGS = -std=c++11 -Wall

# Targets
all: $(BUILD_DIR)/final

$(BUILD_DIR)/final: $(BUILD_DIR)/main.o $(BUILD_DIR)/hello.o
	@echo "Linking and producing executable..."
	g++ $(CXXFLAGS) -o $@ $^

$(BUILD_DIR)/main.o: $(SRC_DIR)/main.cpp
	@echo "Compiling main.cpp..."
	g++ $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

$(BUILD_DIR)/hello.o: $(SRC_DIR)/hello.cpp
	@echo "Compiling hello.cpp..."
	g++ $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

clean:
	@echo "Cleaning up..."
	rm -f $(BUILD_DIR)/*.o $(BUILD_DIR)/final

.PHONY: all clean

run: $(BUILD_DIR)/final
	@echo "Running final executable..."
	./$<
