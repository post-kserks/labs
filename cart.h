#ifndef CART_H
#define CART_H

#include <iostream>
#include <vector>
#include <string>
#include "data.h"
#include "entropy.h"
#include "id3.h"

// Рекурсивная функция построения дерева по алгоритму CART
// Отличие: использует индекс Джини вместо энтропии
TreeNode* build_cart_tree(
    const std::vector<Example>& data,
    std::vector<int> available_attributes,
    const std::vector<std::string>& attr_names,
    int depth = 0) {
    
    TreeNode* node = new TreeNode();
    
    // Базовый случай 1: все примеры одного класса
    if (is_homogeneous(data)) {
        node->is_leaf = true;
        node->class_label = data[0].decision;
        return node;
    }
    
    // Базовый случай 2: нет доступных атрибутов
    if (available_attributes.empty()) {
        node->is_leaf = true;
        node->class_label = get_most_common_class(data);
        return node;
    }
    
    // Выбираем атрибут с максимальным снижением Gini
    int best_attr = -1;
    double max_gini_gain = -1.0;
    
    for (int attr : available_attributes) {
        double gini_gain = calculate_gini_gain(data, attr);
        if (gini_gain > max_gini_gain) {
            max_gini_gain = gini_gain;
            best_attr = attr;
        }
    }
    
    // Создаем внутренний узел с выбранным атрибутом
    node->split_attribute = best_attr;
    node->attribute_name = attr_names[best_attr];
    
    // Удаляем выбранный атрибут из списка доступных
    std::vector<int> remaining_attrs;
    for (int attr : available_attributes) {
        if (attr != best_attr) {
            remaining_attrs.push_back(attr);
        }
    }
    
    // Разбиваем данные по значениям выбранного атрибута
    auto subsets = split_by_attribute(data, best_attr);
    
    // Рекурсивно строим поддеревья для каждого значения
    for (const auto& subset_pair : subsets) {
        if (!subset_pair.second.empty()) {
            node->children[subset_pair.first] = 
                build_cart_tree(subset_pair.second, remaining_attrs, attr_names, depth + 1);
        }
    }
    
    return node;
}

#endif
