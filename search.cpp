#include "search.h"

// ---------- Последовательный поиск ----------
int linearSearch(const std::vector<int>& A, int key) {
    for (int i = 0; i < A.size(); i++) {
        if (A[i] == key)
            return i;
    }
    return -1;
}

// ---------- Бинарный поиск ----------
int binarySearch(const std::vector<int>& A, int key) {
    int left = 0;
    int right = A.size() - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (A[mid] == key)
            return mid;
        else if (A[mid] < key)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}
