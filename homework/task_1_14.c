#include <stdio.h>

int main(void) {
    double a, t, v;
    printf("Enter acceleration a (> 0), time t (>= 0), target speed v (>= 0): ");
    if (scanf("%lf %lf %lf", &a, &t, &v) != 3 || a <= 0.0 || t < 0.0 || v < 0.0) {
        printf("Invalid input.\n");
        return 1;
    }

    double distance = 0.5 * a * t * t;
    double time_to_v = v / a;

    printf("Distance in %.3f s: %.4f\n", t, distance);
    printf("Time to reach speed %.3f: %.4f s\n", v, time_to_v);
    return 0;
}