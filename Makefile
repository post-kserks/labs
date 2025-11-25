# Makefile для lab9
CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall

SRCS = main.cpp algorithms.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = lab9

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp algorithms.h data.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
