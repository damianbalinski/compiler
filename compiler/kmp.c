#define _CRT_SECURE_NO_WARNINGS
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

/**
 * Drukowanie funkcji prefiksowej, do testow.
 */
void print_prefix_function(int* arr, int length)
{
	for (int i = 0; i < length; i++)
		printf("%d ", arr[i]);
	putchar('\n');
}

/**
 * Algorytm Knutha-Morrisa-Pratta
 * file - plik zrodlowy
 * pat - wzorzec do porownania
 * arr - funkcja prefiksowa
 * byte - aktualnie przetwarzany znak
 * q - aktualny stan, zaczynamy od -1, czyli stanu poczatkowego
 * c - licznik przetworzonych znakow ze zrodla
 * m - dlugosc wzorca
 */
void kmp(FILE* file, char* pat)
{
	// dane
	int* arr;
	char byte;
	int m;
	int q;
	int c;

	// inicjalizacja danych
	q = -1;
	c = 0;
	m = strlen(pat);
	init_prefix_function(&arr, m);
	compute_prefix_function(arr, pat, m);

	// przetwarzamy wszystkie znaki w pliku
	while ((byte = getc(file)) != EOF)
	{
		// cofamy sie do stanu, dla ktorego nastepny znak pasuje do wzorca
		while (q > -1 && pat[q + 1] != byte)
			q = arr[q]-1;

		// jesli nastepny znak stanu pasuje do wzorca, przechodzimy dalej
		if (pat[q + 1] == byte)
			q++;

		// indeksujemy zworzec od 0, wiec m-1 oznacza ze znalezlismy pelny
		// wzorzec, drukujemy przesuniecie i wracamy do nastepnego pasujacego
		// stanu
		if (q == m-1)
		{
			printf("%d\n", c - m+1);
			q = arr[q]-1;
		}

		// licznik do drukowania pozycji w pliku
		c++;
	}
}

/**
 * Otwieramy plik w trybie binarnym, dzieki czemu
 * mozemy przetwarzac znaki inne niz ASCII,
 */
int main(int argc, char** argv)
{
	// DANE
	char* str;
	char* pat;
	char* filepath;
	FILE* file;
	
	// TEST
	filepath = "test.txt";
	pat = "¹œæ";
	file = fopen(filepath, "rb");

	kmp(file, pat);

	fclose(file);
	
	return 0;
}