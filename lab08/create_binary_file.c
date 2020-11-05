/*
Write a C program, create_binary_file, 
which takes at least one argument: a filename, and subsequently, 
integers in the range 0…255 inclusive specifying byte values. 
It should create a file of the specified name, containing the specified bytes. 

For example:

./create_binary_file hello.txt 72 101 108 108 111 33 10
cat hello.txt
Hello!
./create_binary_file count.binary 1 2 3 251 252 253 254 255
./print_bytes count.binary
byte    0:   1 0x01
byte    1:   2 0x02
byte    2:   3 0x03
byte    3: 251 0xfb
byte    4: 252 0xfc
byte    5: 253 0xfd
byte    6: 254 0xfe
byte    7: 255 0xff
./create_binary_file 4_bytes.binary 222 173 190 239
./print_bytes 4_bytes.binary
byte    0: 222 0xde
byte    1: 173 0xad
byte    2: 190 0xbe
byte    3: 239 0xef
*/

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc == 1) {
        fprintf(stderr, "Usage: <%s> <0-225>\n", argv[0]);
        return 1;
    }
    FILE *output_stream = fopen(argv[1], "wb");
    if (output_stream == NULL) {
        perror(argv[1]);
        return 1;
    }

    int counter = 2;
    while (counter < argc) {
        fputc(atoi(argv[counter]), output_stream);
        counter++;
    }
    return 0;
}