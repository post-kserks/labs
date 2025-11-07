CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

# Сборка всей программы
all: main

main: main.o brute_force.o optimal.o
	$(CXX) $(CXXFLAGS) -o $@ $^

main.o: main.cpp brute_force.h optimal.h
	$(CXX) $(CXXFLAGS) -c main.cpp

brute_force.o: brute_force.cpp brute_force.h
	$(CXX) $(CXXFLAGS) -c brute_force.cpp

optimal.o: optimal.cpp optimal.h
	$(CXX) $(CXXFLAGS) -c optimal.cpp

# Очистка собранных файлов
clean:
	rm -f *.o main
