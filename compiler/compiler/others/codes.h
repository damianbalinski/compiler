#pragma once

typedef enum {
    GET, PUT, LOAD, STORE, 
    ADD, SUB, RESET, 
    INC, DEC, SHR, SHL,
    JUMP, JZERO, JODD, HALT
} code_type;

const char* code_names[] = {
    "GET", "PUT", "LOAD", "STORE",
    "ADD", "SUB", "RESET",
    "INC" "DEC", "SHR", "SHL",
    "JUMP", "JZERO", "JODD", "HALT"
};

const int code_costs[] = {
    100, 100, 20, 20,
    5, 5, 1,
    1, 1, 1, 1,
    1, 1, 1, 0
};