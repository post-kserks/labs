# Makefile
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
SRCDIR = src
SOURCES = $(SRCDIR)/matrix.cpp
MAIN_SOURCE = $(SRCDIR)/main.cpp
TEST_SOURCE = $(SRCDIR)/test.cpp
MAIN_APP = matrix_app
TEST_APP = test_app

.PHONY: all main test docs clean

all: main test

main: $(SOURCES) $(MAIN_SOURCE)
	$(CXX) $(CXXFLAGS) -o $(MAIN_APP) $(SOURCES) $(MAIN_SOURCE)

test: $(SOURCES) $(TEST_SOURCE)
	$(CXX) $(CXXFLAGS) -o $(TEST_APP) $(SOURCES) $(TEST_SOURCE)

docs:
	doxygen Doxyfile

clean:
	rm -f $(MAIN_APP) $(TEST_APP)
	rm -rf docs/html/ docs/latex/

run-test: test
	./$(TEST_APP)

run-demo: main
	./$(MAIN_APP)

memcheck: test
	valgrind --leak-check=full ./$(TEST_APP)

all-check: test
	./$(TEST_APP)
	valgrind --leak-check=full ./$(TEST_APP)
