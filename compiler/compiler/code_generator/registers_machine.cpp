#include <cmath>
#include <iostream>
#include <cln/cln.h>
#include "registers_machine.hpp"
#include "code_generator.hpp"
#include "../debugger/debugger.hpp"
#include "../debugger/warnings.hpp"
#include "../symbol_table/data_manager.hpp"
#include "../others/const.hpp"

/* Kolejka cykliczna rejestrow */
register_type* head;

/* Inicjalizacja rejestrow. Poczatkowo wszystkie rejestry sa wolne
 * oraz nie wskazuja na zadna komorke pamieci. */
register_type registers[6] = {
    {'a', 0, 0, NULL},
    {'b', 1, 0, NULL},
    {'c', 2, 0, NULL},
    {'d', 3, 0, NULL},
    {'e', 4, 0, NULL},
    {'f', 5, 0, NULL}
};

/* Inicjalizuje rejestry oraz kolejke rejestrow. */
void reg_init() {
    registers[0].next = &registers[1];
    registers[1].next = &registers[2];
    registers[2].next = &registers[3];
    registers[3].next = &registers[4];
    registers[4].next = &registers[0];
    head = &registers[0];
}

/* Zwraca rejestr z poczatku listy, jesli to konieczne,
 * przerzuca jego zawartosc do pamieci. */
int reg_get_free() {
    DBG_REGISTERS_BEGIN("reg_get_free");
    DBG_REGISTER_PRINT();
    DBG_REGISTERS_HEAD_NUM(head->num);

    register_type* reg = head;
    if (reg->unit != NULL) {
        reg_to_mem(reg->unit, reg->num);
        reg_disconnect(reg->unit, reg->num);
    }
        
    head = reg->next;

    DBG_REGISTERS_HEAD_NUM(head->num);
    DBG_REGISTERS_END("reg_get_free");
    return reg->num;
}

/* Zwalnia rejestr. */
void reg_free(int x) {
    DBG_REGISTERS_BEGIN("reg_free");
    DBG_REGISTERS_HEAD_NUM(head->num);
    
    registers[x].unit = NULL;
    head = &registers[x];

    DBG_REGISTERS_HEAD_NUM(head->num);
    DBG_REGISTERS_END("reg_free");
}

/* Sprawdza, czy dane sa w rejestrze,
 * jesli nie, przerzuca je do rejestru */
void reg_check(unit_type* unit) {
    if (unit->val != CLN_NOTHING) {
        int x = reg_get_free();
        DBG_OPTIMIZER_VAL_TO_REG(unit->val, x);
        reg_const_cln(x, unit->val);
        reg_connect(unit, x);
        unit->val = CLN_NOTHING;
    }
    else if (unit->reg == NOTHING) {
        CHECK_REG_CHECK(unit->reg_prev);
        int x = unit->reg_prev;
        mem_to_reg(unit, x);
        reg_connect(unit, x);
    }
}

/* Przerzuca dane z rejestru do pamieci */
inline void reg_to_mem(unit_type* unit, int reg) {
    input_type offset = variable_allocate();   // alokacja pamieci
    reg_const(SUPER_REGISTER, offset);  // offset do rejestru
    store(reg, SUPER_REGISTER);         // rejestr do pamieci
    unit->offset = offset;
}

/* Przerzuca dane z pamieci do rejestru */
inline void mem_to_reg(unit_type* unit, int reg) {
    reg_const(reg, unit->offset);       // offset do rejestru
    load(reg, reg);                     // wartosc do rejestru
}

/* Laczy rejestr z unity */
inline void reg_connect(unit_type* unit, int reg) {
    registers[reg].unit = unit;
    unit->reg = reg;
    unit->reg_prev = NOTHING;
}

/* Odlacza rejestr od unity */
inline void reg_disconnect(unit_type* unit, int reg) {
    registers[reg].unit = NULL;
    unit->reg = NOTHING;
    unit->reg_prev = reg;
}

