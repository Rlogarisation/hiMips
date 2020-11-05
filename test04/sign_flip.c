#include "sign_flip.h"

#define SIGN_BIT 31


// given the 32 bits of a float return it with its sign flipped
uint32_t sign_flip(uint32_t f) {
    // Check the sign of input.
    // 0 is positive, 1 is negative.
    uint32_t signInput = f >> SIGN_BIT;
    uint32_t negativeSign = (uint32_t)1 << SIGN_BIT;
    // If positive
    if (signInput == 0) {
        // then convert to negative.
        uint32_t output = negativeSign | f;
        return output;
    }
    // If negative
    else {
        // Then convert to positive.
        uint32_t mask = ~ negativeSign;
        uint32_t output = mask & f;
        return output;
    }
}
