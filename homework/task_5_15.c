#include <stdio.h>

static unsigned long long reverse_number(unsigned long long n) {
    unsigned long long y = 0;
    while (n > 0) {
        y = y * 10ULL + (n % 10ULL);
        n /= 10ULL;
    }
    return y;
}

int main(void) {
    unsigned long long n;
    printf("Enter natural number n: ");
    if (scanf("%llu", &n) != 1) {
        printf("Invalid input.\n");
        return 1;
    }

    printf("Reversed: %llu\n", reverse_number(n));
    return 0;
}