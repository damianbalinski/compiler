#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv)
{
	char* str;
	int byte;
	FILE* file;

	str = "平";
	file = fopen("test.txt", "r");
	
	// FILE
	printf("FILE:\n");
	while ((byte = getc(file)) != EOF)
		printf("%d\n", byte);
	
	// COMMAND LINE
	printf("COMMAND:\n");
	for (int i = 0; i < strlen(argv[1]); i++)
		printf("%d\n", argv[1][i]);

	// STRING
	printf("STRING:\n");
	for(int i = 0; i < strlen(str); i++)
		printf("%d\n", str[i]);

	fclose(file);
	return 0;
}