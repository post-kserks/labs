# Makefile
CXX = g++
CXXFLAGS = -I./include -Wall -Wextra -std=c++17
DEBUG_FLAGS = -g -fsanitize=address
RELEASE_FLAGS = -O2

TARGET = maze_solver
BUILD_DIR = build
SRC_DIR = src

SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

.PHONY: all debug release clean run test

all: release

debug: CXXFLAGS += $(DEBUG_FLAGS)
debug: $(BUILD_DIR)/$(TARGET)

release: CXXFLAGS += $(RELEASE_FLAGS)
release: $(BUILD_DIR)/$(TARGET)

$(BUILD_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: debug
	./$(BUILD_DIR)/$(TARGET)

test: debug
	valgrind --leak-check=full --show-leak-kinds=all ./$(BUILD_DIR)/$(TARGET)

clean:
	rm -rf $(BUILD_DIR)
