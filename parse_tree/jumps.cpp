#include <cstdlib>
#include "jumps.hpp"
#include "../code_generator/code_generator.hpp"
#include "../debugger/debugger.hpp"
#include "../debugger/warnings.hpp"
#include "../code_generator/registers_machine.hpp"
#include "../debugger/debugger.hpp"

void jump_true_false(labels_type* labels, unit_type* condition, bool type) {
    DBG_INSTRUCTION_BEGIN("jump_true_false");
    if (type == INIT) {
        // JUMP TRUE_FALSE - INIT
        reg_check(condition);
        labels->jump_true_false = jzero(condition->reg, 0);
        reg_disconnect(condition, condition->reg);
    }
    else if (condition->type) {
        // JUMP TRUE - FINISH
        code_modif(labels->jump_true_false, labels->label_cmd - labels->jump_true_false);
    }
    else {
        // JUMP FALSE - FINISH
        code_modif(labels->jump_true_false, labels->label_end - labels->jump_true_false);
    }

    DBG_INSTRUCTION_END("jump_true_false");
}

void jump_end(labels_type* labels, unit_type* condition, bool type) {
    DBG_INSTRUCTION_BEGIN("jump_end");
    if (type == INIT && condition->type) {
        // JUMP END - INIT
         labels->jump_end = jump(0);
    }
    else if (type == INIT) {
        // NOTHING
    }
    else if (condition->type) {
        // JUMP END - FINISH
        code_modif(labels->jump_end, labels->label_end - labels->jump_end);
    }
    else {
        // NOTHING
    }
    DBG_INSTRUCTION_END("jump_end");
}

void jump_cond(labels_type* labels, unit_type* condition, bool type) {
    DBG_INSTRUCTION_BEGIN("jump_cond");
    if (type == INIT) {
        // JUMP_COND - INIT
        labels->jump_cond = jump(0);
    }
    else {
        // JUMP_COND - FINISH
        code_modif(labels->jump_cond, labels->label_cond - labels->jump_cond);
    }
    DBG_INSTRUCTION_END("jump_cond");
}

void jump_else(labels_type* labels, unit_type* condition, bool type) {
    DBG_INSTRUCTION_BEGIN("jump_else");
    if (type == INIT) {
        // JUMP ELSE - INIT
        labels->jump_else = jump(0);
    }
    else if (type == FINISH) {
        // JUMP ELSE - FINISH
        code_modif(labels->jump_else, labels->label_else - labels->jump_else);
    }
    DBG_INSTRUCTION_END("jump_else");
}