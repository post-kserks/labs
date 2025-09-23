# Dockerfile (обновленная версия)
FROM gcc:12.2.0

# Устанавливаем зависимости
RUN apt-get update && apt-get install -y \
    doxygen \
    graphviz \
    valgrind \
    make \
    && rm -rf /var/lib/apt/lists/*

# Создаем рабочую директорию
WORKDIR /app

# Копируем все файлы проекта
COPY . .

# Собираем приложения с помощью Makefile
RUN make all

# Генерируем документацию
RUN make docs

# По умолчанию запускаем тесты
CMD ["./test_app"]
