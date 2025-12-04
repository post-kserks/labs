#ifndef ENTROPY_H
#define ENTROPY_H

#include <vector>
#include <map>
#include <cmath>
#include <string>
#include "data.h"

// Вычисление энтропии для набора данных
// E(S) = -p+ * log2(p+) - p- * log2(p-)
double calculate_entropy(const std::vector<Example>& data) {
    if (data.empty()) return 0.0;
    
    // Подсчитываем количество примеров каждого класса
    std::map<std::string, int> class_count;
    for (const auto& ex : data) {
        class_count[ex.decision]++;
    }
    
    double entropy = 0.0;
    int total = data.size();
    
    // Вычисляем энтропию
    for (const auto& pair : class_count) {
        double probability = (double)pair.second / total;
        if (probability > 0) {
            entropy -= probability * log2(probability);
        }
    }
    
    return entropy;
}

// Разбиение данных по значению атрибута
std::map<std::string, std::vector<Example>> split_by_attribute(
    const std::vector<Example>& data, 
    int attr_index) {
    
    std::map<std::string, std::vector<Example>> subsets;
    
    for (const auto& ex : data) {
        std::string value = get_attribute_value(ex, attr_index);
        subsets[value].push_back(ex);
    }
    
    return subsets;
}

// Вычисление прироста информации для атрибута (для ID3)
// IG(S, A) = E(S) - sum(|Sv|/|S| * E(Sv))
double calculate_information_gain(
    const std::vector<Example>& data,
    int attr_index) {
    
    double base_entropy = calculate_entropy(data);
    auto subsets = split_by_attribute(data, attr_index);
    
    double weighted_entropy = 0.0;
    int total = data.size();
    
    for (const auto& pair : subsets) {
        double weight = (double)pair.second.size() / total;
        weighted_entropy += weight * calculate_entropy(pair.second);
    }
    
    return base_entropy - weighted_entropy;
}

// Вычисление Split Info для C4.5
double calculate_split_info(
    const std::vector<Example>& data,
    int attr_index) {
    
    auto subsets = split_by_attribute(data, attr_index);
    double split_info = 0.0;
    int total = data.size();
    
    for (const auto& pair : subsets) {
        double proportion = (double)pair.second.size() / total;
        if (proportion > 0) {
            split_info -= proportion * log2(proportion);
        }
    }
    
    return split_info;
}

// Вычисление Gain Ratio для C4.5
// GainRatio(S, A) = IG(S, A) / SplitInfo(S, A)
double calculate_gain_ratio(
    const std::vector<Example>& data,
    int attr_index) {
    
    double ig = calculate_information_gain(data, attr_index);
    double split_info = calculate_split_info(data, attr_index);
    
    if (split_info == 0.0) return 0.0;
    return ig / split_info;
}

// Вычисление индекса Джини для CART
// Gini(S) = 1 - sum(p_i^2)
double calculate_gini_index(const std::vector<Example>& data) {
    if (data.empty()) return 0.0;
    
    std::map<std::string, int> class_count;
    for (const auto& ex : data) {
        class_count[ex.decision]++;
    }
    
    double gini = 1.0;
    int total = data.size();
    
    for (const auto& pair : class_count) {
        double probability = (double)pair.second / total;
        gini -= probability * probability;
    }
    
    return gini;
}

// Вычисление снижения Gini для атрибута (для CART)
double calculate_gini_gain(
    const std::vector<Example>& data,
    int attr_index) {
    
    double base_gini = calculate_gini_index(data);
    auto subsets = split_by_attribute(data, attr_index);
    
    double weighted_gini = 0.0;
    int total = data.size();
    
    for (const auto& pair : subsets) {
        double weight = (double)pair.second.size() / total;
        weighted_gini += weight * calculate_gini_index(pair.second);
    }
    
    return base_gini - weighted_gini;
}

// Вычисление хи-квадрат статистики для CHAID
double calculate_chi_square(
    const std::vector<Example>& data,
    int attr_index) {
    
    auto subsets = split_by_attribute(data, attr_index);
    
    // Подсчет общего количества по классам
    std::map<std::string, int> total_class_count;
    for (const auto& ex : data) {
        total_class_count[ex.decision]++;
    }
    
    double chi_square = 0.0;
    int total = data.size();
    
    for (const auto& subset_pair : subsets) {
        int subset_size = subset_pair.second.size();
        
        // Подсчет по классам в подмножестве
        std::map<std::string, int> subset_class_count;
        for (const auto& ex : subset_pair.second) {
            subset_class_count[ex.decision]++;
        }
        
        // Вычисление хи-квадрат
        for (const auto& class_pair : total_class_count) {
            double expected = (double)subset_size * class_pair.second / total;
            int observed = subset_class_count[class_pair.first];
            
            if (expected > 0) {
                double diff = observed - expected;
                chi_square += (diff * diff) / expected;
            }
        }
    }
    
    return chi_square;
}

// Определение наиболее частого класса (для листовых узлов)
std::string get_most_common_class(const std::vector<Example>& data) {
    std::map<std::string, int> class_count;
    for (const auto& ex : data) {
        class_count[ex.decision]++;
    }
    
    std::string most_common;
    int max_count = 0;
    for (const auto& pair : class_count) {
        if (pair.second > max_count) {
            max_count = pair.second;
            most_common = pair.first;
        }
    }
    
    return most_common;
}

// Проверка однородности данных (все примеры одного класса)
bool is_homogeneous(const std::vector<Example>& data) {
    if (data.empty()) return true;
    
    std::string first_class = data[0].decision;
    for (const auto& ex : data) {
        if (ex.decision != first_class) return false;
    }
    return true;
}

#endif
