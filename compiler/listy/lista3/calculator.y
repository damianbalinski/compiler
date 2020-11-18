%{
    #include <string.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include "arythmetic.h"

    #define MAX 1024
    #define NUMB 0
    #define OPER 1

    int LIST[MAX];
    int LIST_TYPE[MAX];
    int N = 0;
    
    void yyerror (char const *s);
    int yylex ();
    void put(int type, int val);
    void clear();
    void print();
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
| exp '\n'           { print(); clear(); printf( "\nWynik: %d\n", $1 ); }
| error '\n'         { yyerrok; clear();                                }
;

exp:
  NUM                { $$ = _norm($$)  ; put(NUMB, $$ ); }
| exp '+' exp        { $$ = _add($1,$3); put(OPER, '+'); }
| exp '-' exp        { $$ = _sub($1,$3); put(OPER, '-'); }
| exp '*' exp        { $$ = _mul($1,$3); put(OPER, '*'); }
| exp '/' exp        { $$ = _div($1,$3); put(OPER, '/'); }  // TODO dzielenie przez 0
| '-' NUM %prec NEG  { $$ = _norm(-$2) ; put(NUMB, $$ ); }
| exp '^' exp        { $$ = _pow($1,$3); put(OPER, '^'); }
| '(' exp ')'        { $$ = $2;                          }
;

%%

void yyerror (char const *s)
{
    fprintf(stderr, "%s\n", s);
}

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

void print()
{
    for(int i = 0; i < N; i++) {
        if (LIST_TYPE[i] == NUMBER)
            printf("%d ", LIST[i]);
        else
            printf("%c ", LIST[i]);
    } 
}

int main()
{
    return yyparse();
}