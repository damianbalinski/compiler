#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../debugger/debugger.h"

typedef struct symbol
{
    char* id;               /* id symbolu            */
    int offset;             /* offset w tablicy data */
    struct symbol* next;    /* nastepny symbol       */
} symbol;

symbol* sym_put();
symbol* sym_get();
