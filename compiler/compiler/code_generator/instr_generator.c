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
        RG(x).offset = sym->offset;
        RG(y).is_free = true;
        return x;
    }
    DBG_INSTRUCTION_END("put_variable");
    return NOTHING;
}


/* Dodaje zmienna o podanej nazwie do tablicy symboli,
 * alokuje miejsce dla nowej zmiennej. Jesli zmienna 
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
    }

    DBG_INSTRUCTION_END("put_variable");
}

/* Dodaje zawartosc jednego rejestru do drugiego,
 * zwalnia niepotrzebny rejstr, zwraca rejestr z suma. */
int reg_add(int x, int y) {
    DBG_INSTRUCTION_BEGIN("add");
    add(x,y);
    RG(y).is_free = true;

    DBG_INSTRUCTION_END("add");
    return x;
}

/* Przypisuje wartosc z rejestru y do zmiennej przechowywanej
 * przez rejestr x, na koniec zwalnia obydwa rejestry. */
void assign(int x, int y) {
    
}