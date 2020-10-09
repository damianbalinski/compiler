#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "kmp.c"

void test_prefix_function();
void test_knuth_morris_pratt();

int main(void)
{
	//test_prefix_function();
	test_knuth_morris_pratt();
}

void test_prefix_function()
{
	char* pattern = "aaabbaa";
	int length = 7;
	int* arr;

	init_prefix_function(&arr, pattern, length);
	print_prefix_function(arr, length);
	compute_prefix_function(arr, pattern, length);
	print_prefix_function(arr, length);
}

void test_knuth_morris_pratt()
{
	FILE* file = fopen("test1.txt", "rb");
	char* pattern = "aaabbaa";

	knuth_morris_pratt(file, pattern);

	fclose(file);
}