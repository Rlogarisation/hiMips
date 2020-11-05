// Extract the 3 parts of a float using bit operations only

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "floats.h"

#define SIGN_POSITION 31
#define EXPONENT_POSITION 23

// separate out the 3 components of a float
float_components_t float_bits(uint32_t f) {
    // Initial struct.
    float_components_t component;
    // Sign.
    component.sign = f >> SIGN_POSITION;

    // Exponent.
    uint32_t maskExponent = 0xFF;
    int shiftedMaskForExponent = maskExponent << EXPONENT_POSITION;
    int exponentValue = shiftedMaskForExponent & f;
    component.exponent = exponentValue >> EXPONENT_POSITION;

    // Fraction.
    uint32_t maskFraction = 0x7FFFFF;
    int fractionValue = f & maskFraction;
    component.fraction = fractionValue;


    return component;
}

// given the 3 components of a float
// return 1 if it is NaN, 0 otherwise
int is_nan(float_components_t f) {
    // The definition of nan is all 8 bits in the exponent part is 1,
    // and the first digit in fraction part is 1, all others are 0.
    uint32_t mask = 0xFF;
    if ((f.exponent & mask) == 0xFF) {
        if (f.fraction >> (EXPONENT_POSITION - 1) == 1) {
            return 1;
        }
    }
    return 0;
}

// given the 3 components of a float
// return 1 if it is inf, 0 otherwise
int is_positive_infinity(float_components_t f) {
    // The definition of +inf is all 8 bits in the exponent part is 1,
    // all others are 0.
    uint32_t mask = 0xFF;
    if ((f.exponent & mask) == 0xFF && f.sign == 0 && f.fraction == 0) {
        return 1;
    }
    return 0;
}

// given the 3 components of a float
// return 1 if it is -inf, 0 otherwise
int is_negative_infinity(float_components_t f) {
    uint32_t mask = 0xFF;
    if ((f.exponent & mask) == 0xFF && f.sign == 1 && f.fraction == 0) {
        return 1;
    }
    return 0;
}

// given the 3 components of a float
// return 1 if it is 0 or -0, 0 otherwise
int is_zero(float_components_t f) {
    if ((f.exponent == 0) && (f.fraction == 0) && 
    ((f.sign == 1) || (f.sign == 0))) {
        return 1;
    }

    return 0;
}
