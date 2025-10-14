#include <iostream>
#include <stack>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <sstream>

using namespace std;

vector<string> dfsTraversal(const unordered_map<string, vector<string>>& graph, const string& start_commit) {
    if (graph.find(start_commit) == graph.end()) {
        throw runtime_error("Стартовый коммит не найден в графе: " + start_commit);
    }

    stack<string> st;
    unordered_set<string> visited;
    vector<string> result;

    st.push(start_commit);

    while (!st.empty()) {
        string current = st.top();
        st.pop();

        if (visited.find(current) == visited.end()) {
            visited.insert(current);
            result.push_back(current);

            if (graph.find(current) != graph.end()) {
                const vector<string>& parents = graph.at(current);
                for (auto it = parents.rbegin(); it != parents.rend(); ++it) {
                    if (graph.find(*it) == graph.end()) {
                        throw runtime_error("Родительский коммит не найден: " + *it);
                    }
                    if (visited.find(*it) == visited.end()) {
                        st.push(*it);
                    }
                }
            }
        }
    }

    return result;
}

void runTest() {
    cout << "=== ТЕСТОВЫЕ ДАННЫЕ ===" << endl;

    unordered_map<string, vector<string>> testGraph = {
        {"C1", {}},
        {"C2", {"C1"}},
        {"C3", {"C1"}},
        {"C4", {"C2", "C3"}}
    };

    cout << "Граф коммитов:" << endl;
    for (const auto& node : testGraph) {
        cout << node.first << " -> ";
        for (const string& parent : node.second) {
            cout << parent << " ";
        }
        cout << endl;
    }

    string start_commit = "C4";
    cout << "Стартовый коммит: " << start_commit << endl;

    vector<string> result = dfsTraversal(testGraph, start_commit);

    cout << "Порядок обхода DFS: ";
    for (size_t i = 0; i < result.size(); i++) {
        cout << result[i];
        if (i < result.size() - 1) cout << " ";
    }
    cout << endl;
    cout << "Посещено коммитов: " << result.size() << endl << endl;
}

void manualInput() {
    cout << "=== РУЧНОЙ ВВОД ===" << endl;

    unordered_map<string, vector<string>> graph;

    cout << "Введите количество коммитов: ";
    int n;
    cin >> n;

    if (n <= 0) {
        throw invalid_argument("Количество коммитов должно быть положительным");
    }

    // Ввод коммитов
    vector<string> commits;
    for (int i = 0; i < n; i++) {
        string commit;
        cout << "Коммит " << i + 1 << ": ";
        cin >> commit;
        if (commit.empty()) {
            throw invalid_argument("Имя коммита не может быть пустым");
        }
        commits.push_back(commit);
        graph[commit] = {};
    }

    // Ввод родителей
    cout << "Введите родителей для каждого коммита (формат: коммит родитель1 родитель2 ...):" << endl;
    cin.ignore();

    for (const string& commit : commits) {
        cout << "Родители для " << commit << ": ";
        string line;
        getline(cin, line);

        if (!line.empty()) {
            stringstream ss(line);
            string parent;
            while (ss >> parent) {
                if (graph.find(parent) == graph.end()) {
                    throw runtime_error("Неизвестный коммит: " + parent);
                }
                graph[commit].push_back(parent);
            }
        }
    }

    string start_commit;
    cout << "Введите стартовый коммит: ";
    cin >> start_commit;

    vector<string> result = dfsTraversal(graph, start_commit);

    cout << "Порядок обхода DFS: ";
    for (size_t i = 0; i < result.size(); i++) {
        cout << result[i];
        if (i < result.size() - 1) cout << " ";
    }
    cout << endl;
    cout << "Посещено коммитов: " << result.size() << endl;
}

int main() {
    try {
        int choice;
        cout << "Обход графа коммитов в глубину (DFS)" << endl;
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
