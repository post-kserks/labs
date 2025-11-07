CXX = g++
CXXFLAGS = -std=c++11 -Wall
TARGET = lab6
SOURCES = main.cpp jordan_gauss.cpp

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -f $(TARGET)

.PHONY: clean
