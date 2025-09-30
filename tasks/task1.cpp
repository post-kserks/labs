#include <iostream>
#include <iomanip>
#include "../helpers.h"

using namespace std;

void generateTemperatures() {
    cout << "=== Задание 1: Генератор ежедневных температур ===" << endl;

    float temperatures[30];

    // Начальная температура
    temperatures[0] = randomDoubleInRange(-15.0, 35.0);

    for (int i = 1; i < 30; i++) {
        // Базовое значение с небольшим трендом от предыдущего дня
        float base = temperatures[i-1] + randomDoubleInRange(-1.5, 1.5);

        // Добавляем случайные колебания ±3°C
        float fluctuation = randomDoubleInRange(-3.0, 3.0);
        temperatures[i] = base + fluctuation;

        // Ограничиваем диапазоном [-15, 35]
        if (temperatures[i] < -15.0) temperatures[i] = -15.0;
        if (temperatures[i] > 35.0) temperatures[i] = 35.0;
    }

    // Выводим результаты с округлением до одной цифры после запятой
    cout << fixed << setprecision(1);
    for (int i = 0; i < 30; i++) {
        cout << "День " << (i + 1) << ": " << temperatures[i] << "°C" << endl;
    }
    cout << endl;
}
