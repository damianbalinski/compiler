%{
    #include <stdio.h>
    int yywrap();
    int yylex();
%}
%%
b*      ;
a*      { ECHO;}

%%
int yywrap() { return 1; }
int main() { return yylex(); }

/**
 * SPECJALNE MAKRA
 * ECHO;       - drukuje dopasowany leksem
 * BEGIN
 * REJECT
 */