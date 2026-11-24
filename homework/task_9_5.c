#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static double** alloc_mat(int r, int c) {
    double** m = (double**)malloc((size_t)r * sizeof(double*));
    if (!m) return NULL;
    for (int i = 0; i < r; ++i) {
        m[i] = (double*)calloc((size_t)c, sizeof(double));
        if (!m[i]) {
            for (int k = 0; k < i; ++k) free(m[k]);
            free(m);
            return NULL;
        }
    }
    return m;
}

static void free_mat(double** m, int r) {
    if (!m) return;
    for (int i = 0; i < r; ++i) free(m[i]);
    free(m);
}

static int calc_rank(double** a, int r, int c) {
    double** m = alloc_mat(r, c);
    if (!m) return -1;
    for (int i = 0; i < r; ++i)
        for (int j = 0; j < c; ++j)
            m[i][j] = a[i][j];

    int rank = 0;
    for (int col = 0, row = 0; col < c && row < r; ++col) {
        int piv = row;
        for (int i = row + 1; i < r; ++i) {
            if (fabs(m[i][col]) > fabs(m[piv][col])) piv = i;
        }
        if (fabs(m[piv][col]) < 1e-12) continue;

        double* tmp = m[row];
        m[row] = m[piv];
        m[piv] = tmp;

        for (int i = row + 1; i < r; ++i) {
            double factor = m[i][col] / m[row][col];
            for (int j = col; j < c; ++j) {
                m[i][j] -= factor * m[row][j];
            }
        }
        ++row;
        ++rank;
    }

    free_mat(m, r);
    return rank;
}

static double calc_det(double** a, int n) {
    double** m = alloc_mat(n, n);
    if (!m) return 0.0;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            m[i][j] = a[i][j];

    double det = 1.0;
    for (int i = 0; i < n; ++i) {
        int piv = i;
        for (int r = i + 1; r < n; ++r) {
            if (fabs(m[r][i]) > fabs(m[piv][i])) piv = r;
        }
        if (fabs(m[piv][i]) < 1e-12) {
            free_mat(m, n);
            return 0.0;
        }
        if (piv != i) {
            double* tmp = m[i];
            m[i] = m[piv];
            m[piv] = tmp;
            det = -det;
        }
        det *= m[i][i];
        for (int r = i + 1; r < n; ++r) {
            double factor = m[r][i] / m[i][i];
            for (int c = i; c < n; ++c) {
                m[r][c] -= factor * m[i][c];
            }
        }
    }

    free_mat(m, n);
    return det;
}

int main(void) {
    int rows, cols;
    printf("Enter rows and cols: ");
    if (scanf("%d %d", &rows, &cols) != 2 || rows <= 0 || cols <= 0) {
        printf("Invalid dimensions.\n");
        return 1;
    }

    double** mat = alloc_mat(rows, cols);
    if (!mat) return 1;

    printf("Enter integer matrix elements:\n");
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            long long v;
            if (scanf("%lld", &v) != 1) {
                free_mat(mat, rows);
                return 1;
            }
            mat[i][j] = (double)v;
        }
    }

    printf("Rank = %d\n", calc_rank(mat, rows, cols));
    if (rows == cols) {
        printf("Determinant = %.4f\n", calc_det(mat, rows));
    }
    else {
        printf("Determinant is defined only for square matrices.\n");
    }

    free_mat(mat, rows);
    return 0;
}