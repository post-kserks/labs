#include "cache.h"
#include <iostream>

// Базовые функции двусвязного списка

// Добавление узла в начало списка
void addToFront(Cache* cache, CacheNode* node) {
    if (!cache || !node) return;

    node->next = cache->head;
    node->prev = nullptr;

    if (cache->head) {
        cache->head->prev = node;
    }
    cache->head = node;

    if (!cache->tail) {
        cache->tail = node;
    }

    cache->size++;
}

// Удаление узла из списка
void removeNode(Cache* cache, CacheNode* node) {
    if (!cache || !node) return;

    if (node->prev) {
        node->prev->next = node->next;
    } else {
        cache->head = node->next;
    }

    if (node->next) {
        node->next->prev = node->prev;
    } else {
        cache->tail = node->prev;
    }

    cache->size--;
}

// Перемещение узла в начало списка
void moveToFront(Cache* cache, CacheNode* node) {
    if (!cache || !node || cache->head == node) return;

    removeNode(cache, node);
    addToFront(cache, node);
}

// LRU итеративная реализация
int lru_get_iterative(Cache* cache, int key) {
    if (!cache) return -1;

    // Итеративный поиск по списку
    CacheNode* current = cache->head;
    while (current) {
        if (current->key == key) {
            // Найден - перемещаем в начало
            moveToFront(cache, current);
            return current->value;
        }
        current = current->next;
    }

    return -1; // Не найден
}

void lru_put_iterative(Cache* cache, int key, int value) {
    if (!cache) return;

    // Проверяем, есть ли уже ключ
    CacheNode* current = cache->head;
    while (current) {
        if (current->key == key) {
            // Обновляем значение и перемещаем в начало
            current->value = value;
            moveToFront(cache, current);
            return;
        }
        current = current->next;
    }

    // Ключа нет - создаем новый узел
    CacheNode* newNode = new CacheNode(key, value);

    // Если кэш полный, удаляем последний элемент
    if (cache->size >= cache->capacity) {
        if (cache->tail) {
            CacheNode* toRemove = cache->tail;
            removeNode(cache, toRemove);
            delete toRemove;
        }
    }

    // Добавляем новый узел в начало
    addToFront(cache, newNode);
}

// LRU рекурсивные вспомогательные функции
CacheNode* lru_find_recursive(CacheNode* current, int key) {
    if (!current) return nullptr;
    if (current->key == key) return current;
    return lru_find_recursive(current->next, key);
}

// LRU рекурсивная реализация
int lru_get_recursive(Cache* cache, int key) {
    if (!cache) return -1;

    CacheNode* found = lru_find_recursive(cache->head, key);
    if (found) {
        moveToFront(cache, found);
        return found->value;
    }

    return -1;
}

void lru_put_recursive(Cache* cache, int key, int value) {
    if (!cache) return;

    // Проверяем наличие ключа рекурсивно
    CacheNode* existing = lru_find_recursive(cache->head, key);
    if (existing) {
        existing->value = value;
        moveToFront(cache, existing);
        return;
    }

    // Создаем новый узел
    CacheNode* newNode = new CacheNode(key, value);

    // Если кэш полный, удаляем последний элемент
    if (cache->size >= cache->capacity && cache->tail) {
        CacheNode* toRemove = cache->tail;
        removeNode(cache, toRemove);
        delete toRemove;
    }

    // Добавляем в начало
    addToFront(cache, newNode);
}

// LFU итеративная реализация
int lfu_get_iterative(Cache* cache, int key) {
    if (!cache) return -1;

    // Итеративный поиск по списку
    CacheNode* current = cache->head;
    while (current) {
        if (current->key == key) {
            // Найден - увеличиваем частоту использования
            current->frequency++;
            return current->value;
        }
        current = current->next;
    }

    return -1; // Не найден
}

void lfu_put_iterative(Cache* cache, int key, int value) {
    if (!cache) return;

    // Проверяем, есть ли уже ключ
    CacheNode* current = cache->head;
    while (current) {
        if (current->key == key) {
            // Обновляем значение и увеличиваем частоту
            current->value = value;
            current->frequency++;
            return;
        }
        current = current->next;
    }

    // Ключа нет - создаем новый узел
    CacheNode* newNode = new CacheNode(key, value);

    // Если кэш полный, ищем и удаляем наименее используемый элемент
    if (cache->size >= cache->capacity) {
        CacheNode* toRemove = cache->head;
        CacheNode* leastFrequent = cache->head;

        // Ищем узел с минимальной частотой использования
        current = cache->head;
        while (current) {
            if (current->frequency < leastFrequent->frequency) {
                leastFrequent = current;
            }
            current = current->next;
        }
        toRemove = leastFrequent;

        // Удаляем найденный узел
        removeNode(cache, toRemove);
        delete toRemove;
    }

    // Добавляем новый узел в начало
    addToFront(cache, newNode);
}

// LFU рекурсивные вспомогательные функции
CacheNode* lfu_find_recursive(CacheNode* current, int key) {
    if (!current) return nullptr;
    if (current->key == key) return current;
    return lfu_find_recursive(current->next, key);
}

CacheNode* lfu_find_least_frequent_recursive(CacheNode* current, CacheNode* min_node) {
    if (!current) return min_node;

    if (current->frequency < min_node->frequency) {
        min_node = current;
    }

    return lfu_find_least_frequent_recursive(current->next, min_node);
}

// LFU рекурсивная реализация
int lfu_get_recursive(Cache* cache, int key) {
    if (!cache) return -1;

    CacheNode* found = lfu_find_recursive(cache->head, key);
    if (found) {
        found->frequency++;
        return found->value;
    }

    return -1;
}

void lfu_put_recursive(Cache* cache, int key, int value) {
    if (!cache) return;

    // Проверяем наличие ключа рекурсивно
    CacheNode* existing = lfu_find_recursive(cache->head, key);
    if (existing) {
        existing->value = value;
        existing->frequency++;
        return;
    }

    // Создаем новый узел
    CacheNode* newNode = new CacheNode(key, value);

    // Если кэш полный, ищем и удаляем наименее используемый элемент рекурсивно
    if (cache->size >= cache->capacity && cache->head) {
        CacheNode* toRemove = lfu_find_least_frequent_recursive(cache->head, cache->head);
        removeNode(cache, toRemove);
        delete toRemove;
    }

    // Добавляем в начало
    addToFront(cache, newNode);
}

// Общие функции
Cache* create_cache(size_t capacity, bool is_lru) {
    return new Cache(capacity, is_lru);
}

void destroy_cache(Cache* cache) {
    if (!cache) return;

    CacheNode* current = cache->head;
    while (current) {
        CacheNode* next = current->next;
        delete current;
        current = next;
    }

    delete cache;
}

void print_cache(const Cache* cache) {
    if (!cache) {
        std::cout << "Cache is null" << std::endl;
        return;
    }

    std::cout << "Cache (" << (cache->is_lru ? "LRU" : "LFU")
              << ", size: " << cache->size << "/" << cache->capacity << "): ";

    CacheNode* current = cache->head;
    while (current) {
        std::cout << current->key;
        if (!cache->is_lru) {
            std::cout << "(f=" << current->frequency << ")";
        }
        if (current->next) {
            std::cout << " -> ";
        }
        current = current->next;
    }
    std::cout << std::endl;
}
