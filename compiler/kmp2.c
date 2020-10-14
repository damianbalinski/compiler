#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void computeLPSarray(char* pat, int M, int* lps)
{
	int len = 0;	//lenght of previous longest prefix suffix
	int i;

	lps[0] = 0;	//lps[0] is always 0
	i = 1;

	while (i < M)	//loop calculates lps[i] for i = 1 to M-1
	{
		if (pat[i] == pat[len])
		{
			len++;
			lps[i] = len;
			i++;
		}
		else	//pat[i] != pat[len]
		{
			if (len != 0)
			{
				//this is tricky
				//consider the example AAACAAAA and i =7
				len = lps[len - 1];
				//we donot increment i here
			}
			else	//if len == 0
			{
				lps[i] = 0;
				i++;
			}
		}
	}
}

void printArray(int* arr, int n)
{
	for (int i = 0; i < n; i++)
		printf("%d ", arr[i]);
	putchar('\n');
}

void KMPSearch(char* pat, char* txt)
{
	int M = strlen(pat);
	int N = strlen(txt);

	int* lps = (int*)malloc(M * sizeof(int));
	int j = 0;

	computeLPSarray(pat, M, lps);
	printArray(lps, M);
	
	int i = 0;
	while (i < N)
	{
		if (pat[j] == txt[i])
		{
			j++;
			i++;
		}
		if (j == M)
		{
			printf("Found pattern at index %d\n", i - j);
			j = lps[j - 1];
		}
		else if (pat[j] != txt[i])
		{
			if (j != 0)
				j = lps[j - 1];
			else
				i++;
		}
	}
	free(lps);
}

int main()
{
	char* txt = "AAABAABAA";
	char* pat = "AABA";

	KMPSearch(pat, txt);
	return 0;
}