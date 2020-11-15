%{
    #include <stdio.h>
    void yyerror (char const *s);
%}
%token num

%%
S : E   { printf( "OK" ); }
  ;

E : E '+' T
  | T 
  ;

T : T '*' F
  | F
  ;

F : '(' E ')'
  | num
  ;
%%
void yyerror (char const *s)
{
    fprintf (stderr, "%s\n", s);
}

int main(void)
{
  printf("START\n");
  yyparse();
  printf("\nEND");
}