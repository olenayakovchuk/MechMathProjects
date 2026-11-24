#include <stdio.h>

static double leaky_relu(double x, double a) {
    return (x < 0.0) ? (a * x) : x;
}

static double leaky_relu_derivative(double x, double a) {
    return (x < 0.0) ? a : 1.0;
}

int main(void) {
    double x, a;
    printf("Enter x and parameter a: ");
    if (scanf("%lf %lf", &x, &a) != 2) {
        printf("Invalid input.\n");
        return 1;
    }

    printf("leakyReLu(%.4f, %.4f)  = %.6f\n", x, a, leaky_relu(x, a));
    printf("leakyReLu'(%.4f, %.4f) = %.6f\n", x, a, leaky_relu_derivative(x, a));
    return 0;
}