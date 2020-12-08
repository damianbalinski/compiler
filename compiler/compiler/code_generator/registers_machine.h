#pragma once
#include "../others/types.h"

#define reg_free(X)    registers[X].unit = NULL
#define reg_unit(X,Y)  registers[X].unit = Y

int reg_get_free();
void reg_const(int x, input_type val);  // DONE

int mem_to_reg(input_type offset);
