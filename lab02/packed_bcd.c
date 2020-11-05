/*
Add code to the function packed_bcd so that, 
given an eight-digit packed binary-coded decimal value, 
it returns the corresponding integer.

In packed binary-coded decimal format,
each 4 bits holds 1 decimal value (0 to 9), 
so each byte contains 2 decimal digits. For example:

./packed_bcd 66         # ... == 0x42
42
./packed_bcd 39321      # ... == 0x9999
9999
./packed_bcd 1111638594 # ... == 0x42424242
42424242
*/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#define N_BCD_DIGITS 8

uint32_t packed_bcd(uint32_t packed_bcd);

int main(int argc, char *argv[]) {

    for (int arg = 1; arg < argc; arg++) {
        long l = strtol(argv[arg], NULL, 0);
        assert(l >= 0 && l <= UINT32_MAX);
        uint32_t packed_bcd_value = l;

        printf("%lu\n", (unsigned long)packed_bcd(packed_bcd_value));
    }

    return 0;
}

// given a packed BCD encoded value between 0 .. 99999999
// return the corresponding integer
uint32_t packed_bcd(uint32_t packed_bcd_value) {
    int size = N_BCD_DIGITS * sizeof packed_bcd_value;
    int value = 0;
    // Convert the value into hexadecimal format.
    int counter = 0;
    int multiplier = 1;
    while (counter * 4 < size) {
        int bit_shifter = counter * 4;
        int hex_digit = packed_bcd_value >> bit_shifter;
        // Mask off all except last 4 digits.
        int mask = 0xF;
        int digit = hex_digit & mask;
        // Add digit into value.
        value += digit * multiplier;
        multiplier *= 10;
        counter++;
    }
    return value;
}
