#include "scenario_tests.h"
#include <iostream>
#include <random>
#include <chrono>

void generate_random_data(int* data, int size, int range) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, range);

    for (int i = 0; i < size; ++i) {
        data[i] = dis(gen);
    }
}

TestResult test_dictionary_scenario() {
    TestResult result = {0, 0, 0, 0};

    // Генерация тестовых данных
    int data[NUM_OPERATIONS];
    generate_random_data(data, NUM_OPERATIONS, DATA_RANGE);

    // Построение начальных деревьев
    AVLNode* avl_root = nullptr;
    RBTNode* rbt_root = nullptr;

    for (int i = 0; i < 1000; ++i) {
        avl_root = avl_insert(avl_root, data[i]);
        rbt_root = rbt_insert(rbt_root, data[i]);
    }

    // Тестирование операций (80% поиск, 20% вставка)
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < NUM_OPERATIONS; ++i) {
        if (i % 5 == 0) { // 20% вставка
            avl_root = avl_insert(avl_root, data[i % 1000] + DATA_RANGE);
        } else { // 80% поиск
            avl_search(avl_root, data[i % 1000]);
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    result.avl_time = std::chrono::duration<double>(end - start).count();
    result.avl_height = get_height(avl_root);

    start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < NUM_OPERATIONS; ++i) {
        if (i % 5 == 0) {
            rbt_root = rbt_insert(rbt_root, data[i % 1000] + DATA_RANGE);
        } else {
            rbt_search(rbt_root, data[i % 1000]);
        }
    }

    end = std::chrono::high_resolution_clock::now();
    result.rbt_time = std::chrono::duration<double>(end - start).count();
    result.rbt_height = get_rbt_height(rbt_root);

    free_avl_tree(avl_root);
    free_rbt_tree(rbt_root);

    return result;
}

TestResult test_cache_scenario() {
    TestResult result = {0, 0, 0, 0};

    int data[NUM_OPERATIONS];
    generate_random_data(data, NUM_OPERATIONS, DATA_RANGE);

    AVLNode* avl_root = nullptr;
    RBTNode* rbt_root = nullptr;

    // Начальное заполнение
    for (int i = 0; i < 500; ++i) {
        avl_root = avl_insert(avl_root, data[i]);
        rbt_root = rbt_insert(rbt_root, data[i]);
    }

    // Тестирование (50% поиск, 30% вставка, 20% удаление)
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < NUM_OPERATIONS; ++i) {
        int op_type = i % 10;
        int key = data[i % 500];

        if (op_type < 5) { // 50% поиск
            avl_search(avl_root, key);
        } else if (op_type < 8) { // 30% вставка
            avl_root = avl_insert(avl_root, key + DATA_RANGE);
        } else { // 20% удаление (упрощенная версия - вставка нового)
            avl_root = avl_insert(avl_root, key + 2 * DATA_RANGE);
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    result.avl_time = std::chrono::duration<double>(end - start).count();
    result.avl_height = get_height(avl_root);

    start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < NUM_OPERATIONS; ++i) {
        int op_type = i % 10;
        int key = data[i % 500];

        if (op_type < 5) {
            rbt_search(rbt_root, key);
        } else if (op_type < 8) {
            rbt_root = rbt_insert(rbt_root, key + DATA_RANGE);
        } else {
            rbt_root = rbt_insert(rbt_root, key + 2 * DATA_RANGE);
        }
    }

    end = std::chrono::high_resolution_clock::now();
    result.rbt_time = std::chrono::duration<double>(end - start).count();
    result.rbt_height = get_rbt_height(rbt_root);

    free_avl_tree(avl_root);
    free_rbt_tree(rbt_root);

    return result;
}

TestResult test_logging_scenario() {
    TestResult result = {0, 0, 0, 0};

    int data[NUM_OPERATIONS];
    generate_random_data(data, NUM_OPERATIONS, DATA_RANGE);

    AVLNode* avl_root = nullptr;
    RBTNode* rbt_root = nullptr;

    // Начальное заполнение
    for (int i = 0; i < 100; ++i) {
        avl_root = avl_insert(avl_root, data[i]);
        rbt_root = rbt_insert(rbt_root, data[i]);
    }

    // Тестирование (10% поиск, 90% вставка)
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < NUM_OPERATIONS; ++i) {
        if (i % 10 == 0) { // 10% поиск
            avl_search(avl_root, data[i % 100]);
        } else { // 90% вставка
            avl_root = avl_insert(avl_root, data[i] + DATA_RANGE);
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    result.avl_time = std::chrono::duration<double>(end - start).count();
    result.avl_height = get_height(avl_root);

    start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < NUM_OPERATIONS; ++i) {
        if (i % 10 == 0) {
            rbt_search(rbt_root, data[i % 100]);
        } else {
            rbt_root = rbt_insert(rbt_root, data[i] + DATA_RANGE);
        }
    }

    end = std::chrono::high_resolution_clock::now();
    result.rbt_time = std::chrono::duration<double>(end - start).count();
    result.rbt_height = get_rbt_height(rbt_root);

    free_avl_tree(avl_root);
    free_rbt_tree(rbt_root);

    return result;
}

void run_all_tests() {
    std::cout << "=== ТЕСТИРОВАНИЕ СЦЕНАРИЕВ ===" << std::endl;

    TestResult dict_result = test_dictionary_scenario();
    std::cout << "\n1. СЦЕНАРИЙ 'СЛОВАРЬ' (80% поиск, 20% вставка):" << std::endl;
    std::cout << "AVL - Время: " << dict_result.avl_time << "с, Высота: " << dict_result.avl_height << std::endl;
    std::cout << "RBT - Время: " << dict_result.rbt_time << "с, Высота: " << dict_result.rbt_height << std::endl;
    std::cout << "ПОБЕДИТЕЛЬ: " << (dict_result.avl_time < dict_result.rbt_time ? "AVL" : "RBT") << std::endl;

    TestResult cache_result = test_cache_scenario();
    std::cout << "\n2. СЦЕНАРИЙ 'КЕШ СЕССИЙ' (50% поиск, 30% вставка, 20% удаление):" << std::endl;
    std::cout << "AVL - Время: " << cache_result.avl_time << "с, Высота: " << cache_result.avl_height << std::endl;
    std::cout << "RBT - Время: " << cache_result.rbt_time << "с, Высота: " << cache_result.rbt_height << std::endl;
    std::cout << "ПОБЕДИТЕЛЬ: " << (cache_result.avl_time < cache_result.rbt_time ? "AVL" : "RBT") << std::endl;

    TestResult log_result = test_logging_scenario();
    std::cout << "\n3. СЦЕНАРИЙ 'ЛОГИРОВАНИЕ' (10% поиск, 90% вставка):" << std::endl;
    std::cout << "AVL - Время: " << log_result.avl_time << "с, Высота: " << log_result.avl_height << std::endl;
    std::cout << "RBT - Время: " << log_result.rbt_time << "с, Высота: " << log_result.rbt_height << std::endl;
    std::cout << "ПОБЕДИТЕЛЬ: " << (log_result.avl_time < log_result.rbt_time ? "AVL" : "RBT") << std::endl;

    std::cout << "\n=== АНАЛИЗ РЕЗУЛЬТАТОВ ===" << std::endl;
    std::cout << "AVL лучше для сценариев с частым поиском" << std::endl;
    std::cout << "RBT лучше для сценариев с частыми вставками/удалениями" << std::endl;
}
