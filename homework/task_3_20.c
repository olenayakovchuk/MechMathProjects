#include <stdio.h>

static double cross(double x1, double y1, double x2, double y2, double px, double py) {
    return (x2 - x1) * (py - y1) - (y2 - y1) * (px - x1);
}

static int point_in_triangle(double x1, double y1,
    double x2, double y2,
    double x3, double y3,
    double px, double py) {
    double d1 = cross(x1, y1, x2, y2, px, py);
    double d2 = cross(x2, y2, x3, y3, px, py);
    double d3 = cross(x3, y3, x1, y1, px, py);

    int has_neg = (d1 < 0.0) || (d2 < 0.0) || (d3 < 0.0);
    int has_pos = (d1 > 0.0) || (d2 > 0.0) || (d3 > 0.0);
    return !(has_neg && has_pos);
}

int main(void) {
    double x1, y1, x2, y2, x3, y3, px, py;
    printf("Enter vertices A(x1 y1), B(x2 y2), C(x3 y3): ");
    if (scanf("%lf %lf %lf %lf %lf %lf", &x1, &y1, &x2, &y2, &x3, &y3) != 6) {
        printf("Invalid input.\n");
        return 1;
    }
    printf("Enter point P(x y): ");
    if (scanf("%lf %lf", &px, &py) != 2) {
        printf("Invalid input.\n");
        return 1;
    }

    if (point_in_triangle(x1, y1, x2, y2, x3, y3, px, py)) {
        printf("Point is INSIDE (or on the boundary of) the triangle.\n");
    }
    else {
        printf("Point is OUTSIDE the triangle.\n");
    }
    return 0;
}