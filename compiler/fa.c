#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX 3
const char* DICT = "abc";

/**
 * Automat skonczony do wyszukiwania wzorca w teksie.
 */

//TODO delete
int pos(char c) {
	return strchr(DICT, c) - DICT;
}

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

	return matrix;
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
			buff[q] = DICT[c];

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

void print_transition_function(int** matrix, int x, int y)
{
	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < x; j++)
			printf("%d ", matrix[i][j]);
		putchar('\n');
	}
}

void finite_automat(FILE* file, char* pattern)
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
	 * Zaczynamy w stanie q = 0, przeszukujemy caly plik
	 */
	q = 0;
	counter = 0;

	// TEST
	//printf("len: %d\n", length);
	//printf("x: %d\n", x);
	//printf("y: %d\n", y);
	//printf("q: %d\n", q);
	//printf("couter: %d\n", counter);


	while ((c = getc(file)) != EOF)
	{
		//printf("c: %c\n", c);
		//printf("pos: %d\n", pos(c));
		//printf("q: %d\n", q);
		//printf("matrix: %d\n", matrix[q][pos(c)]);
		//printf("mat2\n");

		printf("%c   ", c);
		q = matrix[q][pos(c)];
		if (q == length)
			printf("PATTERN %d\n", counter);
		else
			printf("%d\n", q);

		++counter;
	}
}

//int main(int argc, char* args[])
//{
//	// data
//	FILE* input = NULL;
//	FILE* output = NULL;
//	char* input_path = NULL;
//	char* output_path = NULL;
//	char* pattern;
//
//	////TODO TEST
//	//input_path = "test1.txt";
//	//pattern = "abc";
//
//	//// open file
//	//input = fopen(input_path, "rb");
//
//	//// perform pattern searching
//	//finite_automat(input, pattern);
//
//	//// close file
//	//fclose(input);
//
//	return 0;
//}

