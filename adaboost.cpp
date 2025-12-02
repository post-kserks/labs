#include "adaboost.h"
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>

// Генерация синтетического dataset
// Легальные транзакции: малые суммы, средняя частота
// Подозрительные: большие суммы и/или высокая частота
std::vector<Transaction> generate_dataset(int num_samples) {
    std::vector<Transaction> data;
    data.reserve(num_samples);
    
    for (int i = 0; i < num_samples; i++) {
        Transaction t;
        t.weight = 1.0 / num_samples; // Изначально все веса равны
        
        // Генерируем примерно 70% легальных и 30% подозрительных
        if ((rand() % 100) < 70) {
            // Легальная транзакция
            t.amount = 100.0 + (rand() % 5000); // 100-5100 рублей
            t.frequency = 1.0 + (rand() % 10) / 10.0; // 1-2 транзакции в день
            t.label = 0;
        } else {
            // Подозрительная транзакция
            t.amount = 10000.0 + (rand() % 90000); // 10000-100000 рублей
            t.frequency = 5.0 + (rand() % 50) / 10.0; // 5-10 транзакций в день
            t.label = 1;
        }
        
        data.push_back(t);
    }
    
    return data;
}

// Разделение на train/test
void split_dataset(const std::vector<Transaction>& data, 
                   std::vector<Transaction>& train, 
                   std::vector<Transaction>& test,
                   double train_ratio) {
    int train_size = data.size() * train_ratio;
    
    for (int i = 0; i < data.size(); i++) {
        if (i < train_size) {
            train.push_back(data[i]);
        } else {
            test.push_back(data[i]);
        }
    }
}

// Получение значения признака по индексу
double get_feature(const Transaction& t, int feature_index) {
    if (feature_index == 0) return t.amount;
    return t.frequency;
}

// Обучение слабого классификатора (Decision Stump)
// Перебираем все возможные пороги и выбираем лучший
WeakClassifier train_weak_classifier(std::vector<Transaction>& data) {
    WeakClassifier best_clf;
    double min_error = 1e9;
    
    // Пробуем оба признака
    for (int feature = 0; feature < 2; feature++) {
        // Собираем все уникальные значения признака для порогов
        std::vector<double> values;
        for (const auto& t : data) {
            values.push_back(get_feature(t, feature));
        }
        std::sort(values.begin(), values.end());
        
        // Пробуем разные пороги
        for (int i = 0; i < values.size() - 1; i++) {
            double threshold = (values[i] + values[i + 1]) / 2.0;
            
            // Пробуем обе полярности
            for (int polarity : {1, -1}) {
                double error = 0.0;
                
                // Вычисляем взвешенную ошибку
                for (const auto& t : data) {
                    int prediction = (get_feature(t, feature) > threshold) ? polarity : -polarity;
                    int actual = (t.label == 1) ? 1 : -1;
                    
                    if (prediction != actual) {
                        error += t.weight;
                    }
                }
                
                // Сохраняем лучший классификатор
                if (error < min_error) {
                    min_error = error;
                    best_clf.feature_index = feature;
                    best_clf.threshold = threshold;
                    best_clf.polarity = polarity;
                }
            }
        }
    }
    
    return best_clf;
}

// Предсказание одним слабым классификатором
int predict_weak(const WeakClassifier& clf, const Transaction& t) {
    double value = get_feature(t, clf.feature_index);
    return (value > clf.threshold) ? clf.polarity : -clf.polarity;
}

// Обучение AdaBoost алгоритма
std::vector<WeakClassifier> train_adaboost(std::vector<Transaction>& train_data, 
                                            int num_classifiers) {
    std::vector<WeakClassifier> classifiers;
    
    // Инициализация весов
    for (auto& t : train_data) {
        t.weight = 1.0 / train_data.size();
    }
    
    // Обучаем num_classifiers слабых классификаторов
    for (int iter = 0; iter < num_classifiers; iter++) {
        // Обучаем слабый классификатор
        WeakClassifier clf = train_weak_classifier(train_data);
        
        // Вычисляем взвешенную ошибку
        double error = 0.0;
        for (const auto& t : train_data) {
            int prediction = predict_weak(clf, t);
            int actual = (t.label == 1) ? 1 : -1;
            
            if (prediction != actual) {
                error += t.weight;
            }
        }
        
        // Избегаем деления на ноль
        if (error < 1e-10) error = 1e-10;
        if (error > 1.0 - 1e-10) error = 1.0 - 1e-10;
        
        // Вычисляем вес классификатора (alpha)
        clf.alpha = 0.5 * log((1.0 - error) / error);
        
        // Обновляем веса образцов
        double sum_weights = 0.0;
        for (auto& t : train_data) {
            int prediction = predict_weak(clf, t);
            int actual = (t.label == 1) ? 1 : -1;
            
            // Увеличиваем веса неправильно классифицированных
            t.weight *= exp(-clf.alpha * actual * prediction);
            sum_weights += t.weight;
        }
        
        // Нормализация весов
        for (auto& t : train_data) {
            t.weight /= sum_weights;
        }
        
        classifiers.push_back(clf);
    }
    
    return classifiers;
}