/* Drukuje liste rejestrow */
void reg_print() {
    register_type* reg = head;
    printf("r n reg            next           unit\n");
    printf("%c %d %p %p %p\n", reg->name, reg->num, reg, reg->next, reg->unit);
    reg = reg->next;

    while(reg != head) {
        printf("%c %d %p %p %p\n", reg->name, reg->num, reg, reg->next, reg->unit);
        reg = reg->next;
    }
}

/* Umieszcza stala w rejestrze. */
void reg_const(int x, input_type val) {
    DBG_REGISTERS_BEGIN("reg_const");
    CHECK_VAL(val);
    
    reset(x);
    if (val == 0)
        return;
    
    inc(x);
    if (val == 1)
        return;
    
    input_type n = (input_type)log2(val) - 1;    
    for(input_type mask = (1 << n); mask > 0; mask >>= 1) {
        shl(x);
        if (mask & val) inc(x);
    }
    DBG_REGISTERS_END("reg_const");
}

/* Umieszcza stala w rejestrze. */
void reg_const_cln(int x, cln::cl_I& val) {
    DBG_REGISTERS_BEGIN("reg_const_cln");
    CHECK_VAL_CLN(val);

    using namespace cln;
    static const cl_I ZERO(0);
    static const cl_I ONE(1);

    reset(x);
    if (equal(val, ZERO))
        return;
        
    inc(x);
    if (equal(val, ONE))
        return;
        
    uintC n = integer_length(val)-2;
    for(cl_I mask = (ONE<<n); mask > ZERO; mask >>= ONE) {
        shl(x);
        if ((mask & val) != ZERO) inc(x);
    }
    DBG_REGISTERS_END("reg_const_cln");
}

/* Mnozenie.
 * z = x * y, jesli x > y
 * z = y * x, jesli x <= y */
void reg_mul(int x, int y, int z) {
    DBG_REGISTERS_BEGIN("reg_mul");

    reset(z);
    add(z, x);
    sub(z, y);
    jzero(z, 9);

    // x < y
    reset(z);
    jodd(y, 2);
    jump(2);
    add(z,x);
    jzero(y, 12);   /* JUMP END */
    shl(x);
    shr(y);
    jump(-6);       /* JUMP BACK */

    // x >= y
    reset(z);
    jodd(x, 2);
    jump(2);
    add(z,y);
    jzero(x,4);     /* JUMP END */
    shl(y);
    shr(x);
    jump(-6);       /* JUMP BACK */

    DBG_REGISTERS_END("reg_mul");
}

/* Dzielenie. */
void reg_div(int r, int n, int q, int x, int y, int f) {
    DBG_REGISTERS_BEGIN("reg_div");
    reset(q);

    jzero(n, 28);   /* JUMP */
    reset(x);
    add(x, n);
    reset(y);
    inc(y);

    reset(f);
    add(f, x);
    sub(f,r);
    jzero(f, 2);   
    jump(4);         /* JUMP */
    shl(x);
    shl(y);
    jump(-7);       /* JUMP BACK */

    reset(f);
    add(f, n);
    sub(f, x);
    jzero(f, 2);
    jump(12);       /* JUMP */

    reset(f);
    add(f, x);
    sub(f, r);
    jzero(f, 2);
    jump(3);        /* JUMP */
    add(q, y);
    sub(r, x);
    shr(x);
    shr(y);
    jump(-14);      /* JUMP BACK */
    reset(r);

    DBG_REGISTERS_END("reg_div");
}

/* Dodawanie zoptymalizowane. */
bool reg_sum_cln(int x, cln::cl_I& val) {
    DBG_OPTIMIZER_BEGIN("reg_sum_cln");

    using namespace cln;
    static const cl_I ELEVEN(11);

    if (val > ELEVEN) {
        // VAL > 11
        return false;
    }
    else {
        // VAL <= 11
        for(cl_I i(0); i < val; i++)
            inc(x);
        return true;
    }
}

