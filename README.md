# Лабораторная работа: Деревья решений

## Описание
Реализация алгоритмов построения деревьев решений ID3, C4.5, CART и CHAID для предметной области "Выбор заказчика".

## Структура файлов

```
├── data.h          # Обучающая выборка (14 примеров, 4 атрибута)
├── entropy.h       # Функции расчета метрик (энтропия, Gini, хи-квадрат)
├── id3.h           # Алгоритм ID3 (Information Gain)
├── c45.h           # Алгоритм C4.5 (Gain Ratio)
├── cart.h          # Алгоритм CART (Gini Index)
├── chaid.h         # Алгоритм CHAID (Chi-Square)
├── main.cpp        # Главный файл программы
├── Makefile        # Система сборки
└── README.md       # Документация
```

## Предметная область: Выбор заказчика

### Атрибуты:
1. **Бюджет**: Низкий, Средний, Высокий
2. **Надежность**: Низкая, Средняя, Высокая
3. **Опыт совместной работы**: Нет, Есть
4. **Срок оплаты**: Короткий, Длинный

### Целевой атрибут:
**Выбрать**: Да, Нет

## Как использовать

### Сборка проекта
```bash
make
```

### Запуск программы
```bash
make run
```

### Очистка проекта
```bash
make clean
```

### Пересборка
```bash
make rebuild
```

---

# Теория алгоритмов деревьев решений

## 1. Алгоритм ID3 (Iterative Dichotomiser 3)

### Описание
ID3 — классический алгоритм построения деревьев решений, разработанный Россом Куинланом в 1986 году. Использует концепцию **энтропии** и **прироста информации** для выбора наилучшего атрибута на каждом шаге.

### Теория

#### Энтропия
Энтропия измеряет степень неопределенности или "хаоса" в наборе данных:

```
E(S) = -Σ pi * log₂(pi)
```

где:
- `S` — набор данных
- `pi` — доля примеров класса `i`
- Энтропия = 0, если все примеры одного класса (полная определенность)
- Энтропия максимальна, если классы распределены равномерно

**Пример из кода** (`entropy.h`):
```cpp
double calculate_entropy(const std::vector<Example>& data) {
    if (data.empty()) return 0.0;
    
    // Подсчитываем количество примеров каждого класса
    std::map<std::string, int> class_count;
    for (const auto& ex : data) {
        class_count[ex.decision]++;
    }
    
    double entropy = 0.0;
    int total = data.size();
    
    // Вычисляем энтропию: E(S) = -Σ(pi * log2(pi))
    for (const auto& pair : class_count) {
        double probability = (double)pair.second / total;
        if (probability > 0) {
            entropy -= probability * log2(probability);
        }
    }
    
    return entropy;
}
```

#### Прирост информации (Information Gain)
Показывает, насколько уменьшается неопределенность после разбиения по атрибуту:

```
IG(S, A) = E(S) - Σ (|Sv|/|S|) * E(Sv)
```

где:
- `A` — атрибут для разбиения
- `Sv` — подмножество данных со значением `v` атрибута `A`

**Пример из кода** (`entropy.h`):
```cpp
double calculate_information_gain(
    const std::vector<Example>& data,
    int attr_index) {
    
    double base_entropy = calculate_entropy(data);
    auto subsets = split_by_attribute(data, attr_index);
    
    double weighted_entropy = 0.0;
    int total = data.size();
    
    // Вычисляем взвешенную энтропию подмножеств
    for (const auto& pair : subsets) {
        double weight = (double)pair.second.size() / total;
        weighted_entropy += weight * calculate_entropy(pair.second);
    }
    
    return base_entropy - weighted_entropy;  // IG = E(S) - Σ(weighted E(Sv))
}
```

### Ход работы алгоритма ID3

1. **Базовые случаи**:
   - Если все примеры одного класса → создать листовой узел с этим классом
   - Если атрибуты закончились → создать лист с наиболее частым классом

2. **Выбор атрибута**:
   - Для каждого доступного атрибута вычислить прирост информации (IG)
   - Выбрать атрибут с максимальным IG

3. **Разбиение**:
   - Создать узел с выбранным атрибутом
   - Разбить данные по значениям этого атрибута
   - Рекурсивно построить поддеревья для каждого подмножества

