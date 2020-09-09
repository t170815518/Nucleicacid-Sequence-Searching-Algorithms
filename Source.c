// C program for implementation of KMP pattern searching 
// algorithm
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX_LENGTH 1000000

void computeLPSArray(char *pat, int M, int *lps);

int* KMPSearch(char *pat, char *txt, int *noOfOccur)
{
	int *occurance = NULL;
	int M = strlen(pat);
	int N = strlen(txt);

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
			printf("Found pattern at index %d \n", i - j);
			++*noOfOccur;
			occurance = (int*)realloc(occurance, *noOfOccur * sizeof(int));
			occurance[*noOfOccur-1] = i - j;
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
	return occurance;
	free(lps); // to avoid memory leak
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

char *readFile() {
    /* read from the specified file.
     * Return: char array, with non-DNA/RNA information deleted.*/
    FILE * file = fopen("GCF_009858895.2_ASM985889v3_genomic - Copy.fna", "r");
    char dummyInput[200];
    char inputSequence[MAX_LENGTH];
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

// Driver program to test above function
int main()
{
	char *txt = readFile();
	char *pat = "TTTATACCTTCC";
	int noOfOccur = 0;
	int *occurance = KMPSearch(pat, txt, &noOfOccur);
	printf("Number of occurances %i\n", noOfOccur);
	for (int i = 0; i < noOfOccur; ++i)
	{
		printf("Found match at element %i\n", occurance[i]);
	}
	return 0;
}