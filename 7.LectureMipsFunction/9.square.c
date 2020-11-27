#include <stdio.h>

int main(void) {
    int squares[10];
    int i = 0;
    while (i < 10) {
        squares[i] = i * i;
        i++;
    }
    i = 0;
    while (i < 10) {
        printf("%d", squares[i]);
        printf("%c",'\n');
        i++;
    }
    return 0;
}