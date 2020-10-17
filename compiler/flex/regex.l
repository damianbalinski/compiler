%{
#include <stdio.h>
int yywrap();
int yylex();
%}
id          [a-zA-Z_][a-zA-Z0-9_]*
%%
{id}        {printf("ID"); }
%%
int yywrap() {return 1; }
int main() { return yylex(); }