#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iomanip>
#include <cln/cln.h>
#include "symbol_table.hpp"
#include "../debugger/debugger.hpp"
#include "../debugger/warnings.hpp"

symbol* sym_table = NULL;

/* dodaje nowy symbol na poczatek listy,
 * przekopiowuje mu podana nazwa */
symbol* sym_put(char *id) {
    DBG_SYMBOL_PUT(id);
    symbol *ptr;
    ptr = new symbol;
    ptr->id = strdup(id);
    ptr->next = sym_table;
    ptr->prior = PWHITE;
    ptr->is_visited = false;
    ptr->deps = new DependencyList(ptr);
    sym_table = ptr;
    return ptr;
}

/* zwraca symbol o podanej nazwie lub NULL,
 * jesli symbolu nie ma */
symbol* sym_get(char*id) {
    DBG_SYMBOL_GET(id);
    symbol *ptr;
    for (ptr = sym_table; ptr != NULL; ptr = ptr->next)
        if (strcmp(ptr->id, id) == 0 && ptr->is_visible)
            return ptr;
    return NULL;
}

/* Drukuje tablice symboli */
void sym_print() {
    using namespace std;
    symbol* head = sym_table;
    printf("  name t i v offset  begin    end\n");
    while(head != NULL) {
        printf("%6s %d %d %d %6ld %6ld %6ld\n", 
        head->id, head->type, head->is_init, head->is_visible, 
        CLN_CAST(head->offset), CLN_CAST(head->begin), CLN_CAST(head->end));
        head = head->next;
    }
}

/* Drukuje liste zaleznosci */
void deps_print() {
    using namespace std;
    symbol* head = sym_table;
    printf("      name (-) -> deps\n");
    while(head != NULL) {
        printf("%10s (%d) -> ", head->id, head->prior);
        head->deps->print();
        head = head->next;
    }
}

/* Przechodzi po symbolach w tablicy symboli */
void deps_traversal() {
    symbol* head = sym_table;
    while(head != NULL) {
        deps_dfs(head, head->prior);
        head = head->next;
    }
}

/* Przechodzi po symbolach w liscie zaleznosci */
void deps_dfs(symbol* sym, int prior) {
    if (sym->is_visited && sym->prior >= prior) {
        // NOTHING
    }
    else {
        // TRAVERS
        int new_prior = maxi(sym->prior, prior);
        sym->is_visited = true;
        sym->prior = new_prior;
        for(symbol* sym: *(sym->deps))
            deps_dfs(sym, new_prior);
    }
}