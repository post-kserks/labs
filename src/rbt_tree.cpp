#include "rbt_tree.h"
#include <cstdlib>
#include <algorithm>

RBTNode* create_rbt_node(int key) {
    RBTNode* node = (RBTNode*)malloc(sizeof(RBTNode));
    node->key = key;
    node->left = nullptr;
    node->right = nullptr;
    node->parent = nullptr;
    node->is_red = true; // Новый узел всегда красный
    return node;
}

RBTNode* rbt_rotate_left(RBTNode* root, RBTNode* x) {
    RBTNode* y = x->right;
    x->right = y->left;

    if (y->left != nullptr) {
        y->left->parent = x;
    }

    y->parent = x->parent;

    if (x->parent == nullptr) {
        root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }

    y->left = x;
    x->parent = y;

    return root;
}

RBTNode* rbt_rotate_right(RBTNode* root, RBTNode* y) {
    RBTNode* x = y->left;
    y->left = x->right;

    if (x->right != nullptr) {
        x->right->parent = y;
    }

    x->parent = y->parent;

    if (y->parent == nullptr) {
        root = x;
    } else if (y == y->parent->left) {
        y->parent->left = x;
    } else {
        y->parent->right = x;
    }

    x->right = y;
    y->parent = x;

    return root;
}

RBTNode* rbt_insert_fixup(RBTNode* root, RBTNode* z) {
    while (z->parent != nullptr && z->parent->is_red) {
        if (z->parent == z->parent->parent->left) {
            RBTNode* y = z->parent->parent->right;

            if (y != nullptr && y->is_red) {
                // Case 1: дядя красный
                z->parent->is_red = false;
                y->is_red = false;
                z->parent->parent->is_red = true;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    // Case 2: дядя черный, z - правый потомок
                    z = z->parent;
                    root = rbt_rotate_left(root, z);
                }
                // Case 3: дядя черный, z - левый потомок
                z->parent->is_red = false;
                z->parent->parent->is_red = true;
                root = rbt_rotate_right(root, z->parent->parent);
            }
        } else {
            // Симметричный случай
            RBTNode* y = z->parent->parent->left;

            if (y != nullptr && y->is_red) {
                z->parent->is_red = false;
                y->is_red = false;
                z->parent->parent->is_red = true;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    root = rbt_rotate_right(root, z);
                }
                z->parent->is_red = false;
                z->parent->parent->is_red = true;
                root = rbt_rotate_left(root, z->parent->parent);
            }
        }
    }

    root->is_red = false;
    return root;
}

RBTNode* rbt_insert(RBTNode* root, int key) {
    RBTNode* z = create_rbt_node(key);
    RBTNode* y = nullptr;
    RBTNode* x = root;

    // Обычная вставка в бинарное дерево поиска
    while (x != nullptr) {
        y = x;
        if (z->key < x->key) {
            x = x->left;
        } else {
            x = x->right;
        }
    }

    z->parent = y;

    if (y == nullptr) {
        root = z;
    } else if (z->key < y->key) {
        y->left = z;
    } else {
        y->right = z;
    }

    // Балансировка
    return rbt_insert_fixup(root, z);
}

RBTNode* rbt_search(RBTNode* root, int key) {
    if (root == nullptr || root->key == key) {
        return root;
    }

    if (key < root->key) {
        return rbt_search(root->left, key);
    } else {
        return rbt_search(root->right, key);
    }
}

void free_rbt_tree(RBTNode* root) {
    if (root == nullptr) return;
    free_rbt_tree(root->left);
    free_rbt_tree(root->right);
    free(root);
}

int get_rbt_height(RBTNode* root) {
    if (root == nullptr) return 0;
    return std::max(get_rbt_height(root->left), get_rbt_height(root->right)) + 1;
}
