#include "instr_generator.h"

/* pobiera wolny rejestr oraz umieszcza w nim podana stala,
 * zwraca rejestr, w ktorym zostala umieszczona stala */
int load_const(val_type val) {
    DBG_INSTRUCTION_BEGIN("load_const");
    int reg = register_get();
    reset(reg);

    if (val == 0)
        return reg;
    
    val_type n = (val_type)log2(val) - 1;
    inc(reg);
    for(val_type mask = (1 << n); mask > 0; mask >>= 1) {
        shl(reg);
        if (mask & val) inc(reg);
    }

    DBG_INSTRUCTION_END("load_const");
    return reg;
}

/* dodaje zmienna o podanej nazwie do tablicy symboli,
 * alokuje miejsce dla nowej zmiennej */
void put_variable(char* id) {
    DBG_INSTRUCTION_BEGIN("put_variable");
    symbol* sym = sym_get(id);
    
    if (sym != NULL) {
        ERR_ADD();
        ERR_ID_DECLARED();
    }
    else {
        sym = sym_put(id);
        sym->offset = variable_allocate();
    }

    DBG_INSTRUCTION_END("put_variable");
}

int put_table(char* id) {}

int get_variable(char* id) {}

int get_table(char* id) {}