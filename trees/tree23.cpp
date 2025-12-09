#include "tree23.h"
#include <algorithm>

// Создать новый лист с одним ключом
Tree23Node* createLeaf(int key) {
    Tree23Node* node = new Tree23Node(true);
    node->keys[0] = key;
    node->keyCount = 1;
    return node;
}

// Создать новый внутренний узел с двумя потомками
Tree23Node* createInternal(Tree23Node* left, int key, Tree23Node* right) {
    Tree23Node* node = new Tree23Node(false);
    node->keys[0] = key;
    node->keyCount = 1;
    node->children[0] = left;
    node->children[1] = right;
    return node;
}

// Вставить ключ в поддерево
// Возвращает результат с возможным разделением
InsertResult insertIntoNode(Tree23Node* node, int key) {
    // Если лист
    if (node->isLeaf) {
        if (node->keyCount == 1) {
            // Есть место - просто вставляем
            if (key < node->keys[0]) {
                node->keys[1] = node->keys[0];
                node->keys[0] = key;
            } else {
                node->keys[1] = key;
            }
            node->keyCount = 2;
            return InsertResult(node, 0, nullptr, false);
        } else {
            // Лист полон - нужно разделить
            // Сортируем все три ключа
            int keys[3] = {node->keys[0], node->keys[1], key};
            std::sort(keys, keys + 3);

            // Преобразуем текущий узел в левого потомка
            node->keys[0] = keys[0];
            node->keyCount = 1;

            // Создаем правого потомка
            Tree23Node* rightChild = createLeaf(keys[2]);

            // Средний ключ продвигается вверх
            return InsertResult(node, keys[1], rightChild, true);
        }
    }
    // Внутренний узел
    else {
        // Определяем в какого потомка вставлять
        int childIndex = 0;
        if (node->keyCount == 2) {
            if (key < node->keys[0]) childIndex = 0;
            else if (key < node->keys[1]) childIndex = 1;
            else childIndex = 2;
        } else {
            if (key < node->keys[0]) childIndex = 0;
            else childIndex = 1;
        }

        // Вставляем в выбранного потомка
        InsertResult result = insertIntoNode(node->children[childIndex], key);

        if (!result.split) {
            // Разделения не было
            node->children[childIndex] = result.node;
            return InsertResult(node, 0, nullptr, false);
        }

        // Произошло разделение потомка
        int promotedKey = result.promotedKey;
        Tree23Node* rightChild = result.rightChild;

        // Если в текущем узле есть место
        if (node->keyCount == 1) {
            // Вставляем promotedKey и rightChild
            if (childIndex == 0) {
                node->keys[1] = node->keys[0];
                node->keys[0] = promotedKey;
                node->children[2] = node->children[1];
                node->children[1] = rightChild;
            } else {
                node->keys[1] = promotedKey;
                node->children[2] = rightChild;
            }
            node->keyCount = 2;
            return InsertResult(node, 0, nullptr, false);
        } else {
            // Текущий узел тоже полон - нужно разделить его
            // Собираем все ключи и потомков
            int allKeys[3];
            Tree23Node* allChildren[4];

            // Копируем существующие
            allKeys[0] = node->keys[0];
            allKeys[1] = node->keys[1];
            allChildren[0] = node->children[0];
            allChildren[1] = node->children[1];
            allChildren[2] = node->children[2];

            // Вставляем новый ключ и потомка в правильную позицию
            if (childIndex == 0) {
                allKeys[0] = promotedKey;
                allChildren[1] = rightChild;
            } else if (childIndex == 1) {
                allKeys[1] = promotedKey;
                allChildren[2] = rightChild;
            } else {
                allKeys[2] = promotedKey;
                allChildren[3] = rightChild;
            }

            // Теперь у нас 3 ключа и 4 потомка
            // Средний ключ продвигается вверх
            int middleKey = allKeys[1];
            Tree23Node* newRight = createInternal(allChildren[2], allKeys[2], allChildren[3]);

            return InsertResult(node, middleKey, newRight, true);
        }
    }
}

// Основная функция вставки в 2-3 дерево
Tree23Node* insert23(Tree23Node* root, int key) {
    if (!root) {
        return createLeaf(key);
    }

    InsertResult result = insertIntoNode(root, key);

    if (result.split) {
        // Корень разделился - создаем новый корень
        return createInternal(result.node, result.promotedKey, result.rightChild);
    }

    return result.node;
}

// Найти ключ в дереве
bool search23(Tree23Node* root, int key) {
    if (!root) return false;

    if (root->isLeaf) {
        return (root->keyCount >= 1 && root->keys[0] == key) ||
               (root->keyCount == 2 && root->keys[1] == key);
    }

    // Определяем в какого потомка идти
    if (root->keyCount == 1) {
        if (key < root->keys[0]) return search23(root->children[0], key);
        else return search23(root->children[1], key);
    } else {
        if (key < root->keys[0]) return search23(root->children[0], key);
        else if (key < root->keys[1]) return search23(root->children[1], key);
        else return search23(root->children[2], key);
    }
}

// Вывести дерево (упрощенная версия - только ключи)
void print23(Tree23Node* root) {
    if (!root) return;

    std::cout << "Узел: [";
    for (int i = 0; i < root->keyCount; i++) {
        if (i > 0) std::cout << ",";
        std::cout << root->keys[i];
    }
    std::cout << "] (" << (root->isLeaf ? "лист" : "внутренний") << ")" << std::endl;
}

// Освободить память дерева
void deleteTree23(Tree23Node* root) {
    if (!root) return;

    if (!root->isLeaf) {
        for (int i = 0; i <= root->keyCount; i++) {
            deleteTree23(root->children[i]);
        }
    }
    delete root;
}