/* Odejmowanie zoptymalizowane prawostronne. */
bool reg_dif_right_cln(int x, cln::cl_I& val) {
    DBG_OPTIMIZER_BEGIN("reg_dif_right_cln");
    
    using namespace cln;
    static const cl_I ELEVEN(11);

    if (val > ELEVEN) {
        // VAL > 11
        return false;
    }
    else {
        // VAL <= 11
        for(cl_I i(0); i < val; i++)
            dec(x);
        return true;
    }
}

/* Odejmowanie zoptymalizowane lewostronne. */
bool reg_dif_left_cln(int x, cln::cl_I& val) {
    DBG_OPTIMIZER_BEGIN("reg_dif_left_cln");

    if (val == CLN_ZERO) {
        // 0 - VAL
        reset(x);
        return true;
    }

    else if (val == CLN_ONE) {
        // 1 - VAL
        jzero(x, 3);    /* JUMP x=0 */
        reset(x);
        jump(3);        /* JUMP END */
        reset(x);
        inc(x);
        return true;
    }

    else if (val == CLN_TWO) {
        // 2 - VAL
        jzero(x, 5);    /* JUMP x=0 */
        dec(x);
        jzero(x, 7);    /* JUMP x=1 */
        reset(x);       /* x>=2 */
        jump(7);        /* JUMP END */
        reset(x);       /* x=0 */
        inc(x);
        inc(x);
        jump(3);        /* JUMP END */
        reset(x);       /* x=1 */
        inc(x);
        return true;
    }

    else {
        // OTHER - VAL
        return false;
    }
}

/* Mnozenie zoptymalizowane przez 0 */
bool reg_mul_zero(int x, cln::cl_I& val) {
    if (val == CLN_ZERO) {
        // val == 0
        DBG_OPTIMIZER_BEGIN("reg_mul_zero");
        reset(x);
        return true;
    }
    else {
        // val != 0
        return false;
    }
}

/* Mnozenie zoptymalizowane przez 2^n */
bool reg_mul_two_power_cln(int x, cln::cl_I& val) {
    using namespace cln;

    uintC n = integer_length(val);
    n = (n == 0) ? 0 : n-1;
    cl_I val2 = (CLN_ONE << n);
    
    if (val == val2) {
        // val == 2^n
        DBG_OPTIMIZER_BEGIN("reg_mul_two_power_cln");
        for(uintC i = 0; i < n; i++) {
            shl(x);
        }
        return true;
    }
    else {
        // val != 2^n
        return false;
    }
}

/* Mnozenie zoptymalizowane przez n */
bool reg_mul_cln(int x, cln::cl_I& val, int* zptr) {
    DBG_OPTIMIZER_BEGIN("reg_mul_cln");

    int z = reg_get_free();
    *zptr = z;

    reset(z);
    while (val != CLN_ZERO) {
        if ((val & CLN_ONE) == CLN_ONE)
            add(z, x);
        shl(x);
        val >>= 1;
    }
    return true;
}

/* Dzielenie zoptymalizowane lewostronne. */
bool reg_div_left_cln(int x, cln::cl_I& val) {
    DBG_OPTIMIZER_BEGIN("reg_div_left_cln");

    if (val == CLN_ZERO) {
        // 0 / VAL
        reset(x);
        return true;
    }
    else if (val == CLN_ONE) {
        // 1 / VAL
        jzero(x, 7);       /* JUMP END */
        dec(x);
        jzero(x, 3);       /* JUMP x=1 */
        reset(x);
        jump(3);           /* JUMP END */
        reset(x);          /* x=1 */
        inc(x);            
        return true;
    }
    else if (val == CLN_TWO) {
        // 2 / VAL
        jzero(x, 13);      /* JUMP END */
        dec(x);
        jzero(x, 8);       /* JUMP x=1 */
        dec(x);            
        jzero(x, 3);       /* JUMP x=2 */
        reset(x);
        jump(7);           /* JUMP END */
        reset(x);          /* x=2 */
        inc(x);
        jump(4);           /* JUMPE END*/
        reset(x);          /* x=1 */
        inc(x);
        inc(x);
        return true;
    }
    else {
        // OTHER / VAL
        return false;
    }
}

