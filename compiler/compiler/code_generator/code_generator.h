#pragma once
#define MAX_INSTRUCTIONS 999
#define MAX_CODES 15
#include "../others/types.h"

typedef enum {
    GET, PUT, LOAD, STORE, 
    ADD, SUB, RESET, 
    INC, DEC, SHR, SHL,
    JUMP, JZERO, JODD, HALT
} code_type;

typedef struct {
    code_type code;
    int x;
    int y;
} instr_type;

static const char* code_names[] = {
    "GET", "PUT", "LOAD", "STORE",
    "ADD", "SUB", "RESET",
    "INC", "DEC", "SHR", "SHL",
    "JUMP", "JZERO", "JODD", "HALT"
};

static const int code_costs[] = {
    100, 100, 20, 20,
    5, 5, 1,
    1, 1, 1, 1,
    1, 1, 1, 0
};

int _const(val_type val);


void instr_add0(code_type code);
void instr_add1(code_type code, int x);
void instr_add2(code_type code, int x, int y);
void instr_print(code_type code, int x, int y);
void instr_print_all();

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
