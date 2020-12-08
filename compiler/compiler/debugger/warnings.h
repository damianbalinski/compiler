#pragma once
#include <stdio.h>
#include "colors.h"
#include "../code_generator/codes.h"
#include "../symbol_table/data_manager.h"

#define WARNINGS

#ifdef WARNINGS
    #define CHECK_REGISTER(X)       if (X < 0 || X >= MAX_REGISTERS) \
                                        fprintf(stderr, RED "Ostrzezenie: Rejestr %d poza zakresem\n" DEF, X)
    #define CHECK_INSTRUCTION(X)    if (X >= MAX_CODES_TABLE) \
                                        fprintf(stderr, RED "Ostrzezenie: Brak miejsca w tablicy kodow\n" DEF)
    #define CHECK_DATA(X)           if (X >= MAX_DATA) \
                                        fprintf(stderr, RED "Ostrzezenie: Brak miejsca w pamieci\n" DEF)
    #define CHECK_CODE(X)           if (X < 0 || X >= MAX_CODES) \
                                        fprintf(stderr, RED "Ostrzezenie: Kod %d poza zakresem\n" DEF, X)
    #define CHECK_REGISTER_FREE()   fprintf(stderr, RED "Ostrzezenie: Brak wolnych rejestrow\n" DEF)
    #define CHECK_UNIT(X)           if (X == NULL) \
                                        fprintf(stderr, RED "Ostrzezenie: Problem z alokacja unit" DEF)
#else
    #define CHECK_REGISTER(X)
    #define CHECK_INSTRUCTION(X)
    #define CHECK_DATA(X)
    #define CHECK_CODE(X)
    #define CHECK_REGISTER_FREE()
    #define CHECK_UNIT(X)
#endif
