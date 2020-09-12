#include "FNAFilePreprocess.h"
#include "RabinKarpAlgorithm.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>


int main() {
    char * geneticSequence = readFile();
    int occurrences[MAX_OCCURRENCES];
    char patternSequence[MAX_INPUT];

    printf("Type the target pattern to search: ");
    scanf("%s", patternSequence);  // '\0' is appended

//    initializeValueMap();

    // start searching
    clock_t startTime = clock();
    int occurrencesNum = RabinKarpAlgorithmNaive(geneticSequence, patternSequence, occurrences);
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

    double elapsed = (double)(endTime - startTime) * 1000.0 / CLOCKS_PER_SEC;
    printf("==========Execution time = %f==========\n", elapsed);
    return 0;
}


//uint32_t rotl32 (uint32_t value, unsigned int count) {
//    const unsigned int mask = CHAR_BIT * sizeof(value) - 1;
//    count &= mask;
//    return (value << count) | (value >> (-count & mask));
//}