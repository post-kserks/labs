#ifndef AVL_H
#define AVL_H

#include <iostream>

// Структура узла AVL-дерева
struct AVLNode {
    int key;        // ключ
    int height;     // высота поддерева
    AVLNode* left;  // левый потомок
    AVLNode* right; // правый потомок

    AVLNode(int k) : key(k), height(1), left(nullptr), right(nullptr) {}
};

// Получить высоту узла (nullptr имеет высоту 0)
int getHeight(AVLNode* node);

// Обновить высоту узла
void updateHeight(AVLNode* node);

// Получить баланс узла (разница высот левого и правого поддеревьев)
int getBalance(AVLNode* node);

// Правый поворот вокруг узла y
AVLNode* rotateRight(AVLNode* y);

// Левый поворот вокруг узла x
AVLNode* rotateLeft(AVLNode* x);

// Вставить ключ в AVL-дерево и вернуть новый корень
AVLNode* insertAVL(AVLNode* root, int key);

// Вывести дерево в отсортированном порядке (in-order traversal)
void printInOrder(AVLNode* root);

// Освободить память дерева
void deleteTree(AVLNode* root);

#endif // AVL_H
