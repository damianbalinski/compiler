%{
    #include <stdio.h>
    int yywrap();
    int yylex();
    int chars = 0;
    int lines = 0;
%}
%%
\n          { lines++;}
.           { chars++;}
%%
int yywrap() { return 1; }
int main() 
{
    yylex();
    printf("chars: %d\n", chars);
    printf("lines: %d\n", lines);
    return 0;
}
