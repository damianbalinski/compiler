typedef struct symbol
{
    char* id;               /* id symbolu            */
    int offset;             /* offset w tablicy data */
    struct symbol* next;    /* nastepny symbol       */
} symbol;

symbol* putsym();
symbol* getsym();
