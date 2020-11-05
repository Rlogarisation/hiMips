/*

Write a C program, print_bytes, which takes one argument, a filename, 
and which should should read the specifed file and 
print one line for each byte of the file. 
The line should show the byte in decimal and hexadecimal. 
If that byte is a an ASCII printable character, 
its ASCII value should also be printed.

Assume ASCII printable characters are those for which 
the ctype.h function isprint(3) returns a non-zero value.

Follow the format in this example exactly:

echo "Hello Andrew!" >hello.txt
./print_bytes hello.txt
byte    0:  72 0x48 'H'
byte    1: 101 0x65 'e'
byte    2: 108 0x6c 'l'
byte    3: 108 0x6c 'l'
byte    4: 111 0x6f 'o'
byte    5:  32 0x20 ' '
byte    6:  65 0x41 'A'
byte    7: 110 0x6e 'n'
byte    8: 100 0x64 'd'
byte    9: 114 0x72 'r'
byte   10: 101 0x65 'e'
byte   11: 119 0x77 'w'
byte   12:  33 0x21 '!'
byte   13:  10 0x0a
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <source file>", argv[0]);
        return 1;
    }
    FILE *input_stream = fopen(argv[1], "rb");
    int character;
    int counter = 0;
    while ((character = fgetc(input_stream)) != EOF) {
        if (character <= 31 || character >= 126) {
            printf("byte%5d: %3d 0x%02x\n", counter, character,
            character);
        }
        else {
            printf("byte%5d: %3d 0x%02x '%1c'\n", counter, character,
            character, character);
        }
        
        counter++;
    }
    return 0;
}