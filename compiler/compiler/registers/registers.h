#pragma once
#include <stdbool.h>
#include "../others/types.h"

#define A 0
#define B 1
#define C 2
#define D 3
#define E 4
#define F 5
#define NOTHING -1
#define EMPTY -2
#define MAX_REGISTERS 6

typedef struct {
    const char name;          /* nazwa rejestru */
    val_type val;             /* wartosc rejestru */
    int var_id;               /* lokalizacje zmiennej, ktora przechowuje rejestr */
    bool is_free;             /* czy wartosc rejestru nie jest juz potrzebna */

} register_type;

int register_get();
void register_free(int reg);