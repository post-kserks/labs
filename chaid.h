#ifndef CHAID_H
#define CHAID_H

#include <iostream>
#include <vector>
#include <string>
#include "data.h"
#include "entropy.h"
#include "id3.h"

// Рекурсивная функция построения дерева по алгоритму CHAID
// Отличие: использует критерий хи-квадрат для выбора атрибута
TreeNode* build_chaid_tree(
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
    
    // Выбираем атрибут с максимальным значением хи-квадрат
    int best_attr = -1;
    double max_chi_square = -1.0;
    
    for (int attr : available_attributes) {
        double chi_square = calculate_chi_square(data, attr);
        if (chi_square > max_chi_square) {
            max_chi_square = chi_square;
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
                build_chaid_tree(subset_pair.second, remaining_attrs, attr_names, depth + 1);
        }
    }
    
    return node;
}

#endif
