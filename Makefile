CXX = g++
CXXFLAGS = -std=c++17 -O2
TARGET = sem10p1
SOURCES = main.cpp gauss.cpp gauss_seidel.cpp jacobi.cpp matrix_utils.cpp
HEADERS = gauss.h gauss_seidel.h jacobi.h matrix_utils.h

$(TARGET): $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -f $(TARGET)

.PHONY: clean