%{
    #include <string.h>
    #include <stdlib.h>
    #include <stdio.h>
    void yyerror (char const *s);
    int yylex();
%}
%token NUM

%%
Numer: NUM                  { printf( "numer"); }
     ;
    //Koniec: Ciag            { printf( "OK\n"); }
    //  | Ciag Inne       { printf("parser error"); }
    //  ;

Inne: '('
      | ')'
      | ','
      | Liczby
      ;

Ciag: '(' Liczby ')'
      ;

Liczby: NUM
      | Liczby ',' NUM
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