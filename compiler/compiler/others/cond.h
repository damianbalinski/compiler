#pragma once
#include "types.h"
#include "unit.h"

#define INIT true
#define FINISH false

typedef struct {

    unit_type* iter;

    input_type label_cmd;
    input_type label_cond;
    input_type label_else;
    input_type label_end;

    input_type jump_true_false;
    input_type jump_cmd;
    input_type jump_cond;
    input_type jump_else;
    input_type jump_end;

} cond_type;

cond_type* cond_alloc();
void cond_free(cond_type* cond);