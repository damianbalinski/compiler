%{
    #include <stdio.h>
    int yywrap();
    int yylex();
%}

%%
a*      printf("(%s:%d)", yytext, yyleng);
%%
int yywrap() { return 1; }
int main() {
    printf("YYLMAX: %d\n", YYLMAX);
    return yylex();
    }

/**
 * ZMIENNE
 * yytext - wskaznik na leksem (napis dopasowany do wzorca)
 * yyleng - dlugosc dopasowania
 * yyin   - strumien wejsciowy
 * yyout  - strumien wyjsciowy
 *
 * STALE
 * YYLMAX - maksymalna dlugosc tokena
 */