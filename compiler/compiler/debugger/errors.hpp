#pragma once
#include <cstdio>
#include <cstdlib>
#include "colors.hpp"

#define ERR_SYNTAX()           fprintf(stderr, RED "Blad linia %d: Blad skladniowy \'%s\'\n"                  DEF, yylineno, yytext)
#define ERR_ID_DECLARED(X)     fprintf(stderr, RED "Blad linia %d: Ponowna deklaracja identyfikatora %s\n"    DEF, yylineno, X)
#define ERR_ID_UNDECLARED(X)   fprintf(stderr, RED "Blad linia %d: Niezadeklarowany identyfikator %s\n"       DEF, yylineno, X)
#define ERR_ID_NOT_INIT(X)     fprintf(stderr, RED "Blad linia %d: Zmienna %s nie zostala zainicjalizowana\n" DEF, yylineno, X)
#define ERR_ID_NOT_VARIABLE(X) fprintf(stderr, RED "Blad linia %d: Zmienna %s nie jest typu zwyklego\n"       DEF, yylineno, X)
#define ERR_ID_NOT_ARRAY(X)    fprintf(stderr, RED "Blad linia %d: Zmienna %s nie jest typu tablicowego\n"    DEF, yylineno, X)
#define ERR_ID_CONST(X)        fprintf(stderr, RED "Blad linia %d: Zmienna %s jest niemodyfikowalna\n"        DEF, yylineno, X)
#define ERR_ARRAY_INIT_RANGE(X,Y,Z) fprintf(stderr, RED "Blad linia %d: Nieprawidlowy zakres tablicy %s(%lld:%lld)\n" DEF, yylineno, X, Y, Z)
#define ERR_ARRAY_INDEX_RANGE(X,Y)  fprintf(stderr, RED "Blad linia %d: Indeksowanie tablicy poza zakresem %s(%lld)\n" DEF, yylineno, X, Y)
#define ERR_BAD_FILENAME(X)    fprintf(stderr, RED "Problem z otwarciem pliku %s\n"                           DEF, X)
#define ERR_BAD_CALL(X)        fprintf(stderr, RED "Nieprawidlowe wywolanie, sproboj %s <src> <dest>\n"       DEF, X)

static int errors_counter = 0;
#define ERR_ADD() exit(EXIT_FAILURE)
#define ERR_GET() (errors_counter)
