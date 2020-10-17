%{
#include <stdio.h>
int yywrap();
int yylex();
%}

%%
register	;
auto		;
%%

int yywrap() { return 1; }
int main() { return yylex(); }