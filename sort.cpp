#include "sort.h"
#include <algorithm>

// ---------- Сортировка выбором ----------
void selectionSort(std::vector<int>& A) {
    int n = A.size();
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (A[j] < A[minIndex]) {
                minIndex = j;
            }
        }
        std::swap(A[i], A[minIndex]);
    }
}

// ---------- Пузырьковая сортировка ----------
void bubbleSort(std::vector<int>& A) {
    int n = A.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = n - 1; j > i; j--) {
            if (A[j] < A[j - 1]) {
                std::swap(A[j], A[j - 1]);
            }
        }
    }
}

// ---------- Merge (по картинке 7) ----------
static void Merge(std::vector<int>& A, int p, int q, int r) {
    int n1 = q - p + 1;
    int n2 = r - q;
    std::vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++) L[i] = A[p + i];
    for (int j = 0; j < n2; j++) R[j] = A[q + 1 + j];

    int i = 0, j = 0, k = p;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            A[k] = L[i];
            i++;
        } else {
            A[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) A[k++] = L[i++];
    while (j < n2) A[k++] = R[j++];
}

// ---------- MergeSort (по картинке 9) ----------
static void MergeSortRec(std::vector<int>& A, int p, int r) {
    if (p < r) {
        int q = (p + r) / 2;
        MergeSortRec(A, p, q);
        MergeSortRec(A, q + 1, r);
        Merge(A, p, q, r);
    }
}

void mergeSort(std::vector<int>& A) {
    if (!A.empty())
        MergeSortRec(A, 0, A.size() - 1);
}
