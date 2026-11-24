#include <math.h>
#include <stdio.h>

static double median_length(double side_to, double other1, double other2) {
    return 0.5 * sqrt(2.0 * other1 * other1 + 2.0 * other2 * other2 - side_to * side_to);
}

int main(void) {
    double a, b, c;
    printf("Enter triangle sides a, b, c: ");
    if (scanf("%lf %lf %lf", &a, &b, &c) != 3 ||
        a <= 0.0 || b <= 0.0 || c <= 0.0 ||
        a + b <= c || a + c <= b || b + c <= a) {
        printf("Invalid triangle sides.\n");
        return 1;
    }

    printf("m_a = %.4f\n", median_length(a, b, c));
    printf("m_b = %.4f\n", median_length(b, a, c));
    printf("m_c = %.4f\n", median_length(c, a, b));
    return 0;
}