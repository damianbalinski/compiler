#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "fa.c"
#define RES(V) printf("%d\n", V)

void test_suffix();
void test_transition_function();
void test_pos();
void test_finite_automat();

int main(void)
{
	//test_suffix();				// DONE
	//test_transition_function();	// DONE
	//test_pos();					// DONE
	test_finite_automat();

	return 0;
}

void test_suffix()
{
	// SUFIX TEST
	printf("SUFIX 1\n");
	RES(is_suffix("abcdef", 6, "a", 1));
	RES(is_suffix("abcdef", 6, "b", 1));
	RES(is_suffix("abcdef", 6, "c", 1));
	RES(is_suffix("abcdef", 6, "d", 1));
	RES(is_suffix("abcdef", 6, "e", 1));
	RES(is_suffix("abcdef", 6, "f", 1));
	RES(is_suffix("abcdef", 6, "g", 1));

	printf("SUFIX 2\n");
	RES(is_suffix("abcdef", 6, "ab", 2));
	RES(is_suffix("abcdef", 6, "bc", 2));
	RES(is_suffix("abcdef", 6, "cd", 2));
	RES(is_suffix("abcdef", 6, "de", 2));
	RES(is_suffix("abcdef", 6, "ef", 2));
	RES(is_suffix("abcdef", 6, "fg", 2));

	printf("SUFIX 3\n");
	RES(is_suffix("abcdef", 6, "abc", 3));
	RES(is_suffix("abcdef", 6, "bcd", 3));
	RES(is_suffix("abcdef", 6, "cde", 3));
	RES(is_suffix("abcdef", 6, "def", 3));
	RES(is_suffix("abcdef", 6, "efg", 3));
}

void test_transition_function()
{
	char* pattern = "abba";
	int** matrix;
	int x = 3, y = 5;

	init_transition_function(&matrix, x, y);
	print_transition_function(matrix, x, y);

	compute_transition_function(matrix, x, y, pattern);
	print_transition_function(matrix, x, y);
}

void test_finite_automat()
{
	FILE* file = fopen("test2.txt", "rb");
	char* pattern = "abba";

	if (file == NULL)
		printf("error\n");

	finite_automat(file, pattern);

	fclose(file);
}

void test_pos()
{
	printf("%d\n", pos('a'));
	printf("%d\n", pos('b'));
	printf("%d\n", pos('c'));
	printf("%d\n", pos('d'));
}