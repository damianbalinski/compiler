#include <cstdio>
#include "code_generator.hpp"
#include "registers.hpp"
#include "../debugger/debugger.hpp"
#include "../debugger/warnings.hpp"

extern register_type registers[6];
instr_type code_table[MAX_CODES_TABLE];
input_type code_counter = 0;

void get(int x)          { code_put1(GET, x);      }
void put(int x)          { code_put1(PUT, x);      }
void load(int x, int y)  { code_put2(LOAD, x, y);  }
void store(int x, int y) { code_put2(STORE, x, y); }
void add(int x, int y)   { code_put2(ADD, x, y);   DBG_RADD(x,y); }
void sub(int x, int y)   { code_put2(SUB, x, y);   DBG_RSUB(x,y); }
void reset(int x)        { code_put1(RESET, x);    DBG_RRESET(x); }
void inc(int x)          { code_put1(INC, x);      DBG_RINC(x);   }
void dec(int x)          { code_put1(DEC, x);      DBG_RDEC(x);   }
void shr(int x)          { code_put1(SHR, x);      DBG_RSHR(x);   }
void shl(int x)          { code_put1(SHL, x);      DBG_RSHL(x);   }
void halt()              { code_put0(HALT);                       }
input_type jump(int x)         { return code_jump1(JUMP, x);      }
input_type jzero(int x, int y) { return code_jump2(JZERO, x, y);  }
input_type jodd(int x, int y)  { return code_jump2(JODD, x, y);   }

void code_put0(code_type code) {
    CHECK_CODE(code);
    CHECK_INSTRUCTION(code_counter);
    DBG_CODE0(code_counter, code);
    code_table[code_counter++].code = code;
}

void code_put1(code_type code, int x) {
    CHECK_CODE(code);
    CHECK_INSTRUCTION(code_counter);
    CHECK_REGISTER(x);
    DBG_CODE1(code_counter, code, x);
    code_table[code_counter].code = code;
    code_table[code_counter++].x = x;
}

void code_put2(code_type code, int x, int y) {
    CHECK_CODE(code);
    CHECK_INSTRUCTION(code_counter);
    CHECK_REGISTER(x);
    CHECK_REGISTER(y);
    DBG_CODE2(code_counter, code, x, y);
    code_table[code_counter].code = code;
    code_table[code_counter].x = x;
    code_table[code_counter++].y = y;
}

input_type code_jump1(code_type code, int x) {
    CHECK_CODE(code);
    CHECK_INSTRUCTION(code_counter);
    DBG_CODE1(code_counter, code, x);
    code_table[code_counter].code = code;
    code_table[code_counter].x = x;
    return code_counter++;
}

input_type code_jump2(code_type code, int x, int y) {
    CHECK_CODE(code);
    CHECK_INSTRUCTION(code_counter);
    CHECK_REGISTER(x);
    DBG_CODE2(code_counter, code, x, y);
    code_table[code_counter].code = code;
    code_table[code_counter].x = x;
    code_table[code_counter].y = y;
    return code_counter++;
}

void code_modif(input_type offset, int val) {
    CHECK_JUMP(code_table[offset].code);
    if (code_table[offset].code == JUMP)
        code_table[offset].x = val;
    else
        code_table[offset].y = val;
}

/* Zwraca bierzaca pozycje w tablicy kodow. */
input_type code_get_label() {
    return code_counter;
}

/* Drukuje pojedyncza instrukcje. */
void code_print(FILE* file, code_type code, int x, int y) {
    switch(code) {
        case GET:   fprintf(file, "%s %c\n",    code_names[code], registers[x].name);                     break;
        case PUT:   fprintf(file, "%s %c\n",    code_names[code], registers[x].name);                     break;
        case LOAD:  fprintf(file, "%s %c %c\n", code_names[code], registers[x].name, registers[y].name);  break;
        case STORE: fprintf(file, "%s %c %c\n", code_names[code], registers[x].name, registers[y].name);  break;
        case ADD:   fprintf(file, "%s %c %c\n", code_names[code], registers[x].name, registers[y].name);  break;
        case SUB:   fprintf(file, "%s %c %c\n", code_names[code], registers[x].name, registers[y].name);  break;
        case RESET: fprintf(file, "%s %c\n",    code_names[code], registers[x].name);                     break;
        case INC:   fprintf(file, "%s %c\n",    code_names[code], registers[x].name);                     break;
        case DEC:   fprintf(file, "%s %c\n",    code_names[code], registers[x].name);                     break;
        case SHR:   fprintf(file, "%s %c\n",    code_names[code], registers[x].name);                     break;
        case SHL:   fprintf(file, "%s %c\n",    code_names[code], registers[x].name);                     break;
        case JUMP:  fprintf(file, "%s %d\n",    code_names[code], x);                                     break;
        case JZERO: fprintf(file, "%s %c %d\n", code_names[code], registers[x].name, y);                  break;
        case JODD:  fprintf(file, "%s %c %d\n", code_names[code], registers[x].name, y);                  break;
        case HALT:  fprintf(file, "%s\n",       code_names[code]);                                        break;
    }
}

/* Drukuje wszystkie instrukcje. */
void code_print_all(FILE* file) {
    for (int i = 0; i < code_counter; i++)
        code_print(file, code_table[i].code, code_table[i].x, code_table[i].y);
}
