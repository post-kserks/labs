#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

// Исследуемая функция
double f(double x) {
    return x*x - exp(x) + 2;
}

int main() {
    cout << "Анализ функции f(x) = x^2 - e^x + 2" << endl;
    cout << "Поиск интервала изоляции корня" << endl;
    cout << "====================================" << endl;
    cout << setw(8) << "x" << setw(15) << "f(x)" << setw(10) << "Знак" << endl;
    cout << "------------------------------------" << endl;

    // Исследуем точки в предполагаемой области корня
    double x_values[] = {-2, -1.5, -1, -0.5, 0, 0.5, 1, 1.5, 2};
    int num_points = sizeof(x_values) / sizeof(x_values[0]);

    double prev_x = x_values[0];
    double prev_fx = f(prev_x);
    string prev_sign = (prev_fx > 0) ? "+" : (prev_fx < 0) ? "-" : "0";

    cout << setw(8) << prev_x << setw(15) << fixed << setprecision(6) << prev_fx
         << setw(10) << prev_sign << endl;

    // Поиск интервала где функция меняет знак
    for(int i = 1; i < num_points; i++) {
        double x = x_values[i];
        double fx = f(x);
        string sign = (fx > 0) ? "+" : (fx < 0) ? "-" : "0";

        cout << setw(8) << x << setw(15) << fixed << setprecision(6) << fx
             << setw(10) << sign << endl;

        // Проверка смены знака
        if(prev_fx * fx < 0) {
            cout << ">>> НАЙДЕН ИНТЕРВАЛ: [" << prev_x << ", " << x << "]" << endl;
            cout << ">>> f(" << prev_x << ") = " << prev_fx << " (" << prev_sign << ")" << endl;
            cout << ">>> f(" << x << ") = " << fx << " (" << sign << ")" << endl;
        }

        prev_x = x;
        prev_fx = fx;
        prev_sign = sign;
    }

    return 0;
}
