// read  bytes of array + pointer to file array_pointer.save
// breaks even on same machine
// because address of array different for every execution
// see https://en.wikipedia.org/wiki/Address_space_layout_randomization

#include <stdio.h>

int main(void) {
    int array[10];
    int *p;

    FILE *f = fopen("array.save", "r");
    if (f == NULL) {
        perror("array.save");
        return 1;
    }

    if (fread(array, 1, sizeof array, f) != sizeof array) {
        perror("array.save");
        return 1;
    }
    // BROKEN - address of array has almost certainly  changed
    // BROKEN - so address p needs to point has changed
    if (fread(&p, 1, sizeof p, f) != sizeof p) {
        perror("array.save");
        return 1;
    }

    fclose(f);

    // print array
    for (int i = 0; i < 10; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    printf("p         = %p\n", p);
    printf("&array[5] = %p\n", &array[5]);
    printf("array[5]  = %d\n", array[5]);
    printf("*p        = %d\n", *p);

    return 0;
}