#include "../registers/registers.h"

/* Inicjalizacja rejestrow. Poczatkowo wszystkie rejestry sa wolne
 * oraz nie wskazuja na zadna komorke pamieci. */
register_type registers[6] = {
    {'a', 0, NOTHING, true},
    {'b', 0, NOTHING, true},
    {'c', 0, NOTHING, true},
    {'d', 0, NOTHING, true},
    {'e', 0, NOTHING, true},
    {'f', 0, NOTHING, true}
};

/* Zwraca pierwszy z lewej wolny rejestr. Jesli wszystkie rejestry
 * sa zajete, przerzuca zawartosc rejestru do pamieci, ktora zostanie
 * wszytana zaraz po zwolnieniu rejestru */
int register_get() {
    for(int i = 0; i < MAX_REGISTERS; i++)
        if (registers[i].is_free) {
            DBG_REGISTER_GET(i);
            registers[i].is_free = false;
            return i;
        }

    CHECK_REGISTER_FREE();
    return -1;
}
