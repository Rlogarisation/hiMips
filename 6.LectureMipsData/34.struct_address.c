#include <stdio.h>
#include <stdint.h>

/*
z5206267@weill:~/COMP1521/LectureMipsData$ ./struct_address 
&v1      = 0x7fff28f30f80
&(v1.i0) = 0x7fff28f30f80
&(v1.i1) = 0x7fff28f30f84
&(v1.i2) = 0x7fff28f30f88
&(v1.i3) = 0x7fff28f30f8c

This shows struct padding
&v2      = 0x7fff28f30fa0
&(v2.b)  = 0x7fff28f30fa0
&(v2.l)  = 0x7fff28f30fa8

SO IT WILL USED BIGGEST BYTE PATTERN TO ALIGN?
*/
struct s1 {
    uint32_t   i0; // 4 bytes
    uint32_t   i1;
    uint32_t   i2;
    uint32_t   i3;
};

struct s2 {
    uint8_t    b; // 1 bytes
    // But compute creates a 8 bytes space for b.
    uint64_t   l; // 8 bytes
};

int main(void) {
    struct s1 v1;

    printf("&v1      = %p\n", &v1);
    printf("&(v1.i0) = %p\n", &(v1.i0));
    printf("&(v1.i1) = %p\n", &(v1.i1));
    printf("&(v1.i2) = %p\n", &(v1.i2));
    printf("&(v1.i3) = %p\n", &(v1.i3));

    printf("\nThis shows struct padding\n");

    struct s2 v2;
    printf("&v2      = %p\n", &v2);
    printf("&(v2.b)  = %p\n", &(v2.b));
    printf("&(v2.l)  = %p\n", &(v2.l));
}