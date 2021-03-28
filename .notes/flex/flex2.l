%{
    #include <stdio.h>
    int yywrap();
    int yylex();
%}

%%
"long int"      printf("long");
"signed int"    printf("int");
%%
int yywrap() { return 1; }
int main() { return yylex(); }