CXX = g++
CXXFLAGS = -O2 -std=c++17

all: lab7p1

lab7p1: main.o sort.o search.o points.o
	$(CXX) $(CXXFLAGS) -o lab7p1 main.o sort.o search.o points.o

main.o: main.cpp sort.h search.h points.h utils.h
	$(CXX) $(CXXFLAGS) -c main.cpp

sort.o: sort.cpp sort.h utils.h
	$(CXX) $(CXXFLAGS) -c sort.cpp

search.o: search.cpp search.h utils.h
	$(CXX) $(CXXFLAGS) -c search.cpp

points.o: points.cpp points.h utils.h
	$(CXX) $(CXXFLAGS) -c points.cpp

clean:
	rm -f *.o lab7p1
