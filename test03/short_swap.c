/*
./short_swap 0x1234
short_swap(0x1234) returned 0x3412
./short_swap 0xfade
short_swap(0xfade) returned 0xdefa
./short_swap 0x01080
short_swap(0x1080) returned 0x8010
*/

// Swap bytes of a short

#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

// given uint16_t value return the value with its bytes swapped
uint16_t short_swap(uint16_t value) {
    uint16_t mask34 = 0x00FF;
    uint16_t mask12 = 0xFF00;
    uint16_t final = 0;

    uint16_t rightShiftedValue = value >> 8;
    uint16_t value34 = rightShiftedValue & mask34;
    final |= value34;

    uint16_t leftShiftedValue = value << 8;
    uint16_t value12 = leftShiftedValue & mask12;
    final |= value12;

    return final;
}
