#include "instr_generator.h"

extern register_type registers[6];

/* pobiera wolny rejestr oraz umieszcza w nim podana stala,
 * zwraca rejestr, w ktorym zostala umieszczona stala */
int get_const(val_type val) {
    DBG_INSTRUCTION_BEGIN("load_const");
    int reg = register_get();
    reset(reg);
    
    if (val != 0) {
        val_type n = (val_type)log2(val) - 1;
        inc(reg);
    
        for(val_type mask = (1 << n); mask > 0; mask >>= 1) {
            shl(reg);
            if (mask & val) inc(reg);
        }
    }
    
    DBG_RVAL(reg);
    DBG_INSTRUCTION_END("load_const");
    return reg;
}

/* Pobiera dwa wolne rejestry x oraz y. W rejestrze y umieszcza
 * lokalizacje zmiennej id w pamieci. Nastepnie pobiera wartosci
 * pamieci z tej lokalizjacji oraz zapisuje pod rejestrem x.
 * Na koniec zwalnia rejestr y. Jesli podana zmienna nie istnieje,
 * informuje o bledzie. */
int get_variable(char* id) {
    DBG_INSTRUCTION_BEGIN("get_variable");
    symbol* sym = sym_get(id);

    if (sym == NULL) {
        ERR_ADD();
        ERR_ID_UNDECLARED(id);
    }
    else {
        int x = register_get();
        int y = get_const(sym->offset);
        load(x, y);
        REG_OFFSET(x, sym->offset);
        REG_FREE(y);
        return x;
    }
    DBG_INSTRUCTION_END("put_variable");
    return NOTHING;
}

/* Dodaje zmienna o podanej nazwie do tablicy symboli,
 * alokuje miejsce dla nowej zmiennej. Jesli symbol 
 * o podanej nazwie juz istnieje, informuje o bledzie. */
void put_variable(char* id) {
    DBG_INSTRUCTION_BEGIN("put_variable");
    symbol* sym = sym_get(id);
    
    if (sym != NULL) {
        ERR_ADD();
        ERR_ID_DECLARED(id);
    }
    else {
        sym = sym_put(id);
        sym->type = VARIABLE;
        sym->offset = variable_allocate();
        sym->is_init = false;
    }

    DBG_INSTRUCTION_END("put_variable");
    DBG_SYMBOL_PRINT();
}

/* Dodaje tablice o podanej nazwie do tablicy symboli,
 * alokuje miejsce dla nowej tablicy. Jesli symbol
 * o podanej nazwie juz istnieje lub podano nieprawidlowy
 * zakres tablicy, informuje o bledzie. */
void put_array(char* id, input_type begin, input_type end) {
    DBG_INSTRUCTION_BEGIN("put_table");
    symbol* sym = sym_get(id);

    if (sym != NULL) {
        ERR_ADD();
        ERR_ID_DECLARED(id);
    }
    else if (begin > end) {
        ERR_ADD();
        ERR_ARRAY_RANGE(id, begin, end);
    } 
    else {
        sym = sym_put(id);
        sym->type = ARRAY;
        sym->offset = array_allocate(end-begin+1);
        sym->begin = begin;
        sym->end = end;
    }

    DBG_INSTRUCTION_END("put_table");
    DBG_SYMBOL_PRINT();
}

/* Dodaje zawartosc jednego rejestru do drugiego,
 * zwalnia niepotrzebny rejstr, zwraca rejestr z suma. */
int sum(int x, int y) {
    DBG_INSTRUCTION_BEGIN("add");
    add(x,y);
    REG_FREE(y);

    DBG_INSTRUCTION_END("add");
    return x;
}

/* Przypisuje wartosc z rejestru y do zmiennej przechowywanej
 * przez rejestr x, na koniec zwalnia obydwa rejestry. */
void assign(int x, int y) {
    
}