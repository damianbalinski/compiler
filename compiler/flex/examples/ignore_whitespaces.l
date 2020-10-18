%{
    #include <stdio.h>
    int yywrap();
    int yylex();
%}
%%
[ \t]+        putchar( ' ' );
[ \t]+$       /* ignore this token */
%%
int yywrap() { return 1; }
int main() { return yylex(); }
