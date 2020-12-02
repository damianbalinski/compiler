#include <stdbool.h>
#include <stdio.h>
#include "../registers/registers.h"
#include "../debugger/debugger.h"
#include "../errors/errors.h"

/* Inicjalizacja rejestrow. Poczatkowo wszystkie rejestry sa wolne
 * oraz maja niezdeterminowana wartosc. */
register_type registers[6] = {
    {'a', 0, -1, true},
    {'b', 0, -1, true},
    {'c', 0, -1, true},
    {'d', 0, -1, true},
    {'e', 0, -1, true},
    {'f', 0, -1, true}
};

/* Zwraca pierwszy z lewej wolny rejestr. Jesli wszystkie rejestry
 * sa zajete, przerzuca zawartosc rejestru do pamieci, ktora zostanie
 * wszytana zaraz po zwolnieniu rejestru */
int register_get() {
    for(int i = 0; i < MAX_REGISTERS; i++)
        if (registers[i].is_free) {
            PR_REGISTER_GET_FREE(i);
            registers[i].is_free = false;
            return i;
        }

    // TODO przerzucic rejestr
    ERR_ADD;
    fprintf(stderr, ERR_NO_FREE_REGISTER);
    return -1;
}

/* Zwalnia rejestr o podanym indeksie. Nie czysci zawartosci rejestru,
 * ktora moze zostac wykorzystana w przyszlosci */
void register_free(int reg) {
    PR_REGISTER_FREE(reg);
    registers[reg].is_free = true;
}
