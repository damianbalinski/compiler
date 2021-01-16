#include "../debugger/debugger.hpp"
#include "../debugger/errors.hpp"
#include "../optimizer/optimizer.hpp"
#include "../code_generator/registers_machine.hpp"
#include "../code_generator/code_generator.hpp"
#include "../symbol_table/data_manager.hpp"
#include "values.hpp"

extern int yylineno;
extern char* yytext;

/* Wartosc */
void VNum::init() {
    DBG_INIT_BEGIN(val_id);
    val_sym = sym_put(val_id);
    val_sym->is_visible = false;
    val_sym->is_const = true;
    val_sym->is_init = true;
    DBG_INIT_END(val_id);
}


/* Zmienna
 * ERR1 - id nie zostal zadeklarowany
 * ERR2 - id nie jest zmienna
 * ERR3 - (INIT) id nie zostal zainicjalizowany
 * ERR4 - (NOINIT) id jest stala
 */
void VVar::init() {
    DBG_INIT_BEGIN(var_id);
    var = sym_get(var_id);
    if (var == NULL) {
        ERR_ID_UNDECLARED(var_id);
        ERR_ADD();
    }
    else if (var->type != VARIABLE) {
        ERR_ID_NOT_VARIABLE(var_id);
        ERR_ADD();
    }
    else if (is_init == INIT && var->is_init == false) {
        ERR_ID_NOT_INIT(var->id);
        ERR_ADD();
    }
    else if (is_init == NOINIT && var->is_const) {
        ERR_ID_CONST(var->id);
        ERR_ADD();
    }
    if (type == LOCATION) {
        var->is_init = true;
    }

    DBG_INIT_END(var_id);
}

/* Tablica indeksowana liczba
 * ERR1 - id nie zostal zadeklarowany
 * ERR2 - id nie jest tablica
 * ERR3 - num jest poza zakresem tablicy
 */
void VArrNum::init() {
    DBG_INIT_BEGIN(arr_id);
    arr = sym_get(arr_id);

    if (arr == NULL) {
        ERR_ID_UNDECLARED(arr_id);
        ERR_ADD();
    }
    else if (arr->type != ARRAY) {
        ERR_ID_NOT_ARRAY(arr_id);
        ERR_ADD();
    }
    else if (val < arr->begin || val > arr->end) {
        ERR_ARRAY_INDEX_RANGE(arr_id, val);
        ERR_ADD();
    }
    DBG_INIT_END(arr_id);
}

/* Tablica indeksowana zmienna
 * ERR1 - arr nie zostal zadeklarowany
 * ERR2 - arr nie jest tablica
 * ERR3 - var nie zostal zadeklarowany
 * ERR4 - var nie jest zmienna
 * ERR5 - var nie zostal zainicjalizowany
 */
void VArrVar::init() {
    DBG_INIT_END2(arr_id, var_id);
    arr = sym_get(arr_id);
    var = sym_get(var_id);
    
    if (arr == NULL) {
        ERR_ID_UNDECLARED(arr_id);
        ERR_ADD();
    }
    else if (arr->type != ARRAY) {
        ERR_ID_NOT_ARRAY(arr_id);
        ERR_ADD();
    }
    else if (var == NULL) {
        ERR_ID_UNDECLARED(var_id);
        ERR_ADD();
    }
    else if (var->type != VARIABLE) {
        ERR_ID_NOT_VARIABLE(var_id);
        ERR_ADD();
    }
    else if (var->is_init == false) {
        ERR_ID_NOT_INIT(var->id);
        ERR_ADD();
    }
    DBG_INIT_END2(arr_id, var_id);
}

/* Pobiera stala. Przechowuje ja w rejestrze. */
unit_type* get_const(input_type val, bool type) {
    DBG_INSTRUCTION_BEGIN("get_const");
    unit_type* unit = unit_alloc();
    
    if (type == VALUE) {
        // VALUE
        #ifdef OPTIMIZE_CONST_POSTPONE
            unit->val = val;
        #else
            int x = reg_get_free();         // wolny rejestr
            reg_const(x, val);              // stala do rejestru
            reg_connect(unit, x);
        #endif
    }
    else {
        // LOCATION
        int x = reg_get_free();                     // wolny rejestr
        input_type offset = variable_allocate();    // zmienna tymczasowa
        reg_const(x, offset);                       // stala do rejestru
        reg_const(SUPER_REGISTER, val);             // stala do rejestru  
        store(SUPER_REGISTER, x);                   // rejestr do pamieci
        reg_connect(unit, x);
    }

    DBG_INSTRUCTION_END("get_const");
    return unit;
}