// Предсказание ансамблем классификаторов
// Возвращает значение от -1 до 1 (можно использовать как вероятность)
double predict_adaboost(const std::vector<WeakClassifier>& classifiers, 
                        const Transaction& t) {
    double score = 0.0;
    
    for (const auto& clf : classifiers) {
        score += clf.alpha * predict_weak(clf, t);
    }
    
    return score;
}

// Вычисление AUC метрики
double calculate_auc(const std::vector<WeakClassifier>& classifiers,
                     const std::vector<Transaction>& test_data) {
    // Создаем пары (score, label)
    std::vector<std::pair<double, int>> predictions;
    
    for (const auto& t : test_data) {
        double score = predict_adaboost(classifiers, t);
        predictions.push_back({score, t.label});
    }
    
    // Сортируем по убыванию score
    std::sort(predictions.begin(), predictions.end(),
              [](const std::pair<double, int>& a, const std::pair<double, int>& b) { 
                  return a.first > b.first; 
              });
    
    // Вычисляем AUC методом трапеций
    int total_positive = 0;
    int total_negative = 0;
    
    for (const auto& p : predictions) {
        if (p.second == 1) total_positive++;
        else total_negative++;
    }
    
    double auc = 0.0;
    int true_positive = 0;
    int false_positive = 0;
    
    for (const auto& p : predictions) {
        if (p.second == 1) {
            true_positive++;
        } else {
            false_positive++;
            // Добавляем площадь прямоугольника
            auc += (double)true_positive / total_positive;
        }
    }
    
    if (total_negative > 0) {
        auc /= total_negative;
    }
    
    return auc;
}

// Тестирование производительности
void test_adaboost_performance(int num_samples, int num_classifiers) {
    std::cout << "\n=== AdaBoost: Тестирование производительности ===" << std::endl;
    std::cout << "Количество образцов: " << num_samples << std::endl;
    std::cout << "Количество слабых классификаторов: " << num_classifiers << std::endl;
    
    // Генерация данных
    clock_t start = clock();
    std::vector<Transaction> data = generate_dataset(num_samples);
    clock_t end = clock();
    double gen_time = (double)(end - start) / CLOCKS_PER_SEC;
    std::cout << "Время генерации данных: " << gen_time << " сек" << std::endl;
    
    // Разделение на train/test
    std::vector<Transaction> train_data, test_data;
    split_dataset(data, train_data, test_data, 0.7);
    std::cout << "Обучающая выборка: " << train_data.size() << " образцов" << std::endl;
    std::cout << "Тестовая выборка: " << test_data.size() << " образцов" << std::endl;
    
    // Обучение модели
    start = clock();
    std::vector<WeakClassifier> model = train_adaboost(train_data, num_classifiers);
    end = clock();
    double train_time = (double)(end - start) / CLOCKS_PER_SEC;
    std::cout << "Время обучения: " << train_time << " сек" << std::endl;
    
    // Предсказание на тестовой выборке
    start = clock();
    for (const auto& t : test_data) {
        predict_adaboost(model, t);
    }
    end = clock();
    double predict_time = (double)(end - start) / CLOCKS_PER_SEC;
    std::cout << "Время предсказания: " << predict_time << " сек" << std::endl;
    
    // Вычисление AUC
    double auc = calculate_auc(model, test_data);
    std::cout << "AUC: " << auc << std::endl;
    
    if (auc > 0.95) {
        std::cout << "✓ Тест пройден: AUC > 0.95" << std::endl;
    } else {
        std::cout << "✗ Тест не пройден: AUC <= 0.95" << std::endl;
    }
    
    // Вычислительная сложность
    std::cout << "\nАнализ сложности:" << std::endl;
    std::cout << "- Обучение: O(T * N * F * N) = O(T * N^2 * F)" << std::endl;
    std::cout << "  где T=" << num_classifiers << " (классификаторы), ";
    std::cout << "N=" << train_data.size() << " (образцы), F=2 (признаки)" << std::endl;
    std::cout << "- Предсказание: O(T) = O(" << num_classifiers << ")" << std::endl;
}
