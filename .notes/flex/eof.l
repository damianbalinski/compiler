%{
    #include <stdio.h>
    int yywrap();
    int yylex();
%}

%%
<<EOF>>         printf("EOF!");
%%
int yywrap() { return 1; }
int main() { return yylex(); }