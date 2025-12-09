CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall

# Исходные файлы
SRCS = main.cpp median.cpp intersection.cpp minmax.cpp
HEADERS = median.h intersection.h minmax.h

# Объектные файлы
OBJS = $(SRCS:.cpp=.o)

# Исполняемый файл
TARGET = lab

# Правила сборки
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Очистка
clean:
	rm -f $(OBJS) $(TARGET)

# Запуск
run: $(TARGET)
	./$(TARGET)

.PHONY: clean run