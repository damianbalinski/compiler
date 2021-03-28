%{
    #include <stdio.h>
    int yywrap();
    int yylex();
%}
    /*inclusive - reguly ze stanu domyslnego
    sa rowniez aktywne */
%s qstring
%s cond

    /*exclusive - tylko reguly z tego stanu
    sa aktywne */
%x
%%
<qstring>\"         BEGIN INITIAL;  /* konczy cudzyslow */
<qstring>.          ;               /* usuwa wszystko w cudzyslowie */
\"                  BEGIN qstring;  /* rozpoczyna cudzyslow cudzyslow */

aa                  printf("A");
aa.+/[^b][^b]         printf("MANY");
bb                  printf("B");

<cond>{
    a               printf("litera A"); /* wiele wzorcow do warunku poczatkowego*/
    b               printf("litera B"); /* kazda regula ma automatycznie prefix <rule> */
}
%%
int yywrap() { return 1; }
int main() { return yylex(); }

/**
 * STANY POCZATKOWE - ZNAJOMOSC LEWEGO KONTEKSTU
 * %s qstring       - deklaracja stanu (SEKCJA 1)
 * BEGIN qstring    - zmiana stanu na qstring
 * <cond>x          - dopasowanie x tylko, jesli aktualny stan to cond
 * <cond1,cond2>x   - dopasowanie x tylko, jesli aktualny stan to cond1 lub cond2
 * <*>x             - dopasowanie x w dowolnym stanie
 * INITIAL          - stan poczatkowy
 * YY_START, YYSTATE- makro, reprezentuje bierzacy stan
 *
 * OPERATOR PODGLADU - ZNAJOMOSC PRAWEGO KONTEKSTU
 * {Regex}/[^0-9] - za dopasowanym wzorcem nie moze wystapic cyfra
 *
 */