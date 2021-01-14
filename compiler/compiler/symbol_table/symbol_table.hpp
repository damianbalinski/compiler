# pragma once
#include <vector>
#include <cln/integer.h>
#include "../others/types.hpp"

#define VARIABLE true
#define ARRAY false

using std::vector;

typedef struct symbol
{
    char* id;               /* id symbolu                */
    bool type;              /* zmianna/tablica           */
    bool is_init;           /* czy zainicjalizowana      */
    bool is_const;          /* czy stala                 */
    bool is_visible;        /* czy widoczna              */
    input_type offset;      /* lokalizacja w pamieci     */
    input_type begin;       /* indeks poczatkowy tablicy */
    input_type end;         /* indeks poczatkowy tablicy */
    struct symbol* next;    /* nastepny symbol           */
    vector<symbol*>* deps;  /* lista zaleznosci          */
    //cln::cl_I val;        /* wartosc                   */
    
} symbol;

symbol* sym_put(char *id);
symbol* sym_get(char*id);
void sym_print();
