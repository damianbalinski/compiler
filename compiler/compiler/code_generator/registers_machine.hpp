#pragma once
#include "../others/types.hpp"
#include "../others/unit.hpp"
#include "registers.hpp"

#define reg_unit(X,Y)  registers[X].unit = Y

void reg_init();
void reg_print();

int reg_get_free();
void reg_free(int x);
void reg_check(unit_type* unit);
void reg_check_log(unit_type* unit);
void reg_const(int x, input_type val);

void reg_to_mem(unit_type* unit, int reg);
void mem_to_reg(unit_type* unit, int reg);
void reg_connect(unit_type* unit, int reg);
void reg_disconnect(unit_type* unit, int reg);

void reg_mul(int x, int y, int z);
void reg_div(int r, int n, int q, int x, int y, int f);