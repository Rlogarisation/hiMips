/*
COMP1521 lab01 By Zheng Luo (z5206267@ad.unsw.edu.au)
Written 15/Sep/2020

Add code to no_odd_lines.c so that, given text on stdin, 
only print lines with an even number of characters to stdout.

no_odd_lines.c must only use:
fgets(3) to read one line at a time from stdin.
fputs(3) to print one line at a time to stdout.

e.g
./no_odd_lines
Hello, World
Hello, World!
Hello, World!
Andrew is the LiC of COMP1521
Andrew is the LiC of COMP1521
Andrew is the LiC of COMP1521, and Dylan is the Admin
Andrew is the LiC of COMP1521, and Dylan is the Admin
*/
#include <stdio.h>
#include <string.h>

#define MAX_SIZE 100

int main(void) {
	char inputArray[MAX_SIZE];
	while (fgets(inputArray, MAX_SIZE, stdin) != NULL) {
		// Even number of characters.
		if (strlen(inputArray) % 2 == 0) {
			fputs(inputArray, stdout);
		}
		
	}

	return 0;
}
