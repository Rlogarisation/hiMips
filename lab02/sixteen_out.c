// Written by ZHENG LUO (z5206267@ad.unsw.edu.au) at 23/Sep
// Sample solution for COMP1521 lab exercises
//
// Convert a 16-bit signed integer to a string of binary digits
/*
./sixteen_out 0
0000000000000000
./sixteen_out -1
1111111111111111
./sixteen_out 13107
0011001100110011
./sixteen_out -3856
1111000011110000
*/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#define N_BITS 16

char *sixteen_out(int16_t value);

int main(int argc, char *argv[]) {

    for (int arg = 1; arg < argc; arg++) {
        long l = strtol(argv[arg], NULL, 0);
        assert(l >= INT16_MIN && l <= INT16_MAX);
        int16_t value = l;

        char *bits = sixteen_out(value);
        printf("%s\n", bits);

        free(bits);
    }

    return 0;
}

// given a signed 16 bit integer
// return a null-terminated string of 16 binary digits ('1' and '0')
// storage for string is allocated using malloc
char *sixteen_out(int16_t value) {
    char *string = malloc(N_BITS + 1);
    int counter = N_BITS - 1;
    while (counter >= 0) {
        int digit = value >> counter;
        int bit = digit & 1;
        // Detailed in int_to_hex_string.c
        string[N_BITS - counter - 1] = "0123456789"[bit];
        counter--;
    }
    string[N_BITS] = 0;

    return string;
}

