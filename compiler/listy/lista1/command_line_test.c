#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0')

int main(int argc, char** argv)
{
	char* str;
	size_t size;

	size = strlen(argv[1]);

	// SIZE
	printf("size: %ld\n", size);

	// CHARS
	printf("chars: ");
	for (int i = 0; i < size; i++)
		printf("%c ", argv[1][i]);
	printf("\n");
	
	// NUMS
	printf("nums: ");
	for (int i = 0; i < size; i++)
		printf(BYTE_TO_BINARY_PATTERN " ", BYTE_TO_BINARY(argv[1][i]));
	printf("\n");
	
	return 0;
}