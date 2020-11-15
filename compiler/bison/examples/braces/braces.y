%{
    #include <string.h>
    #include <stdlib.h>
    #include <stdio.h>
    void yyerror (char const *s);
    int yylex();
    int NAWIASY = 0;
%}
%token LEWY
%token PRAWY
%token NL
%%
S: E           { printf( "nawiasy: %d\n", NAWIASY); }
 ;
E: '(' E ')'   { ++NAWIASY; }
 |
;
%%

void yyerror (char const *s)
{
    fprintf (stderr, "new_error: %s\n", s);
}

int main()
{
    return yyparse();
}