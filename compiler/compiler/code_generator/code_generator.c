#include "code_generator.h"

extern register_type registers[6];
instr_type code_table[MAX_CODES_TABLE];
int code_counter = 0;

void get(int x)          { code_put1(GET, x);      }
void put(int x)          { code_put1(PUT, x);      }
void load(int x, int y)  { code_put2(LOAD, x, y);  }
void store(int x, int y) { code_put2(STORE, x, y); }
void add(int x, int y)   { code_put2(ADD, x, y);   }
void sub(int x, int y)   { code_put2(SUB, x, y);   }
void reset(int x)        { code_put1(RESET, x);    }
void inc(int x)          { code_put1(INC, x);      }
void dec(int x)          { code_put1(DEC, x);      }
void shr(int x)          { code_put1(SHR, x);      }
void shl(int x)          { code_put1(SHL, x);      }
void jump(int x)         { code_put1(JUMP, x);     }
void jzero(int x, int y) { code_put2(JZERO, x, y); }
void jodd(int x, int y)  { code_put2(JODD, x, y);  }
void halt()              { code_put0(HALT);        }

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

/* drukuje pojedyncza instrukcje */
void code_print(code_type code, int x, int y) {
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

/* drukuje wszystkie instrukcje */
void code_print_all() {
    for (int i = 0; i < code_counter; i++)
        code_print(code_table[i].code, code_table[i].x, code_table[i].y);
}