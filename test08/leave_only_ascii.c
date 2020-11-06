#include <stdio.h>
#include <stdlib.h>


int main (int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input file>", argv[0]);
        return 1;
    }
    FILE *input_stream = fopen(argv[1], "r+");
    if (input_stream == NULL) {
        perror(argv[1]);
        return 1;
    }
    FILE *output_stream = fopen("temp", "w");
    int input_character;
    while ((input_character = fgetc(input_stream)) != EOF) {
        // Assume a byte is non-ASCII 
        // if it contains a value between 128..255 inclusive.
        if (!(input_character >= 128 && input_character <= 255)) {
            fputc(input_character, output_stream);
        }
    }
    fflush(output_stream);
    FILE *input_stream_cp = fopen("temp", "r+");
    FILE *output_stream_cp = fopen(argv[1], "wb");
    int input_character_cp;

    while ((input_character_cp = fgetc(input_stream_cp)) != EOF) {
        fputc(input_character_cp, output_stream_cp);
    }

    return 0;
}