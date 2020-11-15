%{
    #include <string.h>
    #include <stdlib.h>
    #include <stdio.h>
    void yyerror (char const *s);
    int yylex();
%}
%token NUM

%%
s: e                      { printf( "OK" ); }
 ;
e: NUM                  { printf( "numer"); }
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