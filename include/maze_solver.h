// maze_solver.h
#ifndef MAZE_SOLVER_H
#define MAZE_SOLVER_H

#include "matrix.h"

// Константы для лабиринта
const int WALL = 1;
const int PATH = 0;
const int VISITED = 2;

// Создает тестовый лабиринт 5x5 из примера
Matrix create_sample_maze();

// Отображает лабиринт с символами (' ' для пути, '#' для стены)
void print_maze(const Matrix& maze);

// Проверяет, можно ли дойти из start до end
bool is_reachable(Matrix maze, int start_row, int start_col, int end_row, int end_col);

#endif
