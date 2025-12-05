#ifndef FLOYD_H
#define FLOYD_H

#include "graph.h"

// Алгоритм Флойда-Уоршелла для поиска кратчайших путей между всеми парами вершин
// Возвращает матрицу расстояний
void floyd_warshall(int graph[MAX_USERS][MAX_USERS], int dist[MAX_USERS][MAX_USERS], int n) {
    // Инициализация: копируем граф в матрицу расстояний
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                dist[i][j] = 0;  // Расстояние до себя = 0
            } else if (graph[i][j]) {
                dist[i][j] = 1;  // Есть прямая связь
            } else {
                dist[i][j] = INF;  // Нет связи
            }
        }
    }
    
    // Основной алгоритм: для каждой промежуточной вершины k
    // пытаемся улучшить путь между i и j
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    if (dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }
    }
}

#endif
