%{
    #include <string.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include "arythmetic.h"

    void yyerror (char const *s);
    int yylex ();
%}
%token NUM
%left '-' '+'
%left '*' '/'
%precedence NEG
%right '^'

%%
input:
  %empty
| input line
;

line:
  '\n'
| exp '\n'           { printf( "\nWynik: %d\n", $1 ); }
| error '\n'         { yyerrok;                     }
;

exp:
  NUM                { $$ = _norm ($$);    printf ("(1)%d ", $$); }
| exp '+' exp        { $$ = _add ($1, $3); printf ("+ ");      }
| exp '-' exp        { $$ = _sub ($1, $3); printf ("- ");     printf ("(2)%d ", $$); }
| exp '*' exp        { $$ = _mul ($1, $3); printf ("* ");      }
| exp '/' exp        { $$ = _div ($1, $3); printf ("/ ");      }  // TODO dzielenie przez 0
| '-' exp  %prec NEG { $$ = _norm (-$2);    printf ("(2)%d ", $$);                    }
| exp '^' exp        { $$ = _pow ($1, $3); printf ("^ ");      }
| '(' exp ')'        { $$ = $2;                                }
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