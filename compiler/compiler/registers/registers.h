
#define A 0
#define B 1
#define C 2
#define D 3
#define E 4
#define F 5
#define NON_REGISTER -1
#define EMPTY -2

const char* REGISTERS = "abcdef";

typedef struct {
    unsigned long long val;   /* wartosc rejestru */
    bool is_determined;       /* czy wartosc rejestru jest okreslona */
    int var_id;               /* lokalizacje zmiennej, ktora przechowuje rejestr */

} register_t;
