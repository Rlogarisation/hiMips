#include <stdio.h>
#include <stdlib.h>


int main (int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input file>", argv[0]);
        return 1;
    }
    FILE *input_stream = fopen(argv[1], "rb");
    if (input_stream == NULL) {
        perror(argv[1]);
        return 1;
    }
    int input_character;
    int counter = 0;
    while ((input_character = fgetc(input_stream)) != EOF) {
        // Assume a byte is non-ASCII 
        // if it contains a value between 128..255 inclusive.
        if (input_character >= 128 && input_character <= 255) {
            printf("%s: byte %d is non-ASCII\n", argv[1], counter);
            exit(0);
        }
        
        counter++;
    }
    printf("%s is all ASCII\n", argv[1]);
    return 0;
}