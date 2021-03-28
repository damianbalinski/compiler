
#define BASE 1234577						// cialo Zp
#define PHI  1234576						// funkcja Eulera phi(BASE)
#define ZERO 0								// element neutralny dodawania
#define ONE  1								// element neutralny mnozenia

#define ERR_DIV_ZERO "Dzielenie przez zero."
#define ERR_REC_ZERO "Zero nie ma elementu odwrotnego."

int _norm(long long x);				// liczba znormalizowana
int _norm_pow(long long x);			// potega znormalizowana
int _neg(int x);					// liczba przeciwna
int _inv(int x);					// liczba odwrotna

int _add(int x, int y);				// dodawanie
int _sub(int x, int y);				// odejmowanie
int _mul(int x, int y);				// mnozenie
int _div(int x, int y);				// dzielenie
int _pow(int x, int y);				// potega

int _zero(int x);					// sprawdza czy jest zerem
int _one(int x);					// sprawdza czy jest jedynka

void reuklides(int a, int b, int* x, int* y);		// rozszerzony algorytm Euklidesa
void fast_exponent(int a, int b, int* res);	        // szybkie potegowanie
