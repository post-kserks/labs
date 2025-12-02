#ifndef CSV_LOADER_H
#define CSV_LOADER_H

#include <vector>
#include <string>
#include "adaboost.h"

// Загрузка данных из CSV файла Kaggle Credit Card Fraud
// max_samples: максимальное количество загружаемых строк (-1 для всех)
std::vector<Transaction> load_creditcard_csv(const std::string& filename, int max_samples = -1);

#endif
