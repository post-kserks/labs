#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "common.h"

// Создание нового узла AVL
AVLNode* create_avl_node(int key);

// Получение высоты узла
int get_height(AVLNode* node);

// Обновление высоты узла
void update_height(AVLNode* node);

// Получение баланса узла
int get_balance(AVLNode* node);

// Балансировка дерева
AVLNode* balance_avl(AVLNode* node);

// Вставка ключа в AVL-дерево
AVLNode* avl_insert(AVLNode* root, int key);

// Поиск ключа в AVL-дереве
AVLNode* avl_search(AVLNode* root, int key);

// Освобождение памяти AVL-дерева
void free_avl_tree(AVLNode* root);

#endif
