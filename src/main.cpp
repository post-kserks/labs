// main.cpp
#include "matrix.h"
#include "maze_solver.h"
#include <iostream>

using namespace std;

void test_basic_functionality() {
    cout << "=== Тест 1: Базовые операции с матрицей ===" << endl;

    // Создание и освобождение матрицы
    Matrix m = create_matrix(3, 3);
    cout << "Матрица 3x3 создана успешно" << endl;
    free_matrix(&m);
    cout << "Память матрицы освобождена" << endl;

    // Граничный случай - нулевая матрица
    Matrix zero = create_matrix(0, 0);
    cout << "Нулевая матрица создана успешно" << endl;
    free_matrix(&zero);
}

void test_maze_operations() {
    cout << "\n=== Тест 2: Операции с лабиринтом ===" << endl;

    // Создание тестового лабиринта
    Matrix maze = create_sample_maze();
    cout << "Тестовый лабиринт создан:" << endl;
    print_maze(maze);

    // Тест 1: Допустимый путь (1,1) -> (1,3)
    cout << "\nТест пути от (1,1) до (1,3): ";
    bool result1 = is_reachable(maze, 1, 1, 1, 3);
    cout << (result1 ? "Путь существует" : "Путь не существует") << endl;

    // Тест 2: Недопустимый путь (1,1) -> (0,0) через стену
    cout << "Тест пути от (1,1) до (0,0): ";
    bool result2 = is_reachable(maze, 1, 1, 0, 0);
    cout << (result2 ? "Путь существует" : "Путь не существует") << endl;

    // Тест 3: Путь внутри одной клетки
    cout << "Тест пути от (1,1) до (1,1): ";
    bool result3 = is_reachable(maze, 1, 1, 1, 1);
    cout << (result3 ? "Путь существует" : "Путь не существует") << endl;

    // Тест 4: Невалидные координаты
    cout << "Тест невалидных координат (-1,-1) до (1,1): ";
    bool result4 = is_reachable(maze, -1, -1, 1, 1);
    cout << (result4 ? "Путь существует" : "Путь не существует") << endl;

    free_matrix(&maze);
}

void test_edge_cases() {
    cout << "\n=== Тест 3: Граничные случаи ===" << endl;

    // Лабиринт 1x1
    Matrix tiny_maze = create_matrix(1, 1);
    tiny_maze.data[0][0] = PATH;

    cout << "Лабиринт 1x1 (путь): ";
    bool result = is_reachable(tiny_maze, 0, 0, 0, 0);
    cout << (result ? "Путь существует" : "Путь не существует") << endl;

    // Лабиринт 1x1 со стеной
    tiny_maze.data[0][0] = WALL;
    cout << "Лабиринт 1x1 (стена): ";
    result = is_reachable(tiny_maze, 0, 0, 0, 0);
    cout << (result ? "Путь существует" : "Путь не существует") << endl;

    free_matrix(&tiny_maze);
}

int main() {
    try {
        test_basic_functionality();
        test_maze_operations();
        test_edge_cases();

        cout << "\n=== Все тесты завершены успешно ===" << endl;
    }
    catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
        return 1;
    }

    return 0;
}
