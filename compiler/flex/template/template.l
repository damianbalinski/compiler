%{
    #include <stdio.h>
    int yywrap();
    int yylex();
%}
%%

%%
int yywrap() { return 1; }
int main() { return yylex(); }
