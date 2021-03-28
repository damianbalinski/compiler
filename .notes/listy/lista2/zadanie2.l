%{
    #include <stdio.h>
    int yywrap();
    int yylex();
%}
%x STR1
%x STR2
%x STR3

%%
<STR3>\\\"           { ECHO; }                                   /* ignoruje sekwencje \" */
<STR3>\\\\           { ECHO; }                                   /* ignoruje sekwencje \\ */
<STR3>\"\"\"         { printf( "%s", yytext ); BEGIN INITIAL; }  /* konczy docstring */

<STR1>\\\"           { ECHO; }                                   /* ignoruje sekwencje \" */
<STR1>\\\\           { ECHO; }                                   /* ignoruje sekwencje \\ */
<STR1>\"             { printf( "%s", yytext ); BEGIN INITIAL; }  /* konczy cudzyslow */

<STR2>\\\'           { ECHO; }                                   /* ignoruje sekwencje \' */
<STR2>\\\\           { ECHO; }                                   /* ignoruje sekwencje \\ */
<STR2>\'             { printf( "%s", yytext ); BEGIN INITIAL; }  /* konczy cudzyslow */

<INITIAL>\"\"\"     { printf( "%s", yytext ); BEGIN STR3; }      /* rozpoczyna docstring */
<INITIAL>\"         { printf( "%s", yytext ); BEGIN STR1; }      /* rozpoczyna cudzyslow */
<INITIAL>\'         { printf( "%s", yytext ); BEGIN STR2; }      /* rozpoczyna apostrof */
<INITIAL>#.*        { ; }                                       /* usuwamy komentarz jesli nie jestesmy w cudzyslowie */
%%

int yywrap() { return 1; }
int main() { return yylex(); }
