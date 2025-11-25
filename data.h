// data.h
// Описание тем, пререквизитов и канонического порядка.
// Минимальная структура: массив тем, матрица зависимостей.

#ifndef DATA_H
#define DATA_H

#include <vector>
#include <string>

// Список тем (пример минимального учебного плана)
static const std::vector<std::string> TOPICS = {
    "Intro",           // 0
    "Basics",          // 1
    "DataStructures",  // 2
    "Algorithms",      // 3
    "Databases",       // 4
    "WebDev",          // 5
    "AI_Fundamentals", // 6
    "Project"          // 7
};

// Канонический (рекомендованный) порядок — индексная последовательность
static const std::vector<int> CANONICAL = {0,1,2,3,4,5,6,7};

// Пререквизиты: matrix prereq[a][b] = true, если a является пререквизитом для b
// Например: Basics -> DataStructures (1 -> 2)
static const bool PREREQ_MATRIX[8][8] = {
    // 0    1    2    3    4    5    6    7
    {false,false,false,false,false,false,false,false}, // 0 Intro
    {false,false, true, true, false,false,false,false}, // 1 Basics -> 2,3
    {false,false,false, true, false,false,false,false}, // 2 DataStructures -> 3
    {false,false,false,false,false,false,false,false}, // 3 Algorithms
    {false,false,false,false,false,false,false,false}, // 4 Databases
    {false,false,false,false,false,false,false,false}, // 5 WebDev
    {false,false,false,false,false,false,false,false}, // 6 AI_Fundamentals
    {false,false,false,false,false,false,false,false}  // 7 Project
};

#endif // DATA_H
