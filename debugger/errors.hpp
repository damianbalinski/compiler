#pragma once
#include <cstdlib>
#include <iostream>
#include <cln/cln.h>
#include "colors.hpp"

using std::cerr;
using std::endl;

#define ERR_SYNTAX()                cerr << RED "Blad: Blad skladniowy \'" << yytext << "\'"            DEF << endl
#define ERR_ID_DECLARED(X)          cerr << RED "Blad: Ponowna deklaracja identyfikatora " <<X<<        DEF << endl
#define ERR_ID_UNDECLARED(X)        cerr << RED "Blad: Niezadeklarowany identyfikator " <<X<<           DEF << endl
#define ERR_ID_NOT_INIT(X)          cerr << RED "Blad: Zmienna " <<X<< " nie zostala zainicjalizowana"  DEF << endl
#define ERR_ID_NOT_VARIABLE(X)      cerr << RED "Blad: Zmienna " <<X<< " nie jest typu zwyklego"        DEF << endl
#define ERR_ID_NOT_ARRAY(X)         cerr << RED "Blad: Zmienna " <<X<< " nie jest typu tablicowego"     DEF << endl
#define ERR_ID_CONST(X)             cerr << RED "Blad: Zmienna " <<X<< " jest niemodyfikowalna"         DEF << endl
#define ERR_ARRAY_INIT_RANGE(X,Y,Z) cerr << RED "Blad: Nieprawidlowy zakres tablicy " <<X<< "(" <<Y<< ":" <<Z<< ")" DEF << endl
#define ERR_ARRAY_INDEX_RANGE(X,Y)  cerr << RED "Blad: Indeksowanie tablicy poza zakresem " <<X<< "(" <<Y<< ")"     DEF << endl
#define ERR_BAD_FILENAME(X)         cerr << RED "Problem z otwarciem pliku " <<X<<                                  DEF << endl
#define ERR_BAD_CALL(X)             cerr << RED "Nieprawidlowe wywolanie, sproboj " <<X<< " <src> <dest>"           DEF << endl

#define ERR_ADD() exit(EXIT_FAILURE)
