// Andrew Taylor - andrewt@unsw.edu.au
// 08/06/2020

// print the bits of an int, for example:

/*
$ dcc print_bits_of_int.c print_bits.c -o print_bits_of_int
$ ./print_bits_of_int
Enter an int: 42
00000000000000000000000000101010
$ ./print_bits_of_int
Enter an int: -42
11111111111111111111111111010110
$ ./print_bits_of_int
Enter an int: 0
00000000000000000000000000000000
$ ./print_bits_of_int
Enter an int: 1
00000000000000000000000000000001
$ ./print_bits_of_int
Enter an int: -1
11111111111111111111111111111111
$ ./print_bits_of_int
Enter an int: 2147483647
01111111111111111111111111111111
$ ./print_bits_of_int
Enter an int: -2147483648
10000000000000000000000000000000
$

*/

#include <stdio.h>
#include <stdint.h>
#include "print_bits.h"

#define BYTE2BITS 8

int main(void) {

    int a = 0;
    printf("Enter an int: ");
    scanf("%d", &a);

    // sizeof returns number of bytes, a byte has 8 bits
    int n_bits = BYTE2BITS * sizeof a;
    // Since a is int type, so always 4 bytes and 32 bits? (YES, CONFIRMED.)
    // printf("THIS IS BITS:%d\n", n_bits);

    print_bits(a, n_bits);
    // Here the a is int type, but the definition of the function is diff, WHY?
    /*
    Basically we could replace int type with uint32_t, these two are identically
    the same,
    uint64_t is used here for no particular reason as which is more a safe way
    in case the existence of huge number.
    */
    printf("\n");

    return 0;
}