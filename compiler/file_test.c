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

/*
 * MASK1 - do sprawdzania czy pierwszy bit jest 0
 * MASK2 - do sprawdzania czy drugi bit jest 1
 */
#define MASK1 0b10000000
#define MASK2 0b01000000
#define MASK 0b11000000
#define RES 0b10000000

int main(int argc, char** argv)
{
	char* str;
	int byte;
	FILE* file;
	int counter;

	file = fopen("test.txt", "rb");
	counter = 0;
	
	// CHARS
	while((byte = getc(file)) != EOF)
	{
		if((byte&MASK) != RES)
		{
			printf("NEW\n");
			counter++;
		}
		//// jesli pierwszy bit jest 0 lub drugi bit jest 1
		//if (!(byte & MASK1))
		//	printf("BIT1 = 0\n");
		//else if (byte & MASK2)
		//	printf("BIT2 = 1\n");
		
		printf(BYTE_TO_BINARY_PATTERN " ", BYTE_TO_BINARY(byte));
		printf("%c\n", byte);
		printf("-----------\n");
	}

	printf("counter: %d\n", counter);

	return 0;
}