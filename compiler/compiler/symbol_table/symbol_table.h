# pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../debugger/debugger.h"
#define VARIABLE true
#define ARRAY false

typedef struct symbol
{
    bool type;              /* zmianna/tablica           */
    char* id;               /* id symbolu                */
    int offset;             /* lokalizacja w pamieci     */
    bool is_init;           /* czy zainicjalizowana      */
    int begin;              /* indeks poczatkowy tablicy */
    int end;                /* indeks poczatkowy tablicy */
    struct symbol* next;    /* nastepny symbol           */
} symbol;

symbol* sym_put(char *id);
symbol* sym_get(char*id);
