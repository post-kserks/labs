CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2 -Iinclude -Isrc
SRCDIR = src
SOURCES = $(SRCDIR)/main.cpp $(SRCDIR)/integration_methods.cpp $(SRCDIR)/math_functions.cpp $(SRCDIR)/time_measurement.cpp
TARGET = numerical_integration

.PHONY: all clean run test

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -f $(TARGET) test_integration

run: $(TARGET)
	./$(TARGET)

test:
	$(CXX) $(CXXFLAGS) -o test_integration tests/test_integration.cpp $(SRCDIR)/integration_methods.cpp $(SRCDIR)/math_functions.cpp
	./test_integration
