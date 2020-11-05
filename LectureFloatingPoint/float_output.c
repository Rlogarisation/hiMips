
/*
z5206267@wagner:~/COMP1521/LectureFloatingPoint$ ./float_output 
0.571429
5.714286e-01
0.571429
0.571428571
       0.6

*/

#include <stdio.h>

int main(void) {
    // If this is written as (int) 4/ (int) 7,
    // Then d will produce d=0.
    double d = 4.0/7;
    // Or can be written as:
    // double d = (double)4/(double)7;

    // prints in decimal with (default) 6 decimal places
    printf("%lf\n", d);        // prints 0.571429

    // prints in scientific notation
    printf("%le\n", d);       // prints 5.714286e-01

    // picks best of decimal and scientific notation
    printf("%lg\n", d);       // prints 0.571429

    //  prints in decimal with 9 decimal places
    printf("%.9lf\n", d);    // prints 0.571428571

    //  prints in decimal with 1 decimal place and field width of 10
    printf("%10.1lf\n", d);  // prints        0.6

    return 0;
}