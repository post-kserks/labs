#include <iostream>
#include <cstdlib>
#include <ctime>
#include "tasks/task1.h"
#include "tasks/task2.h"
#include "tasks/task3.h"
#include "tasks/task4.h"
#include "tasks/task5.h"
#include "tasks/task6.h"

using namespace std;

int main() {
    srand(time(0)); // Инициализация генератора случайных чисел

    int choice;
    do {
        cout << "=== Семинар 4: Массивы, условия и циклы в C++ ===" << endl;
        cout << "1. Генератор ежедневных температур" << endl;
        cout << "2. Генератор оценок студентов" << endl;
        cout << "3. Генератор ежечасных продаж кофе" << endl;
        cout << "4. Генератор случайных паролей" << endl;
        cout << "5. Генератор графика дел на день" << endl;
        cout << "6. Генератор цветовой палитры" << endl;
        cout << "0. Выход" << endl;
        cout << "Выберите задание: ";
        cin >> choice;

        switch (choice) {
            case 1:
                generateTemperatures();
                break;
            case 2:
                generateGrades();
                break;
            case 3:
                generateCoffeeSales();
                break;
            case 4:
                generatePasswords();
                break;
            case 5:
                generateSchedule();
                break;
            case 6:
                generateColorPalettes();
                break;
            case 0:
                cout << "Выход..." << endl;
                break;
            default:
                cout << "Неверный выбор!" << endl;
        }
    } while (choice != 0);

    return 0;
}
