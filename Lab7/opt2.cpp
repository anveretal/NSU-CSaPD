#include <iostream>
#include <vector>
#include <xmmintrin.h>

using Matrix = std::vector<std::vector<float>>;

void multiply_sse(const float* A, const float* B, float* C, int N) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            __m128 sum = _mm_setzero_ps();
            for (int k = 0; k < N; k += 4) {
                __m128 a = _mm_loadu_ps(&A[i * N + k]);
                __m128 b = _mm_loadu_ps(&B[k * N + j]);
                sum = _mm_add_ps(sum, _mm_mul_ps(a, b));
            }
            float partial_sum[4];
            _mm_storeu_ps(partial_sum, sum);
            C[i * N + j] = partial_sum[0] + partial_sum[1] + partial_sum[2] + partial_sum[3];
        }
    }
}

int main() {
    int N = 2048;
    std::vector<float> A(N * N, 1.0f);
    std::vector<float> B(N * N, 2.0f);
    std::vector<float> C(N * N, 0.0f);

    multiply_sse(A.data(), B.data(), C.data(), N);

    std::cout << "Matrix multiplication completed (SSE)." << std::endl;
    return 0;
}