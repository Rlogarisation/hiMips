// Print out a float.

#include <stdio.h>
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
//
// float_print is given the bits of a float as a uint32_t
// it prints out the float in the same format as "%.9g\n"
// using only putchar & puts
//
void float_print(uint32_t bits) {
    // For signbit, 0 is positive, 1 is negative.
    uint32_t signBits = bits >> SIGN_BITS;
    // Convert the sign bit into positive and negative value.
    int sign = 1;
    if (signBits == 1) {
        sign = -1;
    }

    // Extract exponent value.
    uint32_t exponentBits = (bits >> EXPONENT_LOW_BITS) & 0xFF;
    // Evaluate the power of each bits by minus exponent bias.
    int powerBits = exponentBits - EXPONENT_BIAS;
    // Determine the multiplier term.
    double multiplier = power(powerBits);

    // Extract fraction value.
    uint32_t fractionBits = (bits) & 0x7FFFFF;
    // Determine the fraction size.
    int fractionSize = FRACTION_HIGH_BITS - FRACTION_LOW_BITS + 1;
    // Set the max fraction value.
    double fractionMax = (uint32_t)1 << fractionSize;
    // Calculate the fraction value.
    double fractionValue = 1 + (fractionBits / fractionMax);
    // Final value.
    double finalValue = sign * fractionValue * multiplier;

    // Initial a string to store the final value.
    
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