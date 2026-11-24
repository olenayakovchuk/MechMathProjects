#include <stdio.h>
#include <stdlib.h>

static void free_matrix(double** mat, int rows) {
    if (!mat) return;
    for (int i = 0; i < rows; ++i) {
        free(mat[i]);
    }
    free(mat);
}

int main(void) {
    int rows, cols;
    printf("Enter rows and cols: ");
    if (scanf("%d %d", &rows, &cols) != 2 || rows <= 0 || cols <= 0) {
        printf("Invalid dimensions.\n");
        return 1;
    }

    double** mat = (double**)malloc((size_t)rows * sizeof(double*));
    if (!mat) return 1;
    for (int i = 0; i < rows; ++i) {
        mat[i] = (double*)malloc((size_t)cols * sizeof(double));
        if (!mat[i]) {
            free_matrix(mat, i);
            return 1;
        }
    }

    printf("Enter matrix elements:\n");
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (scanf("%lf", &mat[i][j]) != 1) {
                free_matrix(mat, rows);
                return 1;
            }
        }
    }

    int keep_cols = 0;
    int* keep = (int*)calloc((size_t)cols, sizeof(int));
    if (!keep) {
        free_matrix(mat, rows);
        return 1;
    }

    for (int j = 0; j < cols; ++j) {
        int all_less_than_one = 1;
        for (int i = 0; i < rows; ++i) {
            if (mat[i][j] >= 1.0) {
                all_less_than_one = 0;
                break;
            }
        }
        if (!all_less_than_one) {
            keep[j] = 1;
            ++keep_cols;
        }
    }

    printf("\nResult (%d rows x %d cols):\n", rows, keep_cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (keep[j]) {
                printf("%8.2f", mat[i][j]);
            }
        }
        printf("\n");
    }

    free(keep);
    free_matrix(mat, rows);
    return 0;
}