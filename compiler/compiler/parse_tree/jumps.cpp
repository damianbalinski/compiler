#include <cstdlib>
#include "jumps.hpp"
#include "../code_generator/code_generator.hpp"
#include "../debugger/debugger.hpp"
#include "../debugger/warnings.hpp"
#include "../code_generator/registers_machine.hpp"
#include "../debugger/debugger.hpp"

void jump_true_false(labels_type* cond, unit_type* condition, bool type) {
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

void jump_end(labels_type* cond, unit_type* condition, bool type) {
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

void jump_cond(labels_type* cond, unit_type* condition, bool type) {
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

void jump_else(labels_type* cond, unit_type* condition, bool type) {
    DBG_INSTRUCTION_BEGIN("jump_else");
    if (type == INIT) {
        // JUMP ELSE - INIT
        cond->jump_else = jump(0);
    }
    else if (type == FINISH) {
        // JUMP ELSE - FINISH
        code_modif(cond->jump_else, cond->label_else - cond->jump_else);
    }
    DBG_INSTRUCTION_END("jump_else");
}

/* Zwalnianie pamieci po skokach. */
void jumps_free(labels_type* cond, unit_type* condition) {
    DBG_INSTRUCTION_BEGIN("jumps_free");
    // ZWALNIANIE
    unit_free(condition);
    DBG_INSTRUCTION_END("jumps_free");
}