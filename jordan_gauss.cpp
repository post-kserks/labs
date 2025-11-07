#include "jordan_gauss.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <stdexcept>

using namespace std;

// Вывод матрицы в читаемом формате
void printMatrix(const vector<vector<double>>& matrix) {
    int rows = matrix.size();
    if (rows == 0) return;

    int cols = matrix[0].size();

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << setw(8) << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

// Реализация метода Жордана-Гаусса
vector<double> solveJordanGauss(vector<vector<double>> matrix) {
    int rows = matrix.size();
    if (rows == 0) {
        throw runtime_error("Матрица пустая");
    }

    int cols = matrix[0].size();

    // Проверяем, что матрица имеет правильный размер (n x n+1)
    if (cols != rows + 1) {
        throw runtime_error("Неверный размер матрицы");
    }

    for (int i = 0; i < rows; i++) {
        // Поиск ведущего элемента (максимального по модулю в столбце)
        int maxRow = i;
        for (int k = i + 1; k < rows; k++) {
            if (abs(matrix[k][i]) > abs(matrix[maxRow][i])) {
                maxRow = k;
            }
        }

        // Перестановка строк для обеспечения устойчивости
        if (maxRow != i) {
            swap(matrix[i], matrix[maxRow]);
        }

        // Нормализация текущей строки
        double divisor = matrix[i][i];
        if (abs(divisor) < 1e-10) {
            throw runtime_error("Система вырождена или не имеет единственного решения");
        }

        for (int j = i; j < cols; j++) {
            matrix[i][j] /= divisor;
        }

        // Исключение переменной из других строк
        for (int k = 0; k < rows; k++) {
            if (k != i) {
                double factor = matrix[k][i];
                for (int j = i; j < cols; j++) {
                    matrix[k][j] -= factor * matrix[i][j];
                }
            }
        }
    }

    // Извлекаем решения из последнего столбца
    vector<double> solution(rows);
    for (int i = 0; i < rows; i++) {
        solution[i] = matrix[i][cols - 1];
    }

    return solution;
}

// Вывод решений системы с именами x, y, z
void printSolution(const vector<double>& solution) {
    int size = solution.size();

    if (size >= 1) {
        cout << "x = " << solution[0] << endl;
    }
    if (size >= 2) {
        cout << "y = " << solution[1] << endl;
    }
    if (size >= 3) {
        cout << "z = " << solution[2] << endl;
    }

    // Для систем большего размера продолжаем нумерацию
    for (int i = 3; i < size; i++) {
        cout << "x" << i + 1 << " = " << solution[i] << endl;
    }
}
