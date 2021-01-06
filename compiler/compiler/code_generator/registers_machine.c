#include <math.h>
#include "registers_machine.h"
#include "code_generator.h"
#include "../debugger/debugger.h"
#include "../debugger/warnings.h"
#include "../symbol_table/data_manager.h"

/* Kolejka cykliczna rejestrow */
register_type* head;

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

/* Inicjalizuje rejestry oraz kolejke rejestrow. */
void reg_init() {
    registers[0].next = &registers[1];
    registers[1].next = &registers[2];
    registers[2].next = &registers[3];
    registers[3].next = &registers[4];
    registers[4].next = &registers[0];
    head = &registers[0];
}

/* Zwraca rejestr z poczatku listy, jesli to konieczne,
 * przerzuca jego zawartosc do pamieci. */
int reg_get_free() {
    DBG_REGISTERS_BEGIN("reg_get_free");
    DBG_REGISTER_PRINT();
    DBG_REGISTERS_HEAD_NUM(head->num);

    register_type* reg = head;
    if (reg->unit != NULL) {
        reg_to_mem(reg->unit, reg->num);
        reg_disconnect(reg->unit, reg->num);
    }
        
    head = reg->next;

    DBG_REGISTERS_HEAD_NUM(head->num);
    DBG_REGISTERS_END("reg_get_free");
    return reg->num;
}

/* Zwalnia rejestr. */
void reg_free(int x) {
    DBG_REGISTERS_BEGIN("reg_free");
    DBG_REGISTERS_HEAD_NUM(head->num);
    
    registers[x].unit = NULL;
    head = &registers[x];

    DBG_REGISTERS_HEAD_NUM(head->num);
    DBG_REGISTERS_END("reg_free");
}

/* Sprawdza, czy dane sa w rejestrze,
 * jesli nie, przerzuca je do rejestru */
void reg_check(unit_type* unit) {
    if (unit->reg == NOTHING) {
        CHECK_REG_CHECK(unit->reg_prev);
        int x = unit->reg_prev;
        mem_to_reg(unit, x);
        reg_connect(unit, x);
    }
}

/* Sprawdza, czy dane sa w rejestrze,
 * jesli nie, przerzuca je do rejestru */
void reg_check_log(unit_type* unit) {
    if (unit->reg == NOTHING) {
        printf("new reg\n");
        CHECK_REG_CHECK(unit->reg_prev);
        int x = unit->reg_prev;
        mem_to_reg(unit, x);
        reg_connect(unit, x);
    }
}

/* Przerzuca dane z rejestru do pamieci */
inline void reg_to_mem(unit_type* unit, int reg) {
    int offset = variable_allocate();   // alokacja pamieci
    reg_const(SUPER_REGISTER, offset);  // offset do rejestru
    store(reg, SUPER_REGISTER);         // rejestr do pamieci
    unit->offset = offset;
}

/* Przerzuca dane z pamieci do rejestru */
inline void mem_to_reg(unit_type* unit, int reg) {
    reg_const(reg, unit->offset);       // offset do rejestru
    load(reg, reg);                     // wartosc do rejestru
}

/* Laczy rejestr z unity */
inline void reg_connect(unit_type* unit, int reg) {
    registers[reg].unit = unit;
    unit->reg = reg;
    unit->reg_prev = NOTHING;
}

/* Odlacza rejestr od unity */
inline void reg_disconnect(unit_type* unit, int reg) {
    registers[reg].unit = NULL;
    unit->reg = NOTHING;
    unit->reg_prev = reg;
}

/* Drukuje liste rejestrow */
void reg_print() {
    register_type* reg = head;
    printf("r n reg            next           unit\n");
    printf("%c %d %p %p %p\n", reg->name, reg->num, reg, reg->next, reg->unit);
    reg = reg->next;

    while(reg != head) {
        printf("%c %d %p %p %p\n", reg->name, reg->num, reg, reg->next, reg->unit);
        reg = reg->next;
    }
}

/* Umieszcza stala w rejestrze. */
void reg_const(int x, input_type val) {
    DBG_REGISTERS_BEGIN("reg_const");
    CHECK_VAL(val);
    
    reset(x);

    if (val == 0)
        return;
    
    inc(x);
    if (val == 1)
        return;
    
    input_type n = (input_type)log2(val) - 1;    
    for(input_type mask = (1 << n); mask > 0; mask >>= 1) {
        shl(x);
        if (mask & val) inc(x);
    }

    DBG_RVAL(x);
    DBG_REGISTERS_END("reg_const");
}

/* Mnozenie.
 * z = x * y. */
void reg_mul(int x, int y, int z) {
    DBG_REGISTERS_BEGIN("reg_mul");
    reset(z);

    jodd(y, 2);
    jump(2);
    add(z,x);
    jzero(y,4);
    shl(x);
    shr(y);
    jump(-6);

    DBG_REGISTERS_END("reg_mul");
}

/* Dzielenie. */
void reg_div(int r, int n, int q, int x, int y, int f) {
    DBG_REGISTERS_BEGIN("reg_div");
    reset(q);

    jzero(n, 28);   /* JUMP */
    reset(x);
    add(x, n);
    reset(y);
    inc(y);

    reset(f);
    add(f, x);
    sub(f,r);
    jzero(f, 2);   
    jump(4);         /* JUMP */
    shl(x);
    shl(y);
    jump(-7);       /* JUMP BACK */

    reset(f);
    add(f, n);
    sub(f, x);
    jzero(f, 2);
    jump(12);       /* JUMP */

    reset(f);
    add(f, x);
    sub(f, r);
    jzero(f, 2);
    jump(3);        /* JUMP */
    add(q, y);
    sub(r, x);
    shr(x);
    shr(y);
    jump(-14);      /* JUMP BACK */
    reset(r);

    DBG_REGISTERS_END("reg_div");
}