#include "KMPAlgorithm.h"
#include "FNAFilePreprocess.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void computeLPSArray(char *pat, int M, int *lps);


int KMPSearch(char *txt, char *pat, int *occurrences) {
    int M = strlen(pat);
    int N = strlen(txt);
    int noOfOccur = 0;

    // create lps[] that will hold the longest prefix suffix
    // values for pattern
    int *lps = (int *)malloc(sizeof(int)*M);
    int j = 0;  // index for pat[]

    // Preprocess the pattern (calculate lps[] array)
    computeLPSArray(pat, M, lps);

    int i = 0;  // index for txt[]
    while (i < N)
    {
        if (pat[j] == txt[i])
        {
            j++;
            i++;
        }

        if (j == M)
        {
            ++noOfOccur;
            occurrences[noOfOccur-1] = i - j;
            if (noOfOccur >= MAX_OCCURRENCES)
            {
                printf("==========There are more than %d occurrences. Only %d of them are displayed.==========\n", MAX_OCCURRENCES, MAX_OCCURRENCES);
                break;
            }
            j = lps[j - 1];
        }

            // mismatch after j matches
        else if (i < N && pat[j] != txt[i])
        {
            // Do not match lps[0..lps[j-1]] characters,
            // they will match anyway
            if (j != 0)
                j = lps[j - 1];
            else
                i = i + 1;
        }
    }
    free(lps); // to avoid memory leak
    return noOfOccur;
}


void computeLPSArray(char *pat, int M, int *lps)
{
    int len = 0;  // length of the previous longest prefix suffix
    int i;

    lps[0] = 0; // lps[0] is always 0
    i = 1;

    // the loop calculates lps[i] for i = 1 to M-1
    while (i < M)
    {
        if (pat[i] == pat[len])
        {
            len++;
            lps[i] = len;
            i++;
        }
        else // (pat[i] != pat[len])
        {
            if (len != 0)
            {
                // This is tricky. Consider the example
                // AAACAAAA and i = 7.
                len = lps[len - 1];

                // Also, note that we do not increment i here
            }
            else // if (len == 0)
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}