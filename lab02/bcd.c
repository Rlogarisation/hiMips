/*
Add code to the function bcd so that, 
given a 2 digit Binary-Coded Decimal (BCD) value, 
it returns the corresponding integer.

In binary-coded decimal format, each byte holds 1 decimal value (0 to 9), 
so each byte contains 1 decimal digit. For example:

./bcd 7
7
./bcd 258             # 258 == 0x0102
12
./bcd 1026            # 1026 == 0x0402
42
*/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

int bcd(int bcd_value);

int main(int argc, char *argv[]) {

    for (int arg = 1; arg < argc; arg++) {
        long l = strtol(argv[arg], NULL, 0);
        assert(l >= 0 && l <= 0x0909);
        int bcd_value = l;

        printf("%d\n", bcd(bcd_value));
    }

    return 0;
}

// given a  BCD encoded value between 0 .. 99
// return corresponding integer
int bcd(int bcd_value) {
    int result = 0;
    // Convert to hexadecimal format.
    int hexDigitNumber = sizeof bcd_value;

    int counter = 0;
    int counterForResult = 1;
    while (counter < hexDigitNumber) {
        int bitNumber = counter * hexDigitNumber;
        int shifted = bcd_value >> bitNumber;
        int digit = shifted & 0xF;
        // self comment: Please write it better in the future,
        // or checkout the lab solution after it release,
        // this code is so shit.
        if (counter == 0 || counter == 2) {
            result += digit * counterForResult;
            counterForResult *= 10;
        }   
        counter++;
    }
    
    return result;
}

