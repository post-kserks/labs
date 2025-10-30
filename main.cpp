#include <iostream>
#include <vector>
#include <iomanip>
#include "jordan_gauss.h"

int main() {
    // Расширенная матрица системы из задания
    // Столбцы: x, y, z, свободные члены
    std::vector<std::vector<double>> augmented_matrix = {
        {1,  2,  3,  20},  // x + 2y + 3z = 20
        {2, -1,  1,  5 },  // 2x - y + z = 5
        {3,  1, -2,  8 }   // 3x + y - 2z = 8
    };

    std::cout << "Исходная расширенная матрица системы:" << std::endl;
    printMatrix(augmented_matrix);
    std::cout << std::endl;

    try {
        // Решение системы методом Жордана-Гаусса
        std::vector<double> solution = solveJordanGauss(augmented_matrix);

        std::cout << "Решение системы:" << std::endl;
        std::cout << "x = " << std::fixed << std::setprecision(6) << solution[0] << std::endl;
        std::cout << "y = " << std::fixed << std::setprecision(6) << solution[1] << std::endl;
        std::cout << "z = " << std::fixed << std::setprecision(6) << solution[2] << std::endl;

        // Проверка ожидаемого результата
        std::cout << "\nОжидаемый результат:" << std::endl;
        std::cout << "x = 19/6 ≈ " << 19.0/6.0 << std::endl;
        std::cout << "y = 25/6 ≈ " << 25.0/6.0 << std::endl;
        std::cout << "z = 17/6 ≈ " << 17.0/6.0 << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
