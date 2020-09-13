#include "FNAFilePreprocess.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


unsigned int valueMap[86];  // ASCII value of U = 85
const unsigned long MAX_OCCURRENCES = 100;
const unsigned long MAX_LENGTH = 10000000000;
const unsigned long MAX_INPUT = 100000;

char *readFile();


char *readFile() {
    /* read from the specified file.
     * Return: char array, with non-DNA/RNA information deleted.*/
    // change the path here:
    FILE * file = fopen("/Users/tangyuting/Study/CZ2001/lab/dna.200MB", "r");

    char dummyInput[200];
    char *inputSequence = (char*)malloc(MAX_LENGTH * sizeof(char));
    char buffer;
    unsigned int id = 0;

    fgets(dummyInput, 200, file);  // remove start lines from the file
    while (buffer = fgetc(file), buffer != EOF) {
        if (buffer == '\n') {
            continue;
        } else {
            inputSequence[id] = buffer;
            id += 1;
        }
    }
    inputSequence[id] = '\0';

    fclose(file);
    return inputSequence;
}


void initializeValueMap() {
    /* Initialize the binary values for C,A,T,U,G in uniform distribution. */
    srand (time(NULL));

    valueMap['G'] = 0;
    valueMap['A'] = 0;
    valueMap['C'] = 0;
    valueMap['T'] = 0;
    valueMap['U'] = 0;

    for (int i = 0; i < sizeof(int) * 8; i++) {
        valueMap['G'] = valueMap['G'] * 2 + rand() % 2;
        valueMap['A'] = valueMap['A'] * 2 + rand() % 2;
        valueMap['C'] = valueMap['C'] * 2 + rand() % 2;
        valueMap['T'] = valueMap['T'] * 2 + rand() % 2;
        valueMap['U'] = valueMap['U'] * 2 + rand() % 2;
    }

    printf("==========Random Numbers Generated==========\n");
    printf("G = %u\n", valueMap['G']);
    printf("A = %u\n", valueMap['A']);
    printf("C = %u\n", valueMap['C']);
    printf("T = %u\n", valueMap['T']);
    printf("U = %u\n", valueMap['U']);
}