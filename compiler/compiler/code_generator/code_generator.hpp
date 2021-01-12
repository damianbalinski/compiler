#pragma once
#include <cstdio>
#include "codes.hpp"
#include "../others/types.hpp"

data_type code_get_label();

void code_put0(code_type code);
void code_put1(code_type code, int x);
void code_put2(code_type code, int x, int y);
data_type code_jump1(code_type code, int x);
data_type code_jump2(code_type code, int x, int y);
void code_modif(input_type offset, int val);
void code_print(FILE* file, code_type code, int x, int y);
void code_print_all(FILE* file);

void get(int x);
void put(int x);
void load(int x, int y);
void store(int x, int y);
void add(int x, int y);
void sub(int x, int y);
void reset(int x);
void inc(int x);
void dec(int x);
void shr(int x);
void shl(int x);
data_type jump(int x);
data_type jzero(int x, int y);
data_type jodd(int x, int y);
void halt();
