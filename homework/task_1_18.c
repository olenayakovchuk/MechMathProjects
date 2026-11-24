#include <stdio.h>

int main(void) {
    char board[9] = { '0', 'X', ' ', ' ', ' ', '0', 'X', '0', ' ' };

    printf(" %c | %c | %c \n", board[0], board[1], board[2]);
    printf("---+---+---\n");
    printf(" %c | %c | %c \n", board[3], board[4], board[5]);
    printf("---+---+---\n");
    printf(" %c | %c | %c \n", board[6], board[7], board[8]);

    return 0;
}