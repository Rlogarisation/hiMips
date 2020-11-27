#include <stdio.h>
#include <stdint.h>

/*
z5206267@weill:~/COMP1521/LectureMipsData$ ./unalign 
6 
*/

int main(void) {
    uint8_t bytes[32];
    uint32_t *i = (uint32_t *)&bytes[12];
    // illegal store - not aligned on a 4-byte boundary
    *i = 0x03040506;
    printf("%d\n", bytes[12]);
}

/*
Explaination in the forum by Richard Liu:

Alignment in regards to memory is concerned with how data is arranged in memory. 
Unalignment is the opposite of this, 
when data does not conform to how memory should be arranged.

To break down the code:

We declare an array which has a size of 32 and holds 8 bits at each index
We then want to get a pointer to the address of an element in that array 
and store a value in there, which in this case is a hexadecimal number.
We then print out the decimal number stored at that index
So now lets look at what the binary representation of the hexadecimal number is:

0x03040506 = 00000011 00000100 00000101 00000110

   3        4        5        6
00000011 00000100 00000101 00000110
And since Andrew was using a big endian machine 
(dictates the layout of how bytes are stored in memory), 
the way it actually is stored in the bytes array is:

bytes[12] = 6
bytes[13] = 5
bytes[14] = 4
bytes[15] = 3

This is presuming you have stored the hexadecimal number 
at the memory address of bytes[12].

So now finally onto the alignment and unalignment question. 
Everything in C memory should be 4 byte aligned as 
that is how the compiler/programs read it. 
Now when trying to store memory to an odd address (an odd index), 
it would work fine, but only when it was compiled without any error checking. 
(which will work because of padding)

The main issue with this is that you are storing it at a non 4 byte memory address, 
so you are causing an unalignment in memory 
(which I believe is why memory addresses in C are 4 bytes in length). 
The issue with this is that now instead of just reading memory from one address, 
the program may now need to read memory across multiple memory addresses 
as memory is unaligned. 
Since if we expect everything to be 4 byte aligned, 
we read at the start of every memory address divisible by 4, 
but if we store something in address 5, it could overflow to the other addresses, 
now requiring the program to read 2 memory addresses - 
let alone handling where it should now read from and 
how to align memory after this point.

So in the context of our example:

&bytes[12] = 0x012
&bytes[13] = 0x013
&bytes[14] = 0x014

We could read bytes[12] just by looking at memory address 0x12, 
but for an odd address such as bytes[13] 
we now need to read memory addresses 0x12 - 0x14 to 
see the full data stored across these addresses.

*/