/*
COMP1521 lab01 Zheng Luo (z5206267@ad.unsw.edu.au)
Written 15/Sep/2020
Write a C program no_vowels.c which reads characters 
from its input and writes the same characters to its output, 
except it does not write vowels.
Your program should stop only at the end of input.

no_vowels.c must only use:
scanf(3) to read one character at a time from stdin.
printf(3) to print one character at a time to stdout.

e.g.
./no_vowels
Hello, World!
Hll, Wrld!
(ctrl+d)
echo "Peter Piper picked a peck of pickled peppers." > input
./no_vowels < input
Ptr Ppr pckd  pck f pckld ppprs.

./no_vowels
Andrew is the LiC of COMP1521
ndrw s th LC f CMP1521
Are you saying 'Boo' or 'Boo-Urns'?
r y syng 'B' r 'B-rns'?
In this house, we obey the laws of thermodynamics!
n ths hs, w by th lws f thrmdynmcs!
(ctrl+d)
*/

#include <stdio.h>
#include <stdlib.h>

#define VOWEL 1
#define NOT_VOWEL 0

int vowel(char input);

int main(void) {
	char input;
	while (scanf("%c", &input) != EOF) {
		if (vowel(input) != VOWEL) {
			printf("%c", input);
		}
	}
	return 0;
}

int vowel(char input) {
	if (input == 'a' || input == 'e' || input == 'i' || input == 'o' || 
	input == 'u') {
		return VOWEL;
	}
	else if (input == 'A' || input == 'E' || input == 'I' || input == 'O' || 
	input == 'U') {
		return VOWEL;
	}
	else {
		return NOT_VOWEL;
	}
};
