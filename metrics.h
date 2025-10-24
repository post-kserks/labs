#ifndef METRICS_H
#define METRICS_H

#include <iostream>

struct CacheMetrics {
    size_t hits = 0;
    size_t misses = 0;
    size_t total_operations = 0;

    void record_hit() {
        hits++;
        total_operations++;
    }

    void record_miss() {
        misses++;
        total_operations++;
    }

    double hit_rate() const {
        return total_operations > 0 ? (static_cast<double>(hits) / total_operations) * 100.0 : 0.0;
    }

    double miss_rate() const {
        return total_operations > 0 ? (static_cast<double>(misses) / total_operations) * 100.0 : 0.0;
    }

    void print() const {
        std::cout << "Hits: " << hits << ", Misses: " << misses
                  << ", Hit Rate: " << hit_rate() << "%, Miss Rate: " << miss_rate() << "%\n";
    }
};

#endif