**Пример из кода** (`id3.h`):
```cpp
TreeNode* build_id3_tree(
    const std::vector<Example>& data,
    std::vector<int> available_attributes,
    const std::vector<std::string>& attr_names,
    int depth = 0) {
    
    TreeNode* node = new TreeNode();
    
    // Шаг 1: Базовые случаи
    if (is_homogeneous(data)) {
        node->is_leaf = true;
        node->class_label = data[0].decision;
        return node;
    }
    
    if (available_attributes.empty()) {
        node->is_leaf = true;
        node->class_label = get_most_common_class(data);
        return node;
    }
    
    // Шаг 2: Выбираем атрибут с максимальным IG
    int best_attr = -1;
    double max_gain = -1.0;
    
    for (int attr : available_attributes) {
        double gain = calculate_information_gain(data, attr);
        if (gain > max_gain) {
            max_gain = gain;
            best_attr = attr;
        }
    }
    
    // Шаг 3: Создаем узел и разбиваем данные
    node->split_attribute = best_attr;
    node->attribute_name = attr_names[best_attr];
    
    // Удаляем выбранный атрибут
    std::vector<int> remaining_attrs;
    for (int attr : available_attributes) {
        if (attr != best_attr) {
            remaining_attrs.push_back(attr);
        }
    }
    
    // Рекурсивно строим поддеревья
    auto subsets = split_by_attribute(data, best_attr);
    for (const auto& subset_pair : subsets) {
        if (!subset_pair.second.empty()) {
            node->children[subset_pair.first] = 
                build_id3_tree(subset_pair.second, remaining_attrs, attr_names, depth + 1);
        }
    }
    
    return node;
}
```

### Пример вычислений

Для нашей обучающей выборки (14 примеров: 6 "Да", 8 "Нет"):

1. **Энтропия исходного набора**:
   ```
   E(S) = -(6/14)*log₂(6/14) - (8/14)*log₂(8/14) ≈ 0.985
   ```

2. **Прирост информации для атрибута "Опыт"**:
   - Есть: 6 примеров (4 "Да", 2 "Нет")
   - Нет: 8 примеров (2 "Да", 6 "Нет")
   
   ```
   E(Есть) = -(4/6)*log₂(4/6) - (2/6)*log₂(2/6) ≈ 0.918
   E(Нет) = -(2/8)*log₂(2/8) - (6/8)*log₂(6/8) ≈ 0.811
   IG(Опыт) = 0.985 - (6/14)*0.918 - (8/14)*0.811 ≈ 0.123
   ```

---

## 2. Алгоритм C4.5

### Описание
C4.5 — улучшенная версия ID3, также разработанная Россом Куинланом. Устраняет основной недостаток ID3 — смещение к атрибутам с большим количеством значений.

### Теория

#### Gain Ratio (Нормализованный прирост)
C4.5 использует Gain Ratio вместо Information Gain:

```
GainRatio(S, A) = IG(S, A) / SplitInfo(S, A)
```

#### Split Information
Измеряет, насколько равномерно атрибут разбивает данные:

```
SplitInfo(S, A) = -Σ (|Sv|/|S|) * log₂(|Sv|/|S|)
```

- Если атрибут разбивает данные на много маленьких групп → SplitInfo большая
- Нормализация через SplitInfo предотвращает выбор таких атрибутов

**Пример из кода** (`entropy.h`):
```cpp
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

// Вычисление Gain Ratio
double calculate_gain_ratio(
    const std::vector<Example>& data,
    int attr_index) {
    
    double ig = calculate_information_gain(data, attr_index);
    double split_info = calculate_split_info(data, attr_index);
    
    if (split_info == 0.0) return 0.0;
    return ig / split_info;  // GainRatio = IG / SplitInfo
}
```

### Ход работы алгоритма C4.5

Алгоритм аналогичен ID3, но на шаге выбора атрибута использует **Gain Ratio** вместо **Information Gain**:

**Пример из кода** (`c45.h`):
```cpp
// Выбираем атрибут с максимальным Gain Ratio
int best_attr = -1;
double max_gain_ratio = -1.0;

for (int attr : available_attributes) {
    double gain_ratio = calculate_gain_ratio(data, attr);  // Используем Gain Ratio
    if (gain_ratio > max_gain_ratio) {
        max_gain_ratio = gain_ratio;
        best_attr = attr;
    }
}
```

### Преимущества C4.5 над ID3

1. **Устранение смещения**: не выбирает атрибуты с большим количеством значений просто из-за их "дробления"
2. **Более компактные деревья**: в нашем примере C4.5 построил дерево с 8 узлами против 9 у ID3
3. **Работа с непрерывными атрибутами**: C4.5 может автоматически дискретизировать числовые данные

---

## 3. Алгоритм CART (Classification and Regression Trees)

### Описание
CART — алгоритм, разработанный Брейманом и др. в 1984 году. Использует **индекс Джини** вместо энтропии. Подходит как для классификации, так и для регрессии.

### Теория

#### Индекс Джини
Измеряет вероятность неправильной классификации случайно выбранного элемента:

```
Gini(S) = 1 - Σ pi²
```

где:
- `pi` — доля класса `i`
- Gini = 0, если все примеры одного класса
- Gini максимален при равномерном распределении классов

**Сравнение с энтропией**:
- Энтропия: `E = -Σ pi*log₂(pi)` (более чувствительна к изменениям)
- Gini: `Gini = 1 - Σ pi²` (вычислительно проще, нет логарифмов)

