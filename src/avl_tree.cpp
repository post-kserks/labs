#include "avl_tree.h"
#include <cstdlib>
#include <algorithm>

AVLNode* create_avl_node(int key) {
    AVLNode* node = (AVLNode*)malloc(sizeof(AVLNode));
    node->key = key;
    node->left = nullptr;
    node->right = nullptr;
    node->height = 1;
    return node;
}

int get_height(AVLNode* node) {
    return node ? node->height : 0;
}

void update_height(AVLNode* node) {
    if (node) {
        node->height = std::max(get_height(node->left), get_height(node->right)) + 1;
    }
}

int get_balance(AVLNode* node) {
    return node ? get_height(node->left) - get_height(node->right) : 0;
}

AVLNode* rotate_right(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    update_height(y);
    update_height(x);

    return x;
}

AVLNode* rotate_left(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    update_height(x);
    update_height(y);

    return y;
}

AVLNode* balance_avl(AVLNode* node) {
    if (!node) return node;

    update_height(node);
    int balance = get_balance(node);

    // Left Left Case
    if (balance > 1 && get_balance(node->left) >= 0) {
        return rotate_right(node);
    }

    // Right Right Case
    if (balance < -1 && get_balance(node->right) <= 0) {
        return rotate_left(node);
    }

    // Left Right Case
    if (balance > 1 && get_balance(node->left) < 0) {
        node->left = rotate_left(node->left);
        return rotate_right(node);
    }

    // Right Left Case
    if (balance < -1 && get_balance(node->right) > 0) {
        node->right = rotate_right(node->right);
        return rotate_left(node);
    }

    return node;
}

AVLNode* avl_insert(AVLNode* root, int key) {
    if (!root) {
        return create_avl_node(key);
    }

    if (key < root->key) {
        root->left = avl_insert(root->left, key);
    } else if (key > root->key) {
        root->right = avl_insert(root->right, key);
    } else {
        return root; // Дубликаты не допускаются
    }

    return balance_avl(root);
}

AVLNode* avl_search(AVLNode* root, int key) {
    if (!root || root->key == key) {
        return root;
    }

    if (key < root->key) {
        return avl_search(root->left, key);
    } else {
        return avl_search(root->right, key);
    }
}

void free_avl_tree(AVLNode* root) {
    if (!root) return;
    free_avl_tree(root->left);
    free_avl_tree(root->right);
    free(root);
}
