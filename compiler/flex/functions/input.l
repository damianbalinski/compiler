%{
    #include <stdio.h>
    int yywrap();
    int yylex();
%}
%%
aaa         { printf( "AAA" ); putchar( input() ); putchar( input() ); }
b           { printf( "B" ); }
c           { printf( "C" ); }
%%
int yywrap() { return 1; }
int main() { return yylex(); }

    /* pobiera nastepny znak ze strumienia */
    /* input() */