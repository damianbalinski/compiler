#include <stdio.h>
#include "kmp.c"

void test_prefix_function();

int main(void)
{
	test_prefix_function();
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