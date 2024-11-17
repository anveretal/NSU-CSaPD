#include <iostream>
#include <vector>

using Matrix = std::vector<std::vector<float>>;

Matrix multiply(const Matrix& A, const Matrix& B, int N) {
    Matrix C(N, std::vector<float>(N, 0.0f));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            for (int k = 0; k < N; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

void printMatrix(const Matrix& C, int rows = 5, int cols = 5) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << C[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    int N = 5;
    Matrix A(N, std::vector<float>(N, 1.0f));
    Matrix B(N, std::vector<float>(N, 2.0f));
    Matrix C = multiply(A, B, N);

    std::cout << "Matrix multiplication completed." << std::endl;

    // Вывод первых 5x5 элементов результата
    std::cout << "Sample result (first 5x5 elements):" << std::endl;
    printMatrix(C, 5, 5);

    return 0;
}
