#include <stdio.h>

int main(void) {
    FILE* f = fopen("F.bin", "rb");
    if (!f) {
        printf("Cannot open F.bin\n");
        return 1;
    }

    int x, pos_cnt = 0, neg_cnt = 0;
    while (fread(&x, sizeof(int), 1, f) == 1) {
        if (x > 0) ++pos_cnt;
        else if (x < 0) ++neg_cnt;
    }

    if (pos_cnt != neg_cnt || pos_cnt == 0) {
        printf("Counts of positive and negative numbers are not equal (pos=%d, neg=%d).\n",
            pos_cnt, neg_cnt);
        fclose(f);
        return 0;
    }

    FILE* h = fopen("H.bin", "wb");
    FILE* g = fopen("G.bin", "wb");
    if (!h || !g) {
        if (h) fclose(h);
        if (g) fclose(g);
        fclose(f);
        return 1;
    }

    /* Сначала записываем в G все положительные, а отрицательные сохраняем во временный файл H */
    rewind(f);
    while (fread(&x, sizeof(int), 1, f) == 1) {
        if (x > 0) {
            fwrite(&x, sizeof(int), 1, g);
        }
        else if (x < 0) {
            fwrite(&x, sizeof(int), 1, h);
        }
    }
    fclose(h);

    /* Затем дописываем в G все отрицательные из H */
    h = fopen("H.bin", "rb");
    if (h) {
        while (fread(&x, sizeof(int), 1, h) == 1) {
            fwrite(&x, sizeof(int), 1, g);
        }
        fclose(h);
    }

    fclose(f);
    fclose(g);
    printf("Successfully wrote positives then negatives to G.bin.\n");
    return 0;
}