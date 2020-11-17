#include <stdio.h>
#include <stdint.h>
#include <assert.h>

#include "add.h"
/*
add $d, $s, $t	add	d = s + t	000000ssssstttttddddd00000100000

./add 17 19 3
add(17, 19, 3) returned  0x02638820
./add 9 27 12
add(9, 27, 12) returned 0x036c4820
*/

// return the MIPS opcode for add $d, $s, $t
uint32_t add(uint32_t d, uint32_t s, uint32_t t) {
    uint32_t result = 0x20;
    result |= (d << 11) & 0xF800;
    result |= (t << 16) & 0x1F0000;
    result |= (s << 21) & 0x3E00000;
 
    return result; 

}
