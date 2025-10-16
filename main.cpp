#include <iostream>
#include <iomanip>
#include "results_table.h"

using namespace std;

int main() {
    // Установка локали для корректного вывода чисел
    setlocale(LC_ALL, "Russian");
    
    cout << "==================================================" << endl;
    cout << "Лабораторная работа №4" << endl;
    cout << "Численные методы решения нелинейных уравнений" << endl;
    cout << "Вариант 24: x^2 - e^x + 2 = 0" << endl;
    cout << "==================================================" << endl << endl;
    
    // Запуск анализа уравнения и экспорта в CSV
    analyze_and_export_equation();
    
    cout << "\n==================================================" << endl;
    cout << "Программа завершена успешно!" << endl;
    cout << "Для просмотра результатов откройте файлы:" << endl;
    cout << "  - nonlinear_equation_results.csv (CSV для Excel)" << endl;
    cout << "  - nonlinear_equation_results.tsv (табулированный файл)" << endl;
    cout << "  - nonlinear_equation_report.txt (читабельный отчет)" << endl;
    cout << "==================================================" << endl;
    
    cout << "\nНажмите Enter для выхода...";
    cin.get();
    
    return 0;
}