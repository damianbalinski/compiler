%{
    #include <stdio.h>
    int yywrap();
    int yylex();
%}
%%
aaa         { printf( "AAA" ); unput( 'b' ); unput( 'c' ); }
b           { printf( "B" ); }
c           { printf( "C" ); }
%%
int yywrap() { return 1; }
int main() { return yylex(); }

    /* odklada znak c do strumienia, bedzie od nastepnym
    przetworzonym znakiem, mozliwe wielokrotne odkladanie znakow,
    nie mozna odlozyc znaku EOF */
    /* unput(c) */
