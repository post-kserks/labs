#ifndef SPREAD_H
#define SPREAD_H

#include "graph.h"

// Моделирование распространения поста от начального пользователя
// Возвращает количество охваченных пользователей на каждом шаге
int simulate_spread(int graph[MAX_USERS][MAX_USERS], int n, int start_user, int steps[MAX_USERS]) {
    printf("\n=== ЧАСТЬ 3: МОДЕЛИРОВАНИЕ РАСПРОСТРАНЕНИЯ ИНФОРМАЦИИ ===\n");
    printf("Начальный пользователь: %d\n\n", start_user);
    
    int infected[MAX_USERS] = {0};  // Кто уже видел пост
    int new_infected[MAX_USERS] = {0};  // Кто увидит на следующем шаге
    
    infected[start_user] = 1;
    int total_reached = 1;
    int step = 0;
    steps[step] = 1;
    
    printf("Шаг 0: пост опубликован пользователем %d\n", start_user);
    printf("  Охват: 1 человек\n");
    
    // Симуляция распространения волнами
    int changed = 1;
    while (changed && step < MAX_USERS - 1) {
        changed = 0;
        step++;
        
        // Каждый зараженный распространяет пост своим друзьям
        for (int i = 0; i < n; i++) {
            if (infected[i]) {
                for (int j = 0; j < n; j++) {
                    if (graph[i][j] && !infected[j] && !new_infected[j]) {
                        new_infected[j] = 1;
                        changed = 1;
                    }
                }
            }
        }
        
        // Применяем новые заражения
        int new_count = 0;
        for (int i = 0; i < n; i++) {
            if (new_infected[i]) {
                infected[i] = 1;
                new_infected[i] = 0;
                new_count++;
                total_reached++;
            }
        }
        
        if (new_count > 0) {
            steps[step] = new_count;
            printf("Шаг %d: пост распространился к %d новым пользователям\n", step, new_count);
            printf("  Общий охват: %d человек\n", total_reached);
        }
    }
    
    return total_reached;
}

// Анализ скорости охвата аудитории
void analyze_spread_speed(int total_reached, int n, int num_steps) {
    printf("\nАнализ скорости охвата:\n");
    printf("  Всего пользователей в сети: %d\n", n);
    printf("  Охвачено: %d (%.1f%%)\n", total_reached, 100.0 * total_reached / n);
    printf("  Количество шагов: %d\n", num_steps);
    if (num_steps > 0) {
        printf("  Средняя скорость: %.2f человек/шаг\n", (double)total_reached / num_steps);
    }
}

// Определение ключевых инфлюенсеров
// Запускаем распространение от каждого пользователя и смотрим, кто охватывает больше всего
void find_influencers(int graph[MAX_USERS][MAX_USERS], int n) {
    printf("\nОпределение ключевых инфлюенсеров...\n");
    printf("(запускаем симуляцию от каждого пользователя)\n\n");
    
    int reach[MAX_USERS];
    
    // Тестируем каждого пользователя как начального
    for (int i = 0; i < n; i++) {
        int infected[MAX_USERS] = {0};
        int new_infected[MAX_USERS] = {0};
        
        infected[i] = 1;
        int total = 1;
        
        int changed = 1;
        while (changed) {
            changed = 0;
            
            for (int j = 0; j < n; j++) {
                if (infected[j]) {
                    for (int k = 0; k < n; k++) {
                        if (graph[j][k] && !infected[k] && !new_infected[k]) {
                            new_infected[k] = 1;
                            changed = 1;
                        }
                    }
                }
            }
            
            for (int j = 0; j < n; j++) {
                if (new_infected[j]) {
                    infected[j] = 1;
                    new_infected[j] = 0;
                    total++;
                }
            }
        }
        
        reach[i] = total;
    }
    
    // Находим топ-3 инфлюенсера
    printf("Топ инфлюенсеров (по максимальному охвату):\n");
    for (int rank = 0; rank < 3 && rank < n; rank++) {
        int max_reach = -1;
        int max_user = -1;
        
        for (int i = 0; i < n; i++) {
            if (reach[i] > max_reach) {
                max_reach = reach[i];
                max_user = i;
            }
        }
        
        if (max_user != -1) {
            printf("  %d. Пользователь %d - охват %d человек (%.1f%%)\n", 
                   rank + 1, max_user, max_reach, 100.0 * max_reach / n);
            reach[max_user] = -1;  // Исключаем из следующего поиска
        }
    }
}

#endif
