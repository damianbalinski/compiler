%{
    #include <string.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include "seq.tab.h"
    void yyerror (char const *s);
    int yylex ();
%}
%token NUM

%%
input:
  %empty
| input line
;

line:
  '\n'
| sequence '\n'             { printf( "OK\n" ); }
| error '\n'                { yyerrok; }
;

sequence: 
  '(' nums ')'
;

nums:
  NUM                       { printf("[%d]", $1); }
| nums ',' NUM              { printf("[%d]", $3); }
;

%%

void yyerror (char const *s)
{
    fprintf (stderr, "%s\n", s);
}

int main()
{
    return yyparse();
}