CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2
TARGET = lab8
SOURCES = main.cpp algorithms.cpp metrics.cpp tests.cpp utils.cpp
HEADERS = graph.h algorithms.h metrics.h tests.h utils.h
OBJECTS = $(SOURCES:.cpp=.o)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJECTS)

run: $(TARGET)
	./$(TARGET)

.PHONY: clean run
