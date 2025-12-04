# Компилятор и флаги
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

# Имя исполняемого файла
TARGET = decision_trees

# Исходные файлы
SOURCES = main.cpp

# Объектные файлы
OBJECTS = $(SOURCES:.cpp=.o)

# Правило по умолчанию
all: $(TARGET)

# Правило сборки исполняемого файла
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)
	@echo "✓ Сборка завершена успешно!"

# Правило компиляции объектных файлов
%.o: %.cpp data.h entropy.h id3.h c45.h cart.h chaid.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Правило для запуска программы
run: $(TARGET)
	@echo "════════════════════════════════════════════════════════════════════════"
	@echo "Запуск программы построения деревьев решений..."
	@echo "════════════════════════════════════════════════════════════════════════"
	@./$(TARGET)

# Правило очистки
clean:
	rm -f $(OBJECTS) $(TARGET)
	@echo "✓ Очистка выполнена"

# Правило для пересборки
rebuild: clean all

# Правило для отображения справки
help:
	@echo "Доступные команды:"
	@echo "  make        - собрать проект"
	@echo "  make run    - собрать и запустить программу"
	@echo "  make clean  - удалить объектные файлы и исполняемый файл"
	@echo "  make rebuild - пересобрать проект с нуля"
	@echo "  make help   - показать эту справку"

.PHONY: all run clean rebuild help
