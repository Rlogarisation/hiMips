#include <stdio.h>

#include "get_string.h"

// print a line from stream using fgetc (only)
// reads in at most one less than size characters from stream and stores them into the
// buffer pointed to by s.  Reading stops after an EOF or a newline.  
// If a newline is read, it is stored  into  the buffer. 
// A terminating null byte ('\0') is stored after the last character in the buffer.


/*
./get_string 12
calling get_string(s, 12, stdin):
hello
s now contains 'hello
'
./get_string 16
calling get_string(s, 16, stdin):
good bye
s now contains 'good bye
'
./get_string 5
calling get_string(s, 5, stdin):
hello
s now contains 'hell'
*/
void get_string(char *s, int size, FILE *stream) {
    int c;
    int counter = 0;
    while ((c = fgetc(stream)) != EOF && counter < size - 1) {
        if (c < '0' || c > 'z') {
            break;
        }
        s[counter] = c;
        counter++;
    }
    if (counter < size - 1) {
        s[counter] = '\n';
        s[counter + 1] = '\0';
    } else {
        s[counter] = '\0';
    }
    
    
}
