#pragma once
#include <cstdio>
#include "colors.hpp"
#include "../code_generator/codes.hpp"
#include "../symbol_table/data_manager.hpp"

#define WARNINGS

#ifdef WARNINGS
    #define CHECK_REGISTER(X)       if (X < 0 || X >= MAX_REGISTERS) \
                                        fprintf(stderr, RED "Ostrzezenie: Rejestr %d poza zakresem\n" DEF, X)
    #define CHECK_REG_CHECK(X)      if (registers[X].unit != NULL) \
                                        fprintf(stderr, RED "Ostrzezenie: Proba przywrocenia zajetego rejestru %d\n" DEF, X)
    #define CHECK_INSTRUCTION(X)    if (X >= MAX_CODES_TABLE) \
                                        fprintf(stderr, RED "Ostrzezenie: Brak miejsca w tablicy kodow\n" DEF)
    #define CHECK_DATA(X)           if (X >= MAX_DATA) \
                                        fprintf(stderr, RED "Ostrzezenie: Brak miejsca w pamieci\n" DEF)
    #define CHECK_CODE(X)           if (X < 0 || X >= MAX_CODES) \
                                        fprintf(stderr, RED "Ostrzezenie: Kod %d poza zakresem\n" DEF, X)
    #define CHECK_UNIT(X)           if (X == NULL) \
                                        fprintf(stderr, RED "Ostrzezenie: Problem z alokacja unit" DEF)
    #define CHECK_COND(X)           if (X == NULL) \
                                        fprintf(stderr, RED "Ostrzezenie: Problem z alokacja cond" DEF)
    #define CHECK_ITERATOR(X, Y)    if (strcmp(X, Y) != 0) \
                                        fprintf(stderr, RED "Ostrzezenie: Iterator nie znajduje sie na poczatku listy" DEF)
    #define CHECK_JUMP(X)           if (X != JUMP && X != JZERO && X != JODD) \
                                        fprintf(stderr, RED "Ostrzezenie: Proba modyfikacji kodu, ktory nie jest skokiem" DEF)
    #define CHECK_VAL(X)            if ((long long)X < 0) \
                                        fprintf(stderr, RED "Ostrzezenie: Proba zaladowania wartosci ujemnej %lld" DEF, X)
#else
    #define CHECK_REGISTER(X)
    #define CHECK_INSTRUCTION(X)
    #define CHECK_DATA(X)
    #define CHECK_CODE(X)
    #define CHECK_REGISTER_FREE()
    #define CHECK_UNIT(X)
    #define CHECK_JUMP(X)
#endif
