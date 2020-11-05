/*
COMP1521 lab01 Written by Zheng Luo(z5206267@ad.unsw.edu.au) at 16/Sep/2020

Given aline of input containing a fibonacci number 
the corresponding fibonacci number is printed.

Starting with 0 and 1:
Add the preceding two fibonacci number together 
to get the current fibonacci number:

Input is the number of n,
output is the corresponding F_n.
e.g.
./fibonacci
0 (input)
0
1 (input)
1
2 (input)
1
5 (input)
5
9 (input)
34
(ctrl+d)
*/

#include <stdio.h>
#include <stdlib.h>



int fibonaciiCalculator(int n, int *array);

int main(void)
{
	int array[47] = {0};
	int input;
	while (scanf("%d", &input) != EOF) {
		// To repeat unnecessary calculation.
		// "fibonacci.c should never calculate the sam fibonacci number twice "
		if (array[input] != 0) {
			printf("%d\n", array[input]);
		}
		// Otherwise perform calculation.
		else {
			printf("%d\n", fibonaciiCalculator(input, array));
		}
		
	}
	
	return EXIT_SUCCESS;
}

int fibonaciiCalculator(int n, int *array) {
	int result = 0;
	int counter = 2;
	array[0] = 0;
	array[1] = 1;
	while (counter <= n) {
		array[counter] = array[counter - 1] + array[counter - 2];
		result = array[counter];
		counter++;
	}
	return result; 
}
