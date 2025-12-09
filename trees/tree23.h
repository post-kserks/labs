#ifndef TREE23_H
#define TREE23_H

#include <iostream>

// Узел 2-3 дерева
struct Tree23Node {
    bool isLeaf;           // true если лист
    int keys[2];           // ключи (0 или 1-2 ключа)
    int keyCount;          // количество ключей (1 или 2)
    Tree23Node* children[3]; // потомки (2 или 3)

    Tree23Node(bool leaf = true) : isLeaf(leaf), keyCount(0) {
        children[0] = children[1] = children[2] = nullptr;
    }
};

// Структура для хранения результата вставки
struct InsertResult {
    Tree23Node* node;      // новый узел
    int promotedKey;       // ключ для продвижения вверх (если разделение)
    Tree23Node* rightChild; // правый потомок при разделении
    bool split;            // произошло ли разделение

    InsertResult(Tree23Node* n, int key = 0, Tree23Node* right = nullptr, bool s = false)
        : node(n), promotedKey(key), rightChild(right), split(s) {}
};

// Создать новый лист с одним ключом
Tree23Node* createLeaf(int key);

// Создать новый внутренний узел
Tree23Node* createInternal(Tree23Node* left, int key, Tree23Node* right);

// Вставить ключ в поддерево
InsertResult insertIntoNode(Tree23Node* node, int key);

// Основная функция вставки в 2-3 дерево
Tree23Node* insert23(Tree23Node* root, int key);

// Найти ключ в дереве
bool search23(Tree23Node* root, int key);

// Вывести дерево (простой обход)
void print23(Tree23Node* root);

// Освободить память дерева
void deleteTree23(Tree23Node* root);

#endif // TREE23_H
