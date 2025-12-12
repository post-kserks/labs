#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include <iostream>
#include <iomanip>
#include <cmath>

// Функция для обмена элементов
void swap(int& a, int& b);

// Просеивание вверх (для добавления элемента)
// Использует для построения "снизу-вверх" при добавлении элементов по одному
void sift_up(std::vector<int>& heap, int index);

// Просеивание вниз (для восстановления свойства кучи)
// Используется для построения "сверху-вниз" (из массива)
void sift_down(std::vector<int>& heap, int index);

// Построение пирамиды "восходящим" методом (вставками)
void build_heap_ascending(std::vector<int>& arr);

// Построение пирамиды "нисходящим" методом (Floyd's algorithm, heapify)
void build_heap_descending(std::vector<int>& arr);

// Вспомогательные функции вывода
void print_array(const std::vector<int>& arr);
void print_pyramid(const std::vector<int>& heap);

#endif // HEAP_H
