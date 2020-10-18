%{
    #include <stdio.h>
    int yywrap();
    int yylex();
    int LINES = 0;
    int WORDS = 0;
%}
%%
^[ \t]*\n           printf("EMPTY %s", yytext);         /* puste linie, poza ostatnia */
^[ \t]+             printf("%s", yytext);             /* biale na poczatku */
[ \t]+$             printf("%s", yytext);             /* biale na koncu */
[ \t]+              printf("%s", yytext);             /* biale w srodku */
\n                  { printf("\n"); ++LINES; }          /* linie */
[[:graph:]]+        { printf("%s", yytext); ++WORDS; }  /* slowa */
%%

int yywrap()
{
    ++LINES;            /* ostatnia linia nie ma znaku \n */
    printf("\nLINES: %d", LINES);
    printf("\nWORDS: %d\n", WORDS);
    return 1;
}

int main()
{
    yylex();
    return 0;
}
