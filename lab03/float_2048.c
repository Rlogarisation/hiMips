// Multiply a float by 2048 using bit operations only

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "floats.h"

#define EXPONENT_LOW_BITS 23
#define EXPONENT_HIGH_BITS 30
#define SIGN_BITS 31

 
// float_2048 is given the bits of a float f as a uint32_t
// it uses bit operations and + to calculate f * 2048
// and returns the bits of this value as a uint32_t
//
// if the result is too large to be represented as a float +inf or -inf is returned
//
// if f is +0, -0, +inf or -inf, or Nan it is returned unchanged
//
// float_2048 assumes f is not a denormal number
//
uint32_t float_2048(uint32_t f) {
    // Define the values first.
    uint32_t positiveInf = 0xFF;
    positiveInf <<= EXPONENT_LOW_BITS;
    uint32_t negativeInf = 0x1FF;
    negativeInf <<= EXPONENT_LOW_BITS; 
    uint32_t nan = 0xFF8;
    nan <<= 19;
    uint32_t positiveZero = 0;
    uint32_t negativeZero = 0x80000000;

    // Extract exponent part.
    uint32_t valueExponent = (f >> EXPONENT_LOW_BITS) & 0xFF ;
    // 2^11 == 2048
    valueExponent += 11;

    // Extract sign part.
    // If sign == 0 (positive), sign == 1 (negative).
    int sign = f >> SIGN_BITS;
    uint32_t signValue = sign << SIGN_BITS;

    // Additional check: 
    // If, after multiplication, 
    // the result is too large to be represented as a float, 
    // return inf if the original float was positive, 
    // and -inf if it was negative.
    /*
    luozheng@192-168-1-115 LectureFloatingPoint % ./floating_types 
    float        4 bytes  min=1.17549e-38   max=3.40282e+38
    double       8 bytes  min=2.22507e-308  max=1.79769e+308
    long double 16 bytes  min=3.3621e-4932  max=1.18973e+4932

    ./explain_float_representation inf

    inf is represented as IEEE-754 single-precision by these bits:

    01111111100000000000000000000000

    sign | exponent | fraction
    0 | 11111111 | 00000000000000000000000

    sign bit = 0
    sign = +

    raw exponent    = 11111111 binary
                    = 255 decimal
    number = +inf
    */
    
    if ((valueExponent > 255) && (sign == 0) && (((f >> 22) & 1) == 0)) {
        return positiveInf;
    } else if ((valueExponent > 255) && (sign == 1)) {
        return negativeInf;
    } else if ((valueExponent > 255) && (((f >> 22) & 1) == 1)) {
        return nan;
    } else if (f == 0) {
        return positiveZero;
    } else if ((sign == 1) && (f << 1 == 0)) {
        return negativeZero;
    }

    // Move back to the correct position.
    valueExponent <<= 23;
    // Now we have desired exponent part, but empty fraction part.
    // Hence we need to mask off the exponent part of the original f, then OR.
    uint32_t maskExponentOff = 0x7FFFFF;
    uint32_t valueFraction = maskExponentOff & f;
    // Combine fraction and exponent.
    uint32_t value = valueExponent | valueFraction | signValue;

    return value;
}
