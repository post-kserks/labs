#ifndef ADABOOST_H
#define ADABOOST_H

#include <vector>

// Структура для хранения одной транзакции
struct Transaction {
    double amount;        // Сумма транзакции
    double frequency;     // Частота транзакций (в день)
    int label;           // Метка: 0 - легальная, 1 - подозрительная
    double weight;       // Вес образца для AdaBoost
};

// Структура для слабого классификатора (Decision Stump)
struct WeakClassifier {
    int feature_index;    // Индекс признака (0 - amount, 1 - frequency)
    double threshold;     // Порог для разделения
    int polarity;        // Направление (1 или -1)
    double alpha;        // Вес классификатора в итоговой модели
};

// Создание синтетического dataset финансовых транзакций
std::vector<Transaction> generate_dataset(int num_samples);

// Разделение dataset на обучающую и тестовую выборки
void split_dataset(const std::vector<Transaction>& data, 
                   std::vector<Transaction>& train, 
                   std::vector<Transaction>& test,
                   double train_ratio);

// Обучение одного слабого классификатора
WeakClassifier train_weak_classifier(std::vector<Transaction>& data);

// Предсказание одним слабым классификатором
int predict_weak(const WeakClassifier& clf, const Transaction& t);

// Обучение AdaBoost
std::vector<WeakClassifier> train_adaboost(std::vector<Transaction>& train_data, 
                                            int num_classifiers);

// Предсказание с использованием ансамбля классификаторов
double predict_adaboost(const std::vector<WeakClassifier>& classifiers, 
                        const Transaction& t);

// Вычисление AUC (Area Under Curve) метрики
double calculate_auc(const std::vector<WeakClassifier>& classifiers,
                     const std::vector<Transaction>& test_data);

// Тестирование производительности
void test_adaboost_performance(int num_samples, int num_classifiers);

#endif
