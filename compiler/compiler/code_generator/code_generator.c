#include <stdio.h>
#include "../others/types.h"
#include "../registers/registers.h"
#include "../debugger/debugger.h"
#include "code_generator.h"
#include <math.h>

extern register_type registers[6];

instr_type instr_table[MAX_INSTRUCTIONS];
int instr_counter = 0;

/* pobiera wolny rejestr oraz umieszcza w nim podana stala */
int _const(val_type val) {
    int reg = register_get();
    reset(reg);             // reg = 0

    // wartosc zerowa
    if (val == 0)
        return reg;
    
    // wartosc rozna od zera
    val_type n = (val_type)log2(val);
    for(val_type mask = (1 << n); mask > 0; mask >>= 1) {
        shl(reg);           // reg <<= 1
        if (mask & val)
            inc(reg);      // reg++;
    }
    return reg;
}

/* umieszcza wartosc zmiennej w rejestrze */
void reg_put_variable();

/* dodaje rejestry */
void reg_add(int reg1, int reg2);

/* odejmuje rejestry */
void reg_sub(int reg1, int reg2);

void get(int x)          { instr_add1(GET, x);      }
void put(int x)          { instr_add1(PUT, x);      }
void load(int x, int y)  { instr_add2(LOAD, x, y);  }
void store(int x, int y) { instr_add2(STORE, x, y); }
void add(int x, int y)   { instr_add2(ADD, x, y);   }
void sub(int x, int y)   { instr_add2(SUB, x, y);   }
void reset(int x)        { instr_add1(RESET, x);    }
void inc(int x)          { instr_add1(INC, x);      }
void dec(int x)          { instr_add1(DEC, x);      }
void shr(int x)          { instr_add1(SHR, x);      }
void shl(int x)          { instr_add1(SHL, x);      }
void jump(int x)         { instr_add1(JUMP, x);     }
void jzero(int x, int y) { instr_add2(JZERO, x, y); }
void jodd(int x, int y)  { instr_add2(JODD, x, y);  }
void halt()              { instr_add0(HALT);        }

void instr_add0(code_type code) {
    CHECK_CODE(code);
    CHECK_INSTRUCTION(instr_counter);

    instr_table[instr_counter++].code = code;
    PR_INSTR0(instr_counter-1, code);
}

void instr_add1(code_type code, int x) {
    CHECK_CODE(code);
    CHECK_REGISTER(x);
    CHECK_INSTRUCTION(instr_counter);

    instr_table[instr_counter].code = code;
    instr_table[instr_counter++].x = x;
    PR_INSTR1(instr_counter-1, code, x);
}

void instr_add2(code_type code, int x, int y) {
    CHECK_CODE(code);
    CHECK_REGISTER(x);
    CHECK_REGISTER(y);
    CHECK_INSTRUCTION(instr_counter);
    
    instr_table[instr_counter].code = code;
    instr_table[instr_counter].x = x;
    instr_table[instr_counter++].y = y;
    PR_INSTR2(instr_counter-1, code, x, y);
}

/* drukuje wszystkie instrukcje */
void instr_print_all() {
    for (int i = 0; i < instr_counter; i++)
        instr_print(instr_table[i].code, instr_table[i].x, instr_table[i].y);
}

/* drukuje pojedyncza instrukcje */
void instr_print(code_type code, int x, int y) {
    switch(code) {
        case GET:   printf("%s %c\n",    code_names[code], registers[x].name);                     break;
        case PUT:   printf("%s %c\n",    code_names[code], registers[x].name);                     break;
        case LOAD:  printf("%s %c %c\n", code_names[code], registers[x].name, registers[y].name);  break;
        case STORE: printf("%s %c %c\n", code_names[code], registers[x].name, registers[y].name);  break;
        case ADD:   printf("%s %c %c\n", code_names[code], registers[x].name, registers[y].name);  break;
        case SUB:   printf("%s %c %c\n", code_names[code], registers[x].name, registers[y].name);  break;
        case RESET: printf("%s %c\n",    code_names[code], registers[x].name);                     break;
        case INC:   printf("%s %c\n",    code_names[code], registers[x].name);                     break;
        case DEC:   printf("%s %c\n",    code_names[code], registers[x].name);                     break;
        case SHR:   printf("%s %c\n",    code_names[code], registers[x].name);                     break;
        case SHL:   printf("%s %c\n",    code_names[code], registers[x].name);                     break;
        case JUMP:  printf("%s %d\n",    code_names[code], x);                                     break;
        case JZERO: printf("%s %c %d\n", code_names[code], registers[x].name, y);                  break;
        case JODD:  printf("%s %c %d\n", code_names[code], registers[x].name, y);                  break;
        case HALT:  printf("%s\n",       code_names[code]);                                        break;
    }
}
