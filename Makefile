# Компилятор и флаги
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11

# Имя исполняемого файла
TARGET = slau_solver

# Исходные файлы
SOURCES = main.cpp jordan_gauss.cpp

# Сборка проекта
$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

# Очистка
clean:
	rm -f $(TARGET)

# Запуск
run: $(TARGET)
	./$(TARGET)

.PHONY: clean run
