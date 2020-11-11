// write bytes of array + pointer to file array_pointer.save

/*
$ dcc write_pointer.c -o write_pointer
$ dcc read_pointer.c -o read_pointer
$ ./write_pointer
p         = 0x410234
&array[5] = 0x410234
array[5]  = 15
*p        = 15
$ ls -l array_pointer.save
-rw-r--r-- 1 z5555555 z5555555 48 Oct 30 21:46 array.save
$ ./read_pointer
10 11 12 13 14 15 16 17 18 19
p         = 0x410234
&array[5] = 0x4163f4
array[5]  = 15
*p        = -1203175425
$
*/

#include <stdio.h>

int main(void) {
    int array[10] = { 10, 11, 12, 13, 14, 15, 16, 17, 18, 19 };
    int *p = &array[5];

    FILE *f = fopen("array.save", "w");
    if (f == NULL) {
        perror("array.save");
        return 1;
    }

    if (fwrite(array, 1, sizeof array, f) != sizeof array) {
        perror("array.save");
        return 1;
    }

    if (fwrite(&p, 1, sizeof p, f) != sizeof p) {
        perror("array.save");
        return 1;
    }

    fclose(f);

    printf("p         = %p\n", p);
    printf("&array[5] = %p\n", &array[5]);
    printf("array[5]  = %d\n", array[5]);
    printf("*p        = %d\n", *p);
    return 0;
}