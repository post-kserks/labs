CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

TARGET = lab11_executable
SRCS = main.cpp graph.cpp
HEADERS = graph.h

$(TARGET): $(SRCS) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: clean
