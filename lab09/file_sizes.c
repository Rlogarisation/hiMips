#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>


int main (int argc, char *argv[]) {
    long total = 0;
    for (int counter = 1; counter < argc; counter++) {
        struct stat s;
        if (stat(argv[counter], &s) != 0) {
            perror(argv[counter]);
            exit(1);
        }
        printf("%s: %ld bytes\n", argv[counter], s.st_size);
        total += s.st_size;
    }
    printf("Total: %ld bytes\n", total);
    return 0;
}