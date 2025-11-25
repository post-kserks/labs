#ifndef TESTS_H
#define TESTS_H

#include "graph.h"
#include "algorithms.h"
#include "metrics.h"
#include <vector>
#include <string>

// Тестовый сценарий
struct TestScenario {
    std::string name;
    Map map;
    Point start;
    Point goal;
    double optimalLength;

    // Конструктор по умолчанию
    TestScenario() : name(""), map(0, 0), start(0, 0), goal(0, 0), optimalLength(0.0) {}

    // Конструктор с параметрами
    TestScenario(const std::string& n, int mapWidth, int mapHeight,
                 const Point& s, const Point& g, double optLen)
        : name(n), map(mapWidth, mapHeight), start(s), goal(g), optimalLength(optLen) {}
};

// Создание тестовых сценариев
std::vector<TestScenario> createTestScenarios();

// Запуск тестов и сбор статистики
void runTests();

#endif
