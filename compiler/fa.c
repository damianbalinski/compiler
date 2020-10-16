#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// liczba bajtow
#define MAX 256
#define min(a,b) (((a) < (b)) ? (a) : (b))

/**
 * Automat skonczony do wyszukiwania wzorca w teksie.
 */

/**
 * Sprawdzmy, czy str2 jest sufiksem str1, porownujemy
 * ostatnie len2 znakow w obydwu lancuchach.
 */
bool is_suffix(char* str1, int len1, char* str2, int len2)
{
	return strncmp(str2, str1 + len1 - len2, len2) == 0;
}

/**
 * Inicjalizacja funkcji przejsc, dla wygody przekazujemy wskaznik na macierz.
 */
void init_transition_function(int*** matrix, int x, int y)
{
	*matrix = (int**)malloc(y * sizeof(int*));

	for (int i = 0; i < y; i++)
		(*matrix)[i] = (int*)malloc(x * sizeof(int));
}

/**
 * Obliczanie funkcji przejsc, zaczynamy od q=0
 * Szukamy k takiego ze Pk ] Pq?, czyli Pk jest sufiksem Pq?, gdzie
 * Pk - prefiks wzorca P[0, ..., k-1], P0 jest lancuchem pustym
 * Pq - prefiks wzorca P[0, ..., q-1]
 * ?  - pojedynczy znak ze slownika
 */
void compute_transition_function(int** matrix, int x, int y, char* pattern)
{
	int q = 0;
	char* buff;
	int c;
	int k;

	/**
	 * Zaczynamy od q=0 oraz wyzerowanego bufora,
	 * bufor buff bedzie przechowywal lancuch Pq?, gdzie Pq jest prefikesm
	 * a ? aktualnie rozpatrywanym znakiem
	 * zauwazmy ze maksymalna dlugosc bufora = y = length+1, po 
	 * doliczniu znaku pustego mamy y+1
	 */
	buff = (char*)calloc(y+1, sizeof(char));

	/**
	 * Iterujemy po wszystkich stananch, dla kazdego stanu po wszystkich znakach
	 */
	for (q = 0; q < y; q++)
	{
		for (c = 0; c < MAX; c++)
		{
			// ustawiamy nastepny znak w buforze
			buff[q] = c;

			// obliczamy maksymalna sensowna wartosc k
			k = min(y, q + 1);

			// dekrementujemy k do poki ~ Pk ] Pq?
			while (!is_suffix(buff, q + 1, pattern, k))
				k--;
			
			// otrzymalismy stan, po jakim przejdziemy po dodaniu znaku ? do prefiksu Pq
			matrix[q][c] = k;
		}

		/**
		 * Po wyjsciu z petli przeszlismy wszystki znaki, przechodzimy do nastepnego
		 * stanu, ustawiamy prefiks Pq, czyli w miejsce q wstawiamy prawidlowy znak wzorca
		 */
		buff[q] = pattern[q];
	}
}

/**
 * Drukowanie macierzy przejsc, do testow.
 */
void print_transition_function(int** matrix, int x, int y)
{
	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < x; j++)
			printf("%d ", matrix[i][j]);
		putchar('\n');
	}
}

/**
 * Automat skonczony.
 */
void fa(FILE* file, char* pattern)
{
	int length;
	int** matrix;
	int x, y;
	int c;
	int q;
	int counter;

	/**
	 * Przygotowanie funkcji przejsc.
	 * x = MAX = dlugosc alfabetu
	 * y = length+1 = liczba stanow (lacznie ze stanem zerowym)
	 */
	length = strlen(pattern);
	x = MAX;
	y = length + 1;
	init_transition_function(&matrix, x, y);
	compute_transition_function(matrix, x, y, pattern);

	/**
	 * Zaczynamy w stanie q = 0, przeszukujemy caly plik bajt
	 * po bajcie.
	 */
	q = 0;
	counter = 0;

	while ((c = getc(file)) != EOF)
	{
		q = matrix[q][c];
		if (q == length)
			printf("%d\n", counter-length+1);
		++counter;
	}
}

/**
 * Otwieramy plik w trybie binarnym, przetwarzamy znaki z
 * przedzialu [0,256], w tym znaki polskie [143-243].
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

	if ((file = fopen(filepath, "rb")) == NULL)
	{
		printf("plik \"%s\" nie istnieje\n", filepath);
		return EXIT_FAILURE;
	}

	fa(file, pat);
	fclose(file);

	return EXIT_SUCCESS;
}