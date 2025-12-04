#ifndef ID3_H
#define ID3_H

#include <iostream>
#include <vector>
#include <string>
#include <set>
#include "data.h"
#include "entropy.h"

// Структура узла дерева решений
struct TreeNode {
    bool is_leaf;                           // Является ли узел листом
    std::string class_label;                // Метка класса (для листа)
    int split_attribute;                    // Индекс атрибута для разбиения
    std::string attribute_name;             // Название атрибута для разбиения
    std::map<std::string, TreeNode*> children;  // Дочерние узлы по значениям атрибута
    
    TreeNode() : is_leaf(false), split_attribute(-1) {}
    
    ~TreeNode() {
        for (auto& pair : children) {
            delete pair.second;
        }
    }
};

// Рекурсивная функция построения дерева по алгоритму ID3
TreeNode* build_id3_tree(
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
    
    // Выбираем атрибут с максимальным приростом информации
    int best_attr = -1;
    double max_gain = -1.0;
    
    for (int attr : available_attributes) {
        double gain = calculate_information_gain(data, attr);
        if (gain > max_gain) {
            max_gain = gain;
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
                build_id3_tree(subset_pair.second, remaining_attrs, attr_names, depth + 1);
        }
    }
    
    return node;
}

// Вывод дерева в текстовом виде
void print_tree(TreeNode* node, std::string prefix = "", bool is_last = true) {
    if (node == nullptr) return;
    
    std::cout << prefix;
    std::cout << (is_last ? "└── " : "├── ");
    
    if (node->is_leaf) {
        std::cout << "КЛАСС: " << node->class_label << std::endl;
    } else {
        std::cout << node->attribute_name << std::endl;
        
        int child_count = node->children.size();
        int i = 0;
        for (const auto& child_pair : node->children) {
            bool last = (i == child_count - 1);
            std::string child_prefix = prefix + (is_last ? "    " : "│   ");
            
            std::cout << child_prefix << (last ? "└── " : "├── ");
            std::cout << "[" << child_pair.first << "]" << std::endl;
            
            print_tree(child_pair.second, child_prefix + (last ? "    " : "│   "), true);
            i++;
        }
    }
}

// Подсчет глубины дерева
int get_tree_depth(TreeNode* node) {
    if (node == nullptr || node->is_leaf) return 0;
    
    int max_depth = 0;
    for (const auto& child_pair : node->children) {
        int child_depth = get_tree_depth(child_pair.second);
        if (child_depth > max_depth) {
            max_depth = child_depth;
        }
    }
    return max_depth + 1;
}

// Подсчет количества узлов в дереве
int count_nodes(TreeNode* node) {
    if (node == nullptr) return 0;
    
    int count = 1;
    for (const auto& child_pair : node->children) {
        count += count_nodes(child_pair.second);
    }
    return count;
}

#endif