**Пример из кода** (`entropy.h`):
```cpp
// Вычисление индекса Джини для CART
double calculate_gini_index(const std::vector<Example>& data) {
    if (data.empty()) return 0.0;
    
    std::map<std::string, int> class_count;
    for (const auto& ex : data) {
        class_count[ex.decision]++;
    }
    
    double gini = 1.0;
    int total = data.size();
    
    // Gini = 1 - Σ(pi²)
    for (const auto& pair : class_count) {
        double probability = (double)pair.second / total;
        gini -= probability * probability;
    }
    
    return gini;
}
```

#### Снижение Gini (Gini Gain)
Аналогично приросту информации, но для индекса Джини:

```
GiniGain(S, A) = Gini(S) - Σ (|Sv|/|S|) * Gini(Sv)
```

**Пример из кода** (`entropy.h`):
```cpp
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
```

### Ход работы алгоритма CART

Аналогичен ID3, но использует **Gini Gain** вместо **Information Gain**:

**Пример из кода** (`cart.h`):
```cpp
// Выбираем атрибут с максимальным снижением Gini
int best_attr = -1;
double max_gini_gain = -1.0;

for (int attr : available_attributes) {
    double gini_gain = calculate_gini_gain(data, attr);  // Используем Gini
    if (gini_gain > max_gini_gain) {
        max_gini_gain = gini_gain;
        best_attr = attr;
    }
}
```

### Особенности CART

1. **Бинарное разбиение**: в полной реализации CART создает только 2 ветви на узел
2. **Вычислительная эффективность**: индекс Джини быстрее вычисляется, чем энтропия
3. **Регрессия**: может работать с непрерывными целевыми переменными

---

## 4. Алгоритм CHAID (Chi-squared Automatic Interaction Detection)

### Описание
CHAID — статистический алгоритм, использующий критерий хи-квадрат (χ²) для определения значимости связи между атрибутом и целевой переменной.

### Теория

#### Критерий хи-квадрат
Проверяет гипотезу о независимости между атрибутом и классом:

```
χ² = Σ (O - E)² / E
```

где:
- `O` (Observed) — наблюдаемая частота
- `E` (Expected) — ожидаемая частота при независимости

**Интерпретация**:
- Большое значение χ² → сильная зависимость → атрибут информативен
- Малое значение χ² → слабая зависимость → атрибут не важен

**Пример из кода** (`entropy.h`):
```cpp
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
            // Ожидаемая частота
            double expected = (double)subset_size * class_pair.second / total;
            // Наблюдаемая частота
            int observed = subset_class_count[class_pair.first];
            
            if (expected > 0) {
                double diff = observed - expected;
                chi_square += (diff * diff) / expected;
            }
        }
    }
    
    return chi_square;
}
```

### Ход работы алгоритма CHAID

Аналогичен ID3, но использует **χ²-статистику** для выбора атрибута:

**Пример из кода** (`chaid.h`):
```cpp
// Выбираем атрибут с максимальным значением хи-квадрат
int best_attr = -1;
double max_chi_square = -1.0;

for (int attr : available_attributes) {
    double chi_square = calculate_chi_square(data, attr);  // Используем χ²
    if (chi_square > max_chi_square) {
        max_chi_square = chi_square;
        best_attr = attr;
    }
}
```

### Особенности CHAID

1. **Статистический подход**: учитывает статистическую значимость разбиений
2. **Множественное разбиение**: создает столько ветвей, сколько значений у атрибута
3. **Автоматическое слияние**: может объединять похожие категории
4. **Работа с категориальными данными**: особенно эффективен для номинальных переменных

---

## Сравнение алгоритмов

| Алгоритм | Критерий | Преимущества | Недостатки |
|----------|----------|--------------|------------|
| **ID3** | Information Gain | Простота, интуитивность | Смещение к атрибутам с большим числом значений |
| **C4.5** | Gain Ratio | Устраняет смещение ID3, компактные деревья | Сложнее в реализации |
| **CART** | Gini Index | Быстрые вычисления, работает с регрессией | Бинарное разбиение может быть ограничением |
| **CHAID** | Chi-Square | Статистическая обоснованность, множественное разбиение | Требует больше данных для надежности |

## Результаты работы программы

Программа выводит:
- Обучающую выборку в табличном виде
- Деревья решений для каждого алгоритма с визуализацией
- Характеристики деревьев (глубина, количество узлов)
- Сравнительную таблицу алгоритмов

**Пример вывода**:
```
┌──────────────┬──────────┬────────────────┬─────────────────────────┐
│  Алгоритм    │ Глубина  │ Кол-во узлов   │      Критерий           │
├──────────────┼──────────┼────────────────┼─────────────────────────┤
│ ID3          │    3     │       9        │ Information Gain        │
│ C4.5         │    3     │       8        │ Gain Ratio              │
│ CART         │    3     │       9        │ Gini Index              │
│ CHAID        │    3     │       8        │ Chi-Square              │
└──────────────┴──────────┴────────────────┴─────────────────────────┘
```

## Требования

- Компилятор: g++ с поддержкой C++11
- Система сборки: make
- ОС: macOS, Linux, Windows (с MinGW)

## Автор
Выполнено для МГТУ им. Баумана  
Семинар 13: Деревья решений
