# Makefile для C++ проекта
CXX = g++
CXXFLAGS = -Wall -std=c++11
TARGET = lab5
SOURCES = main.cpp counting_sort.cpp

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: clean run
