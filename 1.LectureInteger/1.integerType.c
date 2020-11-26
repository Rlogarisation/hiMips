// Andrew Taylor - andrewt@unsw.edu.au
// 16/9/2019

// Print size and min and max values of integer types

#include <stdio.h>
#include <limits.h>

// What does %lu means?
/*
A printf format specifier follows the form 
%[flags][width][.precision][length]specifier.
u is a specifier meaning "unsigned decimal integer".
l is a length modifier meaning "long".
*/

// What does the number 20 means for %20d?
/*
The width of number printed is 20 space width,
it usually to do with the formating.
*/

// What is signed/unsigned char, short, long and etc? When would they be used?
/*
char is == unsigned char by default, signed and signed char have same size, but 
different range. 
Unsigned is only storing positive number, 
but signed stores both positive and negative number.

*/

int main(void) {

    char c;
    printf("char               %lu bytes min=%20d, max=%20d\n", 
    sizeof c, CHAR_MIN, CHAR_MAX);

    signed char sc;
    printf("signed char        %lu bytes min=%20d, max=%20d\n", 
    sizeof sc, SCHAR_MIN, SCHAR_MAX);

    unsigned char uc;
    printf("unsigned char      %lu bytes min=%20d, max=%20d\n", 
    sizeof uc, 0, UCHAR_MAX);

    short s;
    printf("short              %lu bytes min=%20d, max=%20d\n", 
    sizeof s, SHRT_MIN, SHRT_MAX);

    unsigned short us;
    printf("unsigned short     %lu bytes min=%20d, max=%20d\n", 
    sizeof us, 0, USHRT_MAX);

    int i;
    printf("int                %lu bytes min=%20d, max=%20d\n", 
    sizeof i, INT_MIN, INT_MAX);

    unsigned int ui;
    printf("unsigned int       %lu bytes min=%20d, max=%20d\n", 
    sizeof ui, 0, UINT_MAX);

    long l;
    printf("long               %lu bytes min=%20ld, max=%20ld\n", 
    sizeof l, LONG_MIN, LONG_MAX);

    unsigned long ul;
    printf("unsigned long      %lu bytes min=%20d, max=%20lu\n", 
    sizeof ul, 0, ULONG_MAX);

    long long ll;
    printf("long long          %lu bytes min=%20lld, max=%20lld\n", 
    sizeof ll, LLONG_MIN, LLONG_MAX);

    unsigned long long ull;
    printf("unsigned long long %lu bytes min=%20d, max=%20llu\n", 
    sizeof ull, 0, ULLONG_MAX);

    return 0;
}

/*
dcc output:
z5206267@wagner:~/COMP1521/LectureInteger$ ./integerType 
char               1 bytes min=                -128, max=                 127
signed char        1 bytes min=                -128, max=                 127
unsigned char      1 bytes min=                   0, max=                 255
short              2 bytes min=              -32768, max=               32767
unsigned short     2 bytes min=                   0, max=               65535
int                4 bytes min=         -2147483648, max=          2147483647
unsigned int       4 bytes min=                   0, max=                  -1
long               8 bytes min=-9223372036854775808, max= 9223372036854775807
unsigned long      8 bytes min=                   0, max=18446744073709551615
long long          8 bytes min=-9223372036854775808, max= 9223372036854775807
unsigned long long 8 bytes min=                   0, max=18446744073709551615
*/