#ifndef SCENARIO_TESTS_H
#define SCENARIO_TESTS_H

#include "common.h"
#include "avl_tree.h"
#include "rbt_tree.h"

// Генерация случайных данных
void generate_random_data(int* data, int size, int range);

// Тестирование сценария "Словарь"
TestResult test_dictionary_scenario();

// Тестирование сценария "Кеш сессий"
TestResult test_cache_scenario();

// Тестирование сценария "Логирование"
TestResult test_logging_scenario();

// Запуск всех тестов и вывод результатов
void run_all_tests();

#endif
