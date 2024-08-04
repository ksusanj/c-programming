/*
 ============================================================================
 Name        : matrix.c
 Author      : kar1o
 Version     : 1.0
 Copyright   : © 2023
 Description : Simple matrix program written in C
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAXR 100
#define MAXC 100

void printMatrix(int *matrix, int r, int c);
void sumMatrices(int *matrix1, int *matrix2, int r, int c);
void moveRowUp(int *matrix, int r, int c);
void moveRowDown(int *matrix, int r, int c);
void sumRowsAndColumns(int *matrix, int r, int c);

int main() {

	int matrix1[MAXR][MAXC], matrix2[MAXR][MAXC];
	int r, c, i, j;
	int fillChoice, operationChoice;

	do {
		printf("Enter the row and column size: ");
		scanf("%d %d", &r, &c);
	} while (r < 1 || r > MAXR || c < 1 || c > MAXC);

	// Fill matrix 1
	printf("\nFill the Matrix 1:");
	printf("\n------------------");
	printf("\n1. automatic\n2. manual\n");

	do {
		scanf("%d", &fillChoice);

		if (fillChoice == 1) {
			srand((unsigned) time(NULL));

			for (i = 0; i < r; i++) {
				for (j = 0; j < c; j++) {
					matrix1[i][j] = rand() % 10;
					printf("%3d", matrix1[i][j]);
				}
				printf("\r");
			}
		} else if (fillChoice == 2) {
			for (i = 0; i < r; i++) {
				for (j = 0; j < c; j++) {
					printf("Enter value for %d,%d position: ", i, j);
					scanf("%d", &matrix1[i][j]);
				}
			}

			for (i = 0; i < r; i++) {
				for (j = 0; j < c; j++) {
					printf("%3d", matrix1[i][j]);
				}
				printf("\r");
			}
		}
	} while (fillChoice != 1 && fillChoice != 2);

	// reset fillChoice
	fillChoice = 0;

	// Fill matrix 2
	printf("\nFill the Matrix 2:");
	printf("\n------------------");
	printf("\n1. automatic\n2. manual\n");

	do {
		scanf("%d", &fillChoice);

		if (fillChoice == 1) {
			srand((unsigned) time(NULL));

			for (i = 0; i < r; i++) {
				for (j = 0; j < c; j++) {
					matrix2[i][j] = rand() % 10;
					printf("%3d", matrix2[i][j]);
				}
				printf("\r");
			}
		} else if (fillChoice == 2) {
			for (i = 0; i < r; i++) {
				for (j = 0; j < c; j++) {
					printf("Enter value for %d,%d position: ", i, j);
					scanf("%d", &matrix2[i][j]);
				}
			}

			for (i = 0; i < r; i++) {
				for (j = 0; j < c; j++) {
					printf("%3d", matrix2[i][j]);
				}
				printf("\r");
			}
		}
	} while (fillChoice != 1 && fillChoice != 2);

	// Operations
	do {
		printf("\nChoose matrix operation:");
		printf("\n-------------------------------------");
		printf("\n1. Sum Matrix 1 and Matrix 2");
		printf("\n2. Move row up Matrix 1");
		printf("\n3. Move row up Matrix 2");
		printf("\n4. Move row down Matrix 1");
		printf("\n5. Move row down Matrix 2");
		printf("\n6. Sum rows and columns for Matrix 1");
		printf("\n7. Sum rows and columns for Matrix 2");
		printf("\n8. Print Matrix 1");
		printf("\n9. Print Matrix 2");
		printf("\n10. Exit");
		printf("\n-------------------------------------");

		scanf("%d", &operationChoice);

		switch (operationChoice) {
			case (1):
				sumMatrices(&matrix1[0][0], &matrix2[0][0], r, c);
				break;
			case (2):
				moveRowUp(&matrix1[0][0], r, c);
				break;
			case (3):
				moveRowUp(&matrix2[0][0], r, c);
				break;
			case (4):
				moveRowDown(&matrix1[0][0], r, c);
				break;
			case (5):
				moveRowDown(&matrix2[0][0], r, c);
				break;
			case (6):
				sumRowsAndColumns(&matrix1[0][0], r, c);
				break;
			case (7):
				sumRowsAndColumns(&matrix2[0][0], r, c);
				break;
			case (8):
				printMatrix(&matrix1[0][0], r, c);
				break;
			case (9):
				printMatrix(&matrix2[0][0], r, c);
				break;
			case (10):
				goto end;
				break;
			default:
				printf("\nInvalid operation!");
		}
	} while (1);

	end:
	return EXIT_SUCCESS;
}

void printMatrix(int *matrix, int r, int c) {

	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			// current element of matrix
			printf("%3d", *(matrix + i * MAXC + j));
		}
		printf("\n");
	}
}

void sumMatrices(int *matrix1, int *matrix2, int r, int c) {

	int matrix3[MAXR][MAXC];

	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			matrix3[i][j] = *(matrix1 + i * MAXC + j) + *(matrix2 + i * MAXC + j);
		}
	}

	printf("\nResult:\n");
	printMatrix(&matrix3[0][0], r, c);
}

void moveRowUp(int *matrix, int r, int c) {

	int tmpRow[c];

	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			if (i == 0) { // first row
				tmpRow[j] = *(matrix + i * MAXC + j); // remember each element of first row

				// matrix has more than one row
				if (r > 1) {
					*(matrix + i * MAXC + j) = *(matrix + (i + 1) * MAXC + j);
				}
			} else if (i == (r - 1)) { // last row
				*(matrix + i * MAXC + j) = tmpRow[j];
			} else {
				*(matrix + i * MAXC + j) = *(matrix + (i + 1) * MAXC + j);
			}
		}
	}

	printf("\nResult:\n");
	printMatrix(matrix, r, c);
}

void moveRowDown(int *matrix, int r, int c) {

	int tmpRow[c];

	for (int i = r; i > 0; i--) {
		for (int j = 0; j < c; j++) {
			if (i == r) { // last row
				tmpRow[j] = *(matrix + (i - 1) * MAXC + j); // remember each element of last row

				if (r > 1) {
					*(matrix + (i - 1) * MAXC + j) = *(matrix + (i - 2) * MAXC + j);
				}
			} else if (i == 1) { // first row
				*(matrix + (i - 1) * MAXC + j) = tmpRow[j];
			} else {
				*(matrix + (i - 1) * MAXC + j) = *(matrix + (i - 2) * MAXC + j);
			}
		}
	}

	printf("\nResult:\n");
	printMatrix(matrix, r, c);
}

void sumRowsAndColumns(int *matrix, int r, int c) {

	int rowSum, clmSum;

	printf("\nResult:\n");

	for (int i = 0; i < r; i++) {
		rowSum = 0;

		for (int j = 0; j < c; j++) {
			printf("%3d", *(matrix + i * MAXC + j));
			rowSum += *(matrix + i * MAXC + j);
		}

		printf("%3d\n", rowSum);
	}

	for (int j = 0; j < c; j++) {
		clmSum = 0;

		for (int i = 0; i < r; i++) {
			clmSum += *(matrix + i * MAXC + j);
		}

		printf("%3d", clmSum);
	}
}
