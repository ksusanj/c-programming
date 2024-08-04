/*
 ============================================================================
 Name        : words.c
 Author      : kar1o
 Version     : 1.0
 Copyright   : 2023
 Description : Simple program written in C using pointers and memory allocations
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {

	char **words = NULL;
	int i, j, w, l;

	printf("Enter number of words: ");
	scanf("%d", &w);

	// allocate memory dynamically
	words = (char**) malloc(sizeof(char*) * w);

	// iterate for each word
	for (i = 0; i < w; i++) {

		printf("Enter number of letters in %d. word: ", i + 1);
		scanf("%d", &l);

		// allocate memory dynamically with initialization
		*(words + i) = (char*) calloc((l + 1), sizeof(char));

		srand((unsigned) time(NULL));

		// generate random word
		for (j = 0; j < l; j++) {
			words[i][j] = (rand() % 26) + 65;
		}
	}

	// print out all generated words
	for (i = 0; i < w; i++) {
		printf("%s\n", *(words + i));
	}

	// deallocate the dynamically allocated memory
	free(words);

	return EXIT_SUCCESS;
}
