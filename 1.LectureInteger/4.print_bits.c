#include <stdio.h>
#include <stdint.h>

#include "print_bits.h"
/* 
uint64_t can be completely replaced by uint32_t or int, there is no need for 
creating uint64_t (for the sake of huge number.)
*/
// extract the nth bit from a value
// This is how we determine whether certain digit is 1 or not.
int get_nth_bit(uint64_t value, int n) {
    // shift the bit right n bits
    // this leaves the n-th bit as the least significant bit
    uint64_t shifted_value = value >> n;

    //printf("THIS IS INPUT VALUE:%lu\n", value);
    //printf("THIS IS COUNTER N:%d\n", n);
    //printf("THIS IS SHIFTED VALUE:%lu\n", shifted_value);
    /*
    Even though the compiler prints out numbers, but computer will process these
    number in terms of binary number.
    */
    
    // The AND operator: only two "1" can result 1, otherwise 0.
    // zero all bits except the the least significant bit
    // This could determine the existence of 1 for the last digit.
    int bit = shifted_value & 1;

    return bit;
}

// print the bottom how_many_bits bits of value
void print_bits(uint64_t value, int how_many_bits) {
    // print bits from most significant to least significant

    // i = 32 - 1 = 31 for int type input. 
    /*
    The counter has been -1 is for the reason of:
    e.g. we want to access the 4th digit.
    0000000001010
    Then we need to >> by 3, rather than 4, 
    hence we need to minus one.
    */

    // (WHY?)(DONT WE ONLY HAVE 16 digits?)
    /*
    Normally we loop thro 32 bits, as which is the bit number of int.
    this can cover all the digits smaller than 32 bits, so regardless how many
    digit we have.
    */
    int i = how_many_bits - 1; 

    while (i >= 0) {
        int bit = get_nth_bit(value, i);
        printf("%d", bit);
        // printf("\n");// TESTING PURPOSE.
        i--;
    }
}

/*
z5206267@weber:~/COMP1521/LectureInteger$ dcc print_bits.c print_bits_of_int.c 
-o print_bits_of_int
z5206267@weber:~/COMP1521/LectureInteger$ ./print_bits_of_int 
Enter an int: 10
THIS IS INPUT VALUE:10
THIS IS COUNTER N:31
THIS IS SHIFTED VALUE:0
0
THIS IS INPUT VALUE:10
THIS IS COUNTER N:30
THIS IS SHIFTED VALUE:0
0
THIS IS INPUT VALUE:10
THIS IS COUNTER N:29
THIS IS SHIFTED VALUE:0
0
THIS IS INPUT VALUE:10
THIS IS COUNTER N:28
THIS IS SHIFTED VALUE:0
0
THIS IS INPUT VALUE:10
THIS IS COUNTER N:27
THIS IS SHIFTED VALUE:0
0
THIS IS INPUT VALUE:10
THIS IS COUNTER N:26
THIS IS SHIFTED VALUE:0
0
THIS IS INPUT VALUE:10
THIS IS COUNTER N:25
THIS IS SHIFTED VALUE:0
0
THIS IS INPUT VALUE:10
THIS IS COUNTER N:24
THIS IS SHIFTED VALUE:0
0
THIS IS INPUT VALUE:10
THIS IS COUNTER N:23
THIS IS SHIFTED VALUE:0
0
THIS IS INPUT VALUE:10
THIS IS COUNTER N:22
THIS IS SHIFTED VALUE:0
0
THIS IS INPUT VALUE:10
THIS IS COUNTER N:21
THIS IS SHIFTED VALUE:0
0
THIS IS INPUT VALUE:10
THIS IS COUNTER N:20
THIS IS SHIFTED VALUE:0
0
THIS IS INPUT VALUE:10
THIS IS COUNTER N:19
THIS IS SHIFTED VALUE:0
0
THIS IS INPUT VALUE:10
THIS IS COUNTER N:18
THIS IS SHIFTED VALUE:0
0
THIS IS INPUT VALUE:10
THIS IS COUNTER N:17
THIS IS SHIFTED VALUE:0
0
THIS IS INPUT VALUE:10
THIS IS COUNTER N:16
THIS IS SHIFTED VALUE:0
0
THIS IS INPUT VALUE:10
THIS IS COUNTER N:15
THIS IS SHIFTED VALUE:0
0
THIS IS INPUT VALUE:10
THIS IS COUNTER N:14
THIS IS SHIFTED VALUE:0
0
THIS IS INPUT VALUE:10
THIS IS COUNTER N:13
THIS IS SHIFTED VALUE:0
0
THIS IS INPUT VALUE:10
THIS IS COUNTER N:12
THIS IS SHIFTED VALUE:0
0
THIS IS INPUT VALUE:10
THIS IS COUNTER N:11
THIS IS SHIFTED VALUE:0
0
THIS IS INPUT VALUE:10
THIS IS COUNTER N:10
THIS IS SHIFTED VALUE:0
0
THIS IS INPUT VALUE:10
THIS IS COUNTER N:9
THIS IS SHIFTED VALUE:0
0
THIS IS INPUT VALUE:10
THIS IS COUNTER N:8
THIS IS SHIFTED VALUE:0
0
THIS IS INPUT VALUE:10
THIS IS COUNTER N:7
THIS IS SHIFTED VALUE:0
0
THIS IS INPUT VALUE:10
THIS IS COUNTER N:6
THIS IS SHIFTED VALUE:0
0
THIS IS INPUT VALUE:10
THIS IS COUNTER N:5
THIS IS SHIFTED VALUE:0
0
THIS IS INPUT VALUE:10
THIS IS COUNTER N:4
THIS IS SHIFTED VALUE:0
0
THIS IS INPUT VALUE:10  => 00001010 (Right shift by counter amount)
THIS IS COUNTER N:3     => 00000001 == 1
THIS IS SHIFTED VALUE:1 => 1
1                       => 00000001 & 00000001 == 00000001
THIS IS INPUT VALUE:10
THIS IS COUNTER N:2
THIS IS SHIFTED VALUE:2
0
THIS IS INPUT VALUE:10  => 00001010
THIS IS COUNTER N:1     => 00000101 == 5
THIS IS SHIFTED VALUE:5 => 5
1                       => 00000101 & 00000001 == 00000001
THIS IS INPUT VALUE:10
THIS IS COUNTER N:0
THIS IS SHIFTED VALUE:10
0
*/

