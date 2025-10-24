#include "cache.h"
#include "metrics.h"
#include <iostream>
#include <chrono>

void test_recursive_vs_iterative() {
    std::cout << "=== Testing Recursive vs Iterative Approaches ===" << std::endl;

    // Тестовая последовательность операций
    int operations[] = {1, 2, 3, 1, 4, 2, 5, 1, 3, 6, 7, 1, 2};
    int num_operations = sizeof(operations) / sizeof(operations[0]);

    // Создаем кэши разных типов
    Cache* lru_iterative = create_cache(4, true);
    Cache* lru_recursive = create_cache(4, true);
    Cache* lfu_iterative = create_cache(4, false);
    Cache* lfu_recursive = create_cache(4, false);

    CacheMetrics lru_iter_metrics, lru_rec_metrics;
    CacheMetrics lfu_iter_metrics, lfu_rec_metrics;

    // Тестируем производительность
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < num_operations; i++) {
        int key = operations[i];
        if (lru_get_iterative(lru_iterative, key) == -1) {
            lru_iter_metrics.record_miss();
            lru_put_iterative(lru_iterative, key, key * 10);
        } else {
            lru_iter_metrics.record_hit();
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto lru_iter_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < num_operations; i++) {
        int key = operations[i];
        if (lru_get_recursive(lru_recursive, key) == -1) {
            lru_rec_metrics.record_miss();
            lru_put_recursive(lru_recursive, key, key * 10);
        } else {
            lru_rec_metrics.record_hit();
        }
    }
    end = std::chrono::high_resolution_clock::now();
    auto lru_rec_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < num_operations; i++) {
        int key = operations[i];
        if (lfu_get_iterative(lfu_iterative, key) == -1) {
            lfu_iter_metrics.record_miss();
            lfu_put_iterative(lfu_iterative, key, key * 10);
        } else {
            lfu_iter_metrics.record_hit();
        }
    }
    end = std::chrono::high_resolution_clock::now();
    auto lfu_iter_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < num_operations; i++) {
        int key = operations[i];
        if (lfu_get_recursive(lfu_recursive, key) == -1) {
            lfu_rec_metrics.record_miss();
            lfu_put_recursive(lfu_recursive, key, key * 10);
        } else {
            lfu_rec_metrics.record_hit();
        }
    }
    end = std::chrono::high_resolution_clock::now();
    auto lfu_rec_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    // Выводим результаты
    std::cout << "LRU Iterative - Time: " << lru_iter_time << "μs, ";
    lru_iter_metrics.print();

    std::cout << "LRU Recursive - Time: " << lru_rec_time << "μs, ";
    lru_rec_metrics.print();

    std::cout << "LFU Iterative - Time: " << lfu_iter_time << "μs, ";
    lfu_iter_metrics.print();

    std::cout << "LFU Recursive - Time: " << lfu_rec_time << "μs, ";
    lfu_rec_metrics.print();

    // Очищаем память
    destroy_cache(lru_iterative);
    destroy_cache(lru_recursive);
    destroy_cache(lfu_iterative);
    destroy_cache(lfu_recursive);
}

int main() {
    test_recursive_vs_iterative();
    return 0;
}
