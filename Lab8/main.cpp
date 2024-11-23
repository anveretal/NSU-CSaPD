#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <chrono>
#include <x86intrin.h> // для __rdtsc

using namespace std;

const int MIN_CACHE_INT = 256; // 256 int = 1 KB
const int MAX_CACHE_INT = 32 * 1024 * 1024 / sizeof(int); // 32 MB

void initialize_array(vector<int>& arr, const string& mode) {
    int n = arr.size();

    if (mode == "direct") {
        for (int i = 0; i < n; i++) {
            arr[i] = (i + 1) % n;
        }
    }
    else if (mode == "reverse") {
        for (int i = 0; i < n; i++) {
            arr[i] = (i - 1 + n) % n;
        }
    }
    else if (mode == "random") {
        vector<int> indices(n);
        iota(indices.begin(), indices.end(), 0);

        random_device rd;
        mt19937 gen(rd());
        shuffle(indices.begin(), indices.end(), gen);

        for (int i = 0; i < n; ++i) {
            arr[indices[i]] = indices[(i + 1) % n];
        }
    }
}

void measure_access_time_cycles(const vector<int>& arr, int iterations) {
    uint64_t n = arr.size();
    volatile int k = 0;

    // "Прогрев" кэша
    for (int iter = 0; iter < iterations; iter++) {
        for (int i = 0; i < n; ++i) {
            int temp = arr[i];
        }
    }

    uint64_t start = __rdtsc();
    for (int iter = 0; iter < iterations; iter++) {
        for (int i = 0; i < n; i++) {
            k = arr[k];
        }
    }
    uint64_t end = __rdtsc();
    cout << (end - start) / (n * iterations) << " ";
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Too few arguments!" << endl;
    }
    int iterations = stoi(string(argv[1]));
    
    int i = 0;
    for (int size = 256; size <= MAX_CACHE_INT; size += 256 * i) {
        i++;
        vector<int> arr(size);

        cout << size << ": ";

        // Прямой обход
        initialize_array(arr, "direct");
        measure_access_time_cycles(arr, iterations);

        // Обратный обход
        initialize_array(arr, "reverse");
        measure_access_time_cycles(arr, iterations);

        // Случайный обход
        initialize_array(arr, "random");
        measure_access_time_cycles(arr, iterations);

        cout << endl;
    }

    return 0;
}