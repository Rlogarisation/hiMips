// COMP1521 lab02 by Zheng Luo (z5206267@ad.unsw.edu.au) at 23/Sep/2020
/*
Convert string of binary digits to 16-bit signed integer
e.g.
./sixteen_in 0000000000000000 
0
$ ./sixteen_in 1111111111111111 
-1
$ ./sixteen_in 0011001100110011 
13107
$ ./sixteen_in 1111000011110000 
-3856
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#define N_BITS 16

int16_t sixteen_in(char *bits);

int main(int argc, char *argv[]) {

    for (int arg = 1; arg < argc; arg++) {
        printf("%d\n", sixteen_in(argv[arg]));
    }

    return 0;
}

//
// given a string of binary digits ('1' and '0')
// return the corresponding signed 16 bit integer
//
int16_t sixteen_in(char *bits) {
    int value = strtol(bits, NULL, 2);
    return value;
}
