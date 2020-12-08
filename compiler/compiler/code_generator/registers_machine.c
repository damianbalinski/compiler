#include <math.h>
#include "registers_machine.h"
#include "registers.h"
#include "code_generator.h"
#include "../others/types.h"
#include "../debugger/debugger.h"
#include "../debugger/warnings.h"

/* Inicjalizacja rejestrow. Poczatkowo wszystkie rejestry sa wolne
 * oraz nie wskazuja na zadna komorke pamieci. */
register_type registers[6] = {
    {'a', 0, NULL},
    {'b', 0, NULL},
    {'c', 0, NULL},
    {'d', 0, NULL},
    {'e', 0, NULL},
    {'f', 0, NULL}
};

/* Szuka wolnego rejestru.
 * Jesli znajdzie wolny rejstr, zwraca go.
 * Jesli wszystkie rejestry sa zajete, wybiera
 * losowy rejestr oraz przerzuca jego zawartosc 
 * do pamieci. */
int reg_get_free() {
    for(int i = 0; i < MAX_REGISTERS; i++)
        if (registers[i].unit == NULL) {
            DBG_REGISTER_GET(i);
            return i;
        }

    CHECK_REGISTER_FREE();
    return -1;
}

/* Umieszcza stala w rejestrze. */
void reg_const(int x, input_type val) {
    DBG_RMACHINE_BEGIN("reg_const");
    reset(x);
    if (val != 0) {
        input_type n = (input_type)log2(val) - 1;
        inc(x);
    
        for(input_type mask = (1 << n); mask > 0; mask >>= 1) {
            shl(x);
            if (mask & val) inc(x);
        }
    }
    DBG_RVAL(x);
    DBG_RMACHINE_END("reg_const");
}

/* Przerzuca zawartosc pamieci do rejstru,
 * zwraca ten rejestr. */
int mem_to_reg(input_type offset) {
    int x = reg_get_free();
    reg_const(x, offset);   // offset do rejestru
    load(x,x);              // pamiec do rejestru
    return x;
}

/* Przerzuca zawartosc rejestru do pamieci,
 * zwraca ten rejestr */
int reg_to_mem(int x) {
    int offset = variable_allocate();
    reg_const(SUPER_REGISTER, offset);  // offset do rejestru
    store(x, SUPER_REGISTER);           // rejestr do pamieci
    // TODO powiadomic unity
    return x;
}