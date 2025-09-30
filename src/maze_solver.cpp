// maze_solver.cpp
#include "maze_solver.h"
#include <iostream>
#include <queue>
#include <tuple>

using namespace std;

Matrix create_sample_maze() {
    Matrix maze = create_matrix(5, 5);

    // Инициализация стен и путей согласно примеру
    int sample[5][5] = {
        {1, 1, 1, 1, 1},
        {1, 0, 0, 0, 1},
        {1, 1, 0, 1, 1},
        {1, 0, 0, 0, 1},
        {1, 1, 1, 1, 1}
    };

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            maze.data[i][j] = sample[i][j];
        }
    }

    return maze;
}

void print_maze(const Matrix& maze) {
    for (int i = 0; i < maze.rows; ++i) {
        for (int j = 0; j < maze.cols; ++j) {
            if (maze.data[i][j] == WALL) {
                cout << "# ";
            } else {
                cout << "  ";
            }
        }
        cout << endl;
    }
}

bool is_reachable(Matrix maze, int start_row, int start_col, int end_row, int end_col) {
    // Проверка валидности входных данных
    if (start_row < 0 || start_row >= maze.rows || start_col < 0 || start_col >= maze.cols ||
        end_row < 0 || end_row >= maze.rows || end_col < 0 || end_col >= maze.cols) {
        return false;
    }

    // Старт или финиш в стене
    if (maze.data[start_row][start_col] == WALL || maze.data[end_row][end_col] == WALL) {
        return false;
    }

    // BFS для поиска пути
    queue<tuple<int, int>> q;
    q.push({start_row, start_col});

    // Матрица для отслеживания посещенных клеток
    Matrix visited = create_matrix(maze.rows, maze.cols);
    visited.data[start_row][start_col] = true;

    // Возможные направления: вверх, вниз, влево, вправо
    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    while (!q.empty()) {
        auto [row, col] = q.front();
        q.pop();

        // Достигли конечной точки
        if (row == end_row && col == end_col) {
            free_matrix(&visited);
            return true;
        }

        // Проверяем все соседние клетки
        for (int i = 0; i < 4; ++i) {
            int new_row = row + directions[i][0];
            int new_col = col + directions[i][1];

            // Проверяем границы и возможность пройти
            if (new_row >= 0 && new_row < maze.rows &&
                new_col >= 0 && new_col < maze.cols &&
                maze.data[new_row][new_col] == PATH &&
                !visited.data[new_row][new_col]) {

                visited.data[new_row][new_col] = true;
                q.push({new_row, new_col});
            }
        }
    }

    free_matrix(&visited);
    return false;
}
