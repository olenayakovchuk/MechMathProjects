#include <stdio.h>
#include <string.h>

typedef struct {
    char name[64];
    double price;
    int age_min;
    int age_max;
} Toy;

int main(void) {
    const char* filename = "toys.bin";
    FILE* fp = fopen(filename, "rb");
    if (!fp) {
        printf("Cannot open %s\n", filename);
        return 1;
    }

    char target_name[64];
    printf("Enter target item name: ");
    if (scanf("%63s", target_name) != 1) {
        fclose(fp);
        return 1;
    }

    Toy t;
    int found = 0;
    double max_price = 0.0;

    while (fread(&t, sizeof(Toy), 1, fp) == 1) {
        if (strcmp(t.name, target_name) == 0) {
            if (!found || t.price > max_price) {
                max_price = t.price;
                found = 1;
            }
        }
    }
    fclose(fp);

    if (!found) {
        printf("Item '%s' not found.\n", target_name);
    }
    else {
        printf("Max price for '%s': %.2f\n", target_name, max_price);
    }
    return 0;
}