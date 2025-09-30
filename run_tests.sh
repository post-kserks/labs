#!/bin/bash
# run_tests.sh

echo "=== Компиляция программы ==="
make debug

echo -e "\n=== Запуск программы ==="
./build/maze_solver

echo -e "\n=== Проверка памяти с Valgrind ==="
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./build/maze_solver

echo -e "\n=== Проверка с AddressSanitizer ==="
make clean
make debug
./build/maze_solver

echo -e "\n=== Все проверки завершены ==="
