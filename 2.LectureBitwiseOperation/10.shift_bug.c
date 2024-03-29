// Andrew Taylor - andrewt@unsw.edu.au
// 08/06/2020

// Examples of illegal bit-shift operations

#include <stdio.h>
#include <stdint.h>

int main(void) {
    // int16_t is a signed type (-32768..32767)
    // below operations are undefined for a signed type
    int16_t i;

    i = -1;
    i = i >> 1; // undefined -  shift of a negative value
    printf("%d\n", i);

    i = -1;
    i = i << 1; // undefined -  shift of a negative value
    printf("%d\n", i);

    // Why?
    i = 32767;
    i = i << 1; // undefined -  left shift produces a negative value

    
    uint64_t j;
    // Because 1 is normally uint32_t, it will be undefined if << 33 positions.
    j = 1 << 33; // undefined - constant 1 is an int
    j = ((uint64_t)1) << 33; // ok

    return 0;
}