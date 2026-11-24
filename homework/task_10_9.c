#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double mass;
    double volume;
} Item;

int main(void) {
    int n;
    printf("Enter number of items N: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid N.\n");
        return 1;
    }

    Item* items = (Item*)malloc((size_t)n * sizeof(Item));
    if (!items) return 1;

    int best_idx = 0;
    double max_density = -1.0;

    for (int i = 0; i < n; ++i) {
        printf("Item %d (mass volume>0): ", i + 1);
        if (scanf("%lf %lf", &items[i].mass, &items[i].volume) != 2 || items[i].volume <= 0.0) {
            printf("Invalid item data.\n");
            free(items);
            return 1;
        }
        double density = items[i].mass / items[i].volume;
        if (i == 0 || density > max_density) {
            max_density = density;
            best_idx = i;
        }
    }

    printf("Highest density item: #%d (density = %.6f)\n", best_idx + 1, max_density);
    free(items);
    return 0;
}