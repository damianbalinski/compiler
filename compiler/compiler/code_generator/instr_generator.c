#include "instr_generator.h"

extern register_type registers[6];


/* Pobiera stala. Przechowuje ja w rejestrze. */
unit_type get_const(input_type val) {
    DBG_INSTRUCTION_BEGIN("get_const");
    unit_type unit;
    
    int x = register_get();
    unit.reg = x;
    reset(x);
    
    if (val != 0) {
        input_type n = (input_type)log2(val) - 1;
        inc(x);
    
        for(input_type mask = (1 << n); mask > 0; mask >>= 1) {
            shl(x);
            if (mask & val) inc(x);
        }
    }
    DBG_RVAL(x);

    DBG_INSTRUCTION_END("get_const");
    return unit;
}


/* Pobiera lokalizacje zmiennej. Ustawia zmienna
 * jako zainicjalizowana.
 * ERR1 - id nie zostal zadeklarowany
 * ERR2 - id nie jest zmienna
 */
unit_type get_lvariable(char* id) {
    DBG_INSTRUCTION_BEGIN("get_lvariable");
    symbol* sym = sym_get(id);
    unit_type unit;

    if (sym == NULL) {
        ERR_ADD();
        ERR_ID_UNDECLARED(id);
    }
    else if (sym->type != VARIABLE) {
        ERR_ADD();
        ERR_ID_NOT_VARIABLE(id);
    }
    else {
        sym->is_init = true;
        unit.offset = sym->offset;
    }

    DBG_INSTRUCTION_END("get_lvariable");
    return unit;
}

/* Pobiera lokalizacje komorki tablicy
 * indeksowanej przez stala.
 * ERR1 - id nie zostal zadeklarowany
 * ERR2 - id nie jest tablica
 * ERR3 - num jest poza zakresem tablicy
 */
unit_type get_larray_num(char* id, input_type num) {
    DBG_INSTRUCTION_BEGIN("get_larray_num");
    symbol* sym = sym_get(id);
    unit_type unit;

    if (sym == NULL) {
        ERR_ADD();
        ERR_ID_UNDECLARED(id);
    }
    else if (sym->type != ARRAY) {
        ERR_ADD();
        ERR_ID_NOT_ARRAY(id);
    }
    else if (num < sym->begin || num > sym->end) {
        ERR_ADD();
        ERR_ARRAY_INDEX_RANGE(id, num);
    }
    else {
        unit.offset = sym->offset + num - sym->begin;
    }

    DBG_INSTRUCTION_END("get_larray_num");
    return unit;
}

/*
 * Pobiera lokalizacje komorki tablicy
 * indeksowanej przez zmienna.
 * ERR1 - id nie zostal zadeklarowany
 * ERR2 - id nie jest tablica
 * ERR3 - id_var nie zostal zadeklarowany
 * ERR4 - id_var nie jest zmienna
 * ERR5 - id_var nie zostal zainicjalizowany
 */
unit_type get_larray_var(char* id, char* id_var) {
    DBG_INSTRUCTION_BEGIN("get_larray_var");
    symbol* sym = sym_get(id);
    symbol* sym_var = sym_get(id_var);
    unit_type unit;

    if (sym == NULL) {
        ERR_ADD();
        ERR_ID_UNDECLARED(id);
    }
    else if (sym->type != ARRAY) {
        ERR_ADD();
        ERR_ID_NOT_ARRAY(id);
    }
    else if (sym_var == NULL) {
        ERR_ADD();
        ERR_ID_UNDECLARED(id_var);
    }
    else if (sym_var->type != VARIABLE) {
        ERR_ADD();
        ERR_ID_NOT_VARIABLE(id_var);
    }
    else if (sym_var->is_init == false) {
        ERR_ADD();
        ERR_ID_NOT_INIT(id_var);
    }
    else {
        // TODO pobiera wolny rejestr, zapisuje w nim adres
        // wskazujacy na komorke pamieci, zapisuje ten rejestr
        // do unit
    }

    DBG_INSTRUCTION_END("get_larray_var");
    return unit;
}


/* Pobiera wartosc zmiennej. Przechowuje ja
 * w rejestrze.
 * ERR1 - id nie zostal zadeklarowany
 * ERR2 - id nie jest zmienna
 * ERR3 - id nie zostal zainicjalizowany
 */
unit_type get_rvariable(char* id) {
    DBG_INSTRUCTION_BEGIN("get_rvariable");
    symbol* sym = sym_get(id);
    unit_type unit;
    
    if (sym == NULL) {
        ERR_ADD();
        ERR_ID_UNDECLARED(id);
    }
    else if (sym->type != VARIABLE) {
        ERR_ADD();
        ERR_ID_NOT_VARIABLE(id);
    }
    else if (sym->is_init == false) {
        ERR_ADD();
        ERR_ID_NOT_INIT(id);
    }
    else {
        unit = get_const(sym->offset);   // pozycja w pamieci do rejestru
        load(unit.reg, unit.reg);        // wartosc zmiennej do rejestru
    }

    DBG_INSTRUCTION_END("get_rvariable");
    return unit;
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
        ERR_ARRAY_INIT_RANGE(id, begin, end);
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