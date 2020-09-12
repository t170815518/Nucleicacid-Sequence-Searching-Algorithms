/* This file contains related functions for Rabin-Karp Algorithm */


#include "RabinKarpAlgorithm.h"
#include "FNAFilePreprocess.h"
#include <stddef.h>
#include <string.h>
#include <math.h>
#include <stdio.h>


#define BASE 3


// function prototypes
int RabinKarpAlgorithmNaive(char *geneticSequence, char *sequenceToFind, int *occurrence);
int bruteForceCompare(const char *sequenceToFind, int patternLength, const char *subString);


int RabinKarpAlgorithmNaive(char *geneticSequence, char *sequenceToFind, int *occurrence) {
    /* A simple and straightforward implementation of RabinKarp Algorithm.
     * The index of occurrence will be kept into int array, occurrence.
     * return: number of occurrence*/
    // preprocess pattern string
    int patternLength = 0;
    unsigned int patternHash = 0;
    while (sequenceToFind[patternLength] != '\0') {
        patternHash += pow(BASE, patternLength) * sequenceToFind[patternLength];
        patternLength += 1;
    }

    int occurrence_id = 0;
    char subString[patternLength];
    unsigned long i = 0;
    int numOfCollisions = 0;

    while (geneticSequence[i+patternLength-1] != '\0') {
        // process substring's hash value
        unsigned int subStringHash = 0;
        strncpy(subString, &geneticSequence[i], patternLength);
        for (int j = 0; j < patternLength; j++) {
            subStringHash += pow(BASE, j) * subString[j];
        }

        if (subStringHash == patternHash) {
            numOfCollisions += 1;
            if (bruteForceCompare(sequenceToFind, patternLength, subString) == 1) {
                occurrence[occurrence_id] = i;
                occurrence_id += 1;

                if (occurrence_id >= MAX_OCCURRENCES) {
                    printf("==========There are more than %d occurances. Only %d of them are displayed.==========\n",
                           MAX_OCCURRENCES, MAX_OCCURRENCES);
                    break;
                }
            }
        }
        i += 1;
    }
    printf("==========%d times of collisions==========\n", numOfCollisions);
    return occurrence_id;
}


int bruteForceCompare(const char *sequenceToFind, int patternLength, const char *subString) {
    for (int j = 0; j < patternLength; j++) {
        if (subString[j] != sequenceToFind[j]) {
            return 0;
        }
    }
    return 1;
}