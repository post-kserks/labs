#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include "data.h"
#include "entropy.h"
#include "id3.h"
#include "c45.h"
#include "cart.h"
#include "chaid.h"

using namespace std;

// Функция для вывода обучающей выборки в виде таблицы
void print_training_data(const vector<Example>& data, const vector<string>& attr_names) {
    cout << "\n╔════════════════════════════════════════════════════════════════════════╗" << endl;
    cout << "║          ОБУЧАЮЩАЯ ВЫБОРКА: Выбор заказчика (14 примеров)            ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════════════════╝\n" << endl;
    
    cout << "┌──────┬────────────┬──────────────┬────────┬──────────────┬──────────┐" << endl;
    cout << "│  №   │   Бюджет   │ Надежность   │  Опыт  │ Срок_оплаты  │ Решение  │" << endl;
    cout << "├──────┼────────────┼──────────────┼────────┼──────────────┼──────────┤" << endl;
    
    for (size_t i = 0; i < data.size(); i++) {
        cout << "│ " << setw(4) << (i+1) << " │ "
             << setw(10) << data[i].budget << " │ "
             << setw(12) << data[i].reliability << " │ "
             << setw(6) << data[i].experience << " │ "
             << setw(12) << data[i].payment_term << " │ "
             << setw(8) << data[i].decision << " │" << endl;
    }
    
    cout << "└──────┴────────────┴──────────────┴────────┴──────────────┴──────────┘" << endl;
}

// Функция для вывода разделителя
void print_separator(const string& title) {
    cout << "\n\n";
    cout << "╔════════════════════════════════════════════════════════════════════════╗" << endl;
    cout << "║  " << setw(70) << left << title << "║" << endl;
    cout << "╚════════════════════════════════════════════════════════════════════════╝\n" << endl;
}

int main() {
    // Устанавливаем кодировку для корректного отображения русских символов
    setlocale(LC_ALL, "ru_RU.UTF-8");
    
    // Загружаем обучающую выборку
    vector<Example> training_data = get_training_data();
    vector<string> attr_names = get_attribute_names();
    
    // Выводим обучающую выборку
    print_training_data(training_data, attr_names);
    
    // Создаем список доступных атрибутов (индексы 0, 1, 2, 3)
    vector<int> available_attributes = {0, 1, 2, 3};
    
    // ========================================================================
    // Алгоритм ID3 (Information Gain)
    // ========================================================================
    print_separator("АЛГОРИТМ ID3 (Information Gain)");
    
    cout << "Описание: ID3 выбирает атрибут с максимальным приростом информации (IG)." << endl;
    cout << "Формула: IG(S, A) = E(S) - Σ(|Sv|/|S| * E(Sv))\n" << endl;
    
    TreeNode* id3_tree = build_id3_tree(training_data, available_attributes, attr_names);
    
    cout << "Построенное дерево решений:\n" << endl;
    print_tree(id3_tree);
    
    cout << "\nХарактеристики дерева ID3:" << endl;
    cout << "  • Глубина дерева: " << get_tree_depth(id3_tree) << endl;
    cout << "  • Количество узлов: " << count_nodes(id3_tree) << endl;
    
    // ========================================================================
    // Алгоритм C4.5 (Gain Ratio)
    // ========================================================================
    print_separator("АЛГОРИТМ C4.5 (Gain Ratio)");
    
    cout << "Описание: C4.5 использует Gain Ratio для устранения смещения ID3." << endl;
    cout << "Формула: GainRatio(S, A) = IG(S, A) / SplitInfo(S, A)\n" << endl;
    
    TreeNode* c45_tree = build_c45_tree(training_data, available_attributes, attr_names);
    
    cout << "Построенное дерево решений:\n" << endl;
    print_tree(c45_tree);
    
    cout << "\nХарактеристики дерева C4.5:" << endl;
    cout << "  • Глубина дерева: " << get_tree_depth(c45_tree) << endl;
    cout << "  • Количество узлов: " << count_nodes(c45_tree) << endl;
    
    // ========================================================================
    // Алгоритм CART (Gini Index)
    // ========================================================================
    print_separator("АЛГОРИТМ CART (Gini Index)");
    
    cout << "Описание: CART использует индекс Джини для оценки чистоты разбиения." << endl;
    cout << "Формула: Gini(S) = 1 - Σ(pi²)\n" << endl;
    
    TreeNode* cart_tree = build_cart_tree(training_data, available_attributes, attr_names);
    
    cout << "Построенное дерево решений:\n" << endl;
    print_tree(cart_tree);
    
    cout << "\nХарактеристики дерева CART:" << endl;
    cout << "  • Глубина дерева: " << get_tree_depth(cart_tree) << endl;
    cout << "  • Количество узлов: " << count_nodes(cart_tree) << endl;
    
    // ========================================================================
    // Алгоритм CHAID (Chi-Square)
    // ========================================================================
    print_separator("АЛГОРИТМ CHAID (Chi-Square)");
    
    cout << "Описание: CHAID использует критерий хи-квадрат для выбора атрибута." << endl;
    cout << "Формула: χ² = Σ((O - E)² / E)\n" << endl;
    
    TreeNode* chaid_tree = build_chaid_tree(training_data, available_attributes, attr_names);
    
    cout << "Построенное дерево решений:\n" << endl;
    print_tree(chaid_tree);
    
    cout << "\nХарактеристики дерева CHAID:" << endl;
    cout << "  • Глубина дерева: " << get_tree_depth(chaid_tree) << endl;
    cout << "  • Количество узлов: " << count_nodes(chaid_tree) << endl;
    
    // ========================================================================
    // Сравнение алгоритмов
    // ========================================================================
    print_separator("СРАВНЕНИЕ АЛГОРИТМОВ");
    
    cout << "┌──────────────┬──────────┬────────────────┬─────────────────────────┐" << endl;
    cout << "│  Алгоритм    │ Глубина  │ Кол-во узлов   │      Критерий           │" << endl;
    cout << "├──────────────┼──────────┼────────────────┼─────────────────────────┤" << endl;
    
    cout << "│ ID3          │    " << get_tree_depth(id3_tree) 
         << "     │       " << count_nodes(id3_tree) 
         << "        │ Information Gain        │" << endl;
    
    cout << "│ C4.5         │    " << get_tree_depth(c45_tree) 
         << "     │       " << count_nodes(c45_tree) 
         << "        │ Gain Ratio              │" << endl;
    
    cout << "│ CART         │    " << get_tree_depth(cart_tree) 
         << "     │       " << count_nodes(cart_tree) 
         << "        │ Gini Index              │" << endl;
    
    cout << "│ CHAID        │    " << get_tree_depth(chaid_tree) 
         << "     │       " << count_nodes(chaid_tree) 
         << "        │ Chi-Square              │" << endl;
    
    cout << "└──────────────┴──────────┴────────────────┴─────────────────────────┘" << endl;
    
    cout << "\nВыводы:" << endl;
    cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
    cout << "• ID3 - классический алгоритм, использующий энтропию" << endl;
    cout << "• C4.5 - улучшенная версия ID3 с нормализацией через SplitInfo" << endl;
    cout << "• CART - использует индекс Джини, часто дает бинарные деревья" << endl;
    cout << "• CHAID - использует статистический критерий хи-квадрат" << endl;
    cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n" << endl;
    
    // Освобождаем память
    delete id3_tree;
    delete c45_tree;
    delete cart_tree;
    delete chaid_tree;
    
    return 0;
}
