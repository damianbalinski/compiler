%{
    #include <stdio.h>
    int yywrap();
    int yylex();
%}

%%
a*      printf("(%s:%d)", yytext, yyleng);
%%
int yywrap() { return 1; }
int main() { return yylex(); }

/**
 * VARIABLES
 * yytext - wskaznik na leksem (napis dopasowany do wzorca)
 * yyleng - dlugosc dopasowania
 */