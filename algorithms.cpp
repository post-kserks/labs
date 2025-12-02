// algorithms.cpp
// Реализация алгоритмов: value, hill climbing, simulated annealing, beam search
// Комментарии на русском языке.

#include "algorithms.h"
#include "data.h"
#include <algorithm>
#include <random>
#include <chrono>
#include <cmath>
#include <set>
#include <iostream>
#include <sstream>

// Random engine
static std::mt19937 rng((unsigned)std::chrono::high_resolution_clock::now().time_since_epoch().count());

// --- Вспомогательные функции ---

// Возвращает количество нарушений пререквизитов.
// Для каждой пары (a->b) если a стоит после b в последовательности => нарушение.
static int count_prereq_violations(const std::vector<int>& seq) {
    int n = (int)seq.size();
    std::vector<int> pos(n);
    for (int i = 0; i < n; ++i) pos[seq[i]] = i;
    int violations = 0;
    for (int a = 0; a < n; ++a) {
        for (int b = 0; b < n; ++b) {
            if (PREREQ_MATRIX[a][b]) {
                if (pos[a] > pos[b]) violations++;
            }
        }
    }
    return violations;
}

// Возвращает measure того, насколько порядок отличается от канонического.
// Считаем количество пар (i,j) которые в seq идут в другом порядке, чем в CANONICAL.
// Чем больше — тем более "инновационно" (отличие от стандартного порядка).
static int canonical_disagreement(const std::vector<int>& seq) {
    int n = (int)seq.size();
    std::vector<int> pos(n);
    for (int i = 0; i < n; ++i) pos[CANONICAL[i]] = i;
    int disagreements = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i+1; j < n; ++j) {
            int a = seq[i], b = seq[j];
            if (pos[a] > pos[b]) disagreements++;
        }
    }
    return disagreements;
}

// Конвертация последовательности в строку с названиями тем
std::string seq_to_string(const std::vector<int>& seq) {
    std::ostringstream oss;
    for (size_t i = 0; i < seq.size(); ++i) {
        if (i) oss << " -> ";
        oss << TOPICS[seq[i]];
    }
    return oss.str();
}

// --- Value function ---
// Большая оценка = лучше. Комбинация: -violations * w_coherence + disagreements * w_novelty
double value_sequence(const std::vector<int>& seq, double w_coherence, double w_novelty) {
    int violations = count_prereq_violations(seq);
    int disagreements = canonical_disagreement(seq);
    double val = - (double)violations * w_coherence + (double)disagreements * w_novelty;
    return val;
}

// --- Hill Climbing ---
// Простая реализация: начинаем с initial, пробуем случайные соседние перестановки (swap двух элементов).
// Если найден сосед с лучшей value — переходим. Повторяем max_iters итераций или пока нет улучшения.
// Для детерминизма можно заменить начальное состояние на CANONICAL.
std::vector<int> hill_climbing(const std::vector<int>& initial, int max_iters, double w_coherence, double w_novelty) {
    std::vector<int> current = initial;
    double current_val = value_sequence(current, w_coherence, w_novelty);

    for (int iter = 0; iter < max_iters; ++iter) {
        bool improved = false;

        // Перебираем всех соседей путем одиночных swap (в минимальном варианте случайная выборка)
        // Для компактности пробуем k случайных swap'ов
        int k = 50; // пробуем 50 случайных соседей на итерацию
        for (int t = 0; t < k; ++t) {
            std::vector<int> neighbor = current;
            int n = (int)neighbor.size();
            int i = std::uniform_int_distribution<int>(0,n-1)(rng);
            int j = std::uniform_int_distribution<int>(0,n-1)(rng);
            if (i == j) continue;
            std::swap(neighbor[i], neighbor[j]);
            double v = value_sequence(neighbor, w_coherence, w_novelty);
            if (v > current_val) {
                current = neighbor;
                current_val = v;
                improved = true;
                break; // жадный переход
            }
        }

        if (!improved) break; // достигнут локальный максимум
    }

    return current;
}

