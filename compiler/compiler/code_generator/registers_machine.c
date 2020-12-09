#include <math.h>
#include "registers_machine.h"
#include "registers.h"
#include "code_generator.h"
#include "../others/types.h"
#include "../debugger/debugger.h"
#include "../debugger/warnings.h"
#include "../symbol_table/data_manager.h"

/* Kolejka dwukierunkowa rejestrow */
register_type* head;
register_type* tail;

/* Inicjalizacja rejestrow. Poczatkowo wszystkie rejestry sa wolne
 * oraz nie wskazuja na zadna komorke pamieci. */
register_type registers[6] = {
    {'a', 0, 0, NULL},
    {'b', 1, 0, NULL},
    {'c', 2, 0, NULL},
    {'d', 3, 0, NULL},
    {'e', 4, 0, NULL},
    {'f', 5, 0, NULL}
};

/* Zwraca rejestr z poczatku listy, jesli to konieczne,
 * przerzuca jego zawartosc do pamieci. */
int reg_get_free() {
    DBG_REGISTER_GET(head->num);
    register_type* reg = head;

    // zwalnianie rejestru
    if (reg->unit != NULL) {
        int offset = variable_allocate();   // alokacja pamieci
        reg_const(SUPER_REGISTER, offset);  // offset do rejestru
        store(reg->num, SUPER_REGISTER);    // rejestr do pamieci
        reg->unit->offset = offset;
        reg->unit->reg = NOTHING;
        reg->unit = NULL;
    }

    // przerzucanie na koniec listy
    reg->prev = tail;
    tail->next = reg;
    tail = reg;
    head = reg->next;

    CHECK_REGISTER_FREE();
    return reg->num;
}

void reg_free(int x) {
    // zwalnianie pamieci
    register_type* reg = registers+x;
    reg->unit = NULL;

    // przerzucenie na poczatek listy
    if (reg == head) {

    }
    else if (reg == tail) {
        head->prev = reg;
        reg->next = head;
        tail = reg->prev;
        head = reg;
    }
    else {
        reg->prev->next = reg->next;
        reg->next->prev = reg->prev;
        reg->next = head;
        head->prev = reg;
        head = reg;
    }
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

/* Sprawdza, czy zawartosc jest w rejestrze,
 * jesli nie, przerzuca ja do rejestru */
void reg_check(unit_type* unit) {
    if (unit->reg == NOTHING) {
        int x = mem_to_reg(unit->offset);
        unit->reg = x;
        reg_unit(x, unit);
    }
}