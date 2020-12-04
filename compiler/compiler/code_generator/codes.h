#pragma once
#define MAX_CODES 15
#define MAX_CODES_TABLE 10

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