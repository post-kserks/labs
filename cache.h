#ifndef CACHE_H
#define CACHE_H

#include <iostream>

struct CacheNode {
    int key;
    int value;
    int frequency;      // Для LFU
    CacheNode* next;
    CacheNode* prev;

    CacheNode(int k, int v) : key(k), value(v), frequency(1), next(nullptr), prev(nullptr) {}
};

struct Cache {
    CacheNode* head;
    CacheNode* tail;
    size_t capacity;
    size_t size;
    bool is_lru;        // true для LRU, false для LFU

    Cache(size_t cap, bool lru) : head(nullptr), tail(nullptr), capacity(cap), size(0), is_lru(lru) {}
};

// Базовые функции списка
void addToFront(Cache* cache, CacheNode* node);
void removeNode(Cache* cache, CacheNode* node);
void moveToFront(Cache* cache, CacheNode* node);

// LRU функции (итеративные)
int lru_get_iterative(Cache* cache, int key);
void lru_put_iterative(Cache* cache, int key, int value);

// LRU функции (рекурсивные)
CacheNode* lru_find_recursive(CacheNode* current, int key);
int lru_get_recursive(Cache* cache, int key);
void lru_put_recursive(Cache* cache, int key, int value);

// LFU функции (итеративные)
int lfu_get_iterative(Cache* cache, int key);
void lfu_put_iterative(Cache* cache, int key, int value);

// LFU функции (рекурсивные)
CacheNode* lfu_find_recursive(CacheNode* current, int key);
CacheNode* lfu_find_least_frequent_recursive(CacheNode* current, CacheNode* min_node);
int lfu_get_recursive(Cache* cache, int key);
void lfu_put_recursive(Cache* cache, int key, int value);

// Общие функции
Cache* create_cache(size_t capacity, bool is_lru);
void destroy_cache(Cache* cache);
void print_cache(const Cache* cache);

#endif
