# pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../debugger/debugger.h"
#include "../others/types.h"

#define VARIABLE true
#define ARRAY false

typedef struct symbol
{
    bool type;              /* zmianna/tablica           */
    char* id;               /* id symbolu                */
    bool is_init;           /* czy zainicjalizowana      */
    input_type offset;      /* lokalizacja w pamieci     */
    input_type begin;       /* indeks poczatkowy tablicy */
    input_type end;         /* indeks poczatkowy tablicy */
    struct symbol* next;    /* nastepny symbol           */
    
} symbol;

symbol* sym_put(char *id);
symbol* sym_get(char*id);
