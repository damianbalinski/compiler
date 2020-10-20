%{
    #include <stdio.h>
    int yywrap();
    int yylex();
%}
%s QSTRING
%%
<QSTRING>\"         { printf( "%s", yytext ); BEGIN INITIAL; }  /* konczy cudzyslow */
\"                  { printf( "%s", yytext ); BEGIN QSTRING; }  /* rozpoczyna cudzyslow cudzyslow */
<INITIAL>#.*        { printf( "COM" ); }                        /* usuwamy jesli nie jestesmy w cudzyslowie */
%%

int yywrap() { return 1; }
int main() { return yylex(); }
