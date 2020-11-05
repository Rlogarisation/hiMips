// swap pairs of bits of a 64-bit value, using bitwise operators

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

// return value with pairs of bits swapped
uint64_t bit_swap(uint64_t value) {
    uint64_t maskRight = 0x5555555555555555;
    uint64_t maskLeft = 0xAAAAAAAAAAAAAAAA;
    uint64_t final = 0;

    uint64_t rightShifted = (value >> 1) & maskRight;
    final |= rightShifted;
    uint64_t leftShifted = (value << 1) & maskLeft;
    final |= leftShifted;

    return final;
}
