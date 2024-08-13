/*
 ============================================================================
 Name        : words.c
 Author      : kar1o
 Version     : 1.0
 Copyright   : © 2024
 Description : Simple program written in C - finding most common word in text
 ============================================================================
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// contains word text, word count (number of occurrences) and link to another same struct
typedef struct struct_data {
    char* word;
    int count;
    struct struct_data* next;
} data;

void addWord(data* _data, char* word);
int countWord(data* _data, char* word);
void deleteData(data* _data);
void printData(data* _data);

int main(void) {
	
    data* _data = (data*) malloc(sizeof(data));

    // text to analyse
    char text[] = "A territorial dispute over islands in the East China Sea boiled over into often "
                "violent anti-Japanese demonstration in China last September has led to tensions "
                "between the world's second and third largest economies. Last week, new Japanese "
                "Prime Minister Shinzo Abe returned from a trip to Southeast Asia to shore up "
                "support of nations also at odds with China over disputed land claims in the South China Sea.";


    char delimiters[] = " \t\n,;";

    // split text into words
    char* word = strtok(text, delimiters);

    while (word != NULL) {
        addWord(_data, word);

        // call with NULL it will return next token (word)
        word = strtok(NULL, delimiters);
    }

    // print data
    printData(_data);

    // delete data
    deleteData(_data);

	return EXIT_SUCCESS;
}

void addWord(data* _data, char* word) {

    data* iterator;
    data* lastData;

    for (iterator = _data; iterator != NULL; iterator = iterator->next) {
        if ((iterator->word != NULL) && (strcmp(iterator->word, word) == 0)) {
            // word exists - increase counter and exit
            iterator->count++;
            return;
        }

        lastData = iterator;
    }
    
    // allocate memory dynamically
    data* newData = (data*) malloc(sizeof(data));

    // allocate memory dynamically with initialization
    newData->word = (char*) calloc(strlen(word), sizeof(char));
    strcpy(newData->word, word);

    newData->count = 1;
    newData->next = NULL;

    lastData->next = newData;
}

int countWord(data* _data, char* word) {

    int count = 0;

    for (data* iterator = _data; iterator != NULL; iterator = iterator->next) {
        if ((iterator->word != NULL) && (strcmp(iterator->word, word) == 0)) {
            count++;
        }
    }

    return count;
}

void deleteData(data* _data) {

    if (_data->next != NULL) {
        deleteData(_data->next);
    }

    if (_data->word != NULL) {
        free(_data->word);
    }
    
    if (_data != NULL) {
        free(_data);
    }
}

void printData(data* _data) {

    for (data* iterator = _data; iterator != NULL; iterator = iterator->next) {
        if (iterator->word != NULL) {
            printf("> \"%s\" occurred %d times.\n", iterator->word, iterator->count);
        }
    }
}