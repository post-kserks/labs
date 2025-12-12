CC = g++
CFLAGS = -std=c++11 -Wall

all: lab_heap

lab_heap: main.o heap.o
	$(CC) $(CFLAGS) -o lab_heap main.o heap.o

main.o: main.cpp heap.h
	$(CC) $(CFLAGS) -c main.cpp

heap.o: heap.cpp heap.h
	$(CC) $(CFLAGS) -c heap.cpp

clean:
	rm -f *.o lab_heap