/* Dzielenie zoptymalizowane prawostronne przez 0 */
bool reg_div_right_zero(int x, cln::cl_I& val) {
    if (val == CLN_ZERO) {
        // val == 0
        DBG_OPTIMIZER_BEGIN("reg_div_right_zero");
        reset(x);
        return true;
    }
    else {
        // val != 0
        return false;
    }
}

/* Dzielenie zoptymalizowane prawostronne przez 2^n */
bool reg_div_right_two_power_cln(int x, cln::cl_I& val) {
    using namespace cln;
    uintC n = integer_length(val);
    n = (n == 0) ? 0 : n-1;
    cl_I val2 = (CLN_ONE << n);
    
    if (val == val2) {
        // val == 2^n
        DBG_OPTIMIZER_BEGIN("reg_div_right_two_power_cln");
        for(uintC i = 0; i < n; i++) {
            shr(x);
        }
        return true;
    }
    else {
        // val != 2^n
        return false;
    }
}

/* Reszta z dzielenia zoptymalizowana lewostronnie. */
bool reg_mod_left_cln(int x, cln::cl_I& val) {
    DBG_OPTIMIZER_BEGIN("reg_mod_left_cln");

    if (val == CLN_ZERO) {
        // 0 % VAL
        reset(x);
        return true;
    }
    else if (val == CLN_ONE) {
        // 1 % VAL
        jzero(x, 5);      /* JUMP END */
        dec(x);
        jzero(x, 3);      /* JUMP END */
        reset(x);
        inc(x);    
        return true;
    }
    else if (val == CLN_TWO) {
        // 2 % VAL
        jzero(x, 8);     /* JUMP END */
        dec(x);
        jzero(x, 6);     /* JUMP END */
        dec(x);
        jzero(x, 4);     /* JUMP END */
        reset(x);
        inc(x);
        inc(x);
        return true;
    }
    else {
        // OTHER % VAL
        return false;
    }
}

/* Reszta z dzielenia zoptymalizowana prawostronnie. */
bool reg_mod_right_cln(int x, cln::cl_I& val) {
    DBG_OPTIMIZER_BEGIN("reg_mod_right_cln");

    if (val == CLN_ZERO) {
        // VAL % 0
        reset(x);
        return true;
    }
    else if (val == CLN_ONE) {
        // VAL % 1
        reset(x);
        return true;
    }
    else if (val == CLN_TWO) {
        // VAL % 2
        jodd(x, 3);     /* JUMP x=1 */
        reset(x);
        jump(3);        /* JUMP END */
        reset(x);
        inc(x);
        return true;
    }
    else {
        // VAL % OTHER
        return false;
    }
}

/* Reszta z dzielenia przez 2^n zoptymalizowana prawostronnie. */
bool reg_mod_right_two_power_cln(int x, cln::cl_I& val, int* yptr, int* zptr) {
    using namespace cln;
    uintC n = integer_length(val);
    n = (n == 0) ? 0 : n-1;
    cl_I val2 = (CLN_ONE << n);

    if (val == val2) {
        // val == 2^n
        DBG_OPTIMIZER_BEGIN("reg_mod_right_two_power_cln");
        int y = reg_get_free();
        int z = reg_get_free();
        *yptr = y;
        *zptr = z;

        reset(y);
        inc(y);
        reset(z);
  
        // 0 - n-2
        for (uintC i = 0; i < n-1; i++) {
            jodd(x, 2);
            jump(2);        /* JUMP NEXT */
            add(z, y);
            shl(y);
            shr(x);
        }

        // n-1
        jodd(x, 2);
        jump(2);            /* JUMP END */
        add(z, y);
        return true;
    }
    else {
        // val != 2^n
        return false;
    }
}

/* Rowne/Rozne zoptymalizowane przez 0. */
bool reg_eq_ne_zero_cln(int x, cln::cl_I& val) {
    if (val == CLN_ZERO) {
        // VAL == 0
        DBG_OPTIMIZER_BEGIN("reg_eq_ne_zero_cln");
        return true;
    }

    else {
        // VAL != 0
        return false;
    }
}