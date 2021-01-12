#pragma once
#include <cstdlib>
#include <iostream>
#include "colors.hpp"

using std::cerr;
using std::endl;

#define ERR_SYNTAX()           /* fprintf(stderr, RED "Blad linia %d: Blad skladniowy \'%s\'\n"                  DEF, yylineno, yytext) */\
                               cerr << RED "Blad linia " << yylineno << ": Blad skladniowy \'" << yytext << "\'" DEF << endl
#define ERR_ID_DECLARED(X)     /* fprintf(stderr, RED "Blad linia %d: Ponowna deklaracja identyfikatora %s\n"    DEF, yylineno, X) */\
                               cerr << RED "Blad linia " << yylineno << ": Ponowna deklaracja identyfikatora " << X << DEF << endl
#define ERR_ID_UNDECLARED(X)   /* fprintf(stderr, RED "Blad linia %d: Niezadeklarowany identyfikator %s\n"       DEF, yylineno, X) */ \
                               cerr << RED "Blad linia " << yylineno << ": Niezadeklarowany identyfikator " << X << DEF << endl
#define ERR_ID_NOT_INIT(X)     /* fprintf(stderr, RED "Blad linia %d: Zmienna %s nie zostala zainicjalizowana\n" DEF, yylineno, X) */\
                               cerr << RED "Blad linia " << yylineno << ": Zmienna " << X << " nie zostala zainicjalizowana" DEF << endl
#define ERR_ID_NOT_VARIABLE(X) /* fprintf(stderr, RED "Blad linia %d: Zmienna %s nie jest typu zwyklego\n"       DEF, yylineno, X) */\
                               cerr << RED "Blad linia " << yylineno << ": Zmienna " << X << " nie jest typu zwyklego" DEF << endl
#define ERR_ID_NOT_ARRAY(X)    /* fprintf(stderr, RED "Blad linia %d: Zmienna %s nie jest typu tablicowego\n"    DEF, yylineno, X) */\
                               cerr << RED "Blad linia " << yylineno << ": Zmienna " << X << " nie jest typu tablicowego" DEF << endl
#define ERR_ID_CONST(X)        /* fprintf(stderr, RED "Blad linia %d: Zmienna %s jest niemodyfikowalna\n"        DEF, yylineno, X) */\
                               cerr << RED "Blad linia " << yylineno << ": Zmienna " << X << " jest niemodyfikowalna" DEF << endl
#define ERR_ARRAY_INIT_RANGE(X,Y,Z) /* fprintf(stderr, RED "Blad linia %d: Nieprawidlowy zakres tablicy %s(%lld:%lld)\n" DEF, yylineno, X, Y, Z) */\
                               cerr << RED "Blad linia " << yylineno << ": Nieprawidlowy zakres tablicy " <<X<< "(" <<Y<< ":" <<Z<< ")" DEF << endl
#define ERR_ARRAY_INDEX_RANGE(X,Y)  /* fprintf(stderr, RED "Blad linia %d: Indeksowanie tablicy poza zakresem %s(%lld)\n" DEF, yylineno, X, Y) */\
                               cerr << RED "Blad linia " << yylineno << ": Indeksowanie tablicy poza zakresem " <<X<< "(" <<Y<< ")" DEF << endl
#define ERR_BAD_FILENAME(X)    /* fprintf(stderr, RED "Problem z otwarciem pliku %s\n"                           DEF, X) */\
                               cerr << RED "Problem z otwarciem pliku " <<X<< DEF << endl
#define ERR_BAD_CALL(X)        /* fprintf(stderr, RED "Nieprawidlowe wywolanie, sproboj %s <src> <dest>\n"       DEF, X) */\
                               cerr << RED "Nieprawidlowe wywolanie, sproboj " <<X<< " <src> <dest>" DEF << endl

static int errors_counter = 0;
#define ERR_ADD() exit(EXIT_FAILURE)
#define ERR_GET() (errors_counter)
