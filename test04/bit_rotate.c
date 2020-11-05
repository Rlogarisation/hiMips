#include "bit_rotate.h"

#define TOTAL_BITS 16

// return the value bits rotated left n_rotations
uint16_t bit_rotate(int n_rotations, uint16_t bits) {
    uint16_t leftShiftedValue, disappearedValue;
    int counter = 0;
    if (n_rotations >= 0) {
        while (counter < n_rotations) {
            // 0x???? ???? ???? 0000
            leftShiftedValue = bits << 1;
            // The number of bits disappeared due to left shift is n_rotations,
            // move total (16) - n_rotations to the right 
            // 0x0000 0000 0000 ????
            disappearedValue = bits >> (TOTAL_BITS - 1);
            bits = leftShiftedValue | disappearedValue;

            counter++;
        }
        
    } else {
        n_rotations *= -1;
        while (counter < n_rotations) {
            leftShiftedValue = bits >> 1;
            disappearedValue = bits << (TOTAL_BITS - 1);
            bits = leftShiftedValue | disappearedValue;
            counter++;
        }
        
    }

    return bits; 
}
