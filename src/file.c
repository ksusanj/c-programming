/*
 ============================================================================
 Name        : file.c
 Author      : kar1o
 Version     : 1.0
 Copyright   : © 2024
 Description : Simple program written in C - files
 ============================================================================
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct struct_book {
    char title[40+1];
    char author[40+1];
    char year[4];
} book;

typedef struct struct_movie {
    char title[40+1];
    char director[40+1];
    char writer[40+1];
    int year;
} movie;

int addBook(FILE* filePtr, book book) {
    
    char string[500] = {'\0'};

    strcpy(string, book.title);
    strcat(string, " ");
    strcat(string, book.author);
    strcat(string, " ");
    strcat(string, book.year);
    strcat(string, "\n");

    // 1. way
    for (int i = 0; string[i] != '\0'; i++) {
        fputc(string[i], filePtr);
    }

    // 2. way
    // fprintf(filePtr, "%s", string);

    // 3. way
    // fputs(string, filePtr);

    return 0;
}

int addMovie(FILE* filePtr, movie movie) {

    if(fwrite(&movie, sizeof(movie), 1, filePtr) != 1) {
        return -1;
    }

    return 0;
}

int printBooks(FILE* filePtr) {

    printf("Books:\n");

    // 1. way
    char character;
    while((character = fgetc(filePtr)) != EOF) {
        putchar(character);
    }

    // 2. way
    /*char line[500+1];
    while(fscanf(filePtr, "%500[^\n]%*[\n]", line) >= 0) {
        printf ("%s\n", line);
    }*/

    // 3. way
    /*char line[500+1];
    while (fgets(line, 500, filePtr) != NULL) {
        line[strlen(line)-1] = '\0';
        puts(line);
    }*/

    return 0;
}

int printMovies(FILE* filePtr) {

    printf("Movies:\n");

    movie movie;
    
    while (fread(&movie, sizeof(movie), 1, filePtr) == 1) {
        printf("%s %s %s %d\n", movie.title, movie.director, movie.writer, movie.year);
    }

    return 0;
}

int main() {

    book book1 = {"Catch-22", "Joseph Heller", "1961"};
    book book2 = {"Fight Club", "Chuck Palahniuk", "1996"};
    book book3 = {"The Unbearable Lightness of Being", "Milan Kundera", "1984"};

    movie movie1 = {"Trainspotting", "Danny Boyle", "Irvine Welsh", 1996};
    movie movie2 = {"American History Y", "Tony Kaye", "David McKenna", 1998};
    movie movie3 = {"The Ninth Gate", "Roman Polanski", "Arturo Perez Reverte", 1999};

    char fileName[] = "books.txt";
    char binaryFileName[] = "movies.dat";

    // Mode w - (Write only. Opens and clears the content of file or creates a new file if it doesn't exist.)
    FILE* filePtr = NULL;

    filePtr = fopen(fileName, "w");
    if (filePtr == NULL) {
        return -1;
    }

    addBook(filePtr, book1);
    addBook(filePtr, book2);
    addBook(filePtr, book3);

    if (fclose(filePtr) == EOF) {
    	return -1;
    }

    // Mode r - (Read only. Start at the beginning of the file.)
    filePtr = NULL;

    filePtr = fopen(fileName, "r");
    if (filePtr == NULL) {
        return -1;
    }

    printBooks(filePtr);
    printf("\n");

    if (fclose(filePtr) == EOF) {
    	return -1;
    }

    // Mode wb - (Binary write only. Opens and clears the content of file or creates a new file if it doesn't exist.)
    filePtr = NULL;

    filePtr = fopen(binaryFileName, "wb");
    if (filePtr == NULL) {
        return -1;
    }

    addMovie(filePtr, movie1);
    addMovie(filePtr, movie2);
    addMovie(filePtr, movie3);

    if (fclose(filePtr) == EOF) {
    	return -1;
    }

    // Mode rb - (Binary read only. Start at the beginning of the file.)
    filePtr = NULL;

    filePtr = fopen(binaryFileName, "rb");
    if (filePtr == NULL) {
        return -1;
    }

    printMovies(filePtr);
    printf("\n");

    if (fclose(filePtr) == EOF) {
    	return -1;
    }

    // Mode rb+ - (Binary read and write. Start at the beginning of the file.)
    filePtr = NULL;

    filePtr = fopen(binaryFileName, "rb+");
    if (filePtr == NULL) {
        return -1;
    }

    movie tmpMovie;

    fseek(filePtr, 1 * sizeof(movie), SEEK_SET);
    fread(&tmpMovie, sizeof(movie), 1, filePtr);

    // correct title of second movie
    strcpy(tmpMovie.title, "American History X");

    fseek(filePtr, -1 * sizeof(movie), SEEK_CUR);
    fwrite(&tmpMovie, sizeof(movie), 1, filePtr);

    fseek(filePtr, -3 * sizeof(movie), SEEK_END);
    printMovies(filePtr);

    if (fclose(filePtr) == EOF) {
    	return -1;
    }

    return EXIT_SUCCESS;
}