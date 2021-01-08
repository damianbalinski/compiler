#include <cstdio>
#include <cstring>
#include <cstdlib>
#include "symbol_table.hpp"
#include "../debugger/debugger.hpp"
#include "../debugger/warnings.hpp"

symbol* sym_table = NULL;

/* dodaje nowy symbol na poczatek listy,
 * przekopiowuje mu podana nazwa */
symbol* sym_put(char *id) {
    DBG_SYMBOL_PUT(id);
    symbol *ptr;
    ptr = (symbol*)malloc(sizeof(symbol));
    ptr->id = strdup(id);
    ptr->next = sym_table;
    //ptr->val = -1;
    sym_table = ptr;
    return ptr;
}

/* usuwa symbol z poczatku listy. */
void sym_pop(char* id) {
    DBG_SYMBOL_REMOVE(id);
    CHECK_ITERATOR(sym_table->id, id);
    symbol* sym = sym_table;
    sym_table = sym_table->next;
    free(sym);
}

/* zwraca symbol o podanej nazwie lub NULL,
 * jesli symbolu nie ma */
symbol* sym_get(char*id) {
    DBG_SYMBOL_GET(id);
    symbol *ptr;
    for (ptr = sym_table; ptr != NULL; ptr = ptr->next)
        if (strcmp(ptr->id, id) == 0)
            return ptr;
    return NULL;
}

/* Drukuje tablice symboli */
void sym_print() {
    symbol* head = sym_table;
    printf("  name t i offset  begin    end\n");
    while(head != NULL) {
        printf("%6s %d %d %6lld %6lld %6lld\n", 
        head->id, head->type, head->is_init, head->offset, head->begin, head->end);
        head = head->next;
    }
}
