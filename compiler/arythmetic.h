
#define BASE 1234577						// podstawa systemu
#define PHI  1234576						// funkcja Eulera phi(BASE)
#define ZERO 0								// element neutralny dodawania
#define ONE  1								// element neutralny mnozenia

#define ERR_DIV_ZERO "Dzielenie przez zero."
#define ERR_REC_ZERO "Zero nie ma elementu odwrotnego."

inline int norm(long long x);				// liczba znormalizowana	TEST
inline int norm_pow(long long x);			// potega znormalizowana
inline int neg(int x);						// liczba przeciwna			TEST
inline int inv(int x);						// liczba odwrotna			TEST

inline int add(int x, int y);				// dodawanie				TEST
inline int sub(int x, int y);				// odejmowanie				TEST
inline int mul(int x, int y);				// mnozenie					TEST
inline int div(int x, int y);				// dzielenie				TEST
inline int pow(int x, int y);				// potega

inline int zero(int x);						// sprawdza czy jest zerem
inline int one(int x);						// sprawdza czy jest jedynka

void reuklides(int a, int b, int* x, int* y);		// rozszerzony algorytm Euklidesa
void fast_multiplication(int a, int b, int* res);	// szybkie mnozenie
