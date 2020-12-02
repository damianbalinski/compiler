#pragma once
#define MAX_INSTRUCTIONS 10
#define MAX_CODES 15

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

const char* code_names[] = {
    "GET", "PUT", "LOAD", "STORE",
    "ADD", "SUB", "RESET",
    "INC", "DEC", "SHR", "SHL",
    "JUMP", "JZERO", "JODD", "HALT"
};

const int code_costs[] = {
    100, 100, 20, 20,
    5, 5, 1,
    1, 1, 1, 1,
    1, 1, 1, 0
};

void instr_add0(code_type code);
void instr_add1(code_type code, int x);
void instr_add2(code_type code, int x, int y);
void instr_print(code_type code, int x, int y);
void instr_print_all();
