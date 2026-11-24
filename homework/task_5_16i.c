#include <math.h>
#include <stdio.h>

int main(void) {
    double x, eps;
    printf("Enter x (|x| < 1) and eps (> 0): ");
    if (scanf("%lf %lf", &x, &eps) != 2 || fabs(x) >= 1.0 || eps <= 0.0) {
        printf("Invalid input.\n");
        return 1;
    }

    double sum = 0.0;
    double term = 1.0; /* k = 0 */
    int k = 0;

    while (fabs(term) >= eps) {
        sum += term;
        ++k;
        /* Рекурентне співвідношення: a_k = -a_{k-1} * x * (k + 2) / k */
        term = -term * x * (double)(k + 2) / (double)k;
    }

    printf("Series sum = %.10f (exact = %.10f)\n", sum, 1.0 / pow(1.0 + x, 3));
    return 0;
}