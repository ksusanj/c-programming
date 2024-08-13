/*
 ============================================================================
 Name        : recursion.c
 Author      : kar1o
 Version     : 1.0
 Copyright   : © 2024
 Description : Simple program written in C - math
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

    printf ("Fibonnaci(6): %d\n", fibonacci(6));
    printf ("Factorial(5): %d\n", factorial(5));

	return EXIT_SUCCESS;
}
