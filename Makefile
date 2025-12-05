# Makefile для сборки проекта "Социальная сеть - анализ связей"

# Компилятор и флаги
CXX = g++
CXXFLAGS = -Wall -std=c++11

# Имя исполняемого файла
TARGET = social_network

# Исходные файлы
SOURCES = main.cpp

# Заголовочные файлы (для зависимостей)
HEADERS = graph.h warshall.h floyd.h analysis.h spread.h

# Правило по умолчанию
all: $(TARGET)

# Компиляция программы
$(TARGET): $(SOURCES) $(HEADERS)
	@echo "Компиляция проекта..."
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)
	@echo "Готово! Запустите ./$(TARGET)"

# Запуск программы
run: $(TARGET)
	@echo "Запуск программы..."
	@./$(TARGET)

# Очистка скомпилированных файлов
clean:
	@echo "Очистка..."
	rm -f $(TARGET)
	@echo "Очистка завершена"

# Пересборка проекта
rebuild: clean all

.PHONY: all run clean rebuild
