CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall
INCLUDES = -Iinclude
BIN_DIR = bin
SRC_DIR = src
BENCH_DIR = bench

all: $(BIN_DIR)/hull

$(BIN_DIR)/hull: $(SRC_DIR)/main.cpp $(SRC_DIR)/convex_hull.cpp $(SRC_DIR)/brute_force.cpp $(SRC_DIR)/utils.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@

$(BIN_DIR)/bench: $(BENCH_DIR)/bench.cpp $(SRC_DIR)/convex_hull.cpp $(SRC_DIR)/brute_force.cpp $(SRC_DIR)/utils.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@

bench: $(BIN_DIR)/bench
	@echo "== Запуск бенчмарка =="
	@./$(BIN_DIR)/bench

clean:
	rm -f $(BIN_DIR)/*
