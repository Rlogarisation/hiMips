/*
z5206267@weill:~/COMP1521/LectureMipsData$ ./struct_packing 
sizeof v1 = 32
sizeof v2 = 20
alignment rules mean struct s1 is padded
&(v1.c1) = 0x7ffe1a322080
&(v1.l1) = 0x7ffe1a322084
&(v1.c2) = 0x7ffe1a322088
&(v1.l2) = 0x7ffe1a32208c
struct s2 is not padded
&(v2.l1) = 0x7ffe1a3220c0
&(v2.l2) = 0x7ffe1a3220c4
&(v2.l4) = 0x7ffe1a3220cc
&(v2.c1) = 0x7ffe1a3220d0
&(v2.c2) = 0x7ffe1a3220d1

*/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

void print_bytes(void *v, int n);

struct s1 {
    uint8_t    c1;  // 1 byte
    uint32_t   l1;  // 4 bytes
    uint8_t    c2;
    uint32_t   l2;
    uint8_t    c3;
    uint32_t   l3;
    uint8_t    c4;
    uint32_t   l4;
};

struct s2 {
    uint32_t   l1;  // 4 bytes
    uint32_t   l2;
    uint32_t   l3;
    uint32_t   l4;
    uint8_t    c1;  // 1 byte
    uint8_t    c2;
    uint8_t    c3;
    uint8_t    c4;
};

int main(void) {
    struct s1 v1;
    struct s2 v2;

    printf("sizeof v1 = %lu\n", sizeof v1);
    printf("sizeof v2 = %lu\n", sizeof v2);

    printf("alignment rules mean struct s1 is padded\n");

    printf("&(v1.c1) = %p\n", &(v1.c1));
    printf("&(v1.l1) = %p\n", &(v1.l1));
    printf("&(v1.c2) = %p\n", &(v1.c2));
    printf("&(v1.l2) = %p\n", &(v1.l2));

    printf("struct s2 is not padded\n");

    printf("&(v2.l1) = %p\n", &(v2.l1));
    printf("&(v2.l2) = %p\n", &(v2.l2));
    printf("&(v2.l4) = %p\n", &(v2.l4));
    printf("&(v2.c1) = %p\n", &(v2.c1));
    printf("&(v2.c2) = %p\n", &(v2.c2));
}