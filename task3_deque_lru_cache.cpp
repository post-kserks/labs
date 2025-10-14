#include <iostream>
#include <deque>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>

using namespace std;

void runTest() {
    cout << "=== ТЕСТОВЫЕ ДАННЫЕ ===" << endl;

    int cache_size = 3;
    vector<string> requests = {"A", "B", "C", "A", "D"};
    deque<string> cache;

    cout << "Размер кэша: " << cache_size << endl;
    cout << "Запросы: ";
    for (const string& req : requests) {
        cout << req << " ";
    }
    cout << endl << endl;

    for (const string& req : requests) {
        cout << "После запроса " << req << ": ";

        auto it = find(cache.begin(), cache.end(), req);

        if (it != cache.end()) {
            cache.erase(it);
            cache.push_back(req);
        } else {
            if (cache.size() >= cache_size) {
                cache.pop_front();
            }
            cache.push_back(req);
        }

        cout << "кеш = [";
        for (size_t i = 0; i < cache.size(); i++) {
            cout << cache[i];
            if (i < cache.size() - 1) cout << ", ";
        }
        cout << "]" << endl;
    }
    cout << endl;
}

void manualInput() {
    cout << "=== РУЧНОЙ ВВОД ===" << endl;

    int cache_size;
    cout << "Введите размер кэша: ";
    cin >> cache_size;

    if (cache_size <= 0) {
        throw invalid_argument("Размер кэша должен быть положительным");
    }

    cout << "Введите запросы через пробел (например: A B C A D): ";
    string input;
    cin.ignore();
    getline(cin, input);

    vector<string> requests;
    stringstream ss(input);
    string req;

    while (ss >> req) {
        if (req.empty()) {
            throw invalid_argument("Запрос не может быть пустым");
        }
        requests.push_back(req);
    }

    if (requests.empty()) {
        throw runtime_error("Список запросов пуст");
    }

    deque<string> cache;

    for (const string& req : requests) {
        cout << "После запроса " << req << ": ";

        auto it = find(cache.begin(), cache.end(), req);

        if (it != cache.end()) {
            cache.erase(it);
            cache.push_back(req);
        } else {
            if (cache.size() >= cache_size) {
                cache.pop_front();
            }
            cache.push_back(req);
        }

        cout << "кеш = [";
        for (size_t i = 0; i < cache.size(); i++) {
            cout << cache[i];
            if (i < cache.size() - 1) cout << ", ";
        }
        cout << "]" << endl;
    }
}

int main() {
    try {
        int choice;
        cout << "LRU-кэш с использованием дека" << endl;
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
