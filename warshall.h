#ifndef WARSHALL_H
#define WARSHALL_H

#include "graph.h"

// Алгоритм Уоршелла для транзитивного замыкания
// Находит все косвенные связи в графе (друзья друзей становятся связанными)
void warshall(int graph[MAX_USERS][MAX_USERS], int n) {
    printf("\n=== ЧАСТЬ 1: ПОСТРОЕНИЕ ГРАФА СВЯЗЕЙ ===\n");
    printf("Применяем алгоритм Уоршелла для транзитивного замыкания...\n");
    
    // Алгоритм: для каждой вершины k проверяем,
    // можно ли добавить путь i -> j через k
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                // Если есть путь i->k и k->j, то добавляем связь i->j
                graph[i][j] = graph[i][j] || (graph[i][k] && graph[k][j]);
            }
        }
    }
    
    print_matrix(graph, n, "Транзитивное замыкание (все связи)");
}

// Определение степени знакомства между двумя пользователями
// Использует BFS (поиск в ширину) для нахождения кратчайшего пути
int familiarity_degree(int graph[MAX_USERS][MAX_USERS], int n, int user1, int user2) {
    if (user1 == user2) return 0;
    if (graph[user1][user2]) return 1;  // Прямая связь
    
    // BFS для поиска кратчайшего пути
    int visited[MAX_USERS] = {0};
    int queue[MAX_USERS];
    int distance[MAX_USERS];
    int front = 0, rear = 0;
    
    // Инициализация
    for (int i = 0; i < n; i++) distance[i] = -1;
    
    queue[rear++] = user1;
    visited[user1] = 1;
    distance[user1] = 0;
    
    while (front < rear) {
        int current = queue[front++];
        
        for (int i = 0; i < n; i++) {
            if (graph[current][i] && !visited[i]) {
                visited[i] = 1;
                distance[i] = distance[current] + 1;
                queue[rear++] = i;
                
                if (i == user2) {
                    return distance[i];
                }
            }
        }
    }
    
    return -1;  // Нет связи
}

// Визуализация графа в текстовом виде
void visualize_graph(int graph[MAX_USERS][MAX_USERS], int n) {
    printf("\nВизуализация социального графа:\n");
    printf("(показаны прямые связи)\n\n");
    
    for (int i = 0; i < n; i++) {
        printf("Пользователь %d связан с: ", i);
        int has_connections = 0;
        for (int j = 0; j < n; j++) {
            if (i != j && graph[i][j]) {
                printf("%d ", j);
                has_connections = 1;
            }
        }
        if (!has_connections) {
            printf("(нет связей)");
        }
        printf("\n");
    }
}

// Демонстрация степени знакомства
void demo_familiarity(int graph[MAX_USERS][MAX_USERS], int n) {
    printf("\nПримеры степени знакомства:\n");
    
    // Несколько примеров
    int pairs[][2] = {{0, 3}, {1, 5}, {2, 7}, {0, 8}};
    int num_pairs = 4;
    
    for (int i = 0; i < num_pairs && pairs[i][0] < n && pairs[i][1] < n; i++) {
        int user1 = pairs[i][0];
        int user2 = pairs[i][1];
        int degree = familiarity_degree(graph, n, user1, user2);
        
        printf("  Пользователи %d и %d: ", user1, user2);
        if (degree == -1) {
            printf("не связаны\n");
        } else if (degree == 0) {
            printf("это один человек\n");
        } else if (degree == 1) {
            printf("прямые друзья\n");
        } else {
            printf("знакомы через %d рукопожатия\n", degree);
        }
    }
}

#endif
