#ifndef COMMON_H
#define COMMON_H

#include <chrono>

// Типы операций
enum OperationType {
    SEARCH,
    INSERT,
    DELETE
};

// Результат теста
struct TestResult {
    double avl_time;
    double rbt_time;
    int avl_height;
    int rbt_height;
};

// Узел AVL-дерева
struct AVLNode {
    int key;
    AVLNode* left;
    AVLNode* right;
    int height;
};

// Узел красно-чёрного дерева
struct RBTNode {
    int key;
    RBTNode* left;
    RBTNode* right;
    RBTNode* parent;
    bool is_red; // true - красный, false - чёрный
};

// Константы для сценариев
const int NUM_OPERATIONS = 10000;
const int DATA_RANGE = 1000;

#endif
