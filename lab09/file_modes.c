#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>


int main (int argc, char *argv[]) {
    for (int counter = 1; counter < argc; counter++) {
        struct stat s;
        if (stat(argv[counter], &s) != 0) {
            perror(argv[counter]);
            exit(1);
        }
        // Check directory or file.
        int type = (s.st_mode >> 15) & 0x1;
        if (type == 1) {
            printf("-");
        } else {
            printf("d");
        }
        
        for (int i = 0; i < 3; i++) {
            int permission = (s.st_mode >> (6 - (i * 3))) & 0x7;
            if (permission == 0x7) {
                printf("rwx");
            }
            else if (permission == 0x6) {
                printf("rw-");
            }
            else if (permission == 0x5) {
                printf("r-x");
            }
            else if (permission == 0x4) {
                printf("r--");
            }
            else if (permission == 0x3) {
                printf("-wx");
            }
            else if (permission == 0x2) {
                printf("-w-");
            }
            else if (permission == 0x1) {
                printf("--x");
            }
            else if (permission == 0x0) {
                printf("---");
            }
        }
        printf(" %s\n", argv[counter]);
    }
    
    return 0;
}