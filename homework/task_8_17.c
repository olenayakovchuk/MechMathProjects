#include <stdio.h>

#define MAX_N 50

int main(void) {
    int n;
    printf("Enter n (matrix size will be 2*n + 1, 1 <= n <= %d): ", MAX_N);
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX_N) {
        printf("Invalid n.\n");
        return 1;
    }

    int size = 2 * n + 1;
    double a[MAX_N * 2 + 1][MAX_N * 2 + 1];
    double res[MAX_N * 2 + 1][MAX_N * 2 + 1];

    printf("Enter %d x %d matrix elements:\n", size, size);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (scanf("%lf", &a[i][j]) != 1) {
                printf("Invalid input.\n");
                return 1;
            }
            res[i][j] = a[i][j];
        }
    }

    /* Поворачиваем каждый из 4 треугольных секторов, ограниченных диагоналями, на 90° */
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            int on_main = (i == j);
            int on_sec = (i + j == size - 1);
            if (on_main || on_sec) {
                continue;
            }
            /* Поворот координат (i, j) в матрице size x size на 90° по часовой стрелке: (j, size - 1 - i) */
            res[j][size - 1 - i] = a[i][j];
        }
    }

    printf("\nResult matrix:\n");
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            printf("%8.2f", res[i][j]);
        }
        printf("\n");
    }
    return 0;
}