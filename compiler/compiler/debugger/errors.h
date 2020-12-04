#pragma once
#include "colors.h"

#define ERR_SYNTAX()           fprintf(stderr, RED "Blad linia %d: Blad skladniowy \'%s\'\n"                 DEF, yylineno, yytext)
#define ERR_ID_DECLARED(X)     fprintf(stderr, RED "Blad linia %d: Ponowna deklaracja identyfikatora %s\n"   DEF, yylineno, X)
#define ERR_ID_UNDECLARED(X)   fprintf(stderr, RED "Blad linia %d: Niezadeklarowany identyfikator %s\n"      DEF, yylineno, X)
#define ERR_ARRAY_RANGE(X,Y,Z) fprintf(stderr, RED "Blad linia %d: Nieprawidlowy zakres tablicy %s(%lld:%lld)\n" DEF, yylineno, X, Y, Z)

static int errors_counter = 0;
#define ERR_ADD() (++errors_counter)
#define ERR_GET() (errors_counter)
