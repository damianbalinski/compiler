%{
    #include <stdio.h>
    int yylex();
    void yyerror (char *s);
%}

%start program
%token LET INTEGER IN
%token SKIP IF THEN ELSE FI END WHILE DO READ WRITE
%token ASSGNOP
%token NUMBER
%token IDENTIFIER
%left '-' '+'
%left '*' '/'
%right '^'
%right '='
%nonassoc '<' '>'

%%

program: LET declarations IN commands END
;

declarations: /* empty */
| INTEGER id_seq IDENTIFIER '.'
;

id_seq: /* empty */
| id_seq IDENTIFIER ','
;

commands: /* empty */
| commands command ';'
;
command: SKIP
| READ IDENTIFIER
| WRITE exp
| IDENTIFIER ASSGNOP exp
| IF exp THEN commands ELSE commands FI
| WHILE exp DO commands END
;

exp: NUMBER
| IDENTIFIER
| exp '<' exp
| exp '=' exp
| exp '>' exp
| exp '+' exp
| exp '-' exp
| exp '*' exp
| exp '/' exp
| exp '^' exp
| '(' exp ')'
;

%%

int main( int argc, char *argv[] )
{
    extern FILE *yyin;
    ++argv; --argc;
    yyin = fopen( argv[0], "r" );
    yydebug = 1;
    //errors = 0;
    return yyparse();
}

void yyerror (char *s) /* Called by yyparse on error */
{
    printf("%s\n", s);
}
