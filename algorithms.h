// algorithms.h
// Прототипы функций алгоритмов и хелперов

#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <vector>
#include <string>

// Value function: возвращает оценку последовательности
double value_sequence(const std::vector<int>& seq, double w_coherence, double w_novelty);

// Hill Climbing
std::vector<int> hill_climbing(const std::vector<int>& initial, int max_iters, double w_coherence, double w_novelty);

// Simulated Annealing
std::vector<int> simulated_annealing(const std::vector<int>& initial, int max_iters, double start_temp, double end_temp, double w_coherence, double w_novelty);

// Beam Search (возвращает vector of sequences)
std::vector<std::vector<int>> beam_search(int beta, double w_coherence, double w_novelty);

std::string seq_to_string(const std::vector<int>& seq);

#endif // ALGORITHMS_H
