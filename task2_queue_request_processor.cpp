#include <iostream>
#include <queue>
#include <vector>
#include <utility>
#include <string>
#include <sstream>

using namespace std;

void processRequests(queue<pair<int, string>>& requests) {
    cout << "Обработка запросов:" << endl;
    int processed_count = 0;

    while (!requests.empty()) {
        auto current_request = requests.front();
        cout << "Обработка запроса " << current_request.first << ": "
             << current_request.second << endl;
        requests.pop();
        processed_count++;
    }

    cout << "Обработано запросов: " << processed_count << endl;
}

void runTest() {
    cout << "=== ТЕСТОВЫЕ ДАННЫЕ ===" << endl;

    queue<pair<int, string>> testQueue;
    vector<pair<int, string>> testRequests = {
        {1, "Login"},
        {2, "QueryData"},
        {3, "Logout"}
    };

    for (const auto& req : testRequests) {
        testQueue.push(req);
    }

    processRequests(testQueue);
    cout << endl;
}

void manualInput() {
    cout << "=== РУЧНОЙ ВВОД ===" << endl;
    cout << "Введите количество запросов: ";
    int n;
    cin >> n;

    if (n <= 0) {
        throw invalid_argument("Количество запросов должно быть положительным");
    }

    queue<pair<int, string>> requests;

    for (int i = 0; i < n; i++) {
        int id;
        string description;

        cout << "Запрос " << i + 1 << " - ID: ";
        cin >> id;
        cout << "Запрос " << i + 1 << " - Описание: ";
        cin.ignore();
        getline(cin, description);

        if (id <= 0) {
            throw invalid_argument("ID запроса должен быть положительным");
        }
        if (description.empty()) {
            throw invalid_argument("Описание не может быть пустым");
        }

        requests.push({id, description});
    }

    processRequests(requests);
}

int main() {
    try {
        int choice;
        cout << "Обработка запросов в очереди" << endl;
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
