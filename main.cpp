#include <iostream>
#include <vector>
#include "jordan_gauss.h"

using namespace std;

int main() {
    // Создаем расширенную матрицу системы (3 уравнения, 3 переменные + столбец свободных членов)
    vector<vector<double>> matrix = {
        {2, 1, 3, 6},
        {2, -1, 1, 3},
        {1, 2, 4, 2}
    };

    cout << "Исходная система:" << endl;
    printMatrix(matrix);

    // Решаем систему методом Жордана-Гаусса
    vector<double> solution = solveJordanGauss(matrix);

    cout << "\nРешение:" << endl;
    printSolution(solution);

    return 0;
}
