%{
    #include <string.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include "arithmetic.h"

    #define MAX 1024
    #define NUMB 0
    #define OPER 1

    int LIST[MAX];
    int LIST_TYPE[MAX];
    int N = 0;
    
    extern int yylineno;
    void yyerror (char const *s);
    int yylex ();
    void put(int type, int val);
    void clear();
    void print();
%}

%token NUM LERROR
%left '-' '+'
%left '*' '/'
%precedence NEG
%nonassoc '^'

%%
input:
  %empty
| input line
;

line:
  '\n'
| exp '\n'           { print(); clear(); printf( "\nWynik: %d\n", $1 ); }
| error '\n'         { yyerrok; clear();                                }
;

exp:
  NUM                { $$ = _norm($$)  ; put(NUMB, $$ ); }
| exp '+' exp        { $$ = _add($1,$3); put(OPER, '+'); }
| exp '-' exp        { $$ = _sub($1,$3); put(OPER, '-'); }
| exp '*' exp        { $$ = _mul($1,$3); put(OPER, '*'); }
| exp '/' exp        { 
                        if (_zero($3)) {
                            yyerror(ERR_DIV_ZERO);
                            YYERROR;
                        }
                        else
                            $$ = _div($1,$3); put(OPER, '/');
                     }
| '-' NUM %prec NEG  { $$ = _norm(-$2) ;  put(NUMB, $$ );                            }
| exp '^' NUM        { $$ = _pow($1,$3);  put(NUMB, _norm_pow($3));  put(OPER, '^'); }
| exp '^' '-' NUM    { $$ = _pow($1,-$3); put(NUMB, _norm_pow(-$3)); put(OPER, '^'); }
| '(' exp ')'        { $$ = $2;                                                      }
;

%%

void yyerror (char const *s)
{
    fprintf(stderr, "Blad [linia %d] : %s\n", yylineno, s);
}

/* Dodaje operator lub liczbe do tablicy */
void put(int type, int val)
{
    LIST_TYPE[N] = type;
    LIST[N] = val;
    ++N;
}

void clear()
{
    N = 0;
}

/* Odtwarza tablice, w zaleznosci od typu drukuje operator
 * lub liczbe. */
void print()
{
    for(int i = 0; i < N; i++) {
        if (LIST_TYPE[i] == NUMB)
            printf("%d ", LIST[i]);
        else
            printf("%c ", LIST[i]);
    } 
}

int main()
{
    yylineno = 0;
    return yyparse();
}