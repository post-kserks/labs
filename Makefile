# Makefile для компиляции проекта

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2
LDFLAGS = -lm
TARGET = nonlinear_solver
SOURCES = main.cpp
HEADERS = math_utils.h equation_systems.h bisection_method.h iteration_method.h newton_method.h results_table.h

all: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES) $(LDFLAGS)

clean:
	rm -f $(TARGET) *.o *.csv

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run