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
                                        cerr << RED "Ostrzezenie: Rejestr " << X << " poza zakresem" DEF << endl
    #define CHECK_REG_CHECK(X)      if (registers[X].unit != NULL) \
                                        cerr << RED "Ostrzezenie: Proba przywrocenia zajetego rejestru " << X << DEF << endl 
    #define CHECK_REG_NOT_EMPTY(X)  if (X != NOTHING) \
                                        cerr << RED "Ostrzezenie: Nie zwolniono rejestru " << X << DEF << endl
    #define CHECK_INSTRUCTION(X)    if (X >= MAX_CODES_TABLE) \
                                        cerr << RED "Ostrzezenie: Brak miejsca w tablicy kodow" DEF << endl
    #define CHECK_DATA(X)           if (X >= MAX_DATA) \
                                        cerr << RED "Ostrzezenie: Brak miejsca w pamieci" DEF << endl
    #define CHECK_CODE(X)           if (X < 0 || X >= MAX_CODES) \
                                        cerr << RED "Ostrzezenie: Kod " << X << " poza zakresem\n" DEF << endl
    #define CHECK_UNIT(X)           if (X == NULL) \
                                        cerr << RED "Ostrzezenie: Problem z alokacja unit" DEF << endl
    #define CHECK_UNIT_COPY(X, Y)   if (X == CLN_NOTHING && Y == NOTHING) \
                                        cerr << RED "Ostrzezenie: Problem z kopia unit" DEF << endl
    #define CHECK_COND(X)           if (X == NULL) \
                                        cerr << RED "Ostrzezenie: Problem z alokacja cond" DEF << endl
    #define CHECK_ITERATOR(X, Y)    if (strcmp(X, Y) != 0) \
                                        cerr << RED "Ostrzezenie: Iterator nie znajduje sie na poczatku listy" DEF << endl
    #define CHECK_JUMP(X)           if (X != JUMP && X != JZERO && X != JODD) \
                                        cerr << RED "Ostrzezenie: Proba modyfikacji kodu, ktory nie jest skokiem" DEF << endl
    #define CHECK_VAL(X)            if (X < 0) \
                                        cerr << RED "Ostrzezenie: Proba zaladowania wartosci ujemnej " << X << DEF << endl
    #define CHECK_VAL_CLN(X)        if (X < 0) \
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
