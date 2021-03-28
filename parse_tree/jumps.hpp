#pragma once
#include "../others/types.hpp"
#include "../others/unit.hpp"
#include "../symbol_table/symbol_table.hpp"

#define INIT true
#define FINISH false

typedef struct {
    input_type label_cmd;
    input_type label_cond;
    input_type label_else;
    input_type label_end;

    input_type jump_true_false;
    input_type jump_cmd;
    input_type jump_cond;
    input_type jump_else;
    input_type jump_end;

} labels_type;

void jump_true_false(labels_type* labels, unit_type* condition, bool type);
void jump_end(labels_type* labels, unit_type* condition, bool type);
void jump_cond(labels_type* labels, unit_type* condition, bool type);
void jump_else(labels_type* labels, unit_type* condition, bool type);
