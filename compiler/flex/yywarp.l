%{
    #include <stdio.h>
    int yywrap();
    int yylex();
    int NL = 0;
%}
%%
\n          { printf("\n"); ++NL; }
%%
int yywrap() // funkcja wykonywana po przetworzeniu danych wejsciowych
{ 
    printf("NL: %d\n", NL);
    return 1;
}

int main() { return yylex(); }