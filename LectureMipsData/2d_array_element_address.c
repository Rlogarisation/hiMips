/*
z5206267@weill:~/COMP1521/LectureMipsData$ ./2d_array_element_address 
0 1 2 3 
1 2 3 4 
2 3 4 5 
sizeof array[2][3] = 4
sizeof array[1] = 16
sizeof array = 48
&array=0x7fff55609980
&array[0]=0x7fff55609980
&array[0][0]=0x7fff55609980
&array[0][1]=0x7fff55609984
&array[0][2]=0x7fff55609988
&array[0][3]=0x7fff5560998c
&array[1]=0x7fff55609990
&array[1][0]=0x7fff55609990
&array[1][1]=0x7fff55609994
&array[1][2]=0x7fff55609998
&array[1][3]=0x7fff5560999c
&array[2]=0x7fff556099a0
&array[2][0]=0x7fff556099a0
&array[2][1]=0x7fff556099a4
&array[2][2]=0x7fff556099a8
&array[2][3]=0x7fff556099ac
*/



#include <stdio.h>

#define X 3
#define Y 4

int main(void) {
    int array[X][Y];

    for (int x = 0; x < X; x++) {
        for (int y = 0; y < Y; y++) {
            array[x][y] = x + y;
        }
    }

    for (int x = 0; x < X; x++) {
        for (int y = 0; y < Y; y++) {
            printf("%d ", array[x][y]);
        }
        printf("\n");
    }

    printf("sizeof array[2][3] = %lu\n", sizeof array[2][3]);
    printf("sizeof array[1] = %lu\n", sizeof array[1]);
    printf("sizeof array = %lu\n", sizeof array);

    printf("&array=%p\n", &array);
    for (int x = 0; x < X; x++) {
        printf("&array[%d]=%p\n", x, &array[x]);
        for (int y = 0; y < Y; y++) {
            printf("&array[%d][%d]=%p\n", x, y, &array[x][y]);
        }
    }
}