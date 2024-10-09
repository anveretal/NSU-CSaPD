#include <stdio.h>

double pi_f(int n) {
    double pi  = 0;
    int    pow = 1;
    int    d   = 1;
    for (int i = 0; i < n; i++) {
        pi += pow * ((double)4 / d);
        d += 2;
        pow *= -1;
    }
    return pi;
}

int main(int argc, char **argv) {
    printf("Input n: ");

    int n;
    scanf("%d", &n);

    printf("Answer: %0.14f\n", pi_f(n));

    return 0;
}
