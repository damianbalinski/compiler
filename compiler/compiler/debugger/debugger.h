#include "../others/colors.h"

#define DEBUG_MODE

#ifdef DEBUG_MODE
    //#define DEBUG_TOKENS
    #define DEBUG_PARSE_BEGIN_END
    #define DEBUG_SYMBOL_TABLE
    #define DEBUG_REGISTERS
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
    #define PR_REGISTER_FREE(X)     printf(GREEN "registers [ free reg %d]\n" DEF, X)
#else
    #define PR_REGISTER_GET_FREE(X)
    #define PR_REGISTER_FREE(X)
#endif