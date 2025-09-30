#include <iostream>
#include <cstring>
#include <cctype>
#include "../helpers.h"

using namespace std;

// Функция для проверки, содержит ли пароль хотя бы одну цифру
bool containsDigit(const char* password, int length) {
    for (int i = 0; i < length; i++) {
        if (isdigit(password[i])) {
            return true;
        }
    }
    return false;
}

void generatePasswords() {
    cout << "=== Задание 4: Генератор случайных паролей ===" << endl;

    const int PASSWORD_COUNT = 10;
    const int PASSWORD_LENGTH = 8;
    char passwords[PASSWORD_COUNT][PASSWORD_LENGTH + 1]; // +1 для нуль-терминатора

    for (int i = 0; i < PASSWORD_COUNT; i++) {
        bool hasDigit;
        do {
            // Первый символ - буква
            passwords[i][0] = randomLetter();

            // Остальные символы - буквы или цифры
            for (int j = 1; j < PASSWORD_LENGTH; j++) {
                passwords[i][j] = randomChar();
            }

            // Завершаем строку
            passwords[i][PASSWORD_LENGTH] = '\0';

            // Проверяем, содержит ли пароль хотя бы одну цифру
            hasDigit = containsDigit(passwords[i], PASSWORD_LENGTH);

            // Если нет цифр, заменяем случайный символ (кроме первого) на цифру
            if (!hasDigit) {
                int pos = randomInRange(1, PASSWORD_LENGTH - 1);
                passwords[i][pos] = '0' + randomInRange(0, 9);
            }
        } while (!hasDigit); // Повторяем, пока не будет хотя бы одной цифры
    }

    // Выводим пароли
    for (int i = 0; i < PASSWORD_COUNT; i++) {
        cout << "Пароль " << (i + 1) << ": " << passwords[i] << endl;
    }
    cout << endl;
}
