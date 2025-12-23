# Компилятор
CXX = g++
# Флаги компиляции
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
# Имя исполняемого файла
TARGET = solve_lp
# Исходные файлы
SRCS = main.cpp simplex.cpp
# Объектные файлы
OBJS = $(SRCS:.cpp=.o)

# Правило по умолчанию
all: $(TARGET)

# Сборка исполняемого файла
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Компиляция .cpp в .o
%.o: %.cpp simplex.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Очистка
clean:
	rm -f $(OBJS) $(TARGET)

# Пересборка
rebuild: clean all

.PHONY: all clean rebuild