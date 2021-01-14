#include "expressions.hpp"
#include "../optimizer/optimizer.hpp"
#include "../debugger/debugger.hpp"
#include "../debugger/warnings.hpp"
#include "../others/const.hpp"
#include "../code_generator/registers_machine.hpp"
#include "../code_generator/code_generator.hpp"

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

    // a + a
    #ifdef OPTIMIZE_SUM_EQUAL
    if (unit1->offset != CLN_NOTHING && unit2->offset != CLN_NOTHING) {
        if (unit1->offset == unit2->offset) {
            DBG_OPTIMIZER_BEGIN("reg_sum_equal");
            CHECK_REG_NOT_EMPTY(unit2->reg);
            reg_check(unit1);
            shl(unit1->reg);
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

    // a - a
    #ifdef OPTIMIZE_DIF_EQUAL
    if (unit1->offset != CLN_NOTHING && unit2->offset != CLN_NOTHING) {
        if (unit1->offset == unit2->offset) {
            DBG_OPTIMIZER_BEGIN("reg_dif_equal");
            CHECK_REG_NOT_EMPTY(unit2->reg);
            reg_check(unit1);
            reset(unit1->reg);
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

    // a / a
    #ifdef OPTIMIZE_DIV_EQUAL
    if (unit1->offset != CLN_NOTHING && unit2->offset != CLN_NOTHING) {
        if (unit1->offset == unit2->offset) {
            DBG_OPTIMIZER_BEGIN("reg_div_equal");
            CHECK_REG_NOT_EMPTY(unit2->reg);
            reg_check(unit1);
            int x = unit1->reg;
            jzero(x, 3);   /* JUMP END */
            reset(x);
            inc(x);
            unit_free(unit2);
            goto u1;
        }
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
 * OPT3     a   % a
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

    // a % a
    #ifdef OPTIMIZE_MOD_EQUAL
    if (unit1->offset != CLN_NOTHING && unit2->offset != CLN_NOTHING) {
        if (unit1->offset == unit2->offset) {
            DBG_OPTIMIZER_BEGIN("reg_mod_equal");
            CHECK_REG_NOT_EMPTY(unit2->reg);
            reg_check(unit1);
            reset(unit1->reg);
            unit_free(unit2);
            goto u1;
        }
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