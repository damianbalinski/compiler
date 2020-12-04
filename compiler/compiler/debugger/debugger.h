#pragma once
#include "colors.h"
#include "../code_generator/codes.h"

#define DEBUG_MODE

#ifdef DEBUG_MODE
    #define DEBUG_TOKENS            /* OK */
    #define DEBUG_PARSE_BEGIN_END   /* OK */
    #define DEBUG_SYMBOL_TABLE      /* OK */
    #define DEBUG_REGISTERS
    #define DEBUG_INSTRUCTIONS
#endif

// TOKENS
#ifdef DEBUG_TOKENS
    #define DBG_TOKEN(X) printf(GREEN "token [ %s %s ]\n" DEF, X, yytext)
#else
    #define DBG_TOKEN(X)
#endif

// PARSE START/STOP
#ifdef DEBUG_PARSE_BEGIN_END
    #define DBG_PARSE_BEGIN() printf(GREEN "perser [ BEGIN ]\n" DEF)
    #define DBG_PARSE_END()   printf(GREEN "parser [ END ]\n"   DEF)
#else
    #define DBG_PARSE_BEGIN()
    #define DBG_PARSE_END()
#endif

// SYMBOL TABLE
#ifdef DEBUG_SYMBOL_TABLE
    #define DBG_SYMBOL_PUT(X) printf(GREEN "symbol table [ new symbol %s]\n" DEF, X)
    #define DBG_SYMBOL_GET(X) printf(GREEN "symbol table [ get symbol %s]\n" DEF, X)
#else
    #define DBG_SYMBOL_PUT(X)
    #define DBG_SYMBOL_GET(X)
#endif

// REGISTERS
#ifdef DEBUG_REGISTERS
    #define DBG_REGISTER_GET(X)  printf(GREEN "registers [ get free reg %d]\n" DEF, X)
    #define DBG_REGISTER_FREE(X) printf(GREEN "registers [ free reg %d]\n"     DEF, X)
#else
    #define DBG_REGISTER_GET(X)
    #define DBG_REGISTER_FREE(X)
#endif

// INSTRUCTIONS
#ifdef DEBUG_INSTRUCTIONS
    #define DBG_INSTR0(C,I)     printf(BLUE "instructions [ (%d) %s ]\n"       DEF, C, code_names[I])
    #define DBG_INSTR1(C,I,X)   printf(BLUE "instructions [ (%d) %s %d ]\n"    DEF, C, code_names[I], X)
    #define DBG_INSTR2(C,I,X,Y) printf(BLUE "instructions [ (%d) %s %d %d ]\n" DEF, C, code_names[I], X, Y)         
#else
    #define DBG_INSTR0(C,I)
    #define DBG_INSTR1(C,I,X)
    #define DBG_INSTR(I,X,Y)
#endif
