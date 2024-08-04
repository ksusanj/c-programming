/*
 ============================================================================
 Name        : recursion.c
 Author      : kar1o
 Version     : 1.0
 Copyright   : 2023
 Description : Simple program written in C
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int fibonacci(int n) {
    if (n <= 1) {
        return 1;
    } else {
        return fibonacci(n-2) + fibonacci(n-1);
    }
}

int factorial(int n){
    if (n <= 1) {
        return 1;
    } else {
        return n * factorial(n-1);
    }
}

int main(void) {

    printf ("%d\n", fibonacci(6));
    printf ("%d\n", factorial(5));

	return EXIT_SUCCESS;
}
