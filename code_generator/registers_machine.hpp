#pragma once
#include <cln/integer.h>
#include "../others/types.hpp"
#include "../others/unit.hpp"
#include "registers.hpp"

#define reg_unit(X,Y)  registers[X].unit = Y

void reg_init();
void reg_print();

int reg_get_free();
void reg_free(int x);
void reg_check(unit_type* unit);
void reg_const(int x, input_type val);

void reg_to_mem(unit_type* unit, int reg);
void mem_to_reg(unit_type* unit, int reg);
void reg_connect(unit_type* unit, int reg);
void reg_disconnect(unit_type* unit, int reg);

void reg_mul(int x, int y, int z);
void reg_div(int r, int n, int q, int x, int y, int f);

// CLN
void reg_const_cln(int x, cln::cl_I& val);
bool reg_sum_cln(int x, cln::cl_I& val);
bool reg_dif_left_cln(int x, cln::cl_I& val);
bool reg_dif_right_cln(int x, cln::cl_I& val);
bool reg_mul_zero(int x, cln::cl_I& val);
bool reg_mul_two_power_cln(int x, cln::cl_I& val);
bool reg_mul_cln(int x, cln::cl_I& val, int* zptr);
bool reg_div_left_cln(int x, cln::cl_I& val);
bool reg_div_right_zero(int x, cln::cl_I& val);
bool reg_div_right_two_power_cln(int x, cln::cl_I& val);
bool reg_mod_left_cln(int x, cln::cl_I& val);
bool reg_mod_right_cln(int x, cln::cl_I& val);
bool reg_mod_right_two_power_cln(int x, cln::cl_I& val, int* yptr, int* zptr);
bool reg_eq_ne_zero_cln(int x, cln::cl_I& val);
