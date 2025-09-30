#include <iostream>
#include <iomanip>
#include <vector>
#include "../helpers.h"
#include "../structures.h"

using namespace std;

void generateSchedule() {
    cout << "=== Задание 5: Генератор графика дел на день ===" << endl;

    const char* TASK_DESCRIPTIONS[] = {
        "Утренняя пробежка",
        "Работа над проектом",
        "Чтение книги",
        "Работа",
        "Перекус",
        "Изучение C++",
        "Прогулка",
        "Спортивная тренировка",
        "Встреча с друзьями",
        "Просмотр фильма",
        "Уборка",
        "Медитация",
        "Планирование дня",
        "Отдых",
        "Работа с документами"
    };

    const int TASK_COUNT = 10;
    Task schedule[TASK_COUNT];

    int current_minute = 8 * 60; // Начинаем в 8:00 (в минутах)

    for (int i = 0; i < TASK_COUNT; i++) {
        // Генерируем продолжительность от 15 до 120 минут с шагом 15 минут
        int duration = randomInRange(1, 8) * 15; // 15, 30, 45, ... 120

        // Проверяем, чтобы не выйти за 22:00 (22*60 = 1320 минут)
        if (current_minute + duration > 1320) {
            // Если выходим за пределы, уменьшаем продолжительность последнего дела
            duration = 1320 - current_minute;
            if (duration <= 0) {
                // Если времени уже нет, прерываем генерацию
                break;
            }
        }

        schedule[i].start_hour = current_minute / 60;
        schedule[i].start_minute = current_minute % 60;
        schedule[i].duration = duration;
        schedule[i].description = TASK_DESCRIPTIONS[randomInRange(0, 14)];

        // Увеличиваем текущее время на продолжительность дела и перерыв 15 минут
        current_minute += duration + 15; // перерыв 15 минут между делами
    }

    // Выводим расписание
    for (int i = 0; i < TASK_COUNT; i++) {
        if (schedule[i].duration <= 0) continue;

        int end_minute = schedule[i].start_hour * 60 + schedule[i].start_minute + schedule[i].duration;
        int end_hour = end_minute / 60;
        int end_min = end_minute % 60;

        cout << setw(2) << setfill('0') << schedule[i].start_hour << ":"
             << setw(2) << setfill('0') << schedule[i].start_minute
             << " - "
             << setw(2) << setfill('0') << end_hour << ":"
             << setw(2) << setfill('0') << end_min
             << ": " << schedule[i].description << endl;
    }
    cout << endl;
}
