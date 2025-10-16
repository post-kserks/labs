#ifndef RESULTS_TABLE_H
#define RESULTS_TABLE_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include "math_utils.h"
#include "bisection_method.h"
#include "iteration_method.h"
#include "newton_method.h"

using namespace std;

// Форматирование числа для CSV (с высокой точностью)
string format_number_csv(double value) {
    if (!is_valid_number(value)) {
        return "NaN";
    }
    
    if (fabs(value) < 1e-20) {
        return "0.0";
    }
    
    ostringstream oss;
    oss << scientific << setprecision(16) << value;
    return oss.str();
}

// Функция для экранирования CSV полей
string escape_csv_field(const string& field) {
    if (field.find(';') != string::npos || field.find('"') != string::npos || field.find('\n') != string::npos) {
        ostringstream oss;
        oss << '"';
        for (char c : field) {
            if (c == '"') oss << '"' << '"'; // Экранирование кавычек
            else oss << c;
        }
        oss << '"';
        return oss.str();
    }
    return field;
}

// Структура для хранения результатов одного эксперимента
struct ExperimentResult {
    string method_name;
    double epsilon;
    double root;
    double function_value;
    double error_estimate;
    int iterations;
    bool converged;
    string status;
};

// Запись результатов в CSV файл с правильным форматированием для Excel
void export_results_to_csv(const vector<ExperimentResult>& results, const string& filename) {
    ofstream file(filename);
    
    if (!file.is_open()) {
        cerr << "Ошибка: не удалось создать файл " << filename << endl;
        return;
    }
    
    // Добавляем BOM для корректного отображения в Excel
    file << "\xEF\xBB\xBF";
    
    // Заголовок CSV с разделителем ";" (точка с запятой)
    file << "Метод" << ";"
         << "Значение Epsilon" << ";"
         << "Корень" << ";"
         << "Значение функции" << ";"
         << "Погрешность" << ";"
         << "Кол-во итераций" << ";"
         << "Сошёлся" << ";"
         << "Статус" << endl;
    
    // Данные
    for (const auto& result : results) {
        file << escape_csv_field(result.method_name) << ";"
             << result.epsilon << ";"
             << format_number_csv(result.root) << ";"
             << format_number_csv(result.function_value) << ";"
             << format_number_csv(result.error_estimate) << ";"
             << result.iterations << ";"
             << (result.converged ? "Да" : "Нет") << ";"
             << escape_csv_field(result.status) << endl;
    }
    
    file.close();
}

// Альтернативный метод: создание TSV (табулированного файла)
void export_results_to_tsv(const vector<ExperimentResult>& results, const string& filename) {
    ofstream file(filename);
    
    if (!file.is_open()) {
        cerr << "Ошибка: не удалось создать файл " << filename << endl;
        return;
    }
    
    // Заголовок TSV
    file << "Метод" << "\t"
         << "Значение Epsilon" << "\t"
         << "Корень" << "\t"
         << "Значение функции" << "\t"
         << "Погрешность" << "\t"
         << "Кол-во итераций" << "\t"
         << "Сошёлся" << "\t"
         << "Статус" << endl;
    
    // Данные
    for (const auto& result : results) {
        file << result.method_name << "\t"
             << result.epsilon << "\t"
             << format_number_csv(result.root) << "\t"
             << format_number_csv(result.function_value) << "\t"
             << format_number_csv(result.error_estimate) << "\t"
             << result.iterations << "\t"
             << (result.converged ? "Да" : "Нет") << "\t"
             << result.status << endl;
    }
    
    file.close();
}

