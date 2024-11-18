#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>

using namespace std;

// Умножение матриц A и B
vector<vector<float>> mulMatrices(const vector<vector<float>>& A, const vector<vector<float>>& B, int N) {
    vector<vector<float>> result(N, vector<float>(N, 0));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return result;
}

// Сложение матриц A и B
vector<vector<float>> addMatrices(const vector<vector<float>>& A, const vector<vector<float>>& B, int N) {
    vector<vector<float>> result(N, vector<float>(N, 0));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            result[i][j] = A[i][j] + B[i][j];
        }
    }
    return result;
}

// Вычитание матриц A - B
vector<vector<float>> subMatrices(const vector<vector<float>>& A, const vector<vector<float>>& B, int N) {
    vector<vector<float>> result(N, vector<float>(N, 0));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            result[i][j] = A[i][j] - B[i][j];
        }
    }
    return result;
}

// Функция для нахождения обратной матрицы
void invertMatrix(const vector<vector<float>>& A, vector<vector<float>>& A_inv, int N, int M) {
    // Нормы ||A||_1 и ||A||_inf
    float norm_1 = 0, norm_inf = 0;
    for (int i = 0; i < N; i++) {
        float row_sum = 0, col_sum = 0;
        for (int j = 0; j < N; j++) {
            row_sum += fabs(A[i][j]);
            col_sum += fabs(A[j][i]);
        }
        norm_inf = max(norm_inf, row_sum);
        norm_1 = max(norm_1, col_sum);
    }

    // Инициализация B и R
    float B_coef = 1.0f / (norm_1 * norm_inf);
    vector<vector<float>> B(N, vector<float>(N, 0));
    vector<vector<float>> R(N, vector<float>(N, 0));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            B[i][j] = A[j][i] * B_coef; // B = A^T / (||A||_1 * ||A||_inf)
        }
    }

    // R = I - BA
    vector<vector<float>> I(N, vector<float>(N, 0));
    for (int i = 0; i < N; i++) {
        I[i][i] = 1.0f;
    }
    R = subMatrices(I, mulMatrices(B, A, N), N);

    // Итерационный процесс
    A_inv = B; // Начальное приближение
    vector<vector<float>> R_pow = I; // R^0 = I
    for (int m = 1; m <= M; m++) {
        R_pow = mulMatrices(R_pow, R, N);             // R^m = R^(m-1) * R
        A_inv = addMatrices(A_inv, mulMatrices(R_pow, B, N), N); // A_inv += R^m * B
    }
}

int main(int argc, char *argv[]) {

    if (argc < 3) {
        cerr << "Too few arguments!" << endl;
    }

    int N = stoi(string(argv[1]));
    int M = stoi(string(argv[2]));

    vector<vector<float>> A = {
        {4, 1, 2, 3},
        {3, 4, 1, 2},
        {2, 3, 4, 1},
        {1, 2, 3, 4}
    };
    vector<vector<float>> A_inv(N, vector<float>(N, 0));

    auto start = chrono::high_resolution_clock::now();
    invertMatrix(A, A_inv, N, M);
    auto end = chrono::high_resolution_clock::now();

    cout << "Вычисление обратной матрицы успешно выполнено." << endl;
    cout << "Время выполнения: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms\n" << endl;

    for (const auto& row : A_inv) {
        for (float val : row)
            cout << val << " ";
        cout << endl;
    }

    return 0;
}
