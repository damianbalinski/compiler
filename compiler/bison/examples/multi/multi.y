%{
    #include <stdio.h>
    void yyerror (char const* str);
    int yylex ();
%}

%define api.value.type union
%token <int> INT
%token <float> FLOAT
%left '+'
%left '*'

%%

input:
  %empty
| input line
;

line:
  '\n'
| iexp '\n'             { printf ("   RES: %d\n", $<int>1);   }
| fexp '\n'             { printf ("   RES: %f\n", $<float>1); }
| error '\n'            { yyerrok;                            }
;

iexp:
  INT                   {                              }  
| iexp '+' iexp         { $<int>$ = $<int>1 + $<int>3; }
| iexp '*' iexp         { $<int>$ = $<int>1 * $<int>3; }
;
 
fexp:
  FLOAT                 {                                    }
| fexp '+' fexp         { $<float>$ = $<float>1 + $<float>3; }  /* addition */
| iexp '+' fexp         { $<float>$ = $<int>1 + $<float>3;   }
| fexp '+' iexp         { $<float>$ = $<float>1 + $<int>3;   }
| fexp '*' fexp         { $<float>$ = $<float>1 * $<float>3; }  /* multiplication */
| iexp '*' fexp         { $<float>$ = $<int>1 * $<float>3;   }
| fexp '*' iexp         { $<float>$ = $<float>1 * $<int>3;   }
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