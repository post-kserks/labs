#include "avl.h"
#include <algorithm>

// Получить высоту узла (nullptr имеет высоту 0)
int getHeight(AVLNode* node) {
    return node ? node->height : 0;
}

// Обновить высоту узла
void updateHeight(AVLNode* node) {
    if (node) {
        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    }
}

// Получить баланс узла (разница высот левого и правого поддеревьев)
int getBalance(AVLNode* node) {
    return node ? getHeight(node->right) - getHeight(node->left) : 0;
}

// Правый поворот вокруг узла y
// Возвращает новый корень поддерева
AVLNode* rotateRight(AVLNode* y) {
    AVLNode* x = y->left;      // x становится новым корнем
    AVLNode* T2 = x->right;    // T2 - правое поддерево x

    // Выполняем поворот
    x->right = y;
    y->left = T2;

    // Обновляем высоты
    updateHeight(y);
    updateHeight(x);

    return x; // x теперь корень этого поддерева
}

// Левый поворот вокруг узла x
// Возвращает новый корень поддерева
AVLNode* rotateLeft(AVLNode* x) {
    AVLNode* y = x->right;     // y становится новым корнем
    AVLNode* T2 = y->left;     // T2 - левое поддерево y

    // Выполняем поворот
    y->left = x;
    x->right = T2;

    // Обновляем высоты
    updateHeight(x);
    updateHeight(y);

    return y; // y теперь корень этого поддерева
}

// Вставить ключ в AVL-дерево и вернуть новый корень
AVLNode* insertAVL(AVLNode* root, int key) {
    // 1. Обычная вставка в бинарное дерево поиска
    if (!root) {
        return new AVLNode(key);
    }

    if (key < root->key) {
        root->left = insertAVL(root->left, key);
    } else if (key > root->key) {
        root->right = insertAVL(root->right, key);
    } else {
        return root; // дубликаты не вставляем
    }

    // 2. Обновляем высоту текущего узла
    updateHeight(root);

    // 3. Получаем баланс для проверки необходимости балансировки
    int balance = getBalance(root);

    // 4. Если узел разбалансирован, выполняем повороты

    // Левый-левый случай (LL)
    if (balance < -1 && key < root->left->key) {
        return rotateRight(root);
    }

    // Правый-правый случай (RR)
    if (balance > 1 && key > root->right->key) {
        return rotateLeft(root);
    }

    // Левый-правый случай (LR)
    if (balance < -1 && key > root->left->key) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    // Правый-левый случай (RL)
    if (balance > 1 && key < root->right->key) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root; // возвращаем неизмененный корень
}

// Вывести дерево в отсортированном порядке (in-order traversal)
void printInOrder(AVLNode* root) {
    if (root) {
        printInOrder(root->left);
        std::cout << root->key << " ";
        printInOrder(root->right);
    }
}

// Освободить память дерева
void deleteTree(AVLNode* root) {
    if (root) {
        deleteTree(root->left);
        deleteTree(root->right);
        delete root;
    }
}

