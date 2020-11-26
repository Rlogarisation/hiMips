#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>

int main (int argc, char *argv[]) {

    char *pathname = getenv("HOME");
    char new_pathname[31];
    snprintf(new_pathname, 31, "%s/.diary", pathname);
    
    FILE *output_stream = fopen(new_pathname, "a+");
    for (int i = 1; i < argc; i++) {
        fputs(argv[i], output_stream);
        fputs(" ", output_stream);
    }
    fputs("\n", output_stream);

    fclose(output_stream);
    return 0;
}