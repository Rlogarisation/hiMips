/*
Write a C program, create_integers_file, which takes 3 arguments:

1. a filename,
2. the beginning of a range of integers, and
3. the end of a range of integers;
and which creates a file of this name containing the specified integers. 

Your program should print a suitable error message 
if given the wrong number of arguments, or if the file can not be created


e.g.
./create_integers_file fortytwo.txt 40 42
cat fortytwo.txt
40
41
42
./create_integers_file a.txt 1 5
cat a.txt
1
2
3
4
5
./create_integers_file 1000.txt 1 1000
wc 1000.txt
1000 1000 3893 1000.txt
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, char *argv[]) {

    if (argc != 4) {
        fprintf(stderr, "Usage: %s <destination file>\
        <starting number> <ending number>\n", argv[0]);
        return 1;
    }

    FILE *output_stream = fopen(argv[1], "wb");
    if (output_stream == NULL) {
        perror(argv[2]);
        return 1;
    }

    int starting_number = atoi(argv[2]);
    int ending_number = atoi(argv[3]);
    assert(starting_number <= ending_number);
    int counter = starting_number;
    while (counter <= ending_number) {
        fprintf(output_stream, "%d\n", counter);
        counter++;
    }

    fclose(output_stream);

    return 0;
}