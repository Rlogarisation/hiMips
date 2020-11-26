#include <stdio.h>
#include <stdint.h>
#include "print_bits.h"

void print_bits_hex(char *description, uint16_t n);

int main(void) {

    uint16_t a = 0;
    printf("Enter a: ");
    // What is %hd means?
    /*
    With scanf, the "h" modifier indicates that it's reading a short integer, 
    which your variable choice just happens to be. 
    So the "%hd" is necessary to write only two bytes (on most machines) 
    instead of the 4 bytes that "%d" writes.
    */
    scanf("%hd", &a);

    uint16_t b = 0;
    printf("Enter b: ");
    scanf("%hd", &b);

    printf("Enter c: ");
    int c = 0;
    scanf("%d", &c);

    print_bits_hex("     a = ", a);
    print_bits_hex("     b = ", b);
    // ~ is symbol for negation.
    print_bits_hex("    ~a = ", ~a);
    print_bits_hex(" a & b = ", a & b);
    print_bits_hex(" a | b = ", a | b);
    // ^ is the symbol for XOR: same number=>0, different number=>1.
    print_bits_hex(" a ^ b = ", a ^ b);
    print_bits_hex("a >> c = ", a >> c);
    print_bits_hex("a << c = ", a << c);

    return 0;
}

// print description then print
// binary, hexadecimal and decimal representation of a value
void print_bits_hex(char *description, uint16_t value) {
    printf("%s", description);
    print_bits(value, 8 * sizeof value);
    /*
    %04x is printing out in terms of hexadecimal(%x) by 4 spaces.
    0xFFFF == 65535

    What is (value & 0xFFFF)?
    This is unneccessary expression, the simplify version can be value only.
    value & 0xFFFF is used when we have more than 16 bits, and we only wish to
    keep the last 16 bits, and filter out all the digits.
    Since the F or each single character in 0xFFFF represents 4 bits 
    in term of binary expression, as we remember 
    1111=>15=>F
    hence 4 of these represents 4*4 bits == 16 bits.

    Why 0xFFFF: because we want to filter out extra digits, 
    e.g.
    ramdom value: 00000000000010101010
    0xFFFF:           1111111111111111
    &
                      0000000010101010
    Which turn out the value doesn't change, but number of digits got reduced.
    */
    printf(" = 0x%04x = %d\n", value & 0xFFFF, value);
}

/*
$ dcc bitwise.c print_bits.c -o bitwise
$ ./bitwise

Enter a: 23032

Enter b: 12345

Enter c: 3
     a = 0101100111111000 = 0x59f8 = 23032
     b = 0011000000111001 = 0x3039 = 12345
    ~a = 1010011000000111 = 0xa607 = 42503
 a & b = 0001000000111000 = 0x1038 = 4152
 a | b = 0111100111111001 = 0x79f9 = 31225
 a ^ b = 0110100111000001 = 0x69c1 = 27073
a >> c = 0000101100111111 = 0x0b3f = 2879
a << c = 1100111111000000 = 0xcfc0 = 53184
*/