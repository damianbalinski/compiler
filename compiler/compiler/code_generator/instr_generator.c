#include "instr_generator.h"
#include "code_generator.h"
#include "registers_machine.h"
#include "registers.h"
#include "../others/types.h"
#include "../others/unit.h"
#include "../debugger/errors.h"
#include "../debugger/debugger.h"
#include "../symbol_table/symbol_table.h"
#include "../symbol_table/data_manager.h"

extern int yylineno;
extern char* yytext;
extern register_type registers[6];

/* Pobiera stala. Przechowuje ja w rejestrze. */
unit_type* get_const(input_type val, bool type) {
    DBG_INSTRUCTION_BEGIN("get_const");
    unit_type* unit = unit_alloc();
    
    if (type == VALUE) {
        // VALUE
        int x = reg_get_free();         // wolny rejestr
        reg_const(x, val);              // stala do rejestru
        reg_connect(unit, x);
    }
    else {
        // LOCATION
        int x = reg_get_free();             // wolny rejestr
        int offset = variable_allocate();   // zmienna tymczasowa
        reg_const(x, offset);               // stala do rejestru
        reg_const(SUPER_REGISTER, val);     // stala do rejestru  
        store(SUPER_REGISTER, x);           // rejestr do pamieci
        reg_connect(unit, x);
    }

    DBG_INSTRUCTION_END("get_const");
    return unit;
}

/* Pobiera lokalizacje zmiennej. Ustawia zmienna
 * jako zainicjalizowana.
 * ERR1 - id nie zostal zadeklarowany
 * ERR2 - id nie jest zmienna
 * ERR3 - (INIT) id nie zostal zainicjalizowany
 */
unit_type* get_variable(char* id, bool type, bool init) {
    DBG_INSTRUCTION_BEGIN("get_variable");
    symbol* sym = sym_get(id);
    unit_type* unit = unit_alloc();

    if (sym == NULL) {
        ERR_ID_UNDECLARED(id);
        ERR_ADD();
    }
    else if (sym->type != VARIABLE) {
        ERR_ID_NOT_VARIABLE(id);
        ERR_ADD();
    }
    else if (init == INIT && sym->is_init == false) {
        ERR_ID_NOT_INIT(id);
        ERR_ADD();
    }
    else if (type == VALUE) {
        // VALUE
        int x = reg_get_free();     // wolny rejestr
        reg_const(x, sym->offset);  // stala do rejestru
        load(x, x);                 // wartosc do rejestru
        reg_connect(unit, x);
    }
    else {
        // LOCATION
        int x = reg_get_free();     // wolny rejestr
        reg_const(x, sym->offset);  // stala do rejestru
        sym->is_init = true;
        reg_connect(unit, x);
    }

    DBG_INSTRUCTION_END("get_variable");
    return unit;
}

/* Pobiera lokalizacje komorki tablicy
 * indeksowanej przez stala.
 * ERR1 - id nie zostal zadeklarowany
 * ERR2 - id nie jest tablica
 * ERR3 - num jest poza zakresem tablicy
 */
unit_type* get_array_num(char* id, input_type num, bool type, bool init) {
    DBG_INSTRUCTION_BEGIN("get_array_num");
    symbol* sym = sym_get(id);
    unit_type* unit = unit_alloc();

    if (sym == NULL) {
        ERR_ID_UNDECLARED(id);
        ERR_ADD();
    }
    else if (sym->type != ARRAY) {
        ERR_ID_NOT_ARRAY(id);
        ERR_ADD();
    }
    else if (num < sym->begin || num > sym->end) {
        ERR_ARRAY_INDEX_RANGE(id, num);
        ERR_ADD();
    }
    else if (type == VALUE) {
        // VALUE
        int x = reg_get_free();                         // wolny rejestr
        reg_const(x, sym->offset + num - sym->begin);   // stala do rejestru
        load(x,x);                                      // wartosc do rejestru
        reg_connect(unit, x);
    }
    else {
        // LOCATION
        int x = reg_get_free();                         // wolny rejestr
        reg_const(x, sym->offset + num - sym->begin);   // stala do rejestru
        reg_connect(unit, x);
    }

    DBG_INSTRUCTION_END("get_array_num");
    return unit;
}

/*
 * Pobiera lokalizacje komorki tablicy indeksowanej 
 * przez zmienna.
 * ERR1 - id nie zostal zadeklarowany
 * ERR2 - id nie jest tablica
 * ERR3 - id_var nie zostal zadeklarowany
 * ERR4 - id_var nie jest zmienna
 * ERR5 - id_var nie zostal zainicjalizowany
 */
