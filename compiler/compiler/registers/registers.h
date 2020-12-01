#pragma once

#define A 0
#define B 1
#define C 2
#define D 3
#define E 4
#define F 5
#define NON_REGISTER -1
#define EMPTY -2
#define NUM_REGS 6

typedef struct {
    char name;                /* nazwa rejestru */
    unsigned long long val;   /* wartosc rejestru */
    int var_id;               /* lokalizacje zmiennej, ktora przechowuje rejestr */
    bool is_free;             /* czy wartosc rejestru nie jest juz potrzebna */

} register_t;
