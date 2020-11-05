/*
COMP1521 lab01 By Zheng Luo (z5206267@ad.unsw.edu.au)
Written 15/Sep/2020

Write a C program no_uppercase.c which reads characters from its input 
and writes the same characters to its output, 
any upper case letters are replaced by their as lower case equivalent.
Your program should stop only at the end of input.

Add code to no_uppercase.c so that, given text on stdin, 
any uppercase letters are printed as lowercase to stdout.

no_uppercase.c must only use:
getchar(3) to read one character at a time from stdin.
putchar(3) to print one character at a time to stdout.

e.g.
./no_uppercase
ABC
abc
ABCabc123
abcabc123
123!@#
123!@#
Hello, World!
hello, world!
Andrew is the LiC of COMP1521
andrew is the lic of comp1521
(ctrl+d)
*/

#include <stdio.h>
#include <ctype.h>

int main(void) {
	int input = getchar();
	while (input != EOF) {
		if (input >= 'A' && input <= 'Z') {
			input = tolower(input);
		}
		putchar(input);
		input = getchar();
	}
	return 0;
}
