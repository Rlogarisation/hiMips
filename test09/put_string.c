#include <stdio.h>

#include "put_string.h"

// print s to stdout with a new line appended using fputc (only)
/*
./put_string hello
calling put_string("hello"):
hello
./put_string 'good bye'
calling put_string("good bye"):
good bye
*/

void put_string(char *s) {
   for (int i = 0; s[i] != '\0'; i++) {
      fputc(s[i], stdout);
      
   }
   fputc('\n',stdout);

}
