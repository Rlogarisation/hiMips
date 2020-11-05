#include "float_exp.h"


#define EXP_LOW_BIT 23

// given the 32 bits of a float return the exponent
uint32_t float_exp(uint32_t f) {
    uint32_t mask = 0xFF;
    uint32_t maskForExponent = mask << EXP_LOW_BIT;
    uint32_t value = maskForExponent & f;
    return value >> EXP_LOW_BIT; // REPLACE ME WITH YOUR CODE
}
