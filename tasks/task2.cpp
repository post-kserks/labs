#include <iostream>
#include "../helpers.h"

using namespace std;

void generateGrades() {
    cout << "=== Задание 2: Генератор оценок студентов ===" << endl;

    const int STUDENTS = 15;
    const int SUBJECTS = 5;
    int grades[STUDENTS][SUBJECTS];

    // Заполняем массив случайными оценками от 2 до 5
    for (int i = 0; i < STUDENTS; i++) {
        for (int j = 0; j < SUBJECTS; j++) {
            grades[i][j] = randomInRange(2, 5);
        }
    }

    // Выбираем 2-3 студентов, у которых будут только хорошие оценки (4-5)
    int goodStudentsCount = randomInRange(2, 3);
    for (int i = 0; i < goodStudentsCount; i++) {
        int studentIndex = randomInRange(0, STUDENTS - 1);
        for (int j = 0; j < SUBJECTS; j++) {
            grades[studentIndex][j] = randomInRange(4, 5);
        }
    }

    // Выводим таблицу
    for (int i = 0; i < STUDENTS; i++) {
        cout << "Студент " << (i + 1) << ": ";
        for (int j = 0; j < SUBJECTS; j++) {
            cout << grades[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}
