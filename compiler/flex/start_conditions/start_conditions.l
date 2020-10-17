%{
    #include <stdio.h>
    int yywrap();
    int yylex();
%}
%s qstring
%%
<qstring>\"         BEGIN INITIAL;  /* konczy cudzyslow cudzyslow */
<qstring>.          ;               /* usuwa wszystko w cudzyslowie */
\"                  BEGIN qstring;  /* rozpoczyna cudzyslow cudzyslow */

aa                  printf("A");
aa.+/[^b][^b]         printf("MANY");
bb                  printf("B");
%%
int yywrap() { return 1; }
int main() { return yylex(); }

/**
 * STANY POCZATKOWE - ZNAJOMOSC LEWEGO KONTEKSTU
 * %s qstring       - deklaracja stanu (SEKCJA 1)
 * BEGIN qstring    - zmiana stanu na qstring
 * <qstring>x       - dopasowanie x tylko, jesli aktualny stan to cond
 * <cond1,cond2>x   - dopasowanie x tylko, jesli aktualny stan to cond1 lub cond2
 * <*>x             - dopasowanie x w dowolnym stanie
 *
 * OPERATOR PODGLADU - ZNAJOMOSC PRAWEGO KONTEKSTU
 * {Regex}/[^0-9] - za dopasowanym wzorcem nie moze wystapic cyfra
 *
 */