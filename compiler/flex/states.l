%{
    #include <stdio.h>
    int yywrap();
    int yylex();
%}
%s qstring
%%
<qstring>\"         BEGIN INITIAL;
<qstring>.          ;
\"                  BEGIN qstring;

aa                  printf("A");
aa.+/[^b][^b]         printf("MANY");
bb                  printf("B");
%%
int yywrap() { return 1; }
int main() { return yylex(); }

/**
 * STANY - ZNAJOMOSC LEWEGO KONTEKSTU
 * %s qstring       - deklaracja stanu (SEKCJA 1)
 * BEGIN qstring    - zmiana stanu na qstring
 *
 * OPERATOR PODGLADU - ZNAJOMOSC PRAWEGO KONTEKSTU
 * {Regex}/[^0-9] - za dopasowanym wzorcem nie moze wystapic cyfra
 *
 */