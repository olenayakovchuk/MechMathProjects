#include <math.h>
#include <stdio.h>

static double my_tanh(double x) {
    double ex = exp(x);
    double emx = exp(-x);
    return (ex - emx) / (ex + emx);
}

static double my_tanh_derivative(double x) {
    double t = my_tanh(x);
    return 1.0 - t * t;
}

int main(void) {
    double x;
    printf("Enter x: ");
    if (scanf("%lf", &x) != 1) {
        printf("Invalid input.\n");
        return 1;
    }

    printf("th(%.4f)  = %.8f\n", x, my_tanh(x));
    printf("th'(%.4f) = %.8f\n", x, my_tanh_derivative(x));
    return 0;
}