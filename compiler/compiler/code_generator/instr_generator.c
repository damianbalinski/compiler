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



/****************** SKOKI ************************/
void jump_true_false(cond_type* cond, unit_type* condition, bool type) {
    DBG_INSTRUCTION_BEGIN("jump_true_false");
    if (type == INIT) {
        // JUMP TRUE_FALSE - INIT
        reg_check(condition);
        cond->jump_true_false = jzero(condition->reg, 0);
    }
    else if (condition->type) {
        // JUMP TRUE - FINISH
        code_modif(cond->jump_true_false, cond->label_cmd - cond->jump_true_false);
    }
    else {
        // JUMP FALSE - FINISH
        code_modif(cond->jump_true_false, cond->label_end - cond->jump_true_false);
    }

    DBG_INSTRUCTION_END("jump_true_false");
}

void jump_end(cond_type* cond, unit_type* condition, bool type) {
    DBG_INSTRUCTION_BEGIN("jump_end");
    if (type == INIT && condition->type) {
        // JUMP END - INIT
         cond->jump_end = jump(0);
    }
    else if (type == INIT) {
        // NOTHING
    }
    else if (condition->type) {
        // JUMP END - FINISH
        code_modif(cond->jump_end, cond->label_end - cond->jump_end);
    }
    else {
        // NOTHING
    }
    DBG_INSTRUCTION_END("jump_end");
}

void jump_cond(cond_type* cond, unit_type* condition, bool type) {
    DBG_INSTRUCTION_BEGIN("jump_cond");
    if (type == INIT) {
        // JUMP_COND - INIT
        reg_check(condition);
        cond->jump_cond = jump(0);
    }
    else {
        // JUMP_COND - FINISH
        code_modif(cond->jump_cond, cond->label_cond - cond->jump_cond);
    }
    DBG_INSTRUCTION_END("jump_cond");
}

void jump_cmd(cond_type* cond, unit_type* condition, bool type) {
    DBG_INSTRUCTION_BEGIN("jump_cmd");
    if (type == INIT && condition->type) {
        // NOTHING
    }
    else if (type == INIT) {
        // JUMP_CMD - INIT
        cond->jump_cmd = jump(0);
    }
    else if (condition->type) {
        // NOTHING
    }
    else {
        // JUMP_CMD - FINISH
        code_modif(cond->jump_cmd, cond->label_cmd - cond->jump_cmd);
    }
    DBG_INSTRUCTION_END("jump_cmd");
}

/* Zwalnianie pamieci po skokach. */
void jumps_free(cond_type* cond, unit_type* condition) {
    DBG_INSTRUCTION_BEGIN("jumps_free");
    // ZWALNIANIE
    cond_free(cond);
    reg_free(condition->reg);
    unit_free(condition);
    DBG_INSTRUCTION_END("jumps_free");
}

/*************************************************/

