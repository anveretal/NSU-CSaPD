#include <iostream>
#include <x86intrin.h>
#include <limits.h>
#include <iomanip>
   		
const size_t L3_SIZE = 24 * 1024 * 1024;
const size_t L3_ARR_SIZE = L3_SIZE / sizeof(int);

using namespace std;



void initialize_array(int* array, int num_fragments) {
	int fragment_size = L3_ARR_SIZE / num_fragments;
    int index = 0;

    for (int j = 0; j < (num_fragments - 1); j++) {
		index = j * L3_ARR_SIZE;
		for (int i = 0; i < fragment_size; i++) {
            array[index + i] = index + i + L3_ARR_SIZE;
        }
	}
	index = L3_ARR_SIZE * (num_fragments - 1);
	for (int i = 0; i < fragment_size; i++) {
		array[index + i] = i + 1;
    }
	array[index + fragment_size - 1] = 0;
}

size_t measure_access_time(int* array, int array_size, int num_fragments, int iterations) {
    size_t min_duration = INT_MAX;
    int fragment_size = L3_ARR_SIZE;

    int k = 0;

    for (int j = 0; j < iterations; j++) {

		for (int iter = 0; iter < iterations; iter++) {
			for (int i = 0; i < array_size; i++) {
				volatile int temp = array[i];
			}
		}

		size_t start = __rdtsc();
		for (int iter = 0; iter < iterations; iter++) {
			do {
				k = array[k];
			} while (k != 0);
		}
		size_t end = __rdtsc();

		size_t duration = (end - start) / (fragment_size * iterations);
		if (duration < min_duration) {
			min_duration = duration;
        }
    }
	return min_duration;
}

void print_logic() {
    cout << endl;
    cout << "                        L3_ARR_SIZE * 32                    " << endl;
    cout << " <--------------------------------------------------------> " << endl;
    cout << " L3_ARR_SIZE" << endl;
    cout << " <-------->" << endl;
    cout << "||   |     |          |          |          |...|          |" << endl;
    cout << "  <->" << endl;
    cout << "   ^" << endl;
    cout << " L3_ARR_SIZE / num_fragments" << endl;
    cout << endl;
}

int main() {
    int iterations;
    cout << "Введите кол-во итераций: ";
    cin >> iterations;

    print_logic();

    size_t array_size = L3_ARR_SIZE * 32;

    int* array = new int[array_size];

	for (int num_fragments = 1; num_fragments <= 32; num_fragments++) {
		cout << setw(2) << num_fragments << " : ";
		initialize_array(array, num_fragments);
        cout << measure_access_time(array, array_size, num_fragments, iterations) << endl;
   	}

    delete[] array;

    return 0;
}