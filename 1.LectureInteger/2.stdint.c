// Andrew Taylor - andrewt@unsw.edu.au
// 08/06/2020

// example declarations of the most commonly used
// fixed width integer types
// found in stdint.h

// What does 8 means in int8_t? And how does it related to 1 byte?
// 1 Byte == 8 bits.
// So here means a int8_t can only contain a 1 byte value(signed char)

/*
This program does not produce any output.
*/

#include <stdint.h>

int main(void) {

                 // range of values for type
                 //             minimum               maximum
    int8_t   i1; //                 -128                  127 (signed) char 
    uint8_t  i2; //                    0                  255 unsigned char
    int16_t  i3; //               -32768                32767 (signed) short
    uint16_t i4; //                    0                65535 unsigned short
    int32_t  i5; //          -2147483648           2147483647 (signed) int
    uint32_t i6; //                    0           4294967295 unsigned int
    int64_t  i7; // -9223372036854775808  9223372036854775807 (signed) long
    uint64_t i8; //                    0 18446744073709551615 unsigned long

    return 0;
}

