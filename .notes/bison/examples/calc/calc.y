/* Infix notation calculator. */
%{
    #include <math.h>
    #include <stdio.h>
    #include <ctype.h>
    #include <stdlib.h>
    int yylex (void);
    void yyerror (char const *);
%}

/* Bison declarations. */
%define api.value.type {double}
%token NUM
%left '-' '+'
%left '*' '/'
%precedence NEG   /* negation--unary minus */
%right '^'        /* exponentiation */

%% /* The grammar follows. */

input:
  %empty
| input line
;

line:
  '\n'
| exp '\n'           { printf ("\t%.10g\n", $1); }
| error '\n'         { yyerrok; }
;

exp:
  NUM
| exp '+' exp        { $$ = $1 + $3;      }
| exp '-' exp        { $$ = $1 - $3;      }
| exp '*' exp        { $$ = $1 * $3;      }
| exp '/' exp        { $$ = $1 / $3;      }
| '-' exp  %prec NEG { $$ = -$2;          }
| exp '^' exp        { $$ = pow ($1, $3); }
| '(' exp ')'        { $$ = $2;           }
;

%%

int main (void){
    return yyparse();
}

/* Called by yyparse on error. */
void yyerror(char const *s)
{
    fprintf(stderr, "%s\n", s);
}

int yylex (void)
{
   int c = getchar ();
  
   /* Skip white space. */
   while (c == ' ' || c == '\t')
      c = getchar ();
   
   /* Process numbers. */
   if (c == '.' || isdigit (c))
   {
      ungetc (c, stdin);
      if (scanf ("%lf", &yylval) != 1)
         abort ();
      return NUM;
   }
   
   /* Return end-of-input. */
   else if (c == EOF)
      return YYEOF;
   /* Return a single char. */
   else
      return c;
}