import numpy as np

# Создание матриц A и B
A = np.array([[1, 2, 3],
              [4, 5, 6],
              [7, 8, 9]])

B = np.array([[9, 8, 7],
              [6, 5, 4],
              [3, 2, 1]])

print("Матрица A:")
print(A)
print("\nМатрица B:")
print(B)

# Умножение матриц с помощью numpy.dot()
C_dot = np.dot(A, B)
print("\nРезультат умножения (np.dot()):")
print(C_dot)

# Умножение матриц с помощью numpy.matmul()
C_matmul = np.matmul(A, B)
print("\nРезультат умножения (np.matmul()):")
print(C_matmul)

# Умножение матриц с помощью оператора @
C_operator = A @ B
print("\nРезультат умножения (A @ B):")
print(C_operator)

# Проверка идентичности результатов
print("\nВсе результаты идентичны:",
      np.array_equal(C_dot, C_matmul) and np.array_equal(C_matmul, C_operator))

# Вычисление вычислительной сложности
n = A.shape[0]
print(f"\nВычислительная сложность стандартного алгоритма: O(n³) = O({n}³) = {n**3} операций")
