#include <iostream>
#include <iomanip>
#include "../helpers.h"

using namespace std;

void generateCoffeeSales() {
    cout << "=== Задание 3: Генератор ежечасных продаж кофе ===" << endl;

    const char* DAYS[] = {"Понедельник", "Вторник", "Среда", "Четверг", "Пятница", "Суббота", "Воскресенье"};
    int coffee_sales[7][14]; // 7 дней, 14 часов в день (8:00-21:00)

    for (int day = 0; day < 7; day++) {
        for (int hour = 0; hour < 14; hour++) {
            int actualHour = hour + 8; // преобразуем к реальному времени (8-21)
            int cups;

            // Определяем диапазон продаж в зависимости от времени суток
            if (actualHour >= 8 && actualHour <= 11) { // Утренние часы
                cups = randomInRange(20, 40);
            } else if (actualHour >= 12 && actualHour <= 14) { // Обеденные часы
                cups = randomInRange(30, 60);
            } else if (actualHour >= 17 && actualHour <= 20) { // Вечерние часы
                cups = randomInRange(15, 35);
            } else { // Остальные часы
                cups = randomInRange(5, 15);
            }

            // Увеличиваем продажи на 20% в выходные
            if (day == 5 || day == 6) { // Суббота или воскресенье
                cups = cups * 1.2;
            }

            coffee_sales[day][hour] = cups;
        }
    }

    // Выводим результаты
    for (int day = 0; day < 7; day++) {
        for (int hour = 0; hour < 14; hour++) {
            int actualHour = hour + 8;
            cout << DAYS[day] << ", "
                 << setw(2) << setfill('0') << actualHour << ":00 - "
                 << coffee_sales[day][hour] << " чашек" << endl;
        }
        cout << endl;
    }
}
