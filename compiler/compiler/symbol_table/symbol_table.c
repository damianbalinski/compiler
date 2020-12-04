#include "symbol_table.h"

symbol* sym_table = NULL;

// dodaje nowy symbol na poczatek listy
symbol* sym_put(char *id)
{
    DBG_SYMBOL_PUT(id);
    symbol *ptr;
    ptr = malloc(sizeof(symbol));
    ptr->id = strdup(id);
    ptr->offset = -1;   //data_location()
    ptr->next = sym_table;
    sym_table = ptr;
    return ptr;
}

// zwraca symbol lub NULL, jesli symbolu nie ma
symbol* sym_get(char*id)
{
    DBG_SYMBOL_GET(id);
    symbol *ptr;
    for (ptr = sym_table; ptr != NULL; ptr = ptr->next)
        if (strcmp(ptr->id, id) == 0)
            return ptr;
    return NULL;
}