unit_type* get_array_var(char* id, char* id_var, bool type, bool init) {
    DBG_INSTRUCTION_BEGIN("get_array_var");
    symbol* sym = sym_get(id);
    symbol* sym_var = sym_get(id_var);
    unit_type* unit = unit_alloc();

    if (sym == NULL) {
        ERR_ID_UNDECLARED(id);
        ERR_ADD();
    }
    else if (sym->type != ARRAY) {
        
        ERR_ID_NOT_ARRAY(id);
        ERR_ADD();
    }
    else if (sym_var == NULL) {
        ERR_ID_UNDECLARED(id_var);
        ERR_ADD();
    }
    else if (sym_var->type != VARIABLE) {
        ERR_ID_NOT_VARIABLE(id_var);
        ERR_ADD();
    }
    else if (sym_var->is_init == false) {
        ERR_ID_NOT_INIT(id_var);
        ERR_ADD();
    }
    else if (type == VALUE) {
        // VALUE
        int x = reg_get_free();                         // wolny rejestr
        reg_const(x, sym->offset - sym->begin);         // stala do rejestru
        reg_const(SUPER_REGISTER, sym_var->offset);     // stala do rejestru
        add(x, SUPER_REGISTER);                         // suma rejestrow
        load(x,x);                                      // wartosc do rejestru
        reg_connect(unit, x);
    }
    else {
        // LOCATION
        int x = reg_get_free();                         // wolny rejestr
        reg_const(x, sym->offset - sym->begin);         // stala do rejestru
        reg_const(SUPER_REGISTER, sym_var->offset);     // stala do rejestru
        add(x, SUPER_REGISTER);                         // suma rejestrow
        reg_connect(unit, x);
    }

    DBG_INSTRUCTION_END("get_array_var");
    return unit;
}

/* Dodaje nowa zmienna, przydziela jej pamiec.
 * ERR1 - id zostal zadeklarowany
 */
void add_variable(char* id) {
    DBG_INSTRUCTION_BEGIN("add_variable");
    symbol* sym = sym_get(id);
    
    if (sym != NULL) {
        ERR_ID_DECLARED(id);
        ERR_ADD();
    }
    else {
        sym = sym_put(id);
        sym->type = VARIABLE;
        sym->is_init = false;
        sym->offset = variable_allocate();
    }

    DBG_INSTRUCTION_END("add_variable");
    DBG_SYMBOL_PRINT();
}

/* Dodaje nowa tablice, przydziela jej pamiec.
 * ERR1 - id zostal zadeklarowany
 * ERR2 - begin wieksze od end
 */
void add_array(char* id, input_type begin, input_type end) {
    DBG_INSTRUCTION_BEGIN("add_table");
    symbol* sym = sym_get(id);

    if (sym != NULL) {
        ERR_ID_DECLARED(id);
        ERR_ADD();
    }
    else if (begin > end) {
        ERR_ARRAY_INIT_RANGE(id, begin, end);
        ERR_ADD();
    } 
    else {
        sym = sym_put(id);
        sym->type = ARRAY;
        sym->offset = array_allocate(end-begin+1);
        sym->begin = begin;
        sym->end = end;
    }

    DBG_INSTRUCTION_END("add_table");
    DBG_SYMBOL_PRINT();
}


/* Przypisuje wartosc do zmiennej. */
void assign(unit_type* unit1, unit_type* unit2) {
    DBG_INSTRUCTION_BEGIN("assign");
    // INSTRUKCJE
    reg_check(unit1);
    reg_check(unit2);
    store(unit2->reg, unit1->reg);
    
    // ZWALNIANIE
    reg_free(unit1->reg);
    reg_free(unit2->reg);
    unit_free(unit1); 
    unit_free(unit2);

    DBG_INSTRUCTION_END("assign");
}

/* Drukuje dane na wyjsciu. */
void write(unit_type* unit) {
    DBG_INSTRUCTION_BEGIN("write");
    // INSTRUKCJE
    reg_check(unit);        // adres zmiennej
    put(unit->reg);         // zapis na wyjscie

    // ZWALNIANIE
    reg_free(unit->reg);
    unit_free(unit); 

    DBG_INSTRUCTION_END("write");
}

/* Pobiera dane z wejscia. */
void read(unit_type* unit) {
    DBG_INSTRUCTION_BEGIN("read");
    // INSTRUKCJE
    reg_check(unit);        // adres zmiennej
    get(unit->reg);         // pobranie wejscia

    // ZWALNIANIE
    reg_free(unit->reg);
    unit_free(unit); 

    DBG_INSTRUCTION_END("read");
}

/* Suma. */
unit_type* sum(unit_type* unit1, unit_type* unit2) {
    DBG_INSTRUCTION_BEGIN("sum");
    // INSTRUKCJE
    reg_check(unit1);       
    reg_check(unit2);
    add(unit1->reg, unit2->reg);

    // ZWALNIANIE
    reg_free(unit2->reg);
    unit_free(unit2); 

    DBG_INSTRUCTION_END("sum");
    return unit1;
}

/* Roznica. */
unit_type* dif(unit_type* unit1, unit_type* unit2) {
    DBG_INSTRUCTION_BEGIN("dif");
    // INSTRUKCJE
    reg_check(unit1);       
    reg_check(unit2);
    sub(unit1->reg, unit2->reg);

    // ZWALNIANIE
    reg_free(unit2->reg);
    unit_free(unit2); 

    DBG_INSTRUCTION_END("dif");
    return unit1;
}