%{
    #include <stdio.h>
    int yywrap();
    int yylex();
%}
%%
aaa     { printf( "(AAA)" ); yyless(1); }
aa      { printf( "(AA)" ); yyless(1); }
a       { printf( "(A)" ); }
%%
int yywrap() { return 1; }
int main() { return yylex(); }

    /* odklada z powrotem do strumienia znaki [n, n+1, ...] ze zmiennej yytext
    /* yyless(n) */