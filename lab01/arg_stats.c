// ***********************IMPORTANT POINTER CASE *********************

/*
COMP1521 lab01 By Zheng Luo (z5206267@ad.unsw.edu.au)
Written 15/Sep/2020

Add code to arg_stats.c so that, given 1 or more command line arguments, 
it prints the minimum and maximum values, 
the sum and product of all the values, and the mean of all the values.

e.g.
./arg_stats
Usage: ./arg_stats NUMBER [NUMBER ...]
./arg_stats 1
MIN:  1
MAX:  1
SUM:  1
PROD: 1
MEAN: 1
./arg_stats 1 2 3 4 5 6 7 8 9
MIN:  1
MAX:  9
SUM:  45
PROD: 362880
MEAN: 5
./arg_stats 9 8 7 6 1 2 3 5 4
MIN:  1
MAX:  9
SUM:  45
PROD: 362880
MEAN: 5
./arg_stats 1 9 1 9 1 9
MIN:  1
MAX:  9
SUM:  30
PROD: 729
MEAN: 5
*/
// argv is taking strings in, 
// so we must follow its format.
#include <stdio.h>
#include <stdlib.h>

#define MAX 10

int findMin(int argc, int *array);
int findMax(int argc, int *array);
int findSum(int argc, int *array);
int findProduct(int argc, int *array);
int findMean(int argc, int sum);

int main(int argc, char **argv) {
    int counter = 1;
    int counterForArray = 0;
    int array[MAX];
    // Rearrange the string into int type array.
    while (counter < argc) {
        array[counterForArray] = atoi(argv[counter]);
        //printf("%d\n", array[counterForArray]);
        counter++;
        counterForArray++;
    }

    if (argc == 1) {
        printf("Usage: ./arg_stats NUMBER [NUMBER ...]\n");
    }
    else {
        printf("MIN:  %d\n", findMin(argc, array));
        printf("MAX:  %d\n", findMax(argc, array));
        printf("SUM:  %d\n", findSum(argc, array));
        printf("PROD: %d\n", findProduct(argc, array));
        printf("MEAN: %d\n", findMean(argc, findSum(argc, array)));
    }

    return 0;
}

int findMin(int argc, int *array) {
    int counter = 0;
    int min = array[counter];
    while (counter < argc - 1) {
        if (array[counter] < min) {
            min = array[counter];
        }
        counter++;
    }
    return min;
}

int findMax(int argc, int *array) {
    int counter = 0;
    int max = array[counter];
    while (counter < argc - 1) {
        if (array[counter] > max) {
            max = array[counter];
        }
        counter++;
    }
    return max;
}

int findSum(int argc, int *array) {
    int sum = 0;
    int counter = 0;
    while (counter < argc - 1) {
        sum += array[counter];
        counter++;
    }
    return sum;
}

int findProduct(int argc, int *array) {
    int product = 1;
    int counter = 0;
    while (counter < argc - 1) {
        product = product * array[counter];
        counter++;
    }
    return product;
}

int findMean(int argc, int sum) {
    return sum / (argc - 1);
}

