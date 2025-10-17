# Лабораторная работа №4: Численные методы решения нелинейных уравнений

## Оглавление
1. [Цель работы](#цель-работы)
2. [Постановка задачи](#постановка-задачи)
3. [Теоретическая часть](#теоретическая-часть)
4. [Практическая реализация](#практическая-реализация)
5. [Анализ результатов](#анализ-результатов)
6. [Инструкция по сборке и запуску](#инструкция-по-сборке-и-запуску)
7. [Ответы на возможные вопросы](#ответы-на-возможные-вопросы)

## Цель работы

**Основная цель**: Изучение и практическая реализация численных методов решения нелинейных уравнений на примере уравнения **x² - eˣ + 2 = 0**.

**Конкретные задачи**:
1. Реализовать три численных метода:
   - Метод половинного деления (бисекции)
   - Метод простых итераций
   - Метод Ньютона (касательных)
2. Найти корень уравнения с двумя различными точностями:
   - ε₁ = 10⁻⁶ (0.000001)
   - ε₂ = 10⁻¹¹ (0.00000000001)
3. Сравнить эффективность методов по количеству итераций и скорости сходимости
4. Проанализировать полученные результаты

## Постановка задачи

### Исходное уравнение
**Уравнение варианта 24**:
```cpp
// Файл: equation_systems.h
double equation_24(double x) {
    return x*x - std::exp(x) + 2;  // x² - eˣ + 2 = 0
}
```

### Требуемые точности
```cpp
// Файл: math_utils.h
const double EPSILON_1 = 0.000001;      // ε < 0.000001
const double EPSILON_2 = 0.00000000001; // ε < 0.00000000001
```

### Критерии остановки
Для всех методов используются два критерия остановки:
1. **По значению функции**: |f(xₙ)| < ε
2. **По изменению аргумента**: |xₙ₊₁ - xₙ| < ε

## Теоретическая часть

### 1. Метод половинного деления (Бисекции)

**Математическая основа**: Теорема Больцано-Коши о промежуточном значении.

**Алгоритм**:
1. Выбирается начальный интервал [a, b], где f(a) × f(b) < 0
2. Вычисляется середина интервала c = (a + b)/2
3. Если f(c) = 0 или |b - a| < 2ε, процесс завершается
4. Иначе выбирается новый интервал [a, c] или [c, b], где знаки функции на концах различны

**Код проверки условия Больцано-Коши**:
```cpp
// Файл: bisection_method.h
bool check_bolzano_condition(double (*func)(double), double a, double b, const char** error_msg) {
    double fa = func(a);
    double fb = func(b);

    if (!is_valid_number(fa) || !is_valid_number(fb)) {
        *error_msg = "Функция возвращает нечисловое значение на границах интервала";
        return false;
    }

    if (fa * fb > 0) {
        *error_msg = "На границах интервала функция имеет одинаковые знаки";
        return false;
    }

    return true;
}
```

**Код вычисления середины интервала**:
```cpp
// Файл: bisection_method.h
for (int iteration = 0; iteration < MAX_ITERATIONS; iteration++) {
    // Вычисление середины интервала
    c = (a + b) / 2.0;  // ← ВОТ ЗДЕСЬ ВЫЧИСЛЯЕТСЯ СЕРЕДИНА
    fc = func(c);

    // Проверка точности по значению функции
    if (std::fabs(fc) < epsilon) {  // ← КРИТЕРИЙ ОСТАНОВКИ 1
        result.root = c;
        result.function_value = fc;
        result.error_estimate = (b - a) / 2.0;
        result.iterations = iteration + 1;
        result.converged = true;
        return result;
    }

    // Проверка точности по длине интервала
    if ((b - a) < 2.0 * epsilon) {  // ← КРИТЕРИЙ ОСТАНОВКИ 2
        result.root = c;
        result.function_value = fc;
        result.error_estimate = (b - a) / 2.0;
        result.iterations = iteration + 1;
        result.converged = true;
        return result;
    }

    // Выбор нового интервала
    if (fa * fc < 0) {
        b = c;
    } else {
        a = c;
        fa = fc;
    }
}
```

### 2. Метод простых итераций

**Математическая основа**: Теорема о сжатом отображении.

**Алгоритм**:
1. Исходное уравнение f(x) = 0 преобразуется к виду x = φ(x)
2. Строится итерационная последовательность: xₙ₊₁ = φ(xₙ)
3. Процесс продолжается до выполнения критериев остановки

**Преобразование для нашего уравнения**:
```cpp
// Файл: equation_systems.h
double equation_24_phi(double x) {
    // Преобразование: x = ln(x² + 2)
    return std::log(x*x + 2);
}
```

**Проверка условия сходимости**:
```cpp
// Файл: iteration_method.h
bool check_contraction_condition(double (*phi)(double), double a, double b, double* max_derivative) {
    const int SAMPLES = 100;
    double step = (b - a) / (SAMPLES - 1);
    double max_phi_prime = 0.0;

    for (int i = 0; i < SAMPLES; i++) {
        double x = a + i * step;
        double phi_prime = numerical_phi_derivative(phi, x);

        if (!is_valid_number(phi_prime)) {
            return false;
        }

        double abs_phi_prime = std::fabs(phi_prime);
        if (abs_phi_prime > max_phi_prime) {
            max_phi_prime = abs_phi_prime;
        }
    }

    *max_derivative = max_phi_prime;
    return (max_phi_prime < 1.0);  // ← ПРОВЕРКА УСЛОВИЯ СЖАТИЯ
}
```

**Код метода простых итераций**:
```cpp
// Файл: iteration_method.h
for (int iteration = 0; iteration < MAX_ITERATIONS; iteration++) {
    // Вычисление нового приближения
    x_current = phi(x_prev);  // ← ОСНОВНАЯ ФОРМУЛА МЕТОДА

    // Проверка критериев остановки
    double delta = std::fabs(x_current - x_prev);
    double f_current = func(x_current);
    double residual = std::fabs(f_current);

    // Проверка сходимости по изменению приближения
    if (delta < epsilon) {  // ← КРИТЕРИЙ ОСТАНОВКИ 1
        result.root = x_current;
        result.function_value = f_current;
        result.error_estimate = delta;
        result.iterations = iteration + 1;
        result.converged = true;
        return result;
    }

    // Проверка сходимости по значению функции
    if (residual < epsilon) {  // ← КРИТЕРИЙ ОСТАНОВКИ 2
        result.root = x_current;
        result.function_value = f_current;
        result.error_estimate = delta;
        result.iterations = iteration + 1;
        result.converged = true;
        return result;
    }

    x_prev = x_current;
}
```

### 3. Метод Ньютона (Касательных)

**Математическая основа**: Линеаризация функции в окрестности текущего приближения.

**Производная функции**:
```cpp
// Файл: equation_systems.h
double equation_24_derivative(double x) {
    return 2*x - std::exp(x);  // f'(x) = 2x - eˣ
}
```

**Код метода Ньютона**:
```cpp
// Файл: newton_method.h
for (int iteration = 0; iteration < MAX_ITERATIONS; iteration++) {
    // Вычисление функции и производной в текущей точке
    f_prev = func(x_prev);
    f_deriv_prev = derivative(x_prev);

    // Проверка что производная не равна нулю
    if (is_zero(f_deriv_prev, 1e-15)) {
        result.error_msg = "Производная слишком близка к нулю - деление на ноль";
        return result;
    }

    // Вычисление нового приближения по формуле Ньютона
    x_current = x_prev - f_prev / f_deriv_prev;  // ← ОСНОВНАЯ ФОРМУЛА НЬЮТОНА

    // Вычисление критериев остановки
    double delta = std::fabs(x_current - x_prev);
    double f_current = func(x_current);
    double residual = std::fabs(f_current);

    // Проверка сходимости по изменению приближения
    if (delta < epsilon) {  // ← КРИТЕРИЙ ОСТАНОВКИ 1
        result.root = x_current;
        result.function_value = f_current;
        result.error_estimate = delta;
        result.iterations = iteration + 1;
        result.converged = true;
        return result;
    }

    // Проверка сходимости по значению функции
    if (residual < epsilon) {  // ← КРИТЕРИЙ ОСТАНОВКИ 2
        result.root = x_current;
        result.function_value = f_current;
        result.error_estimate = delta;
        result.iterations = iteration + 1;
        result.converged = true;
        return result;
    }

    x_prev = x_current;
}
```

## Практическая реализация

### Выбор интервала [1.0, 2.0]

**Обоснование выбора интервала**:

```cpp
// Файл: equation_systems.h
Interval get_recommended_interval() {
    Interval interval;
    // f(1) = 1 - e + 2 ≈ 0.28172 > 0
    // f(2) = 4 - e² + 2 ≈ -1.38906 < 0
    // f(1) × f(2) < 0 → корень существует
    interval.a = 1.0;
    interval.b = 2.0;
    return interval;
}
```

**Проверка корректности интервала**:
```cpp
// Файл: bisection_method.h
// Проверка корректности интервала
if (a >= b) {
    result.error_msg = "Некорректный интервал: левая граница должна быть меньше правой";
    return result;
}
```

### Выбор начальных приближений

**Для метода простых итераций**:
```cpp
// Файл: iteration_method.h
// Начальное приближение - середина интервала
double x0 = (interval.a + interval.b) / 2.0;
```

**Для метода Ньютона**:
```cpp
// Файл: newton_method.h
double choose_newton_initial_guess(double (*func)(double), double a, double b) {
    double fa = func(a);
    double fb = func(b);

    // Вычисляем вторые производные в граничных точках
    double f2a = numerical_second_derivative(func, a);
    double f2b = numerical_second_derivative(func, b);

    // Правило: выбираем тот конец, где f(x) × f''(x) > 0
    if (fa * f2a > 0) {
        return a;
    } else if (fb * f2b > 0) {
        return b;
    } else {
        // Если правило не работает, возвращаем середину интервала
        return (a + b) / 2.0;
    }
}
```

### Обработка особых случаев

**Защита от деления на ноль в методе Ньютона**:
```cpp
// Файл: newton_method.h
// Проверка что производная не равна нулю
if (is_zero(f_deriv_prev, 1e-15)) {
    result.error_msg = "Производная слишком близка к нулю - деление на ноль";
    result.root = x_prev;
    result.function_value = f_prev;
    result.iterations = iteration;
    return result;
}
```

**Защита от бесконечных циклов**:
```cpp
// Во всех методах:
const int MAX_ITERATIONS = 1000;

for (int iteration = 0; iteration < MAX_ITERATIONS; iteration++) {
    // ... основной код ...
}

// Если вышли из цикла по количеству итераций
result.error_msg = "Превышено максимальное количество итераций";
```

**Проверка на корректные числовые значения**:
```cpp
// Файл: math_utils.h
inline bool is_valid_number(double x) {
    return !std::isnan(x) && !std::isinf(x);
}

// Использование в методах:
if (!is_valid_number(fc)) {
    result.error_msg = "Функция возвращает нечисловое значение";
    return result;
}
```

## Анализ результатов

### Структура для хранения результатов
```cpp
// Файл: math_utils.h
struct SolutionResult {
    double root;           // Найденный корень
    double function_value; // Значение функции в корне
    double error_estimate; // Оценка погрешности
    int iterations;        // Количество выполненных итераций
    bool converged;        // Сошелся ли метод
    const char* error_msg; // Сообщение об ошибке (если есть)
};
```

### Экспорт результатов в CSV
```cpp
// Файл: results_table.h
void export_results_to_csv(const vector<ExperimentResult>& results, const string& filename) {
    ofstream file(filename);

    // Добавляем BOM для корректного отображения в Excel
    file << "\xEF\xBB\xBF";

    // Заголовок CSV с разделителем ";" (точка с запятой)
    file << "Method" << ";"
         << "Epsilon" << ";"
         << "Root" << ";"
         << "Function Value" << ";"
         << "Error Estimate" << ";"
         << "Iterations" << ";"
         << "Converged" << ";"
         << "Status" << endl;

    // Данные
    for (const auto& result : results) {
        file << escape_csv_field(result.method_name) << ";"
             << result.epsilon << ";"
             << format_number_csv(result.root) << ";"
             << format_number_csv(result.function_value) << ";"
             << format_number_csv(result.error_estimate) << ";"
             << result.iterations << ";"
             << (result.converged ? "Yes" : "No") << ";"
             << escape_csv_field(result.status) << endl;
    }

    file.close();
}
```

### Найденный корень
```
x ≈ 1.319073676946772 × 10⁰
```

### Сравнение методов по количеству итераций

| Метод | ε = 10⁻⁶ | ε = 10⁻¹¹ | Скорость сходимости |
|-------|----------|-----------|---------------------|
| Половинное деление | 20 | 35 | Линейная O(1/2ⁿ) |
| Простые итерации | 33 | 66 | Линейная O(qⁿ) |
| Метод Ньютона | 5 | 6 | Квадратичная O(ε²ⁿ) |

## Инструкция по сборке и запуску

### Требования
- Компилятор C++ с поддержкой C++11 (g++ 4.8+ или clang 3.3+)
- Операционная система: Linux, Windows (WSL), или macOS

### Сборка проекта
```bash
# Компиляция
make

# Или вручную
g++ -std=c++11 -Wall -Wextra -O2 -o nonlinear_solver main.cpp -lm
```

### Запуск программы
```bash
./nonlinear_solver
```

### Генерируемые файлы
После запуска программы создаются три файла:

1. **`nonlinear_equation_results.csv`** - результаты в формате CSV
2. **`nonlinear_equation_results.tsv`** - результаты в формате TSV
3. **`nonlinear_equation_report.txt`** - читаемый текстовый отчет

### Очистка
```bash
make clean
```

## Ответы на возможные вопросы

### 1. Почему выбран именно интервал [1, 2]?
**Ответ**: Интервал выбран на основе анализа функции:
- f(1) = 1 - e + 2 ≈ 0.2817 > 0
- f(2) = 4 - e² + 2 ≈ -1.3891 < 0
- f(1) × f(2) < 0 → выполняется условие Больцано-Коши
- Корень гарантированно существует в этом интервале

### 2. Почему для метода итераций использовано преобразование x = ln(x² + 2)?
**Ответ**: Рассматривались два преобразования:
1. x = √(eˣ - 2) - имеет ограниченную область определения (только при x ≥ ln2)
2. x = ln(x² + 2) - определено для всех x ∈ ℝ

Второе преобразование было выбрано потому что:
- Оно определено на всем интервале [1, 2]
- |φ'(x)| = |2x/(x² + 2)| < 1 на [1, 2] (максимум ≈ 0.666)
- Условие сходимости выполняется

### 3. Почему начальное приближение для метода Ньютона x₀ = 2.0?
**Ответ**: Начальное приближение выбрано по правилу:
- f(1) > 0, f''(1) < 0 → f(1)×f''(1) < 0
- f(2) < 0, f''(2) < 0 → f(2)×f''(2) > 0
- Выбираем тот конец, где f(x)×f''(x) > 0 → x₀ = 2.0

Это правило обеспечивает монотонную сходимость метода Ньютона.

### 4. Почему метод Ньютона показал наилучший результат?
**Ответ**: Метод Ньютона имеет квадратичную скорость сходимости, в то время как:
- Метод бисекции: линейная сходимость (коэффициент 1/2)
- Метод итераций: линейная сходимость (коэффициент q ≈ 0.666)

Квадратичная сходимость означает, что количество верных цифр удваивается на каждой итерации.

### 5. Как обеспечивалась точность вычислений?
**Ответ**: Были приняты следующие меры:
- Использование типа `double` (точность ~15-17 знаков)
- Сравнение чисел с плавающей точкой с учетом машинного эпсилона
- Двойной критерий остановки (по функции и по аргументу)
- Защита от накопления ошибок округления

### 6. Почему метод простых итераций потребовал больше итераций, чем метод бисекции?
**Ответ**: Несмотря на то, что оба метода имеют линейную сходимость:
- Метод бисекции: коэффициент сходимости 0.5
- Метод итераций: коэффициент сходимости max|φ'(x)| ≈ 0.666

Меньший коэффициент сходимости означает более быструю сходимость, поэтому метод бисекции оказался эффективнее метода итераций для данного уравнения.

### 7. Есть ли у уравнения другие корни?
**Ответ**: Проведенный анализ показывает:
- При x → -∞: x² → +∞, eˣ → 0, f(x) → +∞
- При x → +∞: x² → +∞, eˣ → +∞, но eˣ растет быстрее, поэтому f(x) → -∞
- f(0) = 0 - 1 + 2 = 1 > 0
- f(1) > 0, f(2) < 0 → один корень в [1, 2]
- f(x) монотонно убывает при x > 0.5 (f'(x) = 2x - eˣ < 0)
- Следовательно, уравнение имеет ровно один действительный корень

### 8. Какова реальная достигнутая точность?
**Ответ**: Для метода Ньютона при ε = 10⁻¹¹:
- |f(x)| ≈ 10⁻¹² ÷ 10⁻¹⁶
- |Δx| ≈ 10⁻¹¹
- Реальная точность превышает требуемую ε₂ = 10⁻¹¹

### 9. Почему использованы именно эти критерии остановки?
**Ответ**: Двойной критерий остановки обеспечивает надежность:
1. **|f(xₙ)| < ε** - гарантирует, что значение функции близко к нулю
2. **|xₙ₊₁ - xₙ| < ε** - гарантирует, что приближения стабилизировались

Использование только одного критерия может привести к преждевременной остановке или лишним итерациям.

### 10. Какие меры приняты для избежания бесконечных циклов?
**Ответ**: Реализованы следующие защиты:
- Ограничение максимального числа итераций (1000)
- Проверка условия сходимости перед запуском методов
- Обнаружение расходимости (слишком большие изменения)
- Проверка на NaN и бесконечности
