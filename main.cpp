#include "cache.h"
#include "metrics.h"
#include <iostream>

void test_lru_iterative() {
    std::cout << "=== Testing LRU Iterative ===" << std::endl;
    Cache* cache = create_cache(3, true);
    CacheMetrics metrics;

    // Тестируем по примеру из задания
    lru_put_iterative(cache, 1, 100); // A
    print_cache(cache);

    lru_put_iterative(cache, 2, 200); // B
    print_cache(cache);

    lru_put_iterative(cache, 3, 300); // C
    print_cache(cache);

    if (lru_get_iterative(cache, 1) != -1) metrics.record_hit(); // A
    else metrics.record_miss();
    print_cache(cache);

    lru_put_iterative(cache, 4, 400); // D
    print_cache(cache);

    metrics.print();
    destroy_cache(cache);
}

void test_lfu_iterative() {
    std::cout << "\n=== Testing LFU Iterative ===" << std::endl;
    Cache* cache = create_cache(3, false);
    CacheMetrics metrics;

    // Тестируем по примеру из задания
    lfu_put_iterative(cache, 1, 100); // A (f=1)
    print_cache(cache);

    lfu_put_iterative(cache, 2, 200); // B (f=1)
    print_cache(cache);

    if (lfu_get_iterative(cache, 1) != -1) { // A (f=2)
        metrics.record_hit();
    } else {
        metrics.record_miss();
    }
    print_cache(cache);

    lfu_put_iterative(cache, 3, 300); // C (f=1)
    print_cache(cache);

    if (lfu_get_iterative(cache, 1) != -1) { // A (f=3)
        metrics.record_hit();
    } else {
        metrics.record_miss();
    }
    print_cache(cache);

    lfu_put_iterative(cache, 4, 400); // D (f=1)
    print_cache(cache);

    metrics.print();
    destroy_cache(cache);
}

void test_recursive_approaches() {
    std::cout << "\n=== Testing Recursive Approaches ===" << std::endl;

    Cache* lru_cache = create_cache(3, true);
    Cache* lfu_cache = create_cache(3, false);

    std::cout << "LRU Recursive Test:" << std::endl;
    lru_put_recursive(lru_cache, 1, 100);
    lru_put_recursive(lru_cache, 2, 200);
    lru_put_recursive(lru_cache, 3, 300);
    print_cache(lru_cache);

    lru_get_recursive(lru_cache, 1);
    print_cache(lru_cache);

    lru_put_recursive(lru_cache, 4, 400);
    print_cache(lru_cache);

    std::cout << "LFU Recursive Test:" << std::endl;
    lfu_put_recursive(lfu_cache, 1, 100);
    lfu_put_recursive(lfu_cache, 2, 200);
    lfu_get_recursive(lfu_cache, 1);
    lfu_put_recursive(lfu_cache, 3, 300);
    lfu_get_recursive(lfu_cache, 1);
    print_cache(lfu_cache);

    lfu_put_recursive(lfu_cache, 4, 400);
    print_cache(lfu_cache);

    destroy_cache(lru_cache);
    destroy_cache(lfu_cache);
}

int main() {
    test_lru_iterative();
    test_lfu_iterative();
    test_recursive_approaches();

    return 0;
}
