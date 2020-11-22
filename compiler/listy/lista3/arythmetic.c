#include <stdio.h>
#include <stdlib.h>
#include "arythmetic.h"

/*
 * UWAGA!
 * 2^20 < BASE < 2^21
 * poniewaz istnieje ryzyko przepelnienia,
 * obliczenia posrednie wykonujemy na typie
 * long long
 * 
 * TODO potegowanie, dzielenie
 */

// sprawdza, czy x jest zerem
inline int _zero(int x) {
	return (x % BASE == ZERO);
}

// sprawdza czy x jest jedynka
inline int _one(int x) {
	return (_norm(x) == ONE);
}

// zwraca liczbe znormalizowana w Zp
inline int _norm(long long x) {
	return (x % BASE + BASE) % BASE;
}

// zwraca potege znormalizowana w Zp
inline int _norm_pow(long long x) {
	return (x % PHI + PHI) % PHI;
}

// zwraca liczbe przeciwna
inline int _neg(int x) {
	return _norm((long long)BASE - x);
}

// zwraca liczbe odwrotna
inline int _inv(int x) {
	if (x % BASE == ZERO) {
		fprintf(stderr, "Error %d: %s\n", x, ERR_REC_ZERO);
		exit(-1);
	}
	int p = 1, q = 0;
	reuklides(BASE, _norm(x), &p, &q);
	return _norm(q);
}

// zwraca sume liczb
inline int _add(int x, int y) {
	return _norm((long long)x + y);
}

// zwraca roznice liczb
inline int _sub(int x, int y) {
	return _add(x, _neg(y));
}

// zwraca iloczyn liczb
inline int _mul(int x, int y) {
	return _norm((long long)_norm(x) * _norm(y));
}

// zwraca iloraz liczb
inline int _div(int x, int y) {
	if (y%BASE == ZERO) {
		fprintf(stderr, "Error %d/%d: %s\n", x, y, ERR_DIV_ZERO);
		exit(-1);
	}
	return _mul(x, _inv(y));
}

// zwraca potege liczby
inline int _pow(int a, int b) {
	int x = 1;
	fast_multiplication(_norm(a), _norm_pow(b), &x);
	return x;
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

// algorytm szybkiego mnozenia a^b = res
// w postaci rekurencji ogonowej
void fast_multiplication(int a, int b, int* res)
{
	if (b != 0)
	{
		if (b & 1)  *res = _mul(*res, a);
		fast_multiplication(_mul(a,a), b >> 1, res);
	}
}

//int main(void)
//{
	// NORM TEST
	//for (int i = -23; i <= 23; i++)
	//	printf("norm(% 3d) = %d\n", i, norm(i));
	//printf("norm(%d) = %d\n", INT_MAX, norm(INT_MAX));
	//printf("norm(%lld) = %d\n", LLONG_MAX, norm(LLONG_MAX));

	// NEG TEST
	//printf("%d\n", neg(0));
	//for (int i = -23; i <= 23; i++)
	//	printf("neg(% 3d) = %d\n", i, neg(i));
	//printf("neg(%d) = %d\n", INT_MAX, neg(INT_MAX));

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


	// TEST FAST_MULTIPLICATION
	//int x = 1;
	//fast_multiplication(7, 3, &x);
	//printf("x = %d\n", x);

	// TEST POWER
	//for (int i = -22; i <= 22; i++)
	//	printf("3^%d = %d\n", i, pow(3, i));
	// printf("%d\n", _pow(2, 0));
	// printf("%d\n", _pow(2, -1));
	// printf("%d\n", _pow(2, -2));
	// printf("\n");
	// printf("%d\n", _div(1, 2));
	// printf("%d\n", _div(1, 4));

	// TESTY WYNIKOW
	//printf("%d\n", add(2, mul(3, sub(4, 5))));
	//printf("%d\n", pow(2, 100));
	//printf("%d\n", sub(sub(2,3),2));
	//printf("%d\n", div(269164, 123456));
	//printf("%d\n", sub(-2, -1));
	//printf("%d\n", div(1,-580978));
	//printf("%d\n", norm(123456789));
	//printf("%d\n", norm(-1234567));
	//printf("%d\n", pow(2,123));
	//printf("%d\n", pow(2,-2));

	// ZERO TEST
	// printf("%d\n", zero(0));
	// printf("%d\n", zero(1));
	// printf("%d\n", zero(BASE));
	// printf("%d\n", zero(mul(BASE, BASE)));

	// ONE TEST
	//printf("%d\n", one(1));
	//printf("%d\n", one(0));
	//printf("%d\n", one(BASE+1));
	//printf("%d\n", one(mul(BASE,BASE)+1));
	//return 0;
//}
