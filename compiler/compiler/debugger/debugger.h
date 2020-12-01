#define DEBUG_MODE

#ifdef DEBUG_MODE
    #define DEBUG_TOKENS
#endif

#ifdef DEBUG_TOKENS
    #define PR_TOKEN(X) printf("token [ %s %s ]\n", X, yytext)
#else
    #define PR_TOKEN(X,T)
#endif