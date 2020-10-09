#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// TEST
#define RES(V) printf("%d\n", V)

#define MAX 3

/**
 * Sprawdzmy, czy str2 jest sufiksem str1, porownujemy
 * ostatnie len2 znakow w obydwu lancuchach.
 */
bool is_sufix(char* str1, int len1, char* str2, int len2)
{
	// TEST
	//printf("len1: %d\n", len1);
	//printf("len2: %d\n", len2);
	//printf("str1: %s\n", str1);
	//printf("str2: %s\n", str2);

	//if (strncmp(str2, str1 + len1 - len2, len2) == 0)
	//	printf("    sufix\n");
	//else
	//	printf("    _\n");

	return strncmp(str2, str1 + len1 - len2, len2) == 0;
}

int** init_transition_function(int x, int y)
{
	int** matrix = (int**)malloc(y * sizeof(int*));

	for (int i = 0; i < y; i++)
		matrix[i] = (int*)malloc(x * sizeof(int));

	return matrix;
}

/**
 * Obliczamy przyrostowo funkcje przejsc, zaczynamy od q=0
 * Szukamy k takiego ze Pk ] Pq?, czyli Pk jest sufiksem Pq?, gdzie
 * Pk - prefiks wzorca P[0, ..., k-1], P0 jest lancuchem pustym
 * Pq - prefiks wzorca P[0, ..., q-1]
 * ?  - pojedynczy znak ze zlownika
 * 
 */
int** compute_transition_function(int** matrix, int x, int y, char* pattern, int length)
{
	/**
	 * Stan poczatkowy - zaczynamy od q=0 oraz wyzerowanego bufora,
	 * bufor buff bedzie przechowywal lancuch Pq?
	 * zauwazmy ze maksymalna dlugosc bufora = length + 1
	 */
	int q = 0;
	char* buff = (char)calloc(length + 1, sizeof(char));

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

void transition_function(char* pattern, int length)
{

}

void finite_automat(FILE* file, char* pattern)
{
	char byte;
	int length;

	length = strlen(pattern);

	//TODO TEST
	printf("pattern: %s\n", pattern);
	printf("length : %d\n", length);

	while ((byte = getc(file)) != EOF)
	{
		printf("%c ", byte);
	}
}

int main(int argc, char* args[])
{
	// data
	FILE* input = NULL;
	FILE* output = NULL;
	char* input_path = NULL;
	char* output_path = NULL;
	char* pattern;

	////TODO TEST
	//input_path = "test1.txt";
	//pattern = "abc";

	//// open file
	//input = fopen(input_path, "rb");

	//// perform pattern searching
	//finite_automat(input, pattern);

	//// close file
	//fclose(input);

	return 0;
}

void test()
{
	// SUFIX TEST
	printf("SUFIX 1\n");
	RES(is_sufix("abcdef", 6, "a", 1));
	RES(is_sufix("abcdef", 6, "b", 1));
	RES(is_sufix("abcdef", 6, "c", 1));
	RES(is_sufix("abcdef", 6, "d", 1));
	RES(is_sufix("abcdef", 6, "e", 1));
	RES(is_sufix("abcdef", 6, "f", 1));
	RES(is_sufix("abcdef", 6, "g", 1));

	printf("SUFIX 2\n");
	RES(is_sufix("abcdef", 6, "ab", 2));
	RES(is_sufix("abcdef", 6, "bc", 2));
	RES(is_sufix("abcdef", 6, "cd", 2));
	RES(is_sufix("abcdef", 6, "de", 2));
	RES(is_sufix("abcdef", 6, "ef", 2));
	RES(is_sufix("abcdef", 6, "fg", 2));

	printf("SUFIX 3\n");
	RES(is_sufix("abcdef", 6, "abc", 3));
	RES(is_sufix("abcdef", 6, "bcd", 3));
	RES(is_sufix("abcdef", 6, "cde", 3));
	RES(is_sufix("abcdef", 6, "def", 3));
	RES(is_sufix("abcdef", 6, "efg", 3));
}