#include "symbol_table.h"

symbol* sym_table = NULL;

/* dodaje nowy symbol na poczatek listy,
 * przekopiowuje mu podana nazwa */
symbol* sym_put(char *id) {
    DBG_SYMBOL_PUT(id);
    symbol *ptr;
    ptr = malloc(sizeof(symbol));
    ptr->id = strdup(id);
    ptr->next = sym_table;
    sym_table = ptr;
    return ptr;
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