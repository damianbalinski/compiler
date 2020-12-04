#pragma once
#include <stdbool.h>
#include <stdio.h>
#include "../others/types.h"
#include "../debugger/debugger.h"
#include "../debugger/warnings.h"

#define A 0
#define B 1
#define C 2
#define D 3
#define E 4
#define F 5
#define NOTHING -1
#define EMPTY -2
#define MAX_REGISTERS 6

#define REG_FREE(X)    registers[X].is_free = true
#define REG_OFFSET(X,Y)  registers[X].offset = Y

typedef struct {
    const char name;            /* nazwa rejestru */
    val_type val;               /* wartosc rejestru */
    unsigned long long offset;  /* lokalizacje w pamieci, ktora przechowuje rejestr */
    bool is_free;               /* czy wartosc rejestru nie jest juz potrzebna */

} register_type;

int register_get();