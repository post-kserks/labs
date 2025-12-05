#ifndef ANALYSIS_H
#define ANALYSIS_H

#include "graph.h"
#include "floyd.h"
#include <stdlib.h>

// Вычисление центральности пользователей (closeness centrality)
// Чем меньше сумма расстояний до всех других, тем выше центральность
void compute_centrality(int dist[MAX_USERS][MAX_USERS], int n, double centrality[MAX_USERS]) {
    printf("\n=== ЧАСТЬ 2: АНАЛИЗ ВЛИЯНИЯ ===\n");
    printf("Вычисление центральности пользователей...\n\n");
    
    for (int i = 0; i < n; i++) {
        int sum = 0;
        int reachable = 0;
        
        for (int j = 0; j < n; j++) {
            if (i != j && dist[i][j] != INF) {
                sum += dist[i][j];
                reachable++;
            }
        }
        
        // Центральность = количество достижимых / сумма расстояний
        if (sum > 0) {
            centrality[i] = (double)reachable / sum;
        } else {
            centrality[i] = 0;
        }
    }
    
    // Вывод результатов
    printf("Центральность пользователей:\n");
    for (int i = 0; i < n; i++) {
        printf("  Пользователь %d: %.3f", i, centrality[i]);
        if (centrality[i] > 0.8) {
            printf(" (высокая влиятельность)");
        }
        printf("\n");
    }
}

// Поиск "мостов" - ребер, удаление которых разрывает связность
// Упрощенная версия: проверяем критичные связи
void find_bridges(int graph[MAX_USERS][MAX_USERS], int n) {
    printf("\nПоиск 'мостов' в социальной сети...\n");
    printf("(критичные связи, разрыв которых изолирует пользователей)\n\n");
    
    int bridge_count = 0;
    
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (graph[i][j]) {
                // Временно удаляем ребро
                graph[i][j] = 0;
                graph[j][i] = 0;
                
                // Проверяем связность с помощью BFS
                int visited[MAX_USERS] = {0};
                int queue[MAX_USERS];
                int front = 0, rear = 0;
                
                queue[rear++] = 0;
                visited[0] = 1;
                int count = 1;
                
                while (front < rear) {
                    int current = queue[front++];
                    for (int k = 0; k < n; k++) {
                        if (graph[current][k] && !visited[k]) {
                            visited[k] = 1;
                            queue[rear++] = k;
                            count++;
                        }
                    }
                }
                
                // Если не все вершины достижимы, это мост
                if (count < n) {
                    printf("  Связь %d-%d является мостом!\n", i, j);
                    bridge_count++;
                }
                
                // Восстанавливаем ребро
                graph[i][j] = 1;
                graph[j][i] = 1;
            }
        }
    }
    
    if (bridge_count == 0) {
        printf("  Мостов не найдено - сеть хорошо связана\n");
    }
}

// Простая кластеризация: группируем пользователей по близости
void find_clusters(int dist[MAX_USERS][MAX_USERS], int n) {
    printf("\nОпределение сообществ и кластеров...\n");
    printf("(пользователи с расстоянием <= 2 друг от друга)\n\n");
    
    int cluster[MAX_USERS];
    int cluster_id = 0;
    
    for (int i = 0; i < n; i++) cluster[i] = -1;
    
    for (int i = 0; i < n; i++) {
        if (cluster[i] == -1) {
            cluster[i] = cluster_id;
            printf("Кластер %d: %d", cluster_id, i);
            
            // Добавляем близких пользователей
            for (int j = i + 1; j < n; j++) {
                if (dist[i][j] <= 2 && dist[i][j] != INF) {
                    cluster[j] = cluster_id;
                    printf(", %d", j);
                }
            }
            
            printf("\n");
            cluster_id++;
        }
    }
}

// Рекомендательная система друзей (друзья друзей)
void recommend_friends(int graph[MAX_USERS][MAX_USERS], int n, int user) {
    printf("\nРекомендации друзей для пользователя %d:\n", user);
    
    int recommendations[MAX_USERS] = {0};
    
    // Для каждого друга пользователя
    for (int i = 0; i < n; i++) {
        if (graph[user][i] && i != user) {
            // Смотрим на друзей этого друга
            for (int j = 0; j < n; j++) {
                if (graph[i][j] && j != user && !graph[user][j]) {
                    recommendations[j]++;  // Считаем общих друзей
                }
            }
        }
    }
    
    // Сортируем и выводим рекомендации
    int found = 0;
    for (int count = n; count > 0; count--) {
        for (int i = 0; i < n; i++) {
            if (recommendations[i] == count && count > 0) {
                printf("  Пользователь %d (общих друзей: %d)\n", i, count);
                found = 1;
            }
        }
    }
    
    if (!found) {
        printf("  Нет рекомендаций\n");
    }
}

#endif
