#include "cache.h"
#include "metrics.h"
#include <iostream>
#include <chrono>
#include <random>

void extended_performance_test() {
    std::cout << "=== Extended Performance Test (1000 operations) ===" << std::endl;

    const int NUM_OPERATIONS = 1000;
    const int CACHE_SIZE = 10;
    const int KEY_RANGE = 20; // Ограничиваем диапазон ключей для создания повторений

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> key_dist(1, KEY_RANGE);

    // Генерируем последовательность операций
    int operations[NUM_OPERATIONS];
    for (int i = 0; i < NUM_OPERATIONS; i++) {
        operations[i] = key_dist(gen);
    }

    // Тестируем все подходы
    Cache* caches[] = {
        create_cache(CACHE_SIZE, true),  // LRU Iterative
        create_cache(CACHE_SIZE, true),  // LRU Recursive
        create_cache(CACHE_SIZE, false), // LFU Iterative
        create_cache(CACHE_SIZE, false)  // LFU Recursive
    };

    CacheMetrics metrics[4];
    long long times[4];

    const char* names[] = {
        "LRU Iterative", "LRU Recursive", "LFU Iterative", "LFU Recursive"
    };

    // Тестируем каждый подход
    for (int approach = 0; approach < 4; approach++) {
        auto start = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < NUM_OPERATIONS; i++) {
            int key = operations[i];
            int value;

            switch (approach) {
                case 0: // LRU Iterative
                    value = lru_get_iterative(caches[approach], key);
                    if (value == -1) {
                        metrics[approach].record_miss();
                        lru_put_iterative(caches[approach], key, key * 10);
                    } else {
                        metrics[approach].record_hit();
                    }
                    break;

                case 1: // LRU Recursive
                    value = lru_get_recursive(caches[approach], key);
                    if (value == -1) {
                        metrics[approach].record_miss();
                        lru_put_recursive(caches[approach], key, key * 10);
                    } else {
                        metrics[approach].record_hit();
                    }
                    break;

                case 2: // LFU Iterative
                    value = lfu_get_iterative(caches[approach], key);
                    if (value == -1) {
                        metrics[approach].record_miss();
                        lfu_put_iterative(caches[approach], key, key * 10);
                    } else {
                        metrics[approach].record_hit();
                    }
                    break;

                case 3: // LFU Recursive
                    value = lfu_get_recursive(caches[approach], key);
                    if (value == -1) {
                        metrics[approach].record_miss();
                        lfu_put_recursive(caches[approach], key, key * 10);
                    } else {
                        metrics[approach].record_hit();
                    }
                    break;
            }
        }

        auto end = std::chrono::high_resolution_clock::now();
        times[approach] = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    }

    // Выводим результаты
    for (int i = 0; i < 4; i++) {
        std::cout << names[i] << " - Time: " << times[i] << "μs, ";
        metrics[i].print();
    }

    // Очищаем память
    for (int i = 0; i < 4; i++) {
        destroy_cache(caches[i]);
    }
}

void test_different_access_patterns() {
    std::cout << "\n=== Testing Different Access Patterns ===" << std::endl;

    // Паттерн 1: Частые повторения малого набора ключей
    std::cout << "Pattern 1: Frequent repeats of small key set" << std::endl;
    int pattern1[] = {1,2,1,3,1,2,1,4,1,3,1,2,1,5,1,4,1,3,1,2};

    Cache* lru1 = create_cache(3, true);
    Cache* lfu1 = create_cache(3, false);
    CacheMetrics m_lru1, m_lfu1;

    for (int key : pattern1) {
        if (lru_get_iterative(lru1, key) == -1) {
            m_lru1.record_miss();
            lru_put_iterative(lru1, key, key * 10);
        } else {
            m_lru1.record_hit();
        }

        if (lfu_get_iterative(lfu1, key) == -1) {
            m_lfu1.record_miss();
            lfu_put_iterative(lfu1, key, key * 10);
        } else {
            m_lfu1.record_hit();
        }
    }

    std::cout << "LRU: "; m_lru1.print();
    std::cout << "LFU: "; m_lfu1.print();

    destroy_cache(lru1);
    destroy_cache(lfu1);
}

int main() {
    extended_performance_test();
    test_different_access_patterns();
    return 0;
}
