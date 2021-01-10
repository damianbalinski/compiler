#include "instr_generator.hpp"
#include "code_generator.hpp"
#include "registers_machine.hpp"
#include "registers.hpp"
#include "../others/types.hpp"
#include "../others/unit.hpp"
#include "../debugger/errors.hpp"
#include "../debugger/debugger.hpp"
#include "../symbol_table/symbol_table.hpp"
#include "../symbol_table/data_manager.hpp"
#include "../optimizer/optimizer.hpp"
#include "../others/const.hpp"

extern int yylineno;
extern char* yytext;
extern register_type registers[6];

void jump_true_false(cond_type* cond, unit_type* condition, bool type) {
    DBG_INSTRUCTION_BEGIN("jump_true_false");
    if (type == INIT) {
        // JUMP TRUE_FALSE - INIT
        reg_check(condition);
        cond->jump_true_false = jzero(condition->reg, 0);
        reg_disconnect(condition, condition->reg);
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
        cond->jump_cond = jump(0);
    }
    else {
        // JUMP_COND - FINISH
        code_modif(cond->jump_cond, cond->label_cond - cond->jump_cond);
    }
    DBG_INSTRUCTION_END("jump_cond");
}

void jump_else(cond_type* cond, bool else_type, bool type) {
    DBG_INSTRUCTION_BEGIN("jump_else");
    if (type == INIT && else_type == IF_THEN_ELSE) {
        // JUMP ELSE - INIT
        cond->jump_else = jump(0);
    }
    else if (type == FINISH && else_type == IF_THEN_ELSE) {
        // JUMP ELSE - FINISH
        code_modif(cond->jump_else, cond->label_else - cond->jump_else);
    }
    DBG_INSTRUCTION_END("jump_else");
}

/* Zwalnianie pamieci po skokach. */
void jumps_free(cond_type* cond, unit_type* condition) {
    DBG_INSTRUCTION_BEGIN("jumps_free");
    // ZWALNIANIE
    cond_free(cond);
    unit_free(condition);
    DBG_INSTRUCTION_END("jumps_free");
}

