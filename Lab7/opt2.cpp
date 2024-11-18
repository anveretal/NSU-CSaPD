#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <xmmintrin.h>
#include <cmath>

using namespace std;

// Умножение матриц A и B
void mulMatrices(const float *A, const float *B, float *result, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            __m128 sum = _mm_setzero_ps();
            for (int k = 0; k < N; k += 4) {
                __m128 a = _mm_loadu_ps(&A[i * N + k]);
                __m128 b = _mm_set_ps(B[(k + 3) * N + j], B[(k + 2) * N + j], B[(k + 1) * N + j], B[k * N + j]);
                sum = _mm_add_ps(sum, _mm_mul_ps(a, b));
            }
            float partial_sum[4];
            _mm_storeu_ps(partial_sum, sum);
            result[i * N + j] = partial_sum[0] + partial_sum[1] + partial_sum[2] + partial_sum[3];
        }
    }
}

// Сложение матриц A и B
void addMatrices(const float *A, const float *B, float *result, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j += 4) {
            __m128 a = _mm_loadu_ps(&A[i * N + j]);
            __m128 b = _mm_loadu_ps(&B[i * N + j]);
            __m128 sum = _mm_add_ps(a, b);
            _mm_storeu_ps(&result[i * N + j], sum);
        }
    }
}

// Вычитание матриц A и B
void subMatrices(const float *A, const float *B, float *result, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j += 4) {
            __m128 a = _mm_loadu_ps(&A[i * N + j]);
            __m128 b = _mm_loadu_ps(&B[i * N + j]);
            __m128 diff = _mm_sub_ps(a, b);
            _mm_storeu_ps(&result[i * N + j], diff);
        }
    }
}

void invertMatrix(const float *A, float *A_inv, int N, int M) {
    // Нормы ||A||_1 и ||A||_inf
    float norm_1 = 0, norm_inf = 0;
    for (int i = 0; i < N; i++) {
        float row_sum = 0, col_sum = 0;
        for (int j = 0; j < N; j++) {
            row_sum += fabs(A[i * N + j]);
            col_sum += fabs(A[j * N + i]);
        }
        norm_inf = max(norm_inf, row_sum);
        norm_1 = max(norm_1, col_sum);
    }

    // Инициализация B и I
    float B_coef = 1.0f / (norm_1 * norm_inf);
    vector<float> B(N * N, 0.0f);
    vector<float> I(N * N, 0.0f);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            B[i * N + j] = A[j * N + i] * B_coef; // B = A^T / (||A||_1 * ||A||_inf)
        }
        I[i * N + i] = 1.0f;
    }

    // R = I - BA
    vector<float> R(N * N, 0.0f);
    vector<float> BA(N * N, 0.0f);
    mulMatrices(B.data(), A, BA.data(), N);
    subMatrices(I.data(), BA.data(), R.data(), N);

    // Итерационный процесс
    copy(B.begin(), B.end(), A_inv);
    vector<float> R_pow = I;

    vector<float> temp(N * N, 0.0f);
    for (int m = 1; m <= M; m++) {
        mulMatrices(R_pow.data(), R.data(), temp.data(), N);
        R_pow.swap(temp);
        mulMatrices(R_pow.data(), B.data(), temp.data(), N);
        addMatrices(A_inv, temp.data(), A_inv, N);
    }
}

int main(int argc, char *argv[]) {

    if (argc < 3) {
        cerr << "Too few arguments!" << endl;
    }

    int N = stoi(string(argv[1]));
    int M = stoi(string(argv[2]));

    vector<float> A = {
        4, 1, 2, 3,
        3, 4, 1, 2,
        2, 3, 4, 1,
        1, 2, 3, 4
    };

    vector<float> A_inv(N * N, 0.0f);

    auto start = chrono::high_resolution_clock::now();
    invertMatrix(A.data(), A_inv.data(), N, M);
    auto end = chrono::high_resolution_clock::now();

    cout << "Вычисление обратной матрицы успешно выполнено (SSE)." << endl;
    cout << "Время выполнения: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms\n" << endl;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << A_inv[i * N + j] << ' ';
        }
        cout << endl;
    }
    return 0;
}