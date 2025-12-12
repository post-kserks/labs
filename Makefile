# Компилятор и флаги
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

# Директории
TREE_DIR = trees
SORT_DIR = sorting

# Исходные файлы
TREE_SOURCES = $(TREE_DIR)/avl.cpp $(TREE_DIR)/tree23.cpp
SORT_SOURCES = $(SORT_DIR)/merge.cpp $(SORT_DIR)/quick.cpp $(SORT_DIR)/heap.cpp $(SORT_DIR)/test_sorts.cpp
MAIN_SOURCE = main.cpp

# Объектные файлы
TREE_OBJECTS = $(TREE_SOURCES:.cpp=.o)
SORT_OBJECTS = $(SORT_SOURCES:.cpp=.o)
MAIN_OBJECT = $(MAIN_SOURCE:.cpp=.o)

# Исполняемые файлы
TARGET = lab
SORT_TARGET = test_sorts

# Правила сборки
all: $(TARGET)

sorts: $(SORT_TARGET)

$(TARGET): $(TREE_OBJECTS) $(SORT_OBJECTS) $(MAIN_OBJECT)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(SORT_TARGET): $(SORT_OBJECTS) test_sorts_main.o
	$(CXX) $(CXXFLAGS) -o $@ $^

# Компиляция объектных файлов
$(TREE_DIR)/%.o: $(TREE_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(SORT_DIR)/%.o: $(SORT_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Зависимости
$(TREE_DIR)/avl.o: $(TREE_DIR)/avl.h
$(TREE_DIR)/tree23.o: $(TREE_DIR)/tree23.h
$(SORT_DIR)/merge.o: $(SORT_DIR)/merge.h
$(SORT_DIR)/quick.o: $(SORT_DIR)/quick.h
$(SORT_DIR)/heap.o: $(SORT_DIR)/heap.h
$(SORT_DIR)/test_sorts.o: $(SORT_DIR)/test_sorts.h $(SORT_DIR)/merge.h $(SORT_DIR)/quick.h $(SORT_DIR)/heap.h
test_sorts_main.o: test_sorts_main.cpp $(SORT_DIR)/merge.h $(SORT_DIR)/quick.h $(SORT_DIR)/heap.h
$(MAIN_OBJECT): $(TREE_DIR)/avl.h $(TREE_DIR)/tree23.h $(SORT_DIR)/merge.h $(SORT_DIR)/quick.h $(SORT_DIR)/heap.h $(SORT_DIR)/test_sorts.h

# Очистка
clean:
	rm -f $(TREE_OBJECTS) $(SORT_OBJECTS) $(MAIN_OBJECT) test_sorts_main.o $(TARGET) $(SORT_TARGET)

# Пересборка
rebuild: clean all

# Запуск
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean rebuild run

