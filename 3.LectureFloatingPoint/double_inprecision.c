// Andrew Taylor - andrewt@unsw.edu.au
// 18/2/2019

// The value 0.1 can not be precisely represented as a double
// As a result b != 0

#include <stdio.h>

int main(void) {
    double a, b;

    // Because there is no exact pattern in IEEE-754 for this number in 32 bits.
    a = 0.1; // (double)(0.1000000000000000056)

    // b == 1 - (10 * 0.1) != 0
    b = 1 - (a + a + a + a + a + a + a + a + a + a);

    // Dont do exact comparison with double (approximation).
    // better would be fabs(b) > 0.000001 rather than exact comparison.
    // man fabs()
    // These functions return the absolute value of the floating-point number x.
    if (b != 0) {  
        printf("1 != 0.1+0.1+0.1+0.1+0.1+0.1+0.1+0.1+0.1+0.1\n");
    }

    printf("b = %g\n", b); // prints 1.11022e-16

    return 0;
}