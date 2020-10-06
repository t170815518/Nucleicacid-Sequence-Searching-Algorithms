/* This file contains related functions for Rabin-Karp Algorithm */


#include "RabinKarpAlgorithm.h"
#include "FNAFilePreprocess.h"
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <limits.h>
#include <stdint.h>

#define BitsCount( val ) ( sizeof( val ) * CHAR_BIT )
#define Shift( val, steps ) ( steps % BitsCount( val ) )
#define ROL( val, steps ) ( ( val << Shift( val, steps ) ) | ( val >> ( BitsCount( val ) - Shift( val, steps ) ) ) )
#define BASE 3


// function prototypes
int bruteForceCompare(const char *sequenceToFind, int patternLength, const char *subString);
uint32_t rotl32 (uint32_t value, unsigned int count);


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

            if (bruteForceCompare(sequenceToFind, patternLength, subString) == 1) {
                occurrence[occurrence_id] = i;
                occurrence_id += 1;

                if (occurrence_id >= MAX_OCCURRENCES) {
                    printf("==========There are more than %d occurrences. Only %d of them are displayed.==========\n",
                           MAX_OCCURRENCES, MAX_OCCURRENCES);
                    break;
                }
            } else {
                numOfCollisions += 1;
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


int RabinKarpAlgorithm_ntHash(char *geneticSequence, char *sequenceToFind, int *occurrence) {
    /* RabinKarp Algorithm using ntHash.
    * The index of occurrence will be kept into int array, occurrence.
    * return: number of occurrence*/
    // preprocess pattern string
    int patternLength = 0;
    while (sequenceToFind[patternLength] != '\0') {
        patternLength += 1;
    }

    unsigned int patternHash = 0;
    for (int i = 0; i < patternLength; ++i) {
        patternHash = patternHash ^ ROL(valueMap[sequenceToFind[i]],patternLength-1-i);
    }

    int occurrence_id = 0;
    unsigned int subStringHash = 0;

    int numOfCollisions = 0;
    int hits = 0;
    int isSame;

    for (int i = 0; i < patternLength; ++i) {  // Please ensure the gene sequence is larger than the searching pattern
        subStringHash = subStringHash ^ ROL(valueMap[geneticSequence[i]],patternLength-1-i);
    }

    if (subStringHash == patternHash) {
        hits += 1;
        isSame = 1;
        for (int j = 0; j < patternLength; j++) {
            if (geneticSequence[j] != sequenceToFind[j]) {
                isSame = 0;
                break;
            }
        }

        if (isSame == 1) {
            occurrence[occurrence_id] = 0;
            occurrence_id += 1;
        } else {
            numOfCollisions += 1;
        }
    }

    unsigned long i = 1;

    while (geneticSequence[i+patternLength-1] != '\0') {
        // update substring's hash value
        subStringHash = ROL(subStringHash,1)^ROL(valueMap[geneticSequence[i-1]],patternLength)
                ^valueMap[geneticSequence[i+patternLength-1]];

        if (subStringHash == patternHash) {
            hits += 1;

            isSame = 1;
            for (int j = 0; j < patternLength; j++) {
                if (geneticSequence[i+j] != sequenceToFind[j]) {
                    isSame = 0;
                    break;
                }
            }

            if (isSame == 1) {
                occurrence[occurrence_id] = i;
                occurrence_id += 1;

                if (occurrence_id >= MAX_OCCURRENCES) {
                    printf("==========There are more than %d occurrences. Only %d of them are displayed.==========\n",
                           MAX_OCCURRENCES, MAX_OCCURRENCES);
                    break;
                }
            } else {
                numOfCollisions += 1;
            }
        }
        i += 1;
    }
    printf("==========%d times of collisions==========\n", numOfCollisions);
    return occurrence_id;
}


uint32_t rotl32 (uint32_t value, unsigned int count) {
    /* ref: wikipedia */
    const unsigned int mask = CHAR_BIT * sizeof(value) - 1;
    count &= mask;
    return (value << count) | (value >> (-count & mask));
}