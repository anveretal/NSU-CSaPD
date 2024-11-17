#include <iostream>
#include <vector>
#include <cblas.h>

using Matrix = std::vector<std::vector<float>>;

void multiply_blas(const float* A, const float* B, float* C, int N) {
    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, N, N, N,
                1.0f, A, N, B, N, 0.0f, C, N);
}

int main() {
    int N = 2048;
    std::vector<float> A(N * N, 1.0f);
    std::vector<float> B(N * N, 2.0f);
    std::vector<float> C(N * N, 0.0f);

    multiply_blas(A.data(), B.data(), C.data(), N);

    std::cout << "Matrix multiplication completed (BLAS)." << std::endl;
    return 0;
}