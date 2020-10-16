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

#define MASK 0b11000000
#define RES 0b10000000

int length(char* str, int len)
{
	int counter = 0;
	for(int i = 0; i < len; i++)
		if ((str[i] & MASK) != RES)
			counter++;
	return counter;
}

int main(int argc, char** argv)
{
	char* str;
	int len;
	int mylen;
	size_t size;

	str = argv[1];
	len = strlen(str);
	mylen = length(str, len);

	//for (int i = 0; i < sizeof(str); i++)
	//	printf("%d ", str[i]);
	//printf("\n");
	
	printf("str: %s\n", str);
	printf("len: %d\n", len);
	printf("mylen: %d\n", mylen);
	printf("size: %ld\n", size);
	
	return 0;
}