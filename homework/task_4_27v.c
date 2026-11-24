#include <math.h>
#include <stdio.h>

int main(void) {
    double eps;
    printf("Enter precision eps (> 0): ");
    if (scanf("%lf", &eps) != 1 || eps <= 0.0) {
        printf("Invalid input.\n");
        return 1;
    }

    double radical = sqrt(2.0);
    double prod = radical / 2.0;
    double pi_prev = 2.0 / prod;
    double pi_curr = pi_prev;

    for (int iter = 0; iter < 100000; ++iter) {
        radical = sqrt(2.0 + radical);
        prod *= radical / 2.0;
        pi_curr = 2.0 / prod;
        if (fabs(pi_curr - pi_prev) < eps) {
            break;
        }
        pi_prev = pi_curr;
    }

    printf("pi ~= %.12f\n", pi_curr);
    return 0;
}