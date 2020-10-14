#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Algorytm Knutha-Morrisa-Pratta wyszukiwania wzorca w tekscie.
 */
void init_prefix_function(int** arr, int length)
{
	*arr = (int*)malloc(length * sizeof(int));
}

/**
 * Obliczanie funkcji prefiksow.
 * arr - funkcja prefiksow
 * pattern - wzorzec
 */
void compute_prefix_function(int* arr, char* pattern, int length)
{
	int k;
	int q;

	arr[0] = 0;
	k = 0;

	/**
	 * Iterujemy po wszystkich stanach, zaczynajac od 1,
	 */
	for (q = 1; q < length; q++)
	{
		//printf("   NEW\n");

		// szukamy najdluzszego pasujacego sufiksu
		while (k > 0 && pattern[k] != pattern[q])
		{
			//printf("DECR k\n");
			k = arr[k-1];
		}
			

		if (pattern[k] == pattern[q])
		{
			//printf("INCD k");
			++k;
		}

		arr[q] = k;

		// TEST
		//printf("q = %d\n", q);
		//printf("k = %d\n", k);
		//printf("arr[%d] = %d\n\n", q, arr[q]);
	}
}

void print_prefix_function(int* arr, int length)
{
	for (int i = 0; i < length; i++)
		printf("%d ", arr[i]);
	putchar('\n');
}

//void knuth_morris_pratt(FILE* file, char* pattern)
//{
//	int* arr;
//	int length;
//	int q;
//	int i;
//	char c;
//	int counter;
//
//	// init variables
//	counter = 0;
//	length = strlen(pattern);
//
//	init_prefix_function(&arr, pattern, length);
//	compute_prefix_function(arr, pattern, length);
//	print_prefix_function(arr, length);
//
//	q = 0;
//	while ((c = getc(file)) != EOF)
//	{
//		//printf("    NEW\n");
//		while (q > 0 && pattern[q + 1] != c)
//		{
//			//printf("DECR\n");
//			q = arr[q-1];
//		}
//
//		if (pattern[q + 1] == c)
//		{
//			//printf("INCR\n");
//			++q;
//		}
//
//		printf("%c   ", c);
//		if (q == length-1)
//		{
//			// or q == length-1
//			q = arr[q-1];
//			printf("PATTERN %d | q = %d\n", counter, q);
//		}
//		else
//			printf("%d\n", q);
//		
//		++counter;
//	}
//}

void kmp(char* str, char* pat)
{
	// data
	int* arr;
	int n;
	int m;
	int q;

	// init data
	n = strlen(str);
	m = strlen(pat);
	q = -1;
	init_prefix_function(&arr, m);
	compute_prefix_function(arr, pat, m);

	// TEST
	print_prefix_function(arr, m);

	for(int i = 0; i < n; i++)
	{
		printf("i = %d\n", i);
		while (q > -1 && pat[q + 1] != str[i])
			q = arr[q]-1;
		if (pat[q + 1] == str[i])
			q++;
		if (q == m-1)
		{
			printf("wzorzec %d\n", i - m+1);
			q = arr[q]-1;
		}
	}
}

int main(void)
{
	// TEST
	char* str = "AAABBAABBAABBAABBAABB";
	char* pat = "AABBA";

	

	kmp(str, pat);
	
	return 0;
}