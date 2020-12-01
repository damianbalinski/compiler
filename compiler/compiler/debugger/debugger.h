#include "../others/colors.h"

#define DEBUG_MODE

#ifdef DEBUG_MODE
    #define DEBUG_TOKENS
    #define DEBUG_PARSE_BEGIN_END
#endif

// TOKENS
#ifdef DEBUG_TOKENS
    #define PR_TOKEN(X) printf(GREEN "token [ %s %s ]\n" DEF, X, yytext)
#else
    #define PR_TOKEN(X,T)
#endif

// PARSE START/STOP
#ifdef DEBUG_PARSE_BEGIN_END
    #define PR_PARSE_BEGIN printf(GREEN "perser [ BEGIN ]\n" DEF)
    #define PR_PARSE_END   printf(GREEN "parser [ END ]\n" DEF)
#else
    #define PR_PARSE_BEGIN
    #define PR_PARSE_END
#endif