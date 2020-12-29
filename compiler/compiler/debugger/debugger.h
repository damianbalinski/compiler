#pragma once
#include "colors.h"
#include "../code_generator/codes.h"

#define DEBUG_MODE

#ifdef DEBUG_MODE
    #define DEBUG_TOKENS
    // #define DEBUG_PARSER
    // #define DEBUG_SYMBOL_TABLE
    // #define DEBUG_REGISTERS
    // #define DEBUG_REGISTER_OPERATIONS
    // #define DEBUG_CODES
    // #define DEBUG_INSTRUCTIONS
    // #define DEBUG_DATA_MANAGER
    // #define DEBUG_UNIT
#endif

// TOKENS
#ifdef DEBUG_TOKENS
    #define DBG_TOKEN(X) printf(GREEN "token [ %s %s ]\n" DEF, X, yytext)
#else
    #define DBG_TOKEN(X)
#endif

// PARSE START/STOP
#ifdef DEBUG_PARSER
    #define DBG_PARSER_BEGIN() printf(GREEN "perser [ begin ]\n" DEF)
    #define DBG_PARSER_END()   printf(GREEN "parser [ end ]\n"   DEF)
#else
    #define DBG_PARSER_BEGIN()
    #define DBG_PARSER_END()
#endif

// SYMBOL TABLE
#ifdef DEBUG_SYMBOL_TABLE
    #define DBG_SYMBOL_PUT(X)  printf(GREEN "symbol table [ new symbol %s]\n" DEF, X)
    #define DBG_SYMBOL_GET(X)  printf(GREEN "symbol table [ get symbol %s]\n" DEF, X)
    #define DBG_SYMBOL_PRINT() sym_print()
#else
    #define DBG_SYMBOL_PUT(X)
    #define DBG_SYMBOL_GET(X)
    #define DBG_SYMBOL_PRINT()
#endif

// CODES
#ifdef DEBUG_CODES
    #define DBG_CODE0(C,I)     printf(BLUE "code [ (%lld) %s ]\n"       DEF, C, code_names[I])
    #define DBG_CODE1(C,I,X)   printf(BLUE "code [ (%lld) %s %d ]\n"    DEF, C, code_names[I], X)
    #define DBG_CODE2(C,I,X,Y) printf(BLUE "code [ (%lld) %s %d %d ]\n" DEF, C, code_names[I], X, Y)         
#else
    #define DBG_CODE0(C,I)
    #define DBG_CODE1(C,I,X)
    #define DBG_CODE2(C,I,X,Y)
#endif

// INSTRUCTIONS
#ifdef DEBUG_INSTRUCTIONS
    #define DBG_INSTRUCTION_BEGIN(X) printf(GREEN "instruction [ begin %s ]\n" DEF, X)
    #define DBG_INSTRUCTION_END(X)   printf(GREEN "instruction [ end %s ]\n" DEF, X)
#else
    #define DBG_INSTRUCTION_BEGIN(X)
    #define DBG_INSTRUCTION_END(X) 
#endif

// REGISTER OPERATIONS
#ifdef DEBUG_REGISTER_OPERATIONS
    #define DBG_RRESET(X) registers[X].val = 0
    #define DBG_RINC(X)   registers[X].val++
    #define DBG_RDEC(X)   registers[X].val--
    #define DBG_RSHL(X)   registers[X].val <<= 1
    #define DBG_RSHR(X)   registers[X].val >>= 1
    #define DBG_RADD(X,Y) registers[X].val += registers[Y].val
    #define DBG_RSUB(X,Y) registers[X].val = (registers[X].val > registers[Y].val) ? (registers[X].val - registers[Y].val) : 0
    #define DBG_RVAL(X)   printf(GREEN "registers [ val %d = %lld]\n" DEF, X, registers[X].val)  
#else
    #define DBG_RRESET(X)
    #define DBG_RINC(X)
    #define DBG_RDEC(X)
    #define DBG_RSHL(X)
    #define DBG_RSHR(X)
    #define DBG_RADD(X,Y)
    #define DBG_RSUB(X,Y)
    #define DBG_RVAL(X)
#endif

// DATA MANAGER
#ifdef DEBUG_DATA_MANAGER
    #define DBG_ALLOCATE_VARIABLE(X) printf(GREEN "allocate [ variable %lld ]\n" DEF, X)
    #define DBG_ALLOCATE_ARRAY(X,Y)  printf(GREEN "allocate [ array %lld %lld ]\n" DEF, X, Y)
#else
    #define DBG_ALLOCATE_VARIABLE(X)
    #define DBG_ALLOCATE_ARRAY(X,Y)
#endif

// UNIT
#ifdef DEBUG_UNIT
    #define DBG_UNIT_ALLOC(X) printf(GREEN "unit [ allocate %p ]\n" DEF, X)
    #define DBG_UNIT_FREE(X)  printf(GREEN "unit [ free %p ]\n" DEF, X)
#else
    #define DBG_UNIT_ALLOC(X)
    #define DBG_UNIT_FREE(X)
#endif

// REGISTERS
#ifdef DEBUG_REGISTERS
    #define DBG_REGISTER_PRINT()       reg_print()
    #define DBG_REGISTERS_BEGIN(X)     printf(GREEN "register machine [ begin %s ]\n" DEF, X)
    #define DBG_REGISTERS_END(X)       printf(GREEN "register machine [ end %s ]\n" DEF, X)
    #define DBG_REGISTERS_HEAD_NUM(X)  printf(GREEN "register machine [ head->num =  %d ]\n" DEF, X)
#else
    #define DBG_REGISTER_PRINT()
    #define DBG_REGISTERS_BEGIN(X)
    #define DBG_REGISTERS_END(X)
    #define DBG_REGISTERS_HEAD_NUM(X)
#endif
