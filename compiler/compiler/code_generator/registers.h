#pragma once
#include "../others/types.h"
#include "../others/unit.h"

#define NOTHING -1
#define MAX_REGISTERS 5
#define SUPER_REGISTER 5

typedef struct register_type{
    const char name;            /* nazwa rejestru */
    const int num;
    input_type val;             /* zawartosc rejestru */
    unit_type* unit;            /* unit, ktorego przechowuje rejestr */
    struct register_type* next;
} register_type;
