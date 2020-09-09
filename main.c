#include <stdio.h>
#include <math.h>
#include <string.h>

#define MAX_OCCURANCE 100
#define MAX_LENGTH 1000000
#define MAX_INPUT 100000
#define BASE 10

int getLength(const char *);
unsigned int hash(char *stringSegment, int length);
int bruteForceCompare(const char *sequenceToFind, int patternLength, const char *subString);
int RabinKarpAlgorithm(char *geneticSequence, char *sequenceToFind, int *occurances);
char *readFile();

int main() {
    char * geneticSequence = readFile();
    char patternSequence[MAX_INPUT];
    scanf("%s", patternSequence);

    int occurances[MAX_OCCURANCE] = {};
    int occurancesNum = RabinKarpAlgorithm(geneticSequence, patternSequence, occurances);
    if (occurancesNum != 0) {
        for (int i = 0; i < occurancesNum; i++) {
            printf("%d ", occurances[i]);
        }
    } else {
        printf("Not Found.");
    }

    return 0;
}

char *readFile() {
    /* read from the specified file.
     * Return: char array, with non-DNA/RNA information deleted.*/
    FILE * file = fopen("/Users/tangyuting/Study/CZ2001/lab/GCF_009858895.2_ASM985889v3_genomic.fna", "r");
    char dummyInput[200];
    char inputSequence[MAX_LENGTH] = {};
    char buffer;
    unsigned int id = 0;

    fgets(dummyInput, 200, file);
    while (buffer = fgetc(file), buffer != EOF) {
        if (buffer == '\n') {
            continue;
        } else {
            inputSequence[id] = buffer;
            id += 1;
        }
    }
    fclose(file);
    return inputSequence;
}

unsigned int hash(char *stringSegment, int length) {
    unsigned int hash_value = 0;
    for (int i = 0; i < length; i++) {
        hash_value += pow(BASE, i) * stringSegment[i];
    }
    return hash_value;
}

int RabinKarpAlgorithm(char *geneticSequence, char *sequenceToFind, int *occurances) {
    /* Find matching patterns for string in Rabin-Karp Algorithm.
     * The index of occurrance will be kept into occurances array.
     * return: number of occurances*/
    int occurance_id = 0;
    int patternLength = getLength(sequenceToFind);
    int geneticLength = getLength(geneticSequence);
    unsigned int patternHash = hash(sequenceToFind, patternLength);

    for (int i = 0; i < geneticLength - patternLength; i++) {
        char subString[patternLength];
        strncpy(subString, &geneticSequence[i], patternLength);
        if (hash(subString, patternLength) != patternHash) {
            continue;
        } else {
            if (bruteForceCompare(sequenceToFind, patternLength, subString) == 1) {
                occurances[occurance_id] = i;
                occurance_id += 1;
                if (occurance_id >= MAX_OCCURANCE) {
                    printf("There are more than %d occurances. Only %d of them are displayed.\n", MAX_OCCURANCE, MAX_OCCURANCE);
                    break;
                }
            }
        }
    }
    return occurance_id;
}

int bruteForceCompare(const char *sequenceToFind, int patternLength, const char *subString) {
    for (int j = 0; j < patternLength; j++) {
        if (subString[j] != sequenceToFind[j]) {
            return 0;
        }
    }
    return 1;
}

int getLength(const char *string) {
    int patternLength = 0;
    while (string[patternLength] != '\0' && string[patternLength] != NULL) {
        patternLength += 1;
    }
    return patternLength;
}
