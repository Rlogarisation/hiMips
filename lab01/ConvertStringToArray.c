#include <stdio.h>
#include <stdlib.h>

#define MAX 10
int main(int argc, char **argv) {
    int counter = 1;
    int counterForArray = 0;
    int array[MAX];
    // Rearrange the string into int type array.
    while (counter < argc) {
        array[counterForArray] = atoi(argv[counter]);
        printf("%d\n", array[counterForArray]);
        counter++;
        counterForArray++;
    }

    return 0;
}