%{
    #include <stdio.h>
    void yyerror (char const* str);
    int yylex ();
%}

%union {
    int INT;
    float FLOAT;
}

%token <INT> INT
%token <FLOAT> FLOAT
%left '+'
%left '*'

%%

input:
  %empty
| input line
;

line:
  '\n'
| iexp '\n'             { printf ("   RES: %d\n", $<INT>1);   }
| fexp '\n'             { printf ("   RES: %f\n", $<FLOAT>1); }
| error '\n'            { yyerrok;                            }
;

iexp:
  INT                   {                              }  
| iexp '+' iexp         { $<INT>$ = $<INT>1 + $<INT>3; }
| iexp '*' iexp         { $<INT>$ = $<INT>1 * $<INT>3; }
;
 
fexp:
  FLOAT                 {                                    }
| fexp '+' fexp         { $<FLOAT>$ = $<FLOAT>1 + $<FLOAT>3; }  /* addition */
| iexp '+' fexp         { $<FLOAT>$ = $<INT>1 + $<FLOAT>3;   }
| fexp '+' iexp         { $<FLOAT>$ = $<FLOAT>1 + $<INT>3;   }
| fexp '*' fexp         { $<FLOAT>$ = $<FLOAT>1 * $<FLOAT>3; }  /* multiplication */
| iexp '*' fexp         { $<FLOAT>$ = $<INT>1 * $<FLOAT>3;   }
| fexp '*' iexp         { $<FLOAT>$ = $<FLOAT>1 * $<INT>3;   }
;
%%

void yyerror(char const* str)
{
    fprintf(stderr, "%s\n", str);
}

int main (void)
{
    return yyparse();
}