// --- Simulated Annealing ---
// Простая температура: линейное уменьшение от start_temp до end_temp по итерациям.
// На каждой итерации генерируем случайный сосед (swap двух позиций), считаем Δ = val_new - val_old.
// Если Δ>0 — принимаем, иначе — принимаем с prob = exp(Δ / T) (Δ отрицательно -> small prob).
std::vector<int> simulated_annealing(const std::vector<int>& initial, int max_iters, double start_temp, double end_temp, double w_coherence, double w_novelty) {
    std::vector<int> current = initial;
    double current_val = value_sequence(current, w_coherence, w_novelty);
    std::vector<int> best = current;
    double best_val = current_val;

    for (int iter = 1; iter <= max_iters; ++iter) {
        double frac = (double)(iter-1) / (double)std::max(1, max_iters-1);
        double T = start_temp + frac * (end_temp - start_temp); // линейный
        // генерируем сосед
        std::vector<int> neighbor = current;
        int n = (int)neighbor.size();
        int i = std::uniform_int_distribution<int>(0,n-1)(rng);
        int j = std::uniform_int_distribution<int>(0,n-1)(rng);
        if (i == j) j = (j+1)%n;
        std::swap(neighbor[i], neighbor[j]);
        double v = value_sequence(neighbor, w_coherence, w_novelty);
        double delta = v - current_val;
        if (delta > 0) {
            current = neighbor; current_val = v;
        } else {
            double prob = std::exp(delta / std::max(1e-9, T));
            double r = std::uniform_real_distribution<double>(0.0,1.0)(rng);
            if (r < prob) {
                current = neighbor; current_val = v;
            }
        }
        if (current_val > best_val) {
            best = current; best_val = current_val;
        }
    }
    return best;
}

// --- Beam Search ---
// Простая реализация: состояние — частичная последовательность (перестановка без повторов).
// Изначально пустая последовательность. На каждом шаге расширяем каждый path добавлением одного из оставшихся элементов.
// После расширения всех путей, оставляем только beta лучших partial путей по value (используем value частичной последовательности,
// где мы оцениваем только имеющиеся позиции; для удобства дополняем недостающие элементы каноническим порядком при оценке).
static double score_partial(const std::vector<int>& partial, double w_coherence, double w_novelty) {
    // Для оценки частичной последовательности создадим "полную" последовательность:
    // оставшиеся элементы добавим в конце в порядке CANONICAL для честной оценки coherence.
    int n = (int)TOPICS.size();
    std::vector<bool> used(n,false);
    for (int x : partial) used[x] = true;
    std::vector<int> full = partial;
    for (int idx : CANONICAL) {
        if (!used[idx]) full.push_back(idx);
    }
    return value_sequence(full, w_coherence, w_novelty);
}

std::vector<std::vector<int>> beam_search(int beta, double w_coherence, double w_novelty) {
    using Path = std::vector<int>;
    std::vector<Path> beam;
    beam.push_back(Path()); // пустой путь

    int n = (int)TOPICS.size();
    for (int depth = 0; depth < n; ++depth) {
        std::vector<std::pair<double, Path>> candidates;
        for (const Path& p : beam) {
            // какие элементы ещё не использованы?
            std::vector<bool> used(n,false);
            for (int x : p) used[x] = true;
            for (int x = 0; x < n; ++x) {
                if (used[x]) continue;
                Path np = p;
                np.push_back(x);
                double sc = score_partial(np, w_coherence, w_novelty);
                candidates.emplace_back(sc, np);
            }
        }
        // оставляем beta лучших
        std::sort(candidates.begin(), candidates.end(), [](auto &a, auto &b){ return a.first > b.first; });
        beam.clear();
        for (int i = 0; i < (int)std::min((int)candidates.size(), beta); ++i) {
            beam.push_back(candidates[i].second);
        }
    }
    // beam содержит beta полных путей — возвращаем их
    return beam;
}
