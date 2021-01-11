#define OPTIMIZER_ON

/* 
 * TODO LIST
 * tablica jednoelementowa przy indeksowaniu zachowuje sie jak zwykla zmienna
 * 
 *
 * 
 */

#ifdef OPTIMIZER_ON
    #define OPTIMIZE_CONST
    #define OPTIMIZE_SUM
    #define OPTIMIZE_DIF
    #define OPTIMIZE_MUL
    #define OPTIMIZE_DIV
    #define OPTIMIZE_MOD
    #define OPTIMIZE_CONDITIONS
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
    #define OPTIMIZE_SUM_EQUAL
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

// DIV
#ifdef OPTIMIZE_DIV
    #define OPTIMIZE_DIV_BOTH
    #define OPTIMIZE_DIV_LEFT
    #define OPTIMIZE_DIV_RIGHT
    #define OPTIMIZE_DIV_RIGHT_ZERO
    #define OPTIMIZE_DIV_RIGHT_TWO_POWER
#endif

// MOD
#ifdef OPTIMIZE_MOD
    #define OPTIMIZE_MOD_BOTH
    #define OPTIMIZE_MOD_LEFT
    #define OPTIMIZE_MOD_RIGHT
    #define OPTIMIZE_MOD_RIGHT_SIMPLE
    #define OPTIMIZE_MOD_RIGHT_TWO_POWER
#endif

// CONDITIONS
#ifdef OPTIMIZE_CONDITIONS
    #define OPTIMIZE_LT_GE
    #define OPTIMIZE_GT_LE
    #define OPTIMIZE_EQ_NE_BOTH
    #define OPTIMIZE_EQ_NE_LEFT
    #define OPTIMIZE_EQ_NE_LEFT_ZERO
    #define OPTIMIZE_EQ_NE_RIGHT
    #define OPTIMIZE_EQ_NE_RIGHT_ZERO
#endif