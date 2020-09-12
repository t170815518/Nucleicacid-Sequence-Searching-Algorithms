#include "FNAFilePreprocess.h"
#include "RabinKarpAlgorithm.h"
#include "BruteForce.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>


#define NTHASH_COMMAND "rk-nthash"
#define RABINKARP_COMMAND "rk"


int main(int argc, char *argv[]) {
    char * geneticSequence = readFile();
    int occurrences[MAX_OCCURRENCES];
    char patternSequence[MAX_INPUT];
    int (*func_ptr)(char*, char*, int*);

    if (argc == 2) {
        if (strcmp(argv[1],NTHASH_COMMAND) == 0) {
            func_ptr = &RabinKarpAlgorithm_ntHash;
        } else if (strcmp(argv[1],RABINKARP_COMMAND) == 0) {
            func_ptr = &RabinKarpAlgorithmNaive;
            initializeValueMap();
        }
    } else {
        func_ptr = &BruteForce;  // default algorithm
    }

    printf("Type the target pattern to search (type -1 to exit the program): ");
    scanf("%s", patternSequence);  // '\0' is appended

    while (strcmp(patternSequence,"-1") != 0) {
        // start searching
        clock_t startTime = clock();
        int occurrencesNum = (*func_ptr)(geneticSequence, patternSequence, occurrences);
        clock_t endTime = clock();

        // print the result
        if (occurrencesNum != 0) {
            printf("==========%d occurrences found in total==========\n", occurrencesNum);
            for (int i = 0; i < occurrencesNum; i++) {
                printf("%d ", occurrences[i]);
            }
            printf("\n");
        } else {
            printf("==========Not Found==========\n");
        }

        double elapsed = (double) (endTime - startTime) * 1000.0 / CLOCKS_PER_SEC;
        printf("==========Execution time = %f==========\n", elapsed);

        printf("Type the target pattern to search (type -1 to exit the program): ");
        scanf("%s", patternSequence);
    }

    return 0;
}


