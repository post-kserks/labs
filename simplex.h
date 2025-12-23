#ifndef SIMPLEX_H
#define SIMPLEX_H

#include <vector>
#include <string>

// Структура для хранения решения задачи ЛП
struct LPSolution {
    std::vector<double> variables;  // Значения переменных
    double objective_value;         // Значение целевой функции
    bool feasible;                  // Есть ли допустимое решение
    std::string message;            // Сообщение о результате
};

// Решает задачу линейного программирования симплекс-методом
// Целевая функция: максимизировать c1*x1 + c2*x2 + ... + cn*xn
// Ограничения в виде: A*x <= b, x >= 0
LPSolution simplex_method(
    const std::vector<double>& c,   // Коэффициенты целевой функции (размер n)
    const std::vector<std::vector<double>>& A, // Матрица ограничений (m x n)
    const std::vector<double>& b    // Правые части ограничений (размер m)
);

// Вспомогательные функции
void print_tableau(const std::vector<std::vector<double>>& tableau, 
                   const std::vector<int>& basis);

#endif