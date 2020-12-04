#pragma once
#include "../registers/registers.h"
#include "../code_generator/codes.h"
#include "colors.h"

#define WARNINGS

#ifdef WARNINGS
    #define CHECK_REGISTER(X)       if (X < 0 || X >= MAX_REGISTERS) \
                                        fprintf(stderr, RED "Ostrzezenie: Rejestr %d poza zakresem\n" DEF, X)
    #define CHECK_INSTRUCTION(X)    if (X >= MAX_CODES_TABLE) \
                                        fprintf(stderr, RED "Ostrzezenie: Brak miejsca w tablicy kodow\n" DEF)
    #define CHECK_CODE(X)           if (X < 0 || X >= MAX_CODES) \
                                        fprintf(stderr, RED "Ostrzezenie: Kod %d poza zakresem\n" DEF, X)
    #define CHECK_REGISTER_FREE()   fprintf(stderr, RED "Ostrzezenie: Brak wolnych rejestrow\n" DEF)
#else
    #define CHECK_REGISTER(X)
    #define CHECK_INSTRUCTION(X)
    #define CHECK_CODE(X)
    #define CHECK_REGISTER_FREE()
#endif