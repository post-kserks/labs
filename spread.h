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
// Запускаем распространение от каждого пользователя и учитываем скорость распространения
void find_influencers(int graph[MAX_USERS][MAX_USERS], int n) {
    printf("\nОпределение ключевых инфлюенсеров...\n");
    printf("(запускаем симуляцию от каждого пользователя)\n\n");

    struct Influencer {
        int user;      // номер пользователя
        int total;     // общее количество охваченных
        int steps;     // количество шагов до стабилизации (меньше = быстрее)
    };
    Influencer inf[MAX_USERS];

    // Тестируем каждого пользователя как начального
    for (int i = 0; i < n; i++) {
        int steps_arr[MAX_USERS] = {0};
        int total = simulate_spread(graph, n, i, steps_arr);
        // определяем последний шаг, когда произошли новые заражения
        int last_step = 0;
        for (int s = 0; s < MAX_USERS; s++) {
            if (steps_arr[s] > 0) last_step = s;
        }
        inf[i] = {i, total, last_step};
    }

    // Сортируем инфлюенсеров: сначала по меньшему количеству шагов, затем по большему охвату
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            bool better = false;
            if (inf[j].steps < inf[i].steps) {
                better = true;
            } else if (inf[j].steps == inf[i].steps && inf[j].total > inf[i].total) {
                better = true;
            }
            if (better) {
                Influencer tmp = inf[i];
                inf[i] = inf[j];
                inf[j] = tmp;
            }
        }
    }

    // Выводим всех инфлюенсеров
    printf("Список инфлюенсеров (по скорости распространения, затем охвату):\n");
    for (int rank = 0; rank < n; rank++) {
        Influencer cur = inf[rank];
        printf("  %d. Пользователь %d - охват %d человек (%.1f%%), шагов %d\n",
               rank + 1, cur.user, cur.total, 100.0 * cur.total / n, cur.steps);
    }
}

#endif
