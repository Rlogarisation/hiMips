// Sample solution for COMP1521 lab exercises
//
// generate the opcode for an addi instruction

/*
./addi 17 19 -3
addi(17, 19, -3) returned 0x2271fffd
=
001000 10011 10001 1111111111111101
        19     17       
addi $t, $s, I	t = s + I	001000ssssstttttIIIIIIIIIIIIIIII

*/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "addi.h"

// addi $t, $s, I	t = s + I	001000ssssstttttIIIIIIIIIIIIIIII
#define INSTRUCTIONS_ADDI       0x20000000
#define S_LOW 21
#define T_LOW 16
// return the MIPS opcode for addi $t,$s, i
uint32_t addi(int t, int s, int i) {
    uint32_t t_in_bits = t << T_LOW;
    uint32_t s_in_bits = s << S_LOW;
    uint16_t i_in_bits = i;
    
    uint32_t result = INSTRUCTIONS_ADDI | t_in_bits | s_in_bits | i_in_bits;
    
    return result; 

}
