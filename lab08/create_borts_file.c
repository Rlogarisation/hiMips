/*

Write a C program, create_borts_file, which takes 3 arguments:

1. a filename,
2. the beginning of a range of integers, and
3. the end of a range of integers;
and which creates a file of this name containing the specified borts.

A bort is an unisgned two-byte big-endian integer 
(bort is a contraction of big-endian short).

The possible bort values are 0..65535.

A borts file is not a text file so we can not use cat to inspect its contents.

We can use the print_bytes program from the previous lab exercises 
to print files containing borts.

For example:

dcc -o create_borts_file create_borts_file.c
./create_borts_file fortytwo.bort 40 42
ls -l fortytwo.bort
-rw-r--r-- 1 andrewt andrewt 6 Nov  1 15:21 fortytwo.bort
./print_bytes fortytwo.bort 
byte    0:   0 0x00
byte    1:  40 0x28 '('
byte    2:   0 0x00
byte    3:  41 0x29 ')'
byte    4:   0 0x00
byte    5:  42 0x2a '*'
The linux utilities, xxd and od are also good ways to print a binary file.
xxd fortytwo.bort 
00000000: 0028 0029 002a                           .(.).*
od fortytwo.bort 
0000000 024000 024400 025000
0000006
Another example, creating a file containing the five biggest borts:
./create_borts_file biggest.bort 65530 65535
ls -l biggest.bort
-rw-r--r-- 1 andrewt andrewt 12 Nov  1 15:26 biggest.bort
./print_bytes biggest.bort
byte    0: 255 0xff
byte    1: 250 0xfa
byte    2: 255 0xff
byte    3: 251 0xfb
byte    4: 255 0xff
byte    5: 252 0xfc
byte    6: 255 0xff
byte    7: 253 0xfd
byte    8: 255 0xff
byte    9: 254 0xfe
byte   10: 255 0xff
byte   11: 255 0xff
We can give od command-line options to decode borts, for example:
od --endian=big -t u2 -A d -w2  biggest.bort
0000000 65530
0000002 65531
0000004 65532
0000006 65533
0000008 65534
0000010 65535
0000012
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

// 0000 0000 1111 1111
#define MASK 0xFF

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
    uint32_t counter = (uint32_t)starting_number;
    while (counter <= ending_number) {
        fprintf(output_stream, "%c", counter >> 8);
        fprintf(output_stream, "%c", counter & MASK);
        
        counter++;
    }

    fclose(output_stream);

    return 0;
}