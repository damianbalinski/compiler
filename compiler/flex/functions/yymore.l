%{
    #include <stdio.h>
    int yywrap();
    int yylex();
%}
%%
aa      { 
            printf( "(%s)", yytext );
            yymore();
        }
%%
int yywrap() { return 1; }
int main() { return yylex(); }

    /* mowi scanerowi, ze nastepne dopasowanie wzorca powinno byc dolaczone na
    koniec biezacej wartosci yytext, zamiasto ja nadpisac */
    /* yymore() */