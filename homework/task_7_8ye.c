#include <stdio.h>

static int is_fibonacci(unsigned long long val) {
    if (val == 0 || val == 1) {
        return 1;
    }
    unsigned long long a = 0, b = 1;
    while (b < val) {
        unsigned long long next = a + b;
        a = b;
        b = next;
    }
    return b == val;
}

int main(void) {
    int n;
    printf("Enter array size N (1..1000): ");
    if (scanf("%d", &n) != 1 || n <= 0 || n > 1000) {
        printf("Invalid size.\n");
        return 1;
    }

    unsigned long long arr[1000];
    int fib_count = 0;
    printf("Enter %d natural numbers: ", n);
    for (int i = 0; i < n; ++i) {
        if (scanf("%llu", &arr[i]) != 1) {
            printf("Invalid input.\n");
            return 1;
        }
        if (is_fibonacci(arr[i])) {
            ++fib_count;
        }
    }

    printf("Fibonacci numbers count: %d\n", fib_count);
    return 0;
}