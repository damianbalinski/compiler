#pragma once
#include <stdio.h>
#include "../registers/registers.h"
#include "../debugger/debugger.h"
#include "../debugger/warnings.h"
#include "codes.h"

void code_put0(code_type code);
void code_put1(code_type code, int x);
void code_put2(code_type code, int x, int y);
void code_print(code_type code, int x, int y);
void code_print_all();

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
void jump(int x);
void jzero(int x, int y);
void jodd(int x, int y);
void halt();
