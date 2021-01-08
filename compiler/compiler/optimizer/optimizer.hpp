#define OPTIMIZER_ON

#ifdef OPTIMIZER_ON
    #define OPTIMIZE_CONST
    #define OPTIMIZE_SUM
    #define OPTIMIZE_DIF
    #define OPTIMIZE_MUL
#endif

// ASSIGN
#ifdef OPTIMIZE_CONST
    #define OPTIMIZE_CONST_VAL
#endif

// SUM
#ifdef OPTIMIZE_SUM
    #define OPTIMIZE_SUM_BOTH
    #define OPTIMIZE_SUM_LEFT
    #define OPTIMIZE_SUM_RIGHT
#endif

// DIF
#ifdef OPTIMIZE_DIF
    #define OPTIMIZE_DIF_BOTH
    #define OPTIMIZE_DIF_LEFT
    #define OPTIMIZE_DIF_RIGHT
#endif

// MUL
#ifdef OPTIMIZE_MUL
    #define OPTIMIZE_MUL_BOTH
    #define OPTIMIZE_MUL_LEFT
    #define OPTIMIZE_MUL_LEFT_ZERO
    #define OPTIMIZE_MUL_LEFT_TWO_POWER
    #define OPTIMIZE_MUL_LEFT_OTHERS
    #define OPTIMIZE_MUL_RIGHT
    #define OPTIMIZE_MUL_RIGHT_ZERO
    #define OPTIMIZE_MUL_RIGHT_TWO_POWER
    #define OPTIMIZE_MUL_RIGHT_OTHERS
#endif