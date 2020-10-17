%{
    #include <stdio.h>
    int yywrap();
    int yylex();
%}

%%
aa      printf("Y");
a*      printf("X");
%%
int yywrap() { return 1; }
int main() { return yylex(); }

/**
 * ZASADY ROZSTRZYGANIA NIEJEDNOZNACZNOSCI
 *
 * - zasada najdluzszego dopasowania, wybor wzorda, dle
 * ktorego dopasowanie wzorca jest najdluzsze
 *
 * - zasada wczesniejszego dopasowania, jesli dopasowania
 * sa jednakowej dlugosci, wybierany jest wzorzec dopasowany
 * jako pierwszy
 */