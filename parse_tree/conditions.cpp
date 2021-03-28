#include "../others/unit.hpp"
#include "../debugger/debugger.hpp"
#include "../optimizer/optimizer.hpp"
#include "../others/const.hpp"
#include "../code_generator/registers_machine.hpp"
#include "../code_generator/code_generator.hpp"
#include "expressions.hpp"
#include "conditions.hpp"

/* Rowne/Rozne.
 * type=true    unit1 = (unit1 == unit2)
 * typ2=false   unit1 = (unit1 != unit2) */
unit_type* eq_ne(unit_type* unit1, unit_type* unit2, bool type) {
    DBG_INSTRUCTION_BEGIN("eq_ne");

    // NUM = NUM | NUM != NUM
    #ifdef OPTIMIZE_EQ_NE_BOTH
    if (unit1->val != CLN_NOTHING && unit2->val != CLN_NOTHING) {
        DBG_OPTIMIZER_BEGIN("eq_ne both");
        unit1->val = (unit1->val == unit2->val) ? CLN_ZERO : CLN_ONE;
        unit1->type = type;
        unit_free(unit2);
        goto u1;
    }
    #endif

    // NUM = a | NUM != a
    #ifdef OPTIMIZE_EQ_NE_LEFT
    if (unit1->val != CLN_NOTHING) {
        reg_check(unit2);
        // 0 == a | 0 != a
        #ifdef OPTIMIZE_EQ_NE_LEFT_ZERO
        if (reg_eq_ne_zero_cln(unit2->reg, unit1->val)) {
            unit2->type = type;
            unit_free(unit1);
            goto u2;
        }
        #endif
    }
    #endif

    // a == NUM | a != NUM
    #ifdef OPTIMIZE_EQ_NE_RIGHT
    if (unit2->val != CLN_NOTHING) {
        reg_check(unit1);
        // a == 0 | a != 0
        #ifdef OPTIMIZE_EQ_NE_RIGHT_ZERO
        if (reg_eq_ne_zero_cln(unit1->reg, unit2->val)) {
            unit1->type = type;
            unit_free(unit2);
            goto u1;
        }
        #endif
    }
    #endif

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

u1: DBG_INSTRUCTION_END("eq_ne");
    return unit1;

u2: DBG_INSTRUCTION_END("eq_ne");
    return unit2;
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

unit_type* for_init(symbol* iter, unit_type* begin, unit_type* end, bool type) {
    DBG_INSTRUCTION_BEGIN("for_init");
    reg_check(begin);
    reg_check(end);
    
    // VALUE
    iter->is_init = true;
    reg_const(SUPER_REGISTER, iter->offset);
    store(begin->reg, SUPER_REGISTER);

    if (type == FOR_TO) {
        // FOR TO CONDITION
        inc(SUPER_REGISTER);
        inc(end->reg);
        sub(end->reg, begin->reg);
        store(end->reg, SUPER_REGISTER);
        reg_free(begin->reg);
        unit_free(begin);
        end->type = GREATER;
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
        begin->type = LESS;
        DBG_INSTRUCTION_END("for_init");
        return begin;
    }
}