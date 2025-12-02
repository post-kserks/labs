#include "csv_loader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>

std::vector<Transaction> load_creditcard_csv(const std::string& filename, int max_samples) {
    std::vector<Transaction> data;
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл " << filename << std::endl;
        return data;
    }
    
    std::string line;
    // Пропускаем заголовок
    std::getline(file, line);
    
    int count = 0;
    while (std::getline(file, line) && (max_samples < 0 || count < max_samples)) {
        std::stringstream ss(line);
        std::string value;
        
        Transaction t;
        t.weight = 1.0; // Будет нормализовано позже
        
        // CSV формат: Time,V1,V2,...,V28,Amount,Class
        
        // Пропускаем первую колонку (Time)
        std::getline(ss, value, ',');
        
        // Читаем V1 (используем как frequency для примера)
        std::getline(ss, value, ',');
        double v1 = 0.0;
        try {
            v1 = std::stod(value);
        } catch (...) { v1 = 0.0; }
        
        // Пропускаем V2-V28 (27 колонок)
        for (int i = 0; i < 27; i++) {
            std::getline(ss, value, ',');
        }
        
        // Читаем Amount (предпоследняя колонка)
        std::getline(ss, value, ',');
        try {
            t.amount = std::stod(value);
        } catch (...) { t.amount = 0.0; }
        
        // Читаем Class (последняя колонка)
        std::getline(ss, value, ',');
        try {
            // Удаляем возможные кавычки
            if (value.size() >= 2 && value.front() == '"' && value.back() == '"') {
                value = value.substr(1, value.size() - 2);
            }
            t.label = std::stoi(value);
        } catch (...) { t.label = 0; }
        
        // Используем V1 как frequency (нормализуем для удобства)
        // В реальной задаче нужно выбирать наиболее значимые признаки
        t.frequency = std::abs(v1) + 1.0;
        
        data.push_back(t);
        count++;
    }
    
    file.close();
    
    // Нормализуем веса
    if (!data.empty()) {
        for (auto& t : data) {
            t.weight = 1.0 / data.size();
        }
    }
    
    std::cout << "Загружено " << data.size() << " транзакций из " << filename << std::endl;
    
    // Выводим статистику по классам
    int fraud_count = 0;
    for (const auto& t : data) {
        if (t.label == 1) fraud_count++;
    }
    std::cout << "Легальных: " << (data.size() - fraud_count) 
              << ", Мошеннических: " << fraud_count << std::endl;
              
    return data;
}