// Создание отчета в виде читабельной таблицы
void create_readable_report(const vector<ExperimentResult>& results, const string& filename) {
    ofstream file(filename);
    
    if (!file.is_open()) {
        cerr << "Ошибка: не удалось создать файл " << filename << endl;
        return;
    }
    
    file << "ОТЧЕТ ПО ЛАБОРАТОРНОЙ РАБОТЕ №4" << endl;
    file << "Численные методы решения нелинейных уравнений" << endl;
    file << "Уравнение: x^2 - e^x + 2 = 0" << endl;
    file << "==============================================" << endl << endl;
    
    // Группировка по точности
    file << "РЕЗУЛЬТАТЫ ДЛЯ ТОЧНОСТИ ε = 1e-06:" << endl;
    file << "-----------------------------------" << endl;
    
    for (const auto& result : results) {
        if (result.epsilon == EPSILON_1) {
            file << "Метод: " << result.method_name << endl;
            file << "  Корень: " << format_number_csv(result.root) << endl;
            file << "  Значение функции: " << format_number_csv(result.function_value) << endl;
            file << "  Погрешность: " << format_number_csv(result.error_estimate) << endl;
            file << "  Итерации: " << result.iterations << endl;
            file << "  Сошелся: " << (result.converged ? "Да" : "Нет") << endl;
            file << "  Статус: " << result.status << endl << endl;
        }
    }
    
    file << "РЕЗУЛЬТАТЫ ДЛЯ ТОЧНОСТИ ε = 1e-11:" << endl;
    file << "-----------------------------------" << endl;
    
    for (const auto& result : results) {
        if (result.epsilon == EPSILON_2) {
            file << "Метод: " << result.method_name << endl;
            file << "  Корень: " << format_number_csv(result.root) << endl;
            file << "  Значение функции: " << format_number_csv(result.function_value) << endl;
            file << "  Погрешность: " << format_number_csv(result.error_estimate) << endl;
            file << "  Итерации: " << result.iterations << endl;
            file << "  Сошелся: " << (result.converged ? "Да" : "Нет") << endl;
            file << "  Статус: " << result.status << endl << endl;
        }
    }
    
    // Сравнение методов
    file << "СРАВНЕНИЕ МЕТОДОВ:" << endl;
    file << "------------------" << endl;
    
    int bisection_iter = 0, iteration_iter = 0, newton_iter = 0;
    for (const auto& result : results) {
        if (result.epsilon == EPSILON_2) {
            if (result.method_name == "Половинное деление") bisection_iter = result.iterations;
            else if (result.method_name == "Простые итерации") iteration_iter = result.iterations;
            else if (result.method_name == "Ньютон") newton_iter = result.iterations;
        }
    }
    
    file << "Метод половинного деления: " << bisection_iter << " итераций" << endl;
    file << "Метод простых итераций: " << iteration_iter << " итераций" << endl;
    file << "Метод Ньютона: " << newton_iter << " итераций" << endl;
    
    file.close();
}

