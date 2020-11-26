// write bytes of array to file array.save

/*
$ dcc write_array.c -o write_array
$ dcc read_array.c -o read_array
$ ./write_array
$ ls -l array.save
-rw-r--r-- 1 z5555555 z5555555 40 Oct 30 21:46 array.save
$ ./read_array
10 11 12 13 14 15 16 17 18 19
$
*/

#include <stdio.h>

int main(void) {
    int array[10] = { 10, 11, 12, 13, 14, 15, 16, 17, 18, 19 };

    FILE *f = fopen("array.save", "w");
    if (f == NULL) {
        perror("array.save");
        return 1;
    }
    // assuming int are 4 bytes, this will
    // write 40 bytes of array to "array.save"
    if (fwrite(array, 1, sizeof array, f) != sizeof array) {
        perror("array.save");
        return 1;
    }
    fclose(f);

    return 0;
}