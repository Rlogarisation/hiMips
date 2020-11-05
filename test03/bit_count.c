// count bits in a uint64_t

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>


// return how many 1 bits value contains
int bit_count(uint64_t value) {
    // PUT YOUR CODE HERE
    int counter = 63;
    uint64_t mask = 0x1;
    int counterForZero = 0;

    while (counter >= 0) {
        uint64_t shiftedValue = value >> counter;
        int output = mask & shiftedValue;
        //printf("%d", output);
        if (output == 1) {
            counterForZero++;
        }
        counter --;
    }
    return counterForZero;
}