// Полный анализ уравнения и экспорт в CSV
void analyze_and_export_equation() {
    EquationSystem system = get_equation_system();
    Interval interval = get_recommended_interval();
    
    vector<ExperimentResult> results;
    
    // Решение с первой точностью
    SolutionResult bisection_eps1 = bisection_method(system.equation, interval.a, interval.b, EPSILON_1);
    SolutionResult iteration_eps1 = iteration_analysis(EPSILON_1);
    SolutionResult newton_eps1 = newton_analysis(EPSILON_1);
    results.push_back({"Решение с первой точностью"});
    
    results.push_back({"Половинное деление", EPSILON_1, bisection_eps1.root, bisection_eps1.function_value, 
                      bisection_eps1.error_estimate, bisection_eps1.iterations, 
                      bisection_eps1.converged, bisection_eps1.error_msg ? bisection_eps1.error_msg : "Success"});
    
    results.push_back({"Простые итерации", EPSILON_1, iteration_eps1.root, iteration_eps1.function_value, 
                      iteration_eps1.error_estimate, iteration_eps1.iterations, 
                      iteration_eps1.converged, iteration_eps1.error_msg ? iteration_eps1.error_msg : "Success"});
    
    results.push_back({"Ньютон", EPSILON_1, newton_eps1.root, newton_eps1.function_value, 
                      newton_eps1.error_estimate, newton_eps1.iterations, 
                      newton_eps1.converged, newton_eps1.error_msg ? newton_eps1.error_msg : "Success"});
    
    // Решение со второй точностью
    SolutionResult bisection_eps2 = bisection_method(system.equation, interval.a, interval.b, EPSILON_2);
    SolutionResult iteration_eps2 = iteration_analysis(EPSILON_2);
    SolutionResult newton_eps2 = newton_analysis(EPSILON_2);
    results.push_back({"Решение со второй точностью"});
    
    results.push_back({"Половинное деление", EPSILON_2, bisection_eps2.root, bisection_eps2.function_value, 
                      bisection_eps2.error_estimate, bisection_eps2.iterations, 
                      bisection_eps2.converged, bisection_eps2.error_msg ? bisection_eps2.error_msg : "Success"});
    
    results.push_back({"Простые итерации", EPSILON_2, iteration_eps2.root, iteration_eps2.function_value, 
                      iteration_eps2.error_estimate, iteration_eps2.iterations, 
                      iteration_eps2.converged, iteration_eps2.error_msg ? iteration_eps2.error_msg : "Success"});
    
    results.push_back({"Ньютон", EPSILON_2, newton_eps2.root, newton_eps2.function_value, 
                      newton_eps2.error_estimate, newton_eps2.iterations, 
                      newton_eps2.converged, newton_eps2.error_msg ? newton_eps2.error_msg : "Success"});
    
    // Экспорт в CSV с разделителем ";" (для Excel)
    string csv_filename = "nonlinear_equation_results.csv";
    export_results_to_csv(results, csv_filename);
    
    // Альтернативный экспорт в TSV
    string tsv_filename = "nonlinear_equation_results.tsv";
    export_results_to_tsv(results, tsv_filename);
    
    // Создание читабельного отчета
    string report_filename = "nonlinear_equation_report.txt";
    create_readable_report(results, report_filename);
    
    // Вывод краткой информации в консоль
    cout << "✓ Анализ уравнения завершен успешно!" << endl;
    cout << "✓ Уравнение: " << system.description << endl;
    cout << "✓ Использованный интервал: [" << interval.a << ", " << interval.b << "]" << endl;
    cout << "✓ Точности: ε₁ = " << scientific << EPSILON_1 << ", ε₂ = " << EPSILON_2 << fixed << endl;
    cout << "✓ Результаты сохранены в файлы:" << endl;
    cout << "  - " << csv_filename << " (CSV с разделителем ';' для Excel)" << endl;
    cout << "  - " << tsv_filename << " (TSV - табулированный файл)" << endl;
    cout << "  - " << report_filename << " (читабельный отчет)" << endl;
    
    // Инструкция по открытию в Excel
    cout << "\nИнструкция по открытию CSV в Excel:" << endl;
    cout << "1. Откройте Excel" << endl;
    cout << "2. Перейдите в меню 'Данные' -> 'Получить данные' -> 'Из файла' -> 'Из текста/CSV'" << endl;
    cout << "3. Выберите файл " << csv_filename << endl;
    cout << "4. Укажите разделитель ';' (точка с запятой)" << endl;
    cout << "5. Нажмите 'Загрузить'" << endl;
    
    // Краткое сравнение методов
    cout << "\nКраткое сравнение методов (для ε₂):" << endl;
    cout << "• Метод половинного деления: " << bisection_eps2.iterations << " итераций" << endl;
    cout << "• Метод простых итераций: " << iteration_eps2.iterations << " итераций" << endl;
    cout << "• Метод Ньютона: " << newton_eps2.iterations << " итераций" << endl;
    
    cout << "\nНайденный корень: " << scientific << setprecision(16) << newton_eps2.root << fixed << endl;
}

#endif // RESULTS_TABLE_H