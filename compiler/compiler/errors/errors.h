#pragma once

#include "../others/colors.h"
#include "../code_generator/code_generator.h"

#define ERR_ID_UNDECLARED(X)  RED "Niezadeklarowany identyfikator %s"       DEF, X
#define ERR_ID_DECLARED(X)    RED "Ponowna deklaracja identyfikatora %s"    DEF, X
#define ERR_SYNTAX            RED "Blad linia %d: Blad skladniowy \'%s\'\n" DEF, yylineno, yytext
#define ERR_NO_FREE_REGISTER  RED "Brak wolnych rejestrow\n"                DEF    /* delete */

// obsluga bledow
int errors_counter = 0;
#define ERR_ADD (++errors_counter)
#define ERR_GET errors_counter
