#include <math.h>
#include <stdio.h>

int main(void) {
    int n;
    double x;
    printf("Enter n (>= 0) and x (0 < x < 1): ");
    if (scanf("%d %lf", &n, &x) != 2 || n < 0 || x <= 0.0 || x >= 1.0) {
        printf("Invalid input.\n");
        return 1;
    }

    double sum = 0.0;
    for (int k = 0; k <= n; ++k) {
        sum += k * pow(x, k) * pow(1.0 - x, n - k);
    }

    printf("Sum = %.8f\n", sum);
    return 0;
}