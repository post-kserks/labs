CXX = g++
CXXFLAGS = -Wall -Wextra -O2 -std=c++11
TARGET = lab6_jordan_gauss
SOURCES = main.cpp matrix_operations.cpp jordan_gauss.cpp io_operations.cpp validation.cpp
HEADERS = matrix_operations.h jordan_gauss.h io_operations.h validation.h

$(TARGET): $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: clean run
