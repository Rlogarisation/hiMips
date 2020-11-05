#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

/*
z5206267@wagner:~/COMP1521/LectureMipsData$ ./array_element_address 
&array[0]=0x7ffcb40e4d20
&array[1]=0x7ffcb40e4d28
&array[2]=0x7ffcb40e4d30
&array[3]=0x7ffcb40e4d38
&array[4]=0x7ffcb40e4d40
&array[5]=0x7ffcb40e4d48
&array[6]=0x7ffcb40e4d50
&array[7]=0x7ffcb40e4d58
&array[8]=0x7ffcb40e4d60
&array[9]=0x7ffcb40e4d68

example computation for address of array element \n
&array[0] + 7 * sizeof (double) = 0x7ffcb40e4d58
&array[0] + 7 * 8               = 0x7ffcb40e4d58
0x7ffcb40e4d20 + 7 * 8          = 0x7ffcb40e4d58
&array[7]                       = 0x7ffcb40e4d58
*/

int main(void) {
    double array[10];

    for (int i = 0; i < 10; i++) {
        printf("&array[%d]=%p\n", i, &array[i]);
    }

    printf("\nexample computation for address of array element \\n\n");

    uint64_t a = (uint64_t)&array[0];
    printf("&array[0] + 7 * sizeof (double) = 0x%lx\n",     a + 7 * sizeof (double));
    printf("&array[0] + 7 * %lx               = 0x%lx\n", sizeof (double), a + 7 * sizeof (double));
    printf("0x%lx + 7 * %lx          = 0x%lx\n", a, sizeof (double), a + 7 * sizeof (double));
    printf("&array[7]                       = %p\n", &array[7]);
}