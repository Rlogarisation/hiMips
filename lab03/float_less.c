// Compare 2 floats using bit operations only

#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "floats.h"

#define N_BITS 32
#define SIGN_BITS 31
#define EXPONENT_HIGH_BITS 30
#define EXPONENT_LOW_BITS 23
#define FRACTION_HIGH_BITS 22
#define FRACTION_LOW_BITS 0

#define EXPONENT_BIAS 127
#define EXPONENT_INF_NAN 255

double power(int number);

// float_less is given the bits of 2 floats bits1, bits2 as a uint32_t
// and returns 1 if bits1 < bits2, 0 otherwise
// 0 is return if bits1 or bits2 is Nan
// only bit operations and integer comparisons are used
uint32_t float_less(uint32_t bits1, uint32_t bits2) {
    // For signbit, 0 is positive, 1 is negative.
    uint32_t signBits1 = bits1 >> SIGN_BITS;
    uint32_t signBits2 = bits2 >> SIGN_BITS;

    // Extract exponent value.
    uint32_t exponentBits1 = (bits1 >> EXPONENT_LOW_BITS) & 0xFF;
    uint32_t exponentBits2 = (bits2 >> EXPONENT_LOW_BITS) & 0xFF;
    // Evaluate the power of each bits by minus exponent bias.
    int powerBits1 = exponentBits1 - EXPONENT_BIAS;
    int powerBits2 = exponentBits2 - EXPONENT_BIAS;
    // Determine the multiplier term.
    double multiplier1 = power(powerBits1);
    double multiplier2 = power(powerBits2);

    // Extract fraction value.
    uint32_t fractionBits1 = (bits1) & 0x7FFFFF;
    uint32_t fractionBits2 = (bits2) & 0x7FFFFF;
    // Determine the fraction size.
    int fractionSize = FRACTION_HIGH_BITS - FRACTION_LOW_BITS + 1;
    // Set the max fraction value.
    double fractionMax = (uint32_t)1 << fractionSize;
    // Calculate the fraction value.
    double fractionValue1 = 1 + (fractionBits1 / fractionMax);
    double fractionValue2 = 1 + (fractionBits2 / fractionMax);
    
    // Final value.
    double finalValue1 = fractionValue1 * multiplier1;
    double finalValue2 = fractionValue2 * multiplier2;
    // Test.
    //printf("Fraction value 1&2: %lf %lf\n", fractionValue1, fractionValue2);
    //printf("Multiplier 1&2: %lf %lf\n", multiplier1, multiplier2);
    //printf("%lf      %lf\n", finalValue1, finalValue2);

    //printf("%d %d\n", exponentBits1 == 0xFF, (fractionBits1 >> FRACTION_HIGH_BITS == 1));
    // Return 0 is any bits are nan.
    if ((exponentBits1 == 0xFF && 
    (fractionBits1 >> FRACTION_HIGH_BITS == 1)) || 
    (exponentBits2 == 0xFF && 
    (fractionBits2 >> FRACTION_HIGH_BITS == 1))) {
        return 0;
    }

    // Check the sign of both bits.
    // If bits1 is -, bits2 is +.
    if (signBits1 == 1 && signBits2 == 0) {
        return 1;
    } 
    // If bits 1 is + and bits2 is -.
    else if (signBits1 == 0 && signBits2 == 1) {
        return 0;
    } 
    // If bits are both positive.
    else if (signBits1 == 0 && signBits2 == 0) {
        if (finalValue1 < finalValue2) {
            return 1;
        } else {
            return 0;
        }
    }
    // If bits are both negative.
    else if (signBits1 == 1 && signBits2 == 1) {
        if (finalValue1 > finalValue2) {
            return 1;
        } else {
            return 0;
        }
    }
    return 0;
}

double power(int number) {
    if (number >= 0) {
        int counter = 0;
        double result = 1.0;
        while (counter < number) {
            result *= 2;
            counter++;
        }
        return result;
    } 
    else {
        number *= -1;
        int counter = 0;
        double result = 1.0;
        while (counter < number) {
            result *= 2;
            counter++;
        }
        return (1 / result);
    }
    
}