/* Pobiera stala. Przechowuje ja w rejestrze. */
unit_type* get_const(input_type val, bool type) {
    DBG_INSTRUCTION_BEGIN("get_const");
    unit_type* unit = unit_alloc();
    
    if (type == VALUE) {
        // VALUE
        #ifdef OPTIMIZE_CONST_VAL
            unit->val = val;
        #else
            int x = reg_get_free();         // wolny rejestr
            reg_const(x, val);              // stala do rejestru
            reg_connect(unit, x);
        #endif
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

/* Pobiera lokalizacje/wartosc zmiennej. Ustawia zmienna
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

/* Pobiera lokalizacje/wartosc komorki tablicy
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
 * Pobiera lokalizacje/wartosc komorki tablicy indeksowanej 
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
 * OPT1     NUM + NUM
 * OPT2     NUM + a
 * OPT3     a   + NUM
 * OPT4     a   + a
 * ELSE     a1  + a2 */
unit_type* sum(unit_type* unit1, unit_type* unit2) {
    DBG_INSTRUCTION_BEGIN("sum");
    
    // NUM + NUM
    #ifdef OPTIMIZE_SUM_BOTH
    if (unit1->val != CLN_NOTHING && unit2->val != CLN_NOTHING) {
        unit1->val = unit1->val + unit2->val;
        unit_free(unit2);
        goto u1;
    }
    #endif

    // NUM + a
    #ifdef OPTIMIZE_SUM_LEFT
    if (unit1->val != CLN_NOTHING) {
        reg_check(unit2);
        if (reg_sum_cln(unit2->reg, unit1->val)) {
            unit_free(unit1);
            goto u2;
        }
    }
    #endif

    // a + NUM
    #ifdef OPTIMIZE_SUM_RIGHT
    if (unit2->val != CLN_NOTHING) {
        reg_check(unit1);
        if (reg_sum_cln(unit1->reg, unit2->val)) {
            unit_free(unit2);
            goto u1;
        }
    }
    #endif

    // VAL + VAL
    reg_check(unit1);
    reg_check(unit2);
    add(unit1->reg, unit2->reg);

    // ZWALNIANIE
    reg_free(unit2->reg);
    unit_free(unit2);
    
u1: DBG_INSTRUCTION_END("sum");
    return unit1;

u2: DBG_INSTRUCTION_END("sum");
    return unit2;
}

/* Roznica. 
 * OPT1     NUM - NUM
 * OPT2     NUM - a
 * OPT3     a   - NUM
 * OPT4     a   - a
 * ELSE     a1  - a2 */
unit_type* dif(unit_type* unit1, unit_type* unit2) {
    DBG_INSTRUCTION_BEGIN("dif");

    // NUM - NUM
    #ifdef OPTIMIZE_DIF_BOTH
    if (unit1->val != CLN_NOTHING && unit2->val != CLN_NOTHING) {
        unit1->val = (unit1->val < unit2->val) ? CLN_ZERO : unit1->val - unit2->val;
        unit_free(unit2);
        goto u1;
    }
    #endif

    // NUM - a
    #ifdef OPTIMIZE_DIF_LEFT
    if (unit1->val != CLN_NOTHING) {
        reg_check(unit2);
        if (reg_dif_left_cln(unit2->reg, unit1->val)) {
            unit_free(unit1);
            goto u2;
        }
    }
    #endif

    // a - NUM
    #ifdef OPTIMIZE_DIF_RIGHT
    if (unit2->val != CLN_NOTHING) {
        reg_check(unit1);
        if (reg_dif_right_cln(unit1->reg, unit2->val)) {
            unit_free(unit2);
            goto u1;
        }
    }
    #endif

    // INSTRUKCJE
    reg_check(unit1);       
    reg_check(unit2);
    sub(unit1->reg, unit2->reg);

    // ZWALNIANIE
    reg_free(unit2->reg);
    unit_free(unit2); 

u1: DBG_INSTRUCTION_END("dif");
    return unit1;

u2: DBG_INSTRUCTION_END("dif");
    return unit2;
}

/* Iloczyn.
 * OPT1     NUM * NUM
 * OPT2     NUM * a
 * OPT2     a   * NUM
 * ELSE     a1  * a2 */
unit_type* mul(unit_type* unit1, unit_type* unit2) {
    DBG_INSTRUCTION_BEGIN("mul");
    int z;

    // NUM * NUM
    #ifdef OPTIMIZE_MUL_BOTH
    if (unit1->val != CLN_NOTHING && unit2->val != CLN_NOTHING) {
        unit1->val = unit1->val * unit2->val;
        unit_free(unit2);
        goto u1;
    }
    #endif

    // NUM * a
    #ifdef OPTIMIZE_MUL_LEFT
    if (unit1->val != CLN_NOTHING) {
        reg_check(unit2);

        // 0 * a
        #ifdef OPTIMIZE_MUL_LEFT_ZERO
        if (reg_mul_zero(unit2->reg, unit1->val)) {
            unit_free(unit1);
            goto u2;
        }
        #endif

        // 2^n * a
        #ifdef OPTIMIZE_MUL_LEFT_TWO_POWER
        if (reg_mul_two_power_cln(unit2->reg, unit1->val)) {
            unit_free(unit1);
            goto u2;
        }
        #endif

        // n * a
        #ifdef OPTIMIZE_MUL_LEFT_OTHERS
        if (reg_mul_cln(unit2->reg, unit1->val, &z)) {
            unit_free(unit1);
            reg_free(unit2->reg);
            reg_connect(unit2, z);
            goto u2;
        }
        #endif
    }
    #endif

    // a * NUM
    #ifdef OPTIMIZE_MUL_RIGHT
    if (unit2->val != CLN_NOTHING) {
        reg_check(unit1);

        // a * 0
        #ifdef OPTIMIZE_MUL_RIGHT_ZERO
        if (reg_mul_zero(unit1->reg, unit2->val)) {
            unit_free(unit2);
            goto u1;
        }
        #endif

        // a * 2^n
        #ifdef OPTIMIZE_MUL_RIGHT_TWO_POWER
        if (reg_mul_two_power_cln(unit1->reg, unit2->val)) {
            unit_free(unit2);
            goto u1;
        }
        #endif

        // a * n
        #ifdef OPTIMIZE_MUL_RIGHT_OTHERS
        if (reg_mul_cln(unit1->reg, unit2->val, &z)) {
            unit_free(unit2);
            reg_free(unit1->reg);
            reg_connect(unit1, z);
            goto u1;
        }
        #endif
    }
    #endif
    
    // INSTRUKCJE
    reg_check(unit1);
    reg_check(unit2);
    z = reg_get_free();
    reg_mul(unit1->reg, unit2->reg, z);

    // ZWALNIANIE
    reg_free(unit1->reg);
    reg_connect(unit1, z);
    reg_free(unit2->reg);
    unit_free(unit2);

u1: DBG_INSTRUCTION_END("mul");
    return unit1;

u2: DBG_INSTRUCTION_END("mul");
    return unit2;
}

/* Iloraz.
 * OPT1     NUM / NUM
 * OPT2     NUM / a
 * OPT2     a   / NUM
 * OPT3     a   / a
 * ELSE     a1  / a2 */
 unit_type* divs(unit_type* unit1, unit_type* unit2) {
    DBG_INSTRUCTION_BEGIN("div");
    int q;
    int x;
    int y;

    // NUM / NUM
    #ifdef OPTIMIZE_DIV_BOTH
    if (unit1->val != CLN_NOTHING && unit2->val != CLN_NOTHING) {
        unit1->val = (unit2->val == CLN_ZERO) ? CLN_ZERO : cln::floor1(unit1->val, unit2->val);
        unit_free(unit2);
        goto u1;
    }
    #endif

    // NUM / a
    #ifdef OPTIMIZE_DIV_LEFT
    if (unit1->val != CLN_NOTHING) {
        reg_check(unit2);
        if (reg_div_left_cln(unit2->reg, unit1->val)) {
            unit_free(unit1);
            goto u2;
        }
    }
    #endif

    // a / NUM
    #ifdef OPTIMIZE_DIF_RIGHT
    if (unit2->val != CLN_NOTHING) {
        reg_check(unit1);

        // a / 0
        #ifdef OPTIMIZE_DIV_RIGHT_ZERO
        if (reg_div_right_zero(unit1->reg, unit2->val)) {
            unit_free(unit2);
            goto u1;
        }
        #endif

        // a / 2^n
        #ifdef OPTIMIZE_DIV_RIGHT_TWO_POWER
        if (reg_div_right_two_power_cln(unit1->reg, unit2->val)) {
            unit_free(unit2);
            goto u1;
        }
        #endif
    }
    #endif

    // INSTRUKCJE
    reg_check(unit1);
    reg_check(unit2);
    q = reg_get_free();
    x = reg_get_free();
    y = reg_get_free();
    reg_div(unit1->reg, unit2->reg, q, x, y, SUPER_REGISTER);

    // ZWALNIANIE
    reg_free(unit1->reg);
    reg_free(unit2->reg);
    reg_free(x);
    reg_free(y);
    unit1->reg = q;
    unit_free(unit2);

u1: DBG_INSTRUCTION_END("div");
    return unit1;

u2: DBG_INSTRUCTION_END("div");
    return unit2;
}

/* Reszta z dzielenia.
 * OPT1     NUM % NUM
 * OPT2     NUM % a
 * OPT2     a   % NUM
 * OPT3     a   / a
 * ELSE     a1  % a2 */
 unit_type* mod(unit_type* unit1, unit_type* unit2) {
    DBG_INSTRUCTION_BEGIN("mod");
    int q;
    int x;
    int y;

    // NUM % NUM
    #ifdef OPTIMIZE_MOD_BOTH
    if (unit1->val != CLN_NOTHING && unit2->val != CLN_NOTHING) {
        unit1->val = (unit2->val == CLN_ZERO) ? CLN_ZERO : cln::mod(unit1->val, unit2->val);
        unit_free(unit2);
        goto u1;
    }
    #endif

    // NUM % a
    #ifdef OPTIMIZE_MOD_LEFT
    if (unit1->val != CLN_NOTHING) {
        reg_check(unit2);
        if (reg_mod_left_cln(unit2->reg, unit1->val)) {
            unit_free(unit1);
            goto u2;
        }
    }
    #endif

    // a % NUM
    #ifdef OPTIMIZE_MOD_RIGHT
    if (unit2->val != CLN_NOTHING) {
        reg_check(unit1);

        // a % 0, 1, 2
        #ifdef OPTIMIZE_MOD_RIGHT_SIMPLE
        if (reg_mod_right_cln(unit1->reg, unit2->val)) {
            unit_free(unit2);
            goto u1;
        }
        #endif

        // a % 2^n
        #ifdef OPTIMIZE_MOD_RIGHT_TWO_POWER
        if (reg_mod_right_two_power_cln(unit1->reg, unit2->val, &x, &y)) {
            unit_free(unit2);
            reg_free(unit1->reg);
            reg_free(x);
            reg_connect(unit1, y);
            goto u1;
        }
        #endif
    }
    #endif

    // INSTRUKCJE
    reg_check(unit1);
    reg_check(unit2);
    q = reg_get_free();
    x = reg_get_free();
    y = reg_get_free();
    reg_div(unit1->reg, unit2->reg, q, x, y, SUPER_REGISTER);

    // ZWALNIANIE
    reg_free(unit2->reg);
    reg_free(x);
    reg_free(y);
    reg_free(q);
    unit_free(unit2);

u1: DBG_INSTRUCTION_END("mod");
    return unit1;

u2: DBG_INSTRUCTION_END("mod");
    return unit2;
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
    
    #ifdef OPTIMIZE_LT_GE
        DBG_OPTIMIZER_BEGIN("lt_ge");
        unit_type* res = dif(unit2, unit1);
        res->type = type;
        return res;
    #endif

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

    #ifdef OPTIMIZE_GT_LE
        unit_type* res = dif(unit1, unit2);
        res->type = type;
        return res;
    #endif

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

/* Dodaje iterator. Przydziela pamiec dla iteratora
 * oraz warunku iteracji */
symbol* add_iterator(char* id) {
    DBG_INSTRUCTION_BEGIN("add_iterator");
    symbol* sym;
    sym = sym_put(id);
    sym->type = VARIABLE;
    sym->is_init = false;
    sym->is_const = true;
    sym->offset = array_allocate(2);

    DBG_INSTRUCTION_END("add_iterator");
    DBG_SYMBOL_PRINT();
    return sym;
}

unit_type* for_init(cond_type* cond, unit_type* begin, unit_type* end, bool type) {
    DBG_INSTRUCTION_BEGIN("for_init");
    reg_check(begin);
    reg_check(end);

    // VALUE
    cond->iter->is_init = true;
    reg_const(SUPER_REGISTER, cond->iter->offset);
    store(begin->reg, SUPER_REGISTER);

    if (type == FOR_TO) {
        // FOR TO CONDITION
        inc(SUPER_REGISTER);
        inc(end->reg);
        sub(end->reg, begin->reg);
        store(end->reg, SUPER_REGISTER);
        reg_free(begin->reg);
        unit_free(begin);
        DBG_INSTRUCTION_END("for_init");
        return end;
    }
    else {
        // FOR DOWNTO CONDITION
        inc(SUPER_REGISTER);
        inc(begin->reg);
        sub(begin->reg, end->reg);
        store(begin->reg, SUPER_REGISTER);
        reg_free(end->reg);
        unit_free(end);
        DBG_INSTRUCTION_END("for_init");
        return begin;
    }
}

void for_step(cond_type* cond, unit_type* condition, bool type) {
    DBG_INSTRUCTION_BEGIN("for_step");
    condition->reg = condition->reg_prev;
    int x = condition->reg;

    // VALUE
    reg_const(SUPER_REGISTER, cond->iter->offset);
    load(x, SUPER_REGISTER);
    type == FOR_TO ? inc(x) : dec(x);
    store(x, SUPER_REGISTER);

    // CONDITION
    inc(SUPER_REGISTER);
    load(x, SUPER_REGISTER);
    dec(x);
    store(x, SUPER_REGISTER);
    
    DBG_INSTRUCTION_END("for_step");
}

/* Zwalnianie pamieci po petli for. */
void for_free(cond_type* cond, unit_type* condition) {
    DBG_INSTRUCTION_BEGIN("for_free");
    // ZWALNIANIE
    cond_free(cond);
    reg_free(condition->reg);
    DBG_INSTRUCTION_END("for_free");
}