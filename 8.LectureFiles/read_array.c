// read  bytes of array + pointer to file array_pointer.save
// non-portable between platforms
// breaks if sizeof int changes or endian-ness changes
//
// Handling this safely is called serialization:
// https://en.wikipedia.org/wiki/Serialization

#include <stdio.h>

int main(void) {
    int array[10];

    FILE *f = fopen("array.save", "r");
    if (f == NULL) {
        perror("array.save");
        return 1;
    }
    // read array: NOT-PORTABLE: depends on size of int and byte-order
    if (fread(array, 1, sizeof array, f) != sizeof array) {
        perror("array.save");
        return 1;
    }
    fclose(f);

    for (int i = 0; i < 10; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    return 0;
}