CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

all: lab11p3

lab11p3: main.o methods.o
	$(CXX) $(CXXFLAGS) -o lab11p3 main.o methods.o

main.o: main.cpp matrix.h
	$(CXX) $(CXXFLAGS) -c main.cpp

methods.o: methods.cpp matrix.h
	$(CXX) $(CXXFLAGS) -c methods.cpp

clean:
	rm -f *.o lab11p3

.PHONY: all clean