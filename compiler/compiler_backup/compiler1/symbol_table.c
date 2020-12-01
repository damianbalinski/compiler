#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "errors.h"

/* Tablica symboli w formie listy jednokierunkowej */

typedef struct symrec
{
    char *name;             /* id symbolu            */
    int offset;             /* offset w tablicy data */
    struct symrec *next;    /* nastepny symbol       */
} symrec;

symrec *putsym ();
symrec *getsym ();

symrec *symtable = NULL;

// dodaje nowy symbol na poczatek listy
symrec *putsym( char *symname )
{
    symrec *ptr;
    ptr = (symrec *) malloc (sizeof(symrec));
    ptr->name = strdup(symname);
    ptr->offset = data_location();
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