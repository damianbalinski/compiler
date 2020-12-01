#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../symbol_table/symbol_table.h"
#include "../debugger/debugger.h"

symbol* sym_table = NULL;

// dodaje nowy symbol na poczatek listy
symbol* putsym(char *id)
{
    PR_SYMBOL_PUT(id);
    symbol *ptr;
    ptr = malloc(sizeof(symbol));
    ptr->id     = strdup(id);
    ptr->offset = -1;   //data_location()
    ptr->next   = sym_table;
    sym_table   = ptr;
    return ptr;
}

// zwraca symbol lub NULL, jesli symbolu nie ma
symbol* getsym(char*id)
{
    PR_SYMBOL_GET(id);
    symbol *ptr;
    for (ptr = sym_table; ptr != NULL; ptr = ptr->next)
        if (strcmp (ptr->id, id) == 0)
            return ptr;
    return NULL;
}