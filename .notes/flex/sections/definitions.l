%{
/* blok kodu, kod jest kopiowany ZA deklaracje flexa */
#include <stdio.h>
int yywrap();
int yylex();
%}

%top{
/* blok kodu, kod jest kopiowany PRZED deklaracje flexa */
}

/* komentarz, jest kopiowany doslownie */

/* definicja, przyporzadkowuje identyfikatorowi podany wzorzec*/
ID          [a-zA-Z_][a-zA-Z0-9_]*
%%
{ID}        {printf("ID"); }
%%
int yywrap() {return 1; }
int main() { return yylex(); }

/**
 * DEFINICJE
 * name definition - deklaracja wzorca
 * {name}          - dopasowanie wzorca, jest zamieniane na (name)
 */