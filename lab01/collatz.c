/*
COMP1521 lab01 Written by Zheng Luo(z5206267@ad.unsw.edu.au) at 16/Sep/2020

Take a single positive integer as a command-line argument 
and prints the collatz chain for that number.

This is how the collatz chain is calculated.

If the current number is 1, the series terminates.
If the current number is ODD, 
then multiply by 3 and add 1 to get the next number
If the current number is EVEN, then divide by 2 to get the next number

e.g.
./collatz
Usage: ./collatz NUMBER
./collatz 1
1
./collatz 12
12
6
3
10
5
16
8
4
2
1
./collatz 10
10
5
16
8
4
2
1
*/

#include <stdio.h>
#include <stdlib.h>

void collatzFunction(int input);

int main(int argc, char **argv)
{
	//(void) argc, (void)argv;
	// If no number is entered, print out its usage.
	if (argc == 1) {
		printf("Usage: ./collatz NUMBER\n");
	}
	else if (argc == 2) {
		// Convert the string type char into int type.
		int inputNumber = atoi(argv[1]);
		collatzFunction(inputNumber);

	}
	return EXIT_SUCCESS;
}

void collatzFunction(int input) {
	int variable = input;
	while (variable != 1) {
		printf("%d\n", variable);
		// Even
		if (variable % 2 == 0) {
			variable = variable / 2;
		}
		// Odd
		else if (variable % 2 != 0) {
			variable = variable * 3 + 1;
		}
	}
	printf("%d\n", variable);
}