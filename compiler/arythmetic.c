#include <stdio.h>

#define BASE 11								// podstawa systemu
#define ZERO 0								// element neutralny dodawania
#define ONE 1								// element neutralny mnozenia

#define ERR_DIV_ZERO "Dzielenie przez zero."
#define ERR_REC_ZERO "Zero nie ma elementu odwrotnego"

inline int norm(int x);						// liczba znormalizowana	TEST
inline int neg(int x);						// liczba przeciwna			TEST
inline int rec(int x);						// liczba odwrotna			TEST

inline int add(int x, int y);				// dodawanie				TEST
inline int sub(int x, int y);				// odejmowanie				TEST
inline int mul(int x, int y);				// mnozenie					TEST
inline int div(int x, int y);				// dzielenie				TEST
inline int pow(int x, int y);				// potega

void reuklides(int a, int b, int* x, int* y); // rozszerzony algorytm Euklidesa

// zwraca liczbe znormalizowana w Zp
inline int norm(int x) {
	return (x % BASE + BASE) % BASE;
}

// zwraca liczbe przeciwna
inline int neg(int x) {
	return norm(BASE - x);
}

// zwraca liczbe odwrotna
inline int rec(int x) {
	if (x % BASE == ZERO) {
		fprintf(stderr, "Error %d: %s\n", x, ERR_REC_ZERO);
		exit(-1);
	}
	int p = 1, q = 0;
	reuklides(BASE, norm(x), &p, &q);
	return norm(q);
}

// zwraca sume liczb
inline int add(int x, int y) {
	return norm(x + y);
}

// zwraca roznice liczb
inline int sub(int x, int y) {
	return add(x, neg(y));
}

// zwraca iloczyn liczb
inline int mul(int x, int y) {
	return norm(norm(x) * norm(y));
}

// zwraca iloraz liczb
inline int div(int x, int y) {
	if (y%BASE == ZERO) {
		fprintf(stderr, "Error %d/%d: %s\n", x, y, ERR_DIV_ZERO);
		exit(-1);
	}
	return mul(x, rec(y));
}

// rozszerzony algorytm Euklidesa
// ax + by = NWD(a,b)
void reuklides(int a, int b, int* x, int* y)
{
	if (b != 0)
	{
		reuklides(b, a % b, x, y);
		int pom = *y;
		*y = *x - a / b * (*y);
		*x = pom;
	}
}

int main(void)
{
	// NORM TEST
	//for (int i = -23; i <= 23; i++)
	//	printf("norm(% 3d) = %d\n", i, norm(i));

	// NEG TEST
	//printf("%d\n", neg(0));
	//for (int i = -23; i <= 23; i++)
	//	printf("neg(% 3d) = %d\n", i, neg(i));

	// ADD TEST
	//printf("%d\n", add(11, 11));
	//printf("%d\n", add(0, 0));
	//printf("%d\n", add(5, 6));
	//printf("%d\n", add(6, 6));
	//printf("%d\n", add(20, 20));
	//printf("%d\n", add(5, -6));
	//printf("%d\n", add(-7, 2));
	//printf("%d\n", add(-7, 9));
	//printf("%d\n", add(-7, -3));

	// SUB TEST
	//printf("%d\n", sub(4,5));
	//printf("%d\n", sub(-1,1));
	//printf("%d\n", sub(0,10));

	// EUKLIDES TEST
	//int a = BASE;
	//int b = 4;
	//int x = 1;
	//int y = 0;
	//reuklides(a, b, &x, &y);
	//printf("a = %d\n", a);
	//printf("x = %d\n", x);
	//printf("\n");
	//printf("b = %d\n", b);
	//printf("y = %d\n", y);

	// REC TEST
	//rec(-11);
	//printf("%d\n", norm(-20));
	//for (int i = -200; i <= 200; i++)
	//	if ( i%BASE != 0)
	//		printf("%d * %d  =  %d\n", i, rec(i), mul(i, rec(i)));

	// MUL TEST
	//for (int i = -22; i <= 22; i++)
	//	printf("%d(%d) * 2 = %d\n", i, norm(i), mul(i, 2));

	// DIV TEST
	//printf("%d", div(10, 11));
	//for (int i = -22; i <= 22; i++)
	//	if (i % BASE != ZERO)
	//		printf("%d(%d) / %d = %d\n", i, norm(i), 2, div(i, 2));
	return 0;
}


