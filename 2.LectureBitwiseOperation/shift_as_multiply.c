// Andrew Taylor - andrewt@unsw.edu.au
// 08/06/2020

// Demonstrate that shifting the bits of a positive int
// left 1 position is equivalent to multiplying by 2

/*
$ dcc shift_as_multiply.c print_bits.c -o shift_as_multiply
$ ./shift_as_multiply 4
2 to the power of 4 is 16
In binary it is: 00000000000000000000000000010000
$ ./shift_as_multiply 20
2 to the power of 20 is 1048576
In binary it is: 00000000000100000000000000000000
$ ./shift_as_multiply 31
2 to the power of 31 is 2147483648
In binary it is: 10000000000000000000000000000000
$
*/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "print_bits.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        /*
        The C library function 
        int fprintf(FILE *stream, const char *format, ...) 
        sends formatted output to a stream.

        Stderr, also known as standard error, 
        is the default file descriptor where a process can write error messages.
        */
        fprintf(stderr, "Usage: %s <exponent>\n", argv[0]);
        // Output: Usage: ./shift_as_multiply <exponent>

        // Why return 1, what does it mean?
        /*
        return from main() is equivalent to exit

        the program terminates immediately execution with exit status set 
        as the value passed to return or exit

        return in an inner function (not main) will terminate immediately 
        the execution of the specific function returning the given result 
        to the calling function.

        exit from anywhere on your code will terminate program execution immediately.

        status 0 means the program succeeded.
        status different from 0 means the program exited due to error or anomaly.
        If you exit with a status different from 0 
        you're supposed to fprintf an error message to stderr  
        */
        return 1;
    }

    // Converting string into number.
    int n = strtol(argv[1], NULL, 0);

    uint32_t power_of_two;

    int n_bits = 8 * sizeof power_of_two;

    if (n >= n_bits) {
        fprintf(stderr, "n is too large\n");
        return 1;
    }
    //00000000000000000000000000000001
    power_of_two = 1;   
    /*
    n is the number of power, 
    e.g if we want to ask the power of 4, then n==4,
    we left shift 1<<4, make it become 00000000000000000000000000010000
    Then this is 2^4 = 16.
    */
    power_of_two = power_of_two << n;
    
    printf("2 to the power of %d is %u\n", n, power_of_two);

    printf("In binary it is: ");
    print_bits(power_of_two, n_bits);
    printf("\n");

    return 0;
}