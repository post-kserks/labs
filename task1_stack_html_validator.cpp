#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

bool isValidHTML(const vector<string>& tags) {
    stack<string> tagStack;

    for (const string& tag : tags) {
        if (tag.empty() || tag.length() < 3) {
            throw invalid_argument("Некорректный тег: " + tag);
        }

        if (tag[0] != '<' || tag[tag.length()-1] != '>') {
            throw invalid_argument("Тег должен начинаться с '<' и заканчиваться '>': " + tag);
        }

        if (tag[1] != '/') {
            // Открывающий тег
            tagStack.push(tag);
        } else {
            // Закрывающий тег
            if (tagStack.empty()) {
                return false;
            }

            string openTag = tagStack.top();
            string expectedCloseTag = "</" + openTag.substr(1);

            if (tag == expectedCloseTag) {
                tagStack.pop();
            } else {
                return false;
            }
        }
    }

    return tagStack.empty();
}

void runTest() {
    cout << "=== ТЕСТОВЫЕ ДАННЫЕ ===" << endl;

    vector<vector<string>> testCases = {
        {"<div>", "<p>", "</p>", "</div>"},
        {"<div>", "<p>", "</div>", "</p>"},
        {"<html>", "<body>", "<div>", "</div>", "</body>", "</html>"},
        {"<div>", "</div>"},
        {"<div>", "<p>", "</p>"}
    };

    vector<bool> expected = {true, false, true, true, false};

    for (size_t i = 0; i < testCases.size(); i++) {
        cout << "Тест " << i + 1 << ": ";
        for (const string& tag : testCases[i]) {
            cout << tag << " ";
        }

        bool result = isValidHTML(testCases[i]);
        cout << "-> " << (result ? "Корректно" : "Некорректно");

        if (result == expected[i]) {
            cout << " ✓" << endl;
        } else {
            cout << " ✗ (ожидалось: " << (expected[i] ? "Корректно" : "Некорректно") << ")" << endl;
        }
    }
    cout << endl;
}

void manualInput() {
    cout << "=== РУЧНОЙ ВВОД ===" << endl;
    cout << "Введите HTML-теги через пробел (например: <div> <p> </p> </div>):" << endl;

    string input;
    cin.ignore();
    getline(cin, input);

    vector<string> tags;
    stringstream ss(input);
    string tag;

    while (ss >> tag) {
        tags.push_back(tag);
    }

    try {
        bool result = isValidHTML(tags);
        cout << "Результат: " << (result ? "Корректно" : "Некорректно") << endl;
    } catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
    }
}

int main() {
    try {
        int choice;
        cout << "Проверка корректности HTML-тегов" << endl;
        cout << "1. Запустить тесты" << endl;
        cout << "2. Ручной ввод" << endl;
        cout << "Выберите вариант: ";
        cin >> choice;

        if (choice == 1) {
            runTest();
        } else if (choice == 2) {
            manualInput();
        } else {
            cout << "Неверный выбор" << endl;
        }

    } catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
        return 1;
    }

    return 0;
}
