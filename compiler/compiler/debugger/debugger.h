#include "../others/colors.h"
#include "../code_generator/code_generator.h"
#include "../registers/registers.h"

#define DEBUG_MODE

#ifdef DEBUG_MODE
    //#define DEBUG_TOKENS
    #define DEBUG_PARSE_BEGIN_END
    #define DEBUG_SYMBOL_TABLE
    #define DEBUG_REGISTERS
    #define DEBUG_INSTRUCTIONS
    #define DEBUG_CODES
#endif

// TOKENS
#ifdef DEBUG_TOKENS
    #define PR_TOKEN(X) printf(GREEN "token [ %s %s ]\n" DEF, X, yytext)
#else
    #define PR_TOKEN(X)
#endif

// PARSE START/STOP
#ifdef DEBUG_PARSE_BEGIN_END
    #define PR_PARSE_BEGIN printf(GREEN "perser [ BEGIN ]\n" DEF)
    #define PR_PARSE_END   printf(GREEN "parser [ END ]\n" DEF)
#else
    #define PR_PARSE_BEGIN
    #define PR_PARSE_END
#endif

// SYMBOL TABLE
#ifdef DEBUG_SYMBOL_TABLE
    #define PR_SYMBOL_PUT(X) printf(GREEN "symbol table [ new symbol %s]\n" DEF, X)
    #define PR_SYMBOL_GET(X) printf(GREEN "symbol table [ get symbol %s]\n" DEF, X)
#else
    #define PR_SYMBOL_PUT(X)
    #define PR_SYMBOL_GET(X)
#endif

// REGISTERS
#ifdef DEBUG_REGISTERS
    #define PR_REGISTER_GET_FREE(X) printf(GREEN "registers [ get free reg %d]\n" DEF, X)
    #define PR_REGISTER_FREE(X)     printf(GREEN "registers [ free reg %d]\n"     DEF, X)
    #define CHECK_REGISTER(X)       if (X < 0 || X >= MAX_REGISTERS) \
                                    fprintf(stderr, RED "Rejestr %d poza zakresem\n" DEF, X)
#else
    #define PR_REGISTER_GET_FREE(X)
    #define PR_REGISTER_FREE(X)
    #define CHECK_REGISTER(X)
#endif

// INSTRUCTIONS
#ifdef DEBUG_INSTRUCTIONS
    #define PR_INSTR0(C,I)          printf(BLUE "instructions [ (%d) %s ]\n"       DEF, C, code_names[I])
    #define PR_INSTR1(C,I,X)        printf(BLUE "instructions [ (%d) %s %d ]\n"    DEF, C, code_names[I], X)
    #define PR_INSTR2(C,I,X,Y)      printf(BLUE "instructions [ (%d) %s %d %d ]\n" DEF, C, code_names[I], X, Y)         
    #define CHECK_INSTRUCTION(X)    if (X >= MAX_INSTRUCTIONS) \
                                    fprintf(stderr, RED "Brak miejsca w tablicy kodow\n" DEF)
#else
    #define PR_INSTR0(C,I)
    #define PR_INSTR1(C,I,X)
    #define PR_INSTR(I,X,Y)
    #define CHECK_INSTRUCTION(X)
#endif

// CODES
#ifdef DEBUG_CODES
    #define CHECK_CODE(X)           if (X < 0 || X >= MAX_CODES) \
                                    fprintf(stderr, RED "Kod %d poza zakresem\n" DEF, X)
#else
    #define CHECK_CODE(X)
#endif