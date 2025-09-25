# Matrix Calculator

Полнофункциональная библиотека для работы с матрицами на C++ с полным циклом разработки: от кода до контейнеризации и CI/CD.

## 📋 О проекте

Этот проект представляет собой реализацию калькулятора матриц на C++17, включая:
- Базовые операции с матрицами (сложение, умножение, транспонирование)
- Создание матриц со случайными значениями
- Управление памятью без утечек
- Полную документацию с Doxygen
- Unit-тесты для всех функций
- Docker-контейнеризацию
- Автоматизированный CI/CD пайплайн

## 🚀 Возможности

### Основные функции
- `create_matrix()` - создание матрицы с заданными размерами
- `free_matrix()` - освобождение памяти матрицы
- `matrix_add()` - сложение матриц
- `matrix_multiply()` - умножение матриц
- `matrix_transpose()` - транспонирование матрицы
- `matrix_from_array()` - создание матрицы из массива
- `print_matrix()` - красивый вывод матрицы

### Индивидуальные функции
- `matrix_random()` - создание матрицы со случайными значениями в заданном диапазоне

## 📁 Структура проекта

```
matrix_calculator/
├── src/
│   ├── matrix.h          # Заголовочный файл с объявлениями
│   ├── matrix.cpp        # Реализация функций матриц
│   ├── main.cpp          # Демонстрационная программа
│   └── test.cpp          # Unit-тесты
├── docs/                 # Сгенерированная документация
├── .github/workflows/
│   └── ci.yml           # CI/CD конфигурация
├── Dockerfile           # Конфигурация Docker
├── Doxyfile            # Конфигурация Doxygen
├── Makefile            # Скрипты сборки
└── README.md           # Этот файл
```

## ⚙️ Установка и сборка

### Предварительные требования
- GCC (поддержка C++17)
- Doxygen (для документации)
- Graphviz (для визуализации в Doxygen)
- Docker (для контейнеризации)

### Установка зависимостей (Ubuntu/Debian)
```bash
sudo apt-get update
sudo apt-get install -y g++ doxygen graphviz docker.io make
```

### Сборка проекта
```bash
# Клонирование репозитория
git clone <repository-url>
cd matrix_calculator

# Сборка с помощью Makefile
make all

# Или ручная сборка
g++ -std=c++17 -o matrix_app src/matrix.cpp src/main.cpp
g++ -std=c++17 -o test_app src/matrix.cpp src/test.cpp
```

## 🧪 Тестирование

### Запуск тестов
```bash
# Запуск всех тестов
make run-test

# Или напрямую
./test_app
```

### Проверка памяти
```bash
# Проверка на утечки памяти
make memcheck

# Или с Valgrind
valgrind --leak-check=full ./test_app
```

## 📖 Документация

### Генерация документации
```bash
# Генерация HTML-документации
make docs

# Документация будет доступна в docs/html/index.html
```

### Просмотр документации
Откройте `docs/html/index.html` в браузере для просмотра полной документации по API.

## 🐳 Docker

### Сборка Docker-образа
```bash
docker build -t matrix-calculator .
```

### Запуск в Docker
```bash
# Запуск тестов в контейнере
docker run matrix-calculator

# Интерактивный запуск
docker run -it matrix-calculator /bin/bash

# Запуск демонстрации внутри контейнера
docker run -it matrix-calculator ./matrix_app
```

## 🔄 CI/CD

Проект использует GitHub Actions для автоматической сборки и тестирования. При каждом пуше в репозиторий автоматически:

1. Собирается приложение
2. Запускаются все тесты
3. Проверяется память на утечки
4. Генерируется документация
5. Создается артефакт с документацией

Статус сборки можно посмотреть в разделе Actions репозитория GitHub.

## 💻 Использование

### Пример программы
```cpp
#include "matrix.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
    // Инициализация генератора случайных чисел
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Создание матриц
    Matrix A = create_matrix(2, 2);
    Matrix B = create_matrix(2, 2);

    // Заполнение данными
    A.data[0][0] = 1; A.data[0][1] = 2;
    A.data[1][0] = 3; A.data[1][1] = 4;

    B.data[0][0] = 5; B.data[0][1] = 6;
    B.data[1][0] = 7; B.data[1][1] = 8;

    // Операции с матрицами
    Matrix sum = matrix_add(A, B);
    Matrix product = matrix_multiply(A, B);

    // Создание случайной матрицы
    Matrix random_mat = matrix_random(3, 3, 0.0, 10.0);

    // Вывод результатов
    std::cout << "Matrix A:" << std::endl;
    print_matrix(A);

    std::cout << "Sum A+B:" << std::endl;
    print_matrix(sum);

    std::cout << "Random matrix:" << std::endl;
    print_matrix(random_mat);

    // Освобождение памяти
    free_matrix(A);
    free_matrix(B);
    free_matrix(sum);
    free_matrix(product);
    free_matrix(random_mat);

    return 0;
}
```

### Доступные команды Makefile
- `make all` - собрать все приложения
- `make main` - собрать основное приложение
- `make test` - собрать тестовое приложение
- `make docs` - сгенерировать документацию
- `make run-test` - запустить тесты
- `make run-demo` - запустить демонстрацию
- `make memcheck` - проверить память
- `make clean` - очистить собранные файлы

## 🐛 Отладка и решение проблем

### Распространенные проблемы
1. **Ошибки компиляции**: Убедитесь, что используется C++17 (`-std=c++17`)
2. **Утечки памяти**: Используйте Valgrind для проверки
3. **Ошибки размеров**: Всегда проверяйте совместимость размеров матриц

### Валидация работы
```bash
# Полная проверка
make all-check

# Должна быть зеленая output и никаких ошибок
```

## 🤝 Вклад в проект

1. Форкните репозиторий
2. Создайте ветку для вашей функции (`git checkout -b feature/amazing-feature`)
3. Закоммитьте изменения (`git commit -m 'Add some amazing feature'`)
4. Запушьте в ветку (`git push origin feature/amazing-feature`)
5. Откройте Pull Request

## 📄 Лицензия

Этот проект создан в учебных целях для лабораторной работы.

## 👨‍💻 Автор

Разработано в рамках лабораторной работы по полному циклу разработки ПО.

---

**Статус проекта**: ✅ Завершено
**Последнее обновление**: 2024
