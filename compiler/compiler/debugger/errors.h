#pragma once
#include "colors.h"

#define ERR_SYNTAX()          fprintf(stderr, RED "Blad linia %d: Blad skladniowy \'%s\'\n" DEF, yylineno, yytext)

static int errors_counter = 0;
#define ERR_ADD() (++errors_counter)
#define ERR_GET() (errors_counter)

// TODO
// #define ERR_ID_UNDECLARED(X)  RED "Niezadeklarowany identyfikator %s"       DEF, X
// #define ERR_ID_DECLARED(X)    RED "Ponowna deklaracja identyfikatora %s"    DEF, X