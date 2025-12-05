#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "warshall.h"
#include "floyd.h"
#include "analysis.h"
#include "spread.h"

int main() {
    printf("╔════════════════════════════════════════════════════════╗\n");
    printf("║                        НАЧАЛО                          ║\n");
    printf("╚════════════════════════════════════════════════════════╝\n");
    
    // Количество пользователей в нашей тестовой сети
    int n = 10;
    
    // Матрица смежности графа (социальные связи)
    int graph[MAX_USERS][MAX_USERS];
    init_graph(graph, n);
    
    // Создаем тестовую социальную сеть
    // 1 означает, что пользователи являются друзьями
    printf("\nСоздание тестовой социальной сети из %d пользователей...\n", n);
    
    // Граф имеет несколько связных компонент для демонстрации
    // Основная группа (0-7)
    graph[0][1] = graph[1][0] = 1;
    graph[0][2] = graph[2][0] = 1;
    graph[1][3] = graph[3][1] = 1;
    graph[2][3] = graph[3][2] = 1;
    graph[3][4] = graph[4][3] = 1;
    graph[4][5] = graph[5][4] = 1;
    graph[4][6] = graph[6][4] = 1;
    graph[5][7] = graph[7][5] = 1;
    graph[6][7] = graph[7][6] = 1;
    
    // Маленькая отдельная группа (8-9)
    graph[8][9] = graph[9][8] = 1;
    
    // Мост между группами
    graph[7][8] = graph[8][7] = 1;
    
    print_matrix(graph, n, "Исходный граф (матрица смежности)");
    
    // ========== ЧАСТЬ 1: ПОСТРОЕНИЕ ГРАФА СВЯЗЕЙ ==========
    
    // Копируем граф для алгоритма Уоршелла
    int transitive[MAX_USERS][MAX_USERS];
    copy_matrix(graph, transitive, n);
    
    // Применяем алгоритм Уоршелла
    warshall(transitive, n);
    
    // Визуализация графа
    visualize_graph(graph, n);
    
    // Демонстрация степени знакомства
    demo_familiarity(graph, n);
    
    // ========== ЧАСТЬ 2: АНАЛИЗ ВЛИЯНИЯ ==========
    
    // Применяем алгоритм Флойда-Уоршелла
    int dist[MAX_USERS][MAX_USERS];
    floyd_warshall(graph, dist, n);
    print_matrix(dist, n, "Матрица кратчайших расстояний (Флойд-Уоршелл)");
    
    // Вычисляем центральность пользователей
    double centrality[MAX_USERS];
    compute_centrality(dist, n, centrality);
    
    // Ищем мосты в графе
    // Внимание: эта функция модифицирует граф временно, но восстанавливает его
    find_bridges(graph, n);
    
    // Кластеризация
    find_clusters(dist, n);
    
    // Рекомендации друзей для пользователя 0
    recommend_friends(graph, n, 0);
    
    // ========== ЧАСТЬ 3: МОДЕЛИРОВАНИЕ РАСПРОСТРАНЕНИЯ ИНФОРМАЦИИ ==========
    
    // Симулируем распространение поста от пользователя 0
    int steps[MAX_USERS];
    int start_user = 0;
    int total_reached = simulate_spread(graph, n, start_user, steps);
    
    // Подсчитываем количество шагов
    int num_steps = 0;
    for (int i = 0; i < MAX_USERS; i++) {
        if (steps[i] > 0) num_steps = i;
    }
    
    // Анализируем скорость охвата
    analyze_spread_speed(total_reached, n, num_steps);
    
    // Находим ключевых инфлюенсеров
    find_influencers(graph, n);
    
    // ========== ЗАВЕРШЕНИЕ ==========
    
    printf("\n╔════════════════════════════════════════════════════════╗\n");
    printf("║                           КОНЕЦ                        ║\n");
    printf("╚════════════════════════════════════════════════════════╝\n");
    
    return 0;
}
