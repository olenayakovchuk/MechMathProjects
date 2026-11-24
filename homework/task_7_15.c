#include <stdio.h>

int main(void) {
    long long n;
    printf("Enter an integer: ");
    if (scanf("%lld", &n) != 1) {
        printf("Invalid input.\n");
        return 1;
    }

    unsigned long long val = (n < 0) ? (unsigned long long)(-(n + 1)) + 1ULL : (unsigned long long)n;
    int freq[10] = { 0 };

    if (val == 0) {
        freq[0] = 1;
    }
    else {
        while (val > 0) {
            ++freq[val % 10ULL];
            val /= 10ULL;
        }
    }

    int best_digit = 0;
    for (int d = 1; d <= 9; ++d) {
        if (freq[d] >= freq[best_digit]) { /* >= обирає більшу цифру при однаковій частоті */
            best_digit = d;
        }
    }

    printf("Most frequent digit: %d (count = %d)\n", best_digit, freq[best_digit]);
    return 0;
}