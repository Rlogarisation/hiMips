/*
COMP1521 lab01 By Zheng Luo (z5206267@ad.unsw.edu.au)
Written 15/Sep/2020
Add code to my_args.c so that, given 0 or more command line arguments, 
the command line arguments are "pretty printed".

e.g.
./my_args
Program name: ./my_args
There are no other arguments
../lab01/my_args
Program name: ../lab01/my_args
There are no other arguments
./my_args hello world
Program name: ./my_args
There are 2 arguments:
	Argument 1 is "hello"
	Argument 2 is "world"
./my_args "hello world" 1 2 3 4 5
Program name: ./my_args
There are 6 arguments:
	Argument 1 is "hello world"
	Argument 2 is "1"
	Argument 3 is "2"
	Argument 4 is "3"
	Argument 5 is "4"
	Argument 6 is "5"
*/


#include <stdio.h>

int main(int argc, char **argv) {
	//(void) argc, (void) argv;
	printf("Program name: %s\n", argv[0]);
	if (argc == 1) {
		printf("There are no other arguments\n");
	} else {
		printf("There are %d arguments:\n", argc - 1);
		int counter = 1;
		while (counter < argc) {
			printf("	Argument %d is \"%s\"\n", counter, argv[counter]);
			counter++;
		}
	}
	return 0;
}