/* Pobiera lokalizacje/wartosc zmiennej. Ustawia zmienna
 * jako zainicjalizowana.
 */
unit_type* get_variable(symbol* sym, bool type, bool init) {
    DBG_INSTRUCTION_BEGIN("get_variable");
    unit_type* unit = unit_alloc();

    if (type == VALUE) {
        // VALUE
        #ifdef OPTIMIZE_VAR_POSTPONE
            unit->offset = sym->offset;
        #else
            int x = reg_get_free();     // wolny rejestr
            reg_const(x, sym->offset);  // stala do rejestru
            load(x, x);                 // wartosc do rejestru
            reg_connect(unit, x);
        #endif
    }
    else {
        // LOCATION
        int x = reg_get_free();     // wolny rejestr
        reg_const(x, sym->offset);  // stala do rejestru
        reg_connect(unit, x);
    }

    DBG_INSTRUCTION_END("get_variable");
    return unit;
}

/* Pobiera lokalizacje/wartosc komorki tablicy
 * indeksowanej przez stala.
 */
unit_type* get_array_num(symbol* sym, input_type num, bool type, bool init) {
    DBG_INSTRUCTION_BEGIN("get_array_num");
    unit_type* unit = unit_alloc();

    if (type == VALUE) {
        // VALUE
        #ifdef POTIMIZE_ARR_NUM_POSTPONE
            unit->offset = sym->offset + num - sym->begin;
        #else
            int x = reg_get_free();                         // wolny rejestr
            reg_const(x, sym->offset + num - sym->begin);   // stala do rejestru
            load(x,x);                                      // wartosc do rejestru
            reg_connect(unit, x);
        #endif
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
 * Pobiera lokalizacje/wartosc komorki tablicy indeksowanej 
 * przez zmienna.
 */
unit_type* get_array_var(symbol* sym, symbol* sym_var, bool type, bool init) {
    DBG_INSTRUCTION_BEGIN("get_array_var");
    unit_type* unit = unit_alloc();

    if (type == VALUE) {
        // VALUE
        int x = reg_get_free();                         // wolny rejestr
        reg_const(x, sym_var->offset);                  // stala do rejestru
        load(x, x);                                     // wartosc do rejestru
        reg_const(SUPER_REGISTER, sym->offset);         // stala do rejestru
        add(x, SUPER_REGISTER);                         // suma rejestrow
        reg_const(SUPER_REGISTER, sym->begin);          // stala do rejestru
        sub(x, SUPER_REGISTER);                         // roznica rejestrow
        load(x, x);                                     // wartosc do rejestru
        reg_connect(unit, x);
    }
    else {
        // LOCATION
        int x = reg_get_free();                         // wolny rejestr
        reg_const(x, sym_var->offset);                  // stala do rejestru
        load(x, x);                                     // wartosc do rejestru
        reg_const(SUPER_REGISTER, sym->offset);         // stala do rejestru
        add(x, SUPER_REGISTER);                         // suma rejestrow
        reg_const(SUPER_REGISTER, sym->begin);          // stala do rejestru
        sub(x, SUPER_REGISTER);                         // roznica rejestrow
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
        sym->is_const = false;
        sym->is_visible = true;
        sym->offset = variable_allocate();
    }

    DBG_INSTRUCTION_END("add_variable");
    DBG_SYMBOL_PRINT();
}

/* Dodaje nowa tablice, przydziela jej pamiec.
 * ERR1 - id zostal zadeklarowany
 * ERR2 - begin wieksze od end
 */
void add_array(char* id, data_type begin, data_type end) {
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
        sym->is_visible = true;
    }

    DBG_INSTRUCTION_END("add_table");
    DBG_SYMBOL_PRINT();
}

/* Dodaje iterator. Przydziela pamiec dla iteratora
 * oraz warunku iteracji */
symbol* add_iterator(char* id) {
    DBG_INSTRUCTION_BEGIN("add_iterator");
    symbol* sym;
    sym = sym_put(id);
    sym->type = VARIABLE;
    sym->is_init = false;
    sym->is_const = true;
    sym->is_visible = false;
    sym->offset = array_allocate(2);

    DBG_INSTRUCTION_END("add_iterator");
    DBG_SYMBOL_PRINT();
    return sym;
}