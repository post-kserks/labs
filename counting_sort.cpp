#include "counting_sort.h"

// Функция для вывода массива на экран
void print_array(const std::vector<int>& arr) {
    std::cout << "[";
    for (size_t i = 0; i < arr.size(); i++) {
        std::cout << arr[i];
        if (i < arr.size() - 1) std::cout << ", ";
    }
    std::cout << "]" << std::endl;
}

// Функция сортировки подсчетом
void counting_sort(const std::vector<int>& input, std::vector<int>& sorted) {
    // Создаем массив для подсчета (заполняем нулями)
    int count[RANGE_SIZE] = {0};

    // Подсчитываем сколько раз встречается каждое число
    for (size_t i = 0; i < input.size(); i++) {
        // Проверяем, что число в допустимом диапазоне
        if (input[i] < MIN_RATING || input[i] > MAX_RATING) {
            std::cout << "Ошибка: число " << input[i]
                      << " вне диапазона " << MIN_RATING << "-" << MAX_RATING << std::endl;
            return;
        }
        count[input[i] - MIN_RATING]++;
    }

    // Очищаем и подготавливаем выходной массив
    sorted.clear();

    // Заполняем отсортированный массив
    for (int i = 0; i < RANGE_SIZE; i++) {
        for (int j = 0; j < count[i]; j++) {
            sorted.push_back(i + MIN_RATING);
        }
    }
}

// Функция для вычисления медианы
double calculate_median(const std::vector<int>& sorted_arr) {
    // Если массив пустой
    if (sorted_arr.empty()) {
        std::cout << "Ошибка: массив пустой" << std::endl;
        return -1;
    }

    size_t size = sorted_arr.size();
    size_t middle = size / 2;

    // Если количество элементов нечетное
    if (size % 2 == 1) {
        return static_cast<double>(sorted_arr[middle]);
    }
    // Если количество элементов четное
    else {
        return (sorted_arr[middle - 1] + sorted_arr[middle]) / 2.0;
    }
}
