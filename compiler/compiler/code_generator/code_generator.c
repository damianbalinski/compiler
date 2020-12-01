#include <stdio.h>
#include "../others/types.h"
#include "../registers/registers.h"
#include "../registers/registers.c"
#include "../debugger/debugger.h"
#include "../others/codes.h"

register_type registers[6];

/* umieszcza stala w podanym rejestrze */
int reg_put_const(val_type val) {
    int reg = register_get();
    
    return reg;
}

/* umieszcza wartosc zmiennej w rejestrze */
void reg_put_variable();

/* dodaje rejestry */
void reg_add(int reg1, int reg2);

/* odejmuje rejestry */
void reg_sub(int reg1, int reg2);

/* generuje kod na standardowym wyjsciu */
void generate_code(code_type code, int x, int y) {
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
        default:    fprintf(stderr, ERR_UNDEFINED_CODE(code));
    }
}

int main(void) {
    generate_code(GET, 1, NOTHING);
    generate_code(PUT, 1, NOTHING);
    generate_code(LOAD, 1, 2);
    generate_code(STORE, 1, 2);
}