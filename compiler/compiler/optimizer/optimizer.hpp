#define OPTIMIZER_ON

#ifdef OPTIMIZER_ON
    #define OPTIMIZER_CONST
    #define OPTIMIZER_SUM
#endif

// ASSIGN
#ifdef OPTIMIZER_CONST
    #define OPTIMIZER_CONST_VAL
#endif

// SUM
#ifdef OPTIMIZER_SUM
    #define OPTIMIZER_SUM_BOTH
    #define OPTIMIZER_SUM_LEFT  /* PEND */
#endif