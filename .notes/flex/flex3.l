%{
    #include <stdio.h>
    int yywrap();
    int yylex();
%}
%%
aaa     printf("AAA");
bbb     printf("BBB");
%%
int yywrap() { return 1; }
int main() { return yylex(); }
