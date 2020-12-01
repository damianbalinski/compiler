#ifndef _ERRORS_H_
#define _ERRORS_H_

#include "../others/colors.h"

// identyfikator
#define ERR_ID_UNDECLARED(X) RED "Niezadeklarowany identyfikator %s" DEF, X
#define ERR_ID_DECLARED(X)   RED "Ponowna deklaracja identyfikatora %s" DEF, X

// skladnia
#define ERR_SYNTAX           RED "Blad linia %d: Blad skladniowy \'%s\'\n" DEF, yylineno, yytext

// obsluga bledow
int ERRORS;
#define ERR_INIT (ERRORS = 0)
#define ERR_ADD  (++ERRORS)

#endif      /* _ERRORS_H_ */