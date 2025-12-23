#include "simplex.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <limits>
#include <algorithm>

using namespace std;

// Вывод симплекс-таблицы (для отладки)
void print_tableau(const vector<vector<double>>& tableau, const vector<int>& basis) {
    int m = tableau.size() - 1;
    int n = tableau[0].size() - 1;
    
    cout << "\nСимплекс-таблица:\n";
    cout << "Базисные переменные: ";
    for (int i = 0; i < m; i++) {
        cout << "x" << basis[i] + 1 << " ";
    }
    cout << endl;
    
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            cout << setw(10) << fixed << setprecision(4) << tableau[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// Реализация симплекс-метода
LPSolution simplex_method(const vector<double>& c, 
                         const vector<vector<double>>& A, 
                         const vector<double>& b) {
    
    LPSolution result;
    int m = A.size();    // Количество ограничений
    int n = c.size();    // Количество переменных
    
    // Проверка размеров
    if (m != b.size()) {
        result.feasible = false;
        result.message = "Ошибка: размеры A и b не совпадают";
        return result;
    }
    
    // Создаём симплекс-таблицу (m+1 строк, n+m+1 столбцов)
    // Дополнительные столбцы для slack-переменных
    vector<vector<double>> tableau(m + 1, vector<double>(n + m + 1, 0.0));
    
    // Заполняем матрицу ограничений
    for (int i = 0; i < m; i++) {
        // Копируем коэффициенты исходных переменных
        for (int j = 0; j < n; j++) {
            tableau[i][j] = A[i][j];
        }
        
        // Добавляем slack-переменные (единичная матрица)
        tableau[i][n + i] = 1.0;
        
        // Правая часть
        tableau[i][n + m] = b[i];
    }
    
    // Заполняем строку целевой функции
    for (int j = 0; j < n; j++) {
        tableau[m][j] = -c[j];  // Отрицательные, так как максимизируем
    }
    
    // Slack-переменные в целевой функции имеют коэффициент 0
    
    // Базисные переменные (индексы slack-переменных)
    vector<int> basis(m);
    for (int i = 0; i < m; i++) {
        basis[i] = n + i;  // Slack-переменные
    }
    
    // Отладочный вывод
    // print_tableau(tableau, basis);
    
    // Основной цикл симплекс-метода
    const double EPS = 1e-10;
    int iteration = 0;
    const int MAX_ITERATIONS = 100;
    
    while (iteration++ < MAX_ITERATIONS) {
        // 1. Находим входящую переменную (столбец с наименьшим отрицательным значением в Z-строке)
        int entering = -1;
        double min_val = 0.0;
        
        for (int j = 0; j < n + m; j++) {
            if (tableau[m][j] < min_val - EPS) {
                min_val = tableau[m][j];
                entering = j;
            }
        }
        
        // Если нет отрицательных коэффициентов, достигнут оптимум
        if (entering == -1) {
            break;
        }
        
        // 2. Находим выходящую переменную (минимальное отношение правой части к положительному коэффициенту)
        int leaving = -1;
        double min_ratio = numeric_limits<double>::max();
        
        for (int i = 0; i < m; i++) {
            if (tableau[i][entering] > EPS) {
                double ratio = tableau[i][n + m] / tableau[i][entering];
                if (ratio < min_ratio - EPS) {
                    min_ratio = ratio;
                    leaving = i;
                }
            }
        }
        
        // Если не нашли выходящую переменную, задача неограничена
        if (leaving == -1) {
            result.feasible = false;
            result.message = "Задача неограничена (целевая функция может быть бесконечно большой)";
            return result;
        }
        
        // 3. Обновляем базис
        basis[leaving] = entering;
        
        // 4. Нормализуем ведущую строку (делаем коэффициент при входящей переменной равным 1)
        double pivot = tableau[leaving][entering];
        for (int j = 0; j <= n + m; j++) {
            tableau[leaving][j] /= pivot;
        }
        
        // 5. Обнуляем столбец входящей переменной в других строках
        for (int i = 0; i <= m; i++) {
            if (i != leaving) {
                double factor = tableau[i][entering];
                for (int j = 0; j <= n + m; j++) {
                    tableau[i][j] -= factor * tableau[leaving][j];
                }
            }
        }
        
        // Отладочный вывод
        // cout << "Итерация " << iteration << ": входит x" << entering+1 
        //      << ", выходит x" << basis[leaving]+1 << endl;
        // print_tableau(tableau, basis);
    }
    
    // Проверяем допустимость решения
    bool feasible = true;
    for (int i = 0; i < m; i++) {
        if (tableau[i][n + m] < -EPS) {
            feasible = false;
        }
    }
    
    if (!feasible) {
        result.feasible = false;
        result.message = "Нет допустимого решения";
        return result;
    }
    
    // Извлекаем решение
    result.variables.resize(n, 0.0);
    for (int i = 0; i < m; i++) {
        if (basis[i] < n) {  // Если базисная переменная - исходная
            result.variables[basis[i]] = tableau[i][n + m];
        }
    }
    
    // Значение целевой функции (берём с противоположным знаком)
    result.objective_value = tableau[m][n + m];
    result.feasible = true;
    result.message = "Решение найдено успешно";
    
    return result;
}