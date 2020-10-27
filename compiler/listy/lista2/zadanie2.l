%{
    #include <stdio.h>
    int yywrap();
    int yylex();
%}
%s STR
%%
<STR>\\\"           { ECHO; }                                   /* ignorowanie sekwencji \" */
<STR>\"             { printf( "%s", yytext ); BEGIN INITIAL; }  /* konczy cudzyslow */
\"                  { printf( "%s", yytext ); BEGIN STR; }      /* rozpoczyna cudzyslow cudzyslow */
<INITIAL>#.*        { ; }                                       /* usuwamy jesli nie jestesmy w cudzyslowie */
%%

int yywrap() { return 1; }
int main() { return yylex(); }
