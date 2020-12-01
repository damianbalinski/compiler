#ifndef _ERRORS_H_
#define _ERRORS_H_

// identyfikator
#define ERR_ID_UNDECLARED(X) "Niezadeklarowany identyfikator %s", X
#define ERR_ID_DECLARED(X)   "Ponowna deklaracja identyfikatora %s", X

// skladnia
#define ERR_SYNTAX           "Blad skladniowy"

int ERRORS;

void err_init() {
    ERRORS = 0;
}

void err_add() {
    ++ERRORS;
}

#endif      /* _ERRORS_H_ */