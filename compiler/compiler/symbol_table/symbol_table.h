# pragma once
#include <stdbool.h>
#include "../others/types.h"

#define VARIABLE true
#define ARRAY false

typedef struct symbol
{
    char* id;               /* id symbolu                */
    bool type;              /* zmianna/tablica           */
    bool is_init;           /* czy zainicjalizowana      */
    input_type offset;      /* lokalizacja w pamieci     */
    input_type begin;       /* indeks poczatkowy tablicy */
    input_type end;         /* indeks poczatkowy tablicy */
    struct symbol* next;    /* nastepny symbol           */
    
} symbol;

symbol* sym_put(char *id);
symbol* sym_get(char*id);
void sym_print();
