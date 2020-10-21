#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * KOREKCJA UTF8
 * Kody UTF8 maja postac:
 * 0xxxxxxx
 * 110xxxxx 10xxxxxx
 * 1110xxxx 10xxxxxx 10xxxxxx
 * 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
 * ...
 * Zauwazmy, ze jezeli przetwarzany bajt ma postac 10xxxxxx,
 * nie jest to pierwszy bajt przetwarzanego znaku. W naszej
 * korekcji bedziemy obraca licznik znakow tylko jesli warunek
 * ten nie jest spelniony, tzn (byte & MASK) != RES
 * 
 * Uwaga! Pomimo ze przetwarzamy plik zawierajacy kody UTF-8
 * zakladamy, ze plik nie zawiera na poczatku znacznika BOM,
 * tzn bajtow EF BB BF, jesli jednak, wzorce beda wyszukiwane
 * z przesunieciem +1.
 */
#define MASK 0b11000000
#define RES 0b10000000

/**
 * Algorytm Knutha-Morrisa-Pratta wyszukiwania wzorca w tekscie.
 */
void init_prefix_function(int** arr, int length)
{
	*arr = (int*)malloc(length * sizeof(int));
}

/**
 * Oblicza dlugosc wzorca jako liczbe znakow, nie zlicza bajtow
 * postaci 10xxxxxx
 */
int real_length(char* str, int len)
{
	int counter = 0;
	for (int i = 0; i < len; i++)
		if ((str[i] & MASK) != RES)
			counter++;
	return counter;
}

/**
 * Oblicza funkcje prefiksow.
 * arr - funkcja prefiksow
 * pat - wzorzec
 * length - dlugosc wzorca (w bajtach)
 */
void compute_prefix_function(int* arr, char* pat, int length)
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
		// szukamy najdluzszego pasujacego sufiksu
		while (k > 0 && pat[k] != pat[q])
			k = arr[k-1];
			
		if (pat[k] == pat[q])
			++k;

		arr[q] = k;
	}
}

/**
 * Drukuje funkcje prefiksowa, do testow.
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
 * q - aktualny stan
 * c - licznik przetworzonych znakow ze zrodla
 * length - dlugosc wzorca bajtach
 * rlength - dlugosc wzorca w znakach
 */
void kmp(FILE* file, char* pat)
{
	// dane
	int* arr;
	char byte;
	int q;
	int c;
	int length;
	int rlength;

	/*
	 * Przygotowanie funkcji prefiksow.
	 */
	length = strlen(pat);
	rlength = real_length(pat, length);
	
	init_prefix_function(&arr, length);
	compute_prefix_function(arr, pat, length);

	/**
	 * Zaczynamy w stanie q = -1, przeszukujemy caly plik bajt
	 * po bajcie, licznik c obraca sie tylko jesli rozpoczynamy
	 * nowy znak w UTF8.
	 */
	q = -1;
	c = 0;

	// przetwarzamy wszystkie znaki w pliku
	while ((byte = getc(file)) != EOF)
	{
		// cofamy sie do stanu, dla ktorego nastepny znak pasuje do wzorca
		while (q > -1 && pat[q + 1] != byte)
			q = arr[q]-1;

		// jesli nastepny znak stanu pasuje do wzorca, przechodzimy dalej
		if (pat[q + 1] == byte)
			q++;

		// korekcja UTF8, licznik do drukowania pozycji w pliku
		if ((byte & MASK) != RES)
			c++;
			
		// indeksujemy zworzec od 0, wiec m-1 oznacza ze znalezlismy pelny
		// wzorzec, drukujemy przesuniecie i wracamy do nastepnego pasujacego
		// stanu
		if (q == length-1)
		{
			printf("%d\n", c - rlength);
			q = arr[q]-1;
		}
	}
}

/**
 * Otwieramy plik w trybie binarnym.
 * Uwaga! Plik nie powinien zawierac znacznika BOM.
 */
int main(int argc, char** argv)
{
	// dane
	char* pat;
	char* filepath;
	FILE* file;

	if (argc != 3)
	{
		printf("nieprawidlowe uzycie, sproboj:\n");
		printf("%s <pattern> <file>\n", argv[0]);
		return EXIT_FAILURE;
	}

	filepath = argv[2];
	pat = argv[1];
	
	if((file = fopen(filepath, "rb")) == NULL)
	{
		printf("plik \"%s\" nie istnieje\n", filepath);
		return EXIT_FAILURE;
	}

	kmp(file, pat);
	fclose(file);
	
	return EXIT_SUCCESS;
}