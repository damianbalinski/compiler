%{
    #include <stdio.h>
    int yywrap();
    int yylex();
    int LINES = 0;
    int WORDS = 0;
%}
%%
^[ \t]*\n           ;                                   /* puste linie, bez ostatniej linii */
^[ \t]+             ;                                   /* biale na poczatku */
[ \t]+$             ;                                   /* biale na koncu */
[ \t]+              { printf( " " ); }                  /* biale w srodku */
\n                  { printf("\n"); ++LINES; }          /* linie */
[[:graph:]]+        { printf("%s", yytext); ++WORDS; }  /* slowa */
%%

int yywrap()
{
    ++LINES;                                            /* ostatnia linia*/
    printf("\nLINES: %d", LINES);
    printf("\nWORDS: %d\n", WORDS);
    return 1;
}

int main() { return yylex(); }