/* Modyfikacja skoku jump_else. */
void jumps_modif_else(cond_type* cond, unit_type* condition) {
    DBG_INSTRUCTION_BEGIN("jumps_modif_else");
    code_modif(cond->jump_else, cond->label_else - cond->jump_else);
    DBG_INSTRUCTION_END("jumps_modif_else");
}

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
 * ERR4 - (NOINIT) id jest stala
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
    else if (init == NOINIT && sym->is_const) {
        ERR_ID_CONST(id);
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

/* Dodaje iterator, przydziela mu pamiec. */
symbol* add_iterator(char* id) {
    DBG_INSTRUCTION_BEGIN("add_iterator");
    symbol* sym;
    sym = sym_put(id);
    sym->type = VARIABLE;
    sym->is_init = true;
    sym->is_const = true;
    sym->offset = variable_allocate();

    DBG_INSTRUCTION_END("add_iterator");
    DBG_SYMBOL_PRINT();
    return sym;
}

/* Pobiera lokalizacje iteratora. */
// unit_type* get_iterator(char* id) {
//     DBG_INSTRUCTION_BEGIN("get_iterator");
//     symbol* sym = sym_get(id);
//     unit_type* unit = unit_alloc();
//     int x = reg_get_free();         // wolny rejestr
//     reg_const(x, sym->offset);      // stala do rejestru
//     sym->is_init = true;
//     reg_connect(unit, x);

//     DBG_INSTRUCTION_END("get_iterator");
//     return unit;
// }

/* Usuwa iterator. */
void remove_iterator(char* id) {
    DBG_INSTRUCTION_BEGIN("remove_iterator");
    sym_pop(id);
    DBG_INSTRUCTION_END("remove_iterator");
    DBG_SYMBOL_PRINT();
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

/* Suma. 
 * unit1 = unit1 + unit2 */
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

/* Roznica. 
 * unit1 = unit1 - unit2 */
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

/* Iloczyn.
 * unit1 = unit1 * unit2 */
unit_type* mul(unit_type* unit1, unit_type* unit2) {
    DBG_INSTRUCTION_BEGIN("mul");
    // INSTRUKCJE
    reg_check(unit1);
    reg_check(unit2);
    int z = reg_get_free();
    reg_mul(unit1->reg, unit2->reg, z);

    // ZWALNIANIE
    reg_free(unit1->reg);
    unit1->reg = z;
    reg_free(unit2->reg);
    unit_free(unit2);

    DBG_INSTRUCTION_END("mul");
    return unit1;
}

/* Rowne/Rozne.
 * type=true    unit1 = (unit1 == unit2)
 * typ2=false   unit1 = (unit1 != unit2) */
unit_type* eq_ne(unit_type* unit1, unit_type* unit2, bool type) {
    DBG_INSTRUCTION_BEGIN("eq_ne");
    // INSTRUKCJE
    reg_check(unit1);
    reg_check(unit2);
    unit1->type = type;

    reset(SUPER_REGISTER);
    add(SUPER_REGISTER, unit2->reg);
    sub(unit2->reg, unit1->reg);
    sub(unit1->reg, SUPER_REGISTER);
    add(unit1->reg, unit2->reg);

    // ZWALNIANIE
    reg_free(unit2->reg);
    unit_free(unit2);

    DBG_INSTRUCTION_END("eq_ne");
    return unit1;
}


/* Mniejsze/Wieksze rowne.
 * type=false    unit2 = (unit1 < unit2)
 * typ2=true     unit2 = (unit1 >= unit2) */
unit_type* lt_ge(unit_type* unit1, unit_type* unit2, bool type) {
    DBG_INSTRUCTION_BEGIN("lt_ge");
    // INSTRUKCJE
    reg_check(unit1);
    reg_check(unit2);
    unit2->type = type;
    sub(unit2->reg, unit1->reg);

    // ZWALNIANIE
    reg_free(unit1->reg);
    unit_free(unit1);

    DBG_INSTRUCTION_END("lt_ge");
    return unit2;
}

/* Wieksze/Mniejsze rowne.
 * type=false   unit1 = (unit1 > unit2)
 * type=true    unit1 = (unit1 <= unit2) */
unit_type* gt_le(unit_type* unit1, unit_type* unit2, bool type) {
    DBG_INSTRUCTION_BEGIN("gt_le");
    // INSTRUKCJE
    reg_check(unit1);
    reg_check(unit2);
    unit1->type = type;
    sub(unit1->reg, unit2->reg);

    // ZWALNIANIE
    reg_free(unit2->reg);
    unit_free(unit2);

    DBG_INSTRUCTION_END("gt_le");
    return unit1;
}

void for_cond(unit_type* value, unit_type* condition, bool type) {
    DBG_INSTRUCTION_BEGIN("for_cond");
    reg_check(value);
    reg_check(condition);
    condition->type = GREATER;
    if (type == FOR_TO) {
        // FOR TO
        inc(condition->reg);
        sub(condition->reg, value->reg);
    }
    else {
        // FOR DOWNTO
        int x = reg_get_free();
        reset(x);
        add(x, value->reg);
        inc(x);
        sub(x, condition->reg);
        reg_free(condition->reg);
        reg_connect(condition, x);
    }
    DBG_INSTRUCTION_END("for_cond");
}

void for_init(cond_type* cond, unit_type* value) {
    DBG_INSTRUCTION_BEGIN("for_init");
    reg_check(value);
    reg_const(SUPER_REGISTER, cond->iter->offset);
    store(value->reg, SUPER_REGISTER);
    DBG_INSTRUCTION_END("for_init");
}

void for_step(cond_type* cond, unit_type* value, unit_type* condition, bool type) {
    DBG_INSTRUCTION_BEGIN("for_step");
    reg_check(value);
    reg_check_log(condition);

    if (type == FOR_TO) {
        // FOR TO
        // reg_const(value->reg, cond->iter->offset);
        // load(value->reg, value->reg)
        inc(value->reg);
        reg_const(SUPER_REGISTER, cond->iter->offset);
        store(value->reg, SUPER_REGISTER);
        dec(condition->reg);
    }
    else {
        // FOR DOWNTO
        dec(value->reg);
        reg_const(SUPER_REGISTER, cond->iter->offset);
        store(value->reg, SUPER_REGISTER);
        dec(condition->reg);
    }
    
    DBG_INSTRUCTION_END("for_step");
}

/* Zwalnianie pamieci po petli for. */
void for_free(cond_type* cond, unit_type* value, unit_type* condition) {
    DBG_INSTRUCTION_BEGIN("for_free");
    // ZWALNIANIE
    cond_free(cond);
    reg_free(value->reg);
    unit_free(value);
    reg_free(condition->reg);
    unit_free(condition);
    DBG_INSTRUCTION_END("for_free");
}