#include "simplex.h"
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

int main() {
    cout << "=========================================\n";
    cout << "Решение задачи линейного программирования\n";
    cout << "Метод: симплекс-метод\n";
    cout << "=========================================\n\n";
    
    // Исходная задача из задания:
    // Максимизировать 0.10x + 0.07y + 0.03z
    // при условиях:
    // 1) x + y + z = 100
    // 2) x <= (1/3)y
    // 3) z >= 0.25(x + y)
    // 4) x, y, z >= 0
    
    // Приводим к стандартной форме:
    // 1) x + y + z = 100 -> заменяем на два неравенства:
    //    x + y + z <= 100
    //    -x - y - z <= -100
    // 2) x <= (1/3)y -> x - (1/3)y <= 0
    // 3) z >= 0.25(x + y) -> -0.25x - 0.25y + z >= 0 -> 
    //    умножаем на -1: 0.25x + 0.25y - z <= 0
    // 4) x, y, z >= 0 (неотрицательность учтётся в симплекс-методе)
    
    // Коэффициенты целевой функции (максимизировать)
    vector<double> c = {0.10, 0.07, 0.03};
    
    // Матрица ограничений A (5 ограничений × 3 переменных)
    // Формат: A*x <= b
    vector<vector<double>> A = {
        // 1) x + y + z <= 100
        {1.0, 1.0, 1.0},
        // 2) -x - y - z <= -100
        {-1.0, -1.0, -1.0},
        // 3) x - (1/3)y <= 0
        {1.0, -1.0/3.0, 0.0},
        // 4) 0.25x + 0.25y - z <= 0
        {0.25, 0.25, -1.0}
    };
    
    // Правые части ограничений
    vector<double> b = {100.0, -100.0, 0.0, 0.0};
    
    // Решаем задачу
    LPSolution solution = simplex_method(c, A, b);
    
    // Выводим результаты
    cout << "Результат решения:\n";
    cout << "------------------\n";
    
    if (solution.feasible) {
        cout << "Статус: " << solution.message << endl;
        cout << "Значение целевой функции: " 
             << fixed << setprecision(6) << solution.objective_value << endl;
        cout << "\nОптимальные значения переменных:\n";
        cout << "x = " << solution.variables[0] << endl;
        cout << "y = " << solution.variables[1] << endl;
        cout << "z = " << solution.variables[2] << endl;
        
        // Проверяем ограничения
        cout << "\nПроверка ограничений:\n";
        cout << "1) x + y + z = " 
             << solution.variables[0] + solution.variables[1] + solution.variables[2] 
             << " (должно быть = 100)" << endl;
        cout << "2) x <= (1/3)y: " << solution.variables[0] 
             << " <= " << solution.variables[1]/3.0 << "? "
             << (solution.variables[0] <= solution.variables[1]/3.0 + 1e-6 ? "ДА" : "НЕТ") << endl;
        cout << "3) z >= 0.25(x+y): " << solution.variables[2] 
             << " >= " << 0.25*(solution.variables[0] + solution.variables[1]) << "? "
             << (solution.variables[2] >= 0.25*(solution.variables[0] + solution.variables[1]) - 1e-6 ? "ДА" : "НЕТ") << endl;
    } else {
        cout << "Решение не найдено: " << solution.message << endl;
    }
    
    cout << "\n=========================================\n";
    return 0;
}