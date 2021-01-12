#pragma once
#include <iostream>
#include "colors.hpp"
#include "../code_generator/codes.hpp"
#include "../symbol_table/data_manager.hpp"
#include "../others/const.hpp"
#include "../code_generator/registers.hpp"

using std::cerr;
using std::endl;

#define WARNINGS

#ifdef WARNINGS
    #define CHECK_REGISTER(X)       if (X < 0 || X >= MAX_REGISTERS) \
                                        /* fprintf(stderr, RED "Ostrzezenie: Rejestr %d poza zakresem\n" DEF, X) */\
                                        cerr << RED "Ostrzezenie: Rejestr " << X << " poza zakresem" DEF << endl
    #define CHECK_REG_CHECK(X)      if (registers[X].unit != NULL) \
                                        /* fprintf(stderr, RED "Ostrzezenie: Proba przywrocenia zajetego rejestru %d\n" DEF, X) */\
                                        cerr << RED "Ostrzezenie: Proba przywrocenia zajetego rejestru " << X << DEF << endl 
    #define CHECK_REG_NOT_EMPTY(X)  if (X != NOTHING) \
                                        /* fprintf(stderr, RED "Ostrzezenie: Nie zwolniono rejestru %d\n" DEF, X) */\
                                        cerr << RED "Ostrzezenie: Nie zwolniono rejestru " << X << DEF << endl
    #define CHECK_INSTRUCTION(X)    if (X >= MAX_CODES_TABLE) \
                                        /* fprintf(stderr, RED "Ostrzezenie: Brak miejsca w tablicy kodow\n" DEF) */\
                                        cerr << RED "Ostrzezenie: Brak miejsca w tablicy kodow" DEF << endl
    #define CHECK_DATA(X)           if (X >= MAX_DATA) \
                                        /* fprintf(stderr, RED "Ostrzezenie: Brak miejsca w pamieci\n" DEF) */\
                                        cerr << RED "Ostrzezenie: Brak miejsca w pamieci" DEF << endl
    #define CHECK_CODE(X)           if (X < 0 || X >= MAX_CODES) \
                                        /* fprintf(stderr, RED "Ostrzezenie: Kod %d poza zakresem\n" DEF, X) */\
                                        cerr << RED "Ostrzezenie: Kod " << X << " poza zakresem\n" DEF << endl
    #define CHECK_UNIT(X)           if (X == NULL) \
                                        /* fprintf(stderr, RED "Ostrzezenie: Problem z alokacja unit" DEF) */\
                                        cerr << RED "Ostrzezenie: Problem z alokacja unit" DEF << endl
    #define CHECK_UNIT_COPY(X, Y)   if (X == CLN_NOTHING && Y == NOTHING) \
                                        /* fprintf(stderr, RED "Ostrzezenie: Problem z kopia unit" DEF) */\
                                        cerr << RED "Ostrzezenie: Problem z kopia unit" DEF << endl
    #define CHECK_COND(X)           if (X == NULL) \
                                        /* fprintf(stderr, RED "Ostrzezenie: Problem z alokacja cond" DEF) */\
                                        cerr << RED "Ostrzezenie: Problem z alokacja cond" DEF << endl
    #define CHECK_ITERATOR(X, Y)    if (strcmp(X, Y) != 0) \
                                        /* fprintf(stderr, RED "Ostrzezenie: Iterator nie znajduje sie na poczatku listy" DEF) */\
                                        cerr << RED "Ostrzezenie: Iterator nie znajduje sie na poczatku listy" DEF << endl
    #define CHECK_JUMP(X)           if (X != JUMP && X != JZERO && X != JODD) \
                                        /* fprintf(stderr, RED "Ostrzezenie: Proba modyfikacji kodu, ktory nie jest skokiem" DEF) */\
                                        cerr << RED "Ostrzezenie: Proba modyfikacji kodu, ktory nie jest skokiem" DEF << endl
    #define CHECK_VAL(X)            if (X < 0) \
                                        /* fprintf(stderr, RED "Ostrzezenie: Proba zaladowania wartosci ujemnej %lld" DEF, X) */\
                                        cerr << RED "Ostrzezenie: Proba zaladowania wartosci ujemnej " << X << DEF << endl
    #define CHECK_VAL_CLN(X)        if (X < 0) \
                                        /* fprintf(stderr, RED "Ostrzezenie: Proba zaladowania wartosci ujemnej " DEF) */\
                                        cerr << RED "Ostrzezenie: Proba zaladowania wartosci ujemnej " << X << DEF << endl

#else
    #define CHECK_REGISTER(X)
    #define CHECK_REG_CHECK(X)
    #define CHECK_REG_NOT_EMPTY(X)
    #define CHECK_INSTRUCTION(X)
    #define CHECK_DATA(X)
    #define CHECK_CODE(X)
    #define CHECK_UNIT(X)
    #define CHECK_UNIT_COPY(X, Y)
    #define CHECK_COND(X)
    #define CHECK_ITERATOR(X, Y)
    #define CHECK_JUMP(X)
    #define CHECK_VAL(X)
    #define CHECK_VAL_CLN(X)
#endif
