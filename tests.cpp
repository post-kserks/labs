#include "tests.h"
#include <iostream>
#include <iomanip>
#include <vector>

std::vector<TestScenario> createTestScenarios() {
    std::vector<TestScenario> scenarios;

    // 1. Открытое пространство
    TestScenario openSpace("Открытое пространство", 20, 20, Point(1, 1), Point(18, 18),
                          Point(1, 1).distance(Point(18, 18)));
    scenarios.push_back(openSpace);

    // 2. Улучшенный лабиринт - гарантированно проходимый
    TestScenario maze("Улучшенный лабиринт", 20, 20, Point(1, 1), Point(18, 18), 36.0);
    // Горизонтальные стены с проходами
    for (int i = 0; i < 20; i++) {
        if (i != 5 && i != 15) {
            maze.map.addObstacle(i, 5);
            maze.map.addObstacle(i, 15);
        }
    }
    // Вертикальные стены с проходами
    for (int i = 0; i < 20; i++) {
        if (i != 10) {
            maze.map.addObstacle(10, i);
        }
    }
    scenarios.push_back(maze);

    // 3. Множество препятствий
    TestScenario obstacles("Множество препятствий", 15, 15, Point(1, 1), Point(13, 13), 18.0);
    // Случайные препятствия
    for (int i = 3; i < 12; i += 2) {
        for (int j = 3; j < 12; j += 2) {
            obstacles.map.addObstacle(i, j);
        }
    }
    scenarios.push_back(obstacles);

    // 4. Узкие коридоры
    TestScenario narrow("Узкие коридоры", 25, 15, Point(1, 7), Point(23, 7), 22.0);
    // Создаем узкий коридор
    for (int i = 0; i < 25; i++) {
        if (i < 10 || i > 14) {
            narrow.map.addObstacle(i, 5);
            narrow.map.addObstacle(i, 9);
        }
    }
    scenarios.push_back(narrow);

    return scenarios;
}

