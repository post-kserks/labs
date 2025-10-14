#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>
#include <string>
#include <sstream>

using namespace std;

vector<string> topologicalSort(unordered_map<string, vector<string>>& dependencies) {
    // Построим обратный граф: кто от кого зависит
    unordered_map<string, vector<string>> graph;
    unordered_map<string, int> indegree;

    // Инициализируем степени
    for (const auto& dep : dependencies) {
        indegree[dep.first] = 0;
    }

    // Строим граф в правильном направлении
    for (const auto& dep : dependencies) {
        string node = dep.first;
        for (const string& dependency : dep.second) {
            graph[dependency].push_back(node); // dependency -> node
            indegree[node]++;
        }
    }

    // Очередь для вершин с нулевой входящей степенью
    queue<string> q;
    for (const auto& node : indegree) {
        if (node.second == 0) {
            q.push(node.first);
        }
    }

    if (q.empty()) {
        throw runtime_error("Обнаружен цикл в графе зависимостей");
    }

    // Топологическая сортировка
    vector<string> result;
    while (!q.empty()) {
        string current = q.front();
        q.pop();
        result.push_back(current);

        if (graph.find(current) != graph.end()) {
            for (const string& neighbor : graph[current]) {
                indegree[neighbor]--;
                if (indegree[neighbor] == 0) {
                    q.push(neighbor);
                }
            }
        }
    }

    if (result.size() != indegree.size()) {
        throw runtime_error("Граф содержит циклы, топологическая сортировка невозможна");
    }

    return result;
}

void runTest() {
    cout << "=== ТЕСТОВЫЕ ДАННЫЕ ===" << endl;

    unordered_map<string, vector<string>> testDependencies = {
        {"A", {"B"}},
        {"B", {"C"}},
        {"C", {}}
    };

    cout << "Граф зависимостей:" << endl;
    for (const auto& dep : testDependencies) {
        cout << dep.first << " зависит от: ";
        for (const string& d : dep.second) {
            cout << d << " ";
        }
        cout << endl;
    }

    vector<string> result = topologicalSort(testDependencies);

    cout << "Топологический порядок: ";
    for (size_t i = 0; i < result.size(); i++) {
        cout << result[i];
        if (i < result.size() - 1) cout << ", ";
    }
    cout << endl << endl;
}

void manualInput() {
    cout << "=== РУЧНОЙ ВВОД ===" << endl;

    unordered_map<string, vector<string>> dependencies;

    cout << "Введите количество узлов: ";
    int n;
    cin >> n;

    if (n <= 0) {
        throw invalid_argument("Количество узлов должно быть положительным");
    }

    // Ввод узлов
    vector<string> nodes;
    for (int i = 0; i < n; i++) {
        string node;
        cout << "Узел " << i + 1 << ": ";
        cin >> node;
        if (node.empty()) {
            throw invalid_argument("Имя узла не может быть пустым");
        }
        nodes.push_back(node);
        dependencies[node] = {};
    }

    // Ввод зависимостей
    cout << "Введите зависимости (формат: узел зависимость1 зависимость2 ...):" << endl;
    cin.ignore();

    for (const string& node : nodes) {
        cout << node << " зависит от: ";
        string line;
        getline(cin, line);

        if (!line.empty()) {
            stringstream ss(line);
            string dep;
            while (ss >> dep) {
                if (dependencies.find(dep) == dependencies.end()) {
                    throw runtime_error("Неизвестная зависимость: " + dep);
                }
                dependencies[node].push_back(dep);
            }
        }
    }

    vector<string> result = topologicalSort(dependencies);

    cout << "Топологический порядок: ";
    for (size_t i = 0; i < result.size(); i++) {
        cout << result[i];
        if (i < result.size() - 1) cout << ", ";
    }
    cout << endl;
}

int main() {
    try {
        int choice;
        cout << "Топологическая сортировка графа" << endl;
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
