#include <stdio.h>
#include <stdlib.h>

typedef struct {
    size_t size;
    double* data;
} Vector;

static int vector_input(Vector* v) {
    printf("Enter vector size: ");
    if (scanf("%zu", &v->size) != 1 || v->size == 0) {
        return 0;
    }
    v->data = (double*)malloc(v->size * sizeof(double));
    if (!v->data) {
        return 0;
    }
    printf("Enter %zu elements: ", v->size);
    for (size_t i = 0; i < v->size; ++i) {
        if (scanf("%lf", &v->data[i]) != 1) {
            free(v->data);
            v->data = NULL;
            return 0;
        }
    }
    return 1;
}

static void vector_print(const Vector* v) {
    printf("Vector (size %zu): [", v->size);
    for (size_t i = 0; i < v->size; ++i) {
        printf("%.4f%s", v->data[i], (i + 1 < v->size) ? ", " : "");
    }
    printf("]\n");
}

int main(void) {
    Vector v = { 0, NULL };
    if (!vector_input(&v)) {
        printf("Input or memory error.\n");
        return 1;
    }
    vector_print(&v);
    free(v.data);
    return 0;
}