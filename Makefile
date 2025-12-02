# Makefile для лабораторной работы - Вариант 16
# Компиляция проекта AdaBoost + Camellia

# Компилятор и флаги
CXX = g++
CXXFLAGS = -std=c++11 -Wall -O2

# Имя исполняемого файла
TARGET = lab_variant16

# Объектные файлы
OBJS = main.o adaboost.o camellia.o csv_loader.o

# Правило по умолчанию - собрать исполняемый файл
all: $(TARGET)

# Сборка исполняемого файла
$(TARGET): $(OBJS)
	@echo "Сборка исполняемого файла $(TARGET)..."
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)
	@echo "Сборка завершена успешно!"

# Компиляция main.cpp
main.o: main.cpp adaboost.h camellia.h
	@echo "Компиляция main.cpp..."
	$(CXX) $(CXXFLAGS) -c main.cpp

# Компиляция adaboost.cpp
adaboost.o: adaboost.cpp adaboost.h
	@echo "Компиляция adaboost.cpp..."
	$(CXX) $(CXXFLAGS) -c adaboost.cpp

# Компиляция camellia.cpp
camellia.o: camellia.cpp camellia.h
	@echo "Компиляция camellia.cpp..."
	$(CXX) $(CXXFLAGS) -c camellia.cpp

# Компиляция csv_loader.cpp
csv_loader.o: csv_loader.cpp csv_loader.h adaboost.h
	@echo "Компиляция csv_loader.cpp..."
	$(CXX) $(CXXFLAGS) -c csv_loader.cpp

# Запуск программы
run: $(TARGET)
	@echo "Запуск программы..."
	@echo ""
	./$(TARGET)

# Очистка скомпилированных файлов
clean:
	@echo "Удаление объектных файлов и исполняемого файла..."
	rm -f $(OBJS) $(TARGET)
	@echo "Очистка завершена."

# Полная пересборка
rebuild: clean all

# Информация о проекте
info:
	@echo "=========================================="
	@echo "  Лабораторная работа - Вариант 16"
	@echo "=========================================="
	@echo "Файлы проекта:"
	@echo "  - main.cpp        : главный файл"
	@echo "  - adaboost.cpp/h  : реализация AdaBoost"
	@echo "  - camellia.cpp/h  : реализация Camellia"
	@echo ""
	@echo "Команды:"
	@echo "  make       : собрать проект"
	@echo "  make run   : собрать и запустить"
	@echo "  make clean : удалить скомпилированные файлы"
	@echo "  make rebuild : полная пересборка"
	@echo "=========================================="

.PHONY: all run clean rebuild info
