CXX = g++
CXXFLAGS = -std=c++11 -O2 -Wall
TARGET = matrix_multiply
SOURCES = main.cpp matrix_operations.cpp strassen.cpp

# Основная цель сборки
$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

# Очистка
clean:
	rm -f $(TARGET)

# Пересборка
rebuild: clean $(TARGET)

# Запуск
run: $(TARGET)
	./$(TARGET)

.PHONY: clean rebuild run
