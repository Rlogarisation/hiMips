#include <stdio.h>
#include <stdlib.h>


int main (int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input file 1> <input file 2>", argv[0]);
        return 1;
    }
    FILE *input_stream_1 = fopen(argv[1], "rb");
    if (input_stream_1 == NULL) {
        perror(argv[1]);
        return 1;
    }
    FILE *input_stream_2 = fopen(argv[2], "rb");
    if (input_stream_2 == NULL) {
        perror(argv[2]);
        return 1;
    }
    int input_character_1 = fgetc(input_stream_1);
    if (input_character_1 == EOF) {
        printf("EOF on %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    int input_character_2 = fgetc(input_stream_2);
    if (input_character_2 == EOF) {
        printf("EOF on %s\n", argv[2]);
        exit(EXIT_FAILURE);
    }
    int counter = 0;
    while (input_character_1 != EOF || input_character_2 != EOF) {
        if (input_character_1 == EOF && input_character_2 != EOF) {
            printf("EOF on %s\n", argv[1]);
            exit(EXIT_FAILURE);
        }
        if (input_character_1 != EOF && input_character_2 == EOF) {
            printf("EOF on %s\n", argv[2]);
            exit(EXIT_FAILURE);
        }
        if (input_character_1 != input_character_2) {
            printf("Files differ at byte %d\n", counter);
            exit(EXIT_FAILURE);
        }
        input_character_1 = fgetc(input_stream_1);
        input_character_2 = fgetc(input_stream_2);
        counter++;
    }
    printf("Files are identical\n");
    return 0;
}