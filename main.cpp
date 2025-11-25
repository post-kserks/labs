#include <algorithm>
#include <random>

#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include "algorithms.h"
#include "data.h"

int main(int argc, char** argv) {
    std::cout << "lab9 — составление учебных планов\n";
    std::cout << "Доступные режимы: hc, beam, sa\n";
    std::cout << "Пример: ./lab9 hc\n\n";

    std::string mode = "hc";
    if (argc >= 2) mode = argv[1];

    // Начальное состояние: возьмём канонический порядок как старт для HC и Beam,
    // для SA запустим и от канонического, и от случайного внутри функции.
    std::vector<int> initial = CANONICAL;

    if (mode == "hc") {
        std::cout << "[HC] Hill Climbing — строит логичную последовательность без инноваций\n";
        // HC: сильный вес за coherence, малый/отрицательный за novelty
        double w_coh = 5.0;
        double w_nov = -0.1;
        int max_iters = 200;
        auto start = std::chrono::high_resolution_clock::now();
        std::vector<int> res = hill_climbing(initial, max_iters, w_coh, w_nov);
        auto end = std::chrono::high_resolution_clock::now();
        std::cout << "Результат HC:\n" << seq_to_string(res) << "\n";
        std::cout << "Value: " << value_sequence(res, w_coh, w_nov) << "\n";
        std::cout << "Время (ms): " << std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count() << "\n";
    }
    else if (mode == "beam") {
        std::cout << "[Beam] Beam Search — создаёт несколько альтернативных учебных планов\n";
        int beta = 3; // ширина луча — сколько альтернатив хотим
        double w_coh = 2.0;
        double w_nov = 0.5; // даём небольшую свободу инновации
        auto start = std::chrono::high_resolution_clock::now();
        auto plans = beam_search(beta, w_coh, w_nov);
        auto end = std::chrono::high_resolution_clock::now();
        std::cout << "Найдено " << plans.size() << " план(а/ов):\n";
        for (size_t i = 0; i < plans.size(); ++i) {
            std::cout << i+1 << ") " << seq_to_string(plans[i]) << "\n";
            double v = value_sequence(plans[i], w_coh, w_nov);
            std::cout << "   Value: " << v << "\n";
        }
        std::cout << "Время (ms): " << std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count() << "\n";
    }
    else if (mode == "sa") {
        std::cout << "[SA] Simulated Annealing — ищет инновационные подходы\n";
        // SA: меньше штрафа за нарушения, положительный бонус за novelty
        double w_coh = 1.5;
        double w_nov = 1.0;
        int max_iters = 2000;
        double start_temp = 1.0;
        double end_temp = 0.001;
        // Для устойчивости выполним несколько запусков и покажем лучший
        std::vector<int> best_overall;
        double best_val = -1e18;
        int runs = 4;
        for (int r = 0; r < runs; ++r) {
            // начальное состояние: немного перемешаем канонический порядок для разнообразия
            std::vector<int> start_seq = CANONICAL;
            // небольшая случайная перестановка
            if (r > 0) {
                std::shuffle(start_seq.begin(), start_seq.end(), std::mt19937((unsigned)r*13 + 7));
            }
            std::vector<int> result = simulated_annealing(start_seq, max_iters, start_temp, end_temp, w_coh, w_nov);
            double v = value_sequence(result, w_coh, w_nov);
            std::cout << "Run " << r+1 << ": " << seq_to_string(result) << "   Value=" << v << "\n";
            if (v > best_val) {
                best_val = v;
                best_overall = result;
            }
        }
        std::cout << "\nЛучший найденный SA-план:\n" << seq_to_string(best_overall) << "\n";
        std::cout << "Value: " << best_val << "\n";
    }
    else {
        std::cout << "Неизвестный режим: " << mode << "\n";
        std::cout << "Используйте: hc | beam | sa\n";
    }

    return 0;
}
