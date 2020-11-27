#include <string.h>
#include <stdlib.h>

struct symrec
{
    char *name; /* name of symbol */
    struct symrec *next; /* link field */
};

typedef struct symrec symrec;
symrec *symtable = (symrec *)0;
symrec *putsym ();
symrec *getsym ();

// dodaje nowy symbol na poczatek listy
symrec *putsym( char *symname )
{
    symrec *ptr;
    ptr = (symrec *) malloc (sizeof(symrec));
    ptr->name = (char *) malloc (strlen(symname)+1);
    strcpy (ptr->name, symname);
    ptr->next = (struct symrec *)symtable;
    symtable = ptr;
    return ptr;
}

// zwraca symbol lub NULL, jesli symbolu nie ma
symrec *getsym ( char *symname )
{
    symrec *ptr;
    for (ptr = symtable; ptr != (symrec *) 0; ptr = (symrec *)ptr->next)
        if (strcmp (ptr->name,symname) == 0)
            return ptr;
    return 0;
}

// int main(void)
// {
//     return 0;
// }