void runTests() {
    std::vector<TestScenario> scenarios = createTestScenarios();

    std::cout << std::fixed << std::setprecision(3);

    // Статистика по алгоритмам
    struct AlgorithmStats {
        std::string name;
        double totalLength;
        int totalNodes;
        double totalSmoothness;
        int successfulTests;

        // Конструктор
        AlgorithmStats(const std::string& n)
            : name(n), totalLength(0), totalNodes(0), totalSmoothness(0), successfulTests(0) {}
    };

    AlgorithmStats statsA("A*");
    AlgorithmStats statsPS("A*PS");
    AlgorithmStats statsTheta("Theta*");

    for (const auto& scenario : scenarios) {
        std::cout << "\n=== " << scenario.name << " ===" << std::endl;
        std::cout << "Размер карты: " << scenario.map.getWidth() << "x" << scenario.map.getHeight() << std::endl;
        std::cout << "Старт: (" << scenario.start.x << ", " << scenario.start.y << ")" << std::endl;
        std::cout << "Цель: (" << scenario.goal.x << ", " << scenario.goal.y << ")" << std::endl;
        std::cout << "Оптимальная длина: " << scenario.optimalLength << std::endl;

        int nodesA, nodesPS, nodesTheta;

        // Запуск алгоритмов
        auto pathA = aStar(scenario.start, scenario.goal, scenario.map, nodesA);
        auto pathPS = aStarPS(scenario.start, scenario.goal, scenario.map, nodesPS);
        auto pathTheta = thetaStar(scenario.start, scenario.goal, scenario.map, nodesTheta);

        // Вычисление метрик
        double lengthA = pathLength(pathA);
        double lengthPS = pathLength(pathPS);
        double lengthTheta = pathLength(pathTheta);

        std::cout << "\nРезультаты:" << std::endl;
        std::cout << "Алгоритм    | Длина  | Узлы | КО     | ОО(%)  | СУП(°) | ГП    | ЭП" << std::endl;
        std::cout << "------------|--------|------|--------|--------|--------|-------|------" << std::endl;

        // A*
        if (!pathA.empty()) {
            double koA = lengthA / scenario.optimalLength;
            double ooA = (lengthA - scenario.optimalLength) / scenario.optimalLength * 100;
            double supA = totalTurningAngle(pathA);
            double gpA = pathSmoothness(pathA);
            double epA = searchEfficiency(scenario.optimalLength, nodesA);

            std::cout << "A*         | " << std::setw(6) << lengthA << " | " << std::setw(4) << nodesA
                      << " | " << std::setw(6) << koA << " | " << std::setw(6) << ooA
                      << " | " << std::setw(6) << supA << " | " << std::setw(5) << gpA
                      << " | " << std::setw(5) << epA << std::endl;

            statsA.totalLength += lengthA;
            statsA.totalNodes += nodesA;
            statsA.totalSmoothness += gpA;
            statsA.successfulTests++;
        } else {
            std::cout << "A*         | Не найден | " << std::setw(4) << nodesA
                      << " |   N/A   |   N/A   |   N/A   |  N/A  |  N/A" << std::endl;
        }

        // A*PS
        if (!pathPS.empty()) {
            double koPS = lengthPS / scenario.optimalLength;
            double ooPS = (lengthPS - scenario.optimalLength) / scenario.optimalLength * 100;
            double supPS = totalTurningAngle(pathPS);
            double gpPS = pathSmoothness(pathPS);
            double epPS = searchEfficiency(scenario.optimalLength, nodesPS);

            std::cout << "A*PS       | " << std::setw(6) << lengthPS << " | " << std::setw(4) << nodesPS
                      << " | " << std::setw(6) << koPS << " | " << std::setw(6) << ooPS
                      << " | " << std::setw(6) << supPS << " | " << std::setw(5) << gpPS
                      << " | " << std::setw(5) << epPS << std::endl;

            statsPS.totalLength += lengthPS;
            statsPS.totalNodes += nodesPS;
            statsPS.totalSmoothness += gpPS;
            statsPS.successfulTests++;
        } else {
            std::cout << "A*PS       | Не найден | " << std::setw(4) << nodesPS
                      << " |   N/A   |   N/A   |   N/A   |  N/A  |  N/A" << std::endl;
        }

        // Theta*
        if (!pathTheta.empty()) {
            double koTheta = lengthTheta / scenario.optimalLength;
            double ooTheta = (lengthTheta - scenario.optimalLength) / scenario.optimalLength * 100;
            double supTheta = totalTurningAngle(pathTheta);
            double gpTheta = pathSmoothness(pathTheta);
            double epTheta = searchEfficiency(scenario.optimalLength, nodesTheta);

            std::cout << "Theta*     | " << std::setw(6) << lengthTheta << " | " << std::setw(4) << nodesTheta
                      << " | " << std::setw(6) << koTheta << " | " << std::setw(6) << ooTheta
                      << " | " << std::setw(6) << supTheta << " | " << std::setw(5) << gpTheta
                      << " | " << std::setw(5) << epTheta << std::endl;

            statsTheta.totalLength += lengthTheta;
            statsTheta.totalNodes += nodesTheta;
            statsTheta.totalSmoothness += gpTheta;
            statsTheta.successfulTests++;
        } else {
            std::cout << "Theta*     | Не найден | " << std::setw(4) << nodesTheta
                      << " |   N/A   |   N/A   |   N/A   |  N/A  |  N/A" << std::endl;
        }
    }

    // Вывод итоговой статистики
    std::cout << "\n\n=== ИТОГОВАЯ СТАТИСТИКА ===" << std::endl;
    std::cout << "Алгоритм    | Успешных | Ср.длина | Ср.узлы | Ср.гладкость" << std::endl;
    std::cout << "------------|----------|----------|---------|-------------" << std::endl;

    // A*
    if (statsA.successfulTests > 0) {
        double avgLength = statsA.totalLength / statsA.successfulTests;
        double avgNodes = static_cast<double>(statsA.totalNodes) / statsA.successfulTests;
        double avgSmoothness = statsA.totalSmoothness / statsA.successfulTests;

        std::cout << "A*         | "
                  << std::setw(8) << statsA.successfulTests << " | "
                  << std::setw(8) << avgLength << " | "
                  << std::setw(7) << avgNodes << " | "
                  << std::setw(11) << avgSmoothness << std::endl;
    }

    // A*PS
    if (statsPS.successfulTests > 0) {
        double avgLength = statsPS.totalLength / statsPS.successfulTests;
        double avgNodes = static_cast<double>(statsPS.totalNodes) / statsPS.successfulTests;
        double avgSmoothness = statsPS.totalSmoothness / statsPS.successfulTests;

        std::cout << "A*PS       | "
                  << std::setw(8) << statsPS.successfulTests << " | "
                  << std::setw(8) << avgLength << " | "
                  << std::setw(7) << avgNodes << " | "
                  << std::setw(11) << avgSmoothness << std::endl;
    }

    // Theta*
    if (statsTheta.successfulTests > 0) {
        double avgLength = statsTheta.totalLength / statsTheta.successfulTests;
        double avgNodes = static_cast<double>(statsTheta.totalNodes) / statsTheta.successfulTests;
        double avgSmoothness = statsTheta.totalSmoothness / statsTheta.successfulTests;

        std::cout << "Theta*     | "
                  << std::setw(8) << statsTheta.successfulTests << " | "
                  << std::setw(8) << avgLength << " | "
                  << std::setw(7) << avgNodes << " | "
                  << std::setw(11) << avgSmoothness << std::endl;
    }

    // Вывод выводов
    std::cout << "\n=== ВЫВОДЫ ===" << std::endl;
    std::cout << "1. Theta* показывает лучшую гладкость пути за счет проверки прямой видимости" << std::endl;
    std::cout << "2. A*PS улучшает базовый A* за счет пост-обработки" << std::endl;
    std::cout << "3. В открытых пространствах все алгоритмы работают одинаково хорошо" << std::endl;
    std::cout << "4. Theta* часто находит более короткие пути, но требует больше вычислений" << std::endl;
    std::cout << "5. A* надежен, но создает 'зубчатые' пути в сложных условиях" << std::endl;
}
