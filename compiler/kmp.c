#include <stdio.h>
#include <stdlib.h>

/**
 * Algorytm Knuta-Morrisa-Prata wyszukiwania wzorca w tekscie.
 */

void init_prefix_function(int** arr, char* pattern, int length)
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
		printf("   NEW\n");

		// szukamy najdluzszego pasujacego sufiksu
		while (k > 0 && pattern[k] != pattern[q])
		{
			printf("DECR k\n");
			k = arr[k - 1];
		}
			

		if (pattern[k] == pattern[q])
		{
			printf("INCD k");
			++k;
		}

		// TEST
		printf("q = %d\n", q);
		printf("k = %d\n", k);
		printf("arr[%d] = %d\n", q, arr[q]);

		arr[q] = k;
		printf("q = %d\n", q);
		printf("k = %d\n", k);
		printf("arr[%d] = %d\n\n", q, arr[q]);
	}
}

void print_prefix_function(int* arr, int length)
{
	for (int i = 0; i < length; i++)
		printf("%d ", arr[i]);
	putchar('\n');
}

//int main(void)
//{
//	printf("hello world\n");
//	return 0;
//}