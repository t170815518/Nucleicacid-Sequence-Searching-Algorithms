#include "BruteForce.h"
#include "FNAFilePreprocess.h"
#include <stdio.h>


int BruteForce(char *geneticSequence, char *sequenceToFind, int *occurrence) {
    /* brute force sequential search */
    long long curr,index;
    //TODO: dynamically increase occurence limit
    curr = 0;
    int noOfOccur = 0;
    index = 0;

    //Analysis should start from here
    while(geneticSequence[curr] != '\0'){ //loop while genetic sequence is not end
        while(geneticSequence[curr+index] != '\0' && sequenceToFind[index] == geneticSequence[curr+index]){
            //compare every index of sequenceToFind with curr + index character of geneticSequence
            //if geneticSequence reaches end of string jump out of the loop
            //if sequenceToFind[index] != geneticSequence[curr+index] jump out of the loop
            index++;
            if(sequenceToFind[index] == '\0'){
                //if sequenceToFind reaches end of string, it means occurence is found
                // add to occurence list
                occurrence[noOfOccur] = curr;
                (noOfOccur)++;
                break;
            }
        }
        if (noOfOccur >= MAX_OCCURRENCES) {
            printf("==========There are more than %d occurrences. Only %d of them are displayed.==========\n",
                   MAX_OCCURRENCES, MAX_OCCURRENCES);
            break;
        }
        curr++;
        index = 0;
    }
    return noOfOccur;
}