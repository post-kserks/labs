#ifndef RBT_TREE_H
#define RBT_TREE_H

#include "common.h"

// Создание нового узла RBT
RBTNode* create_rbt_node(int key);

// Вставка ключа в RBT
RBTNode* rbt_insert(RBTNode* root, int key);

// Вспомогательные функции для балансировки RBT
RBTNode* rbt_insert_fixup(RBTNode* root, RBTNode* node);

// Левый поворот для RBT
RBTNode* rbt_rotate_left(RBTNode* root, RBTNode* x);

// Правый поворот для RBT
RBTNode* rbt_rotate_right(RBTNode* root, RBTNode* y);

// Поиск ключа в RBT
RBTNode* rbt_search(RBTNode* root, int key);

// Освобождение памяти RBT
void free_rbt_tree(RBTNode* root);

// Получение высоты RBT (для сравнения)
int get_rbt_height(RBTNode* root);

#endif
