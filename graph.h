#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <string.h>

#define MAX_USERS 15  // Максимальное количество пользователей
#define INF 999999    // Бесконечность для алгоритмов

// Инициализация матрицы смежности нулями
void init_graph(int graph[MAX_USERS][MAX_USERS], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            graph[i][j] = 0;
        }
    }
}

// Копирование одной матрицы в другую
void copy_matrix(int src[MAX_USERS][MAX_USERS], int dst[MAX_USERS][MAX_USERS], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dst[i][j] = src[i][j];
        }
    }
}

// Вывод матрицы в консоль
void print_matrix(int matrix[MAX_USERS][MAX_USERS], int n, const char* title) {
    printf("\n%s:\n", title);
    printf("   ");
    for (int i = 0; i < n; i++) {
        printf("%3d", i);
    }
    printf("\n");
    
    for (int i = 0; i < n; i++) {
        printf("%2d:", i);
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == INF) {
                printf("  ∞");
            } else {
                printf("%3d", matrix[i][j]);
            }
        }
        printf("\n");
    }
}

#endif
