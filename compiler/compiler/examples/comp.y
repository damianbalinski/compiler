%{
    #include <stdio.h>
    #include <stdlib.h>
    #include "symbol_table.c"
    #define YYDEBUG 1
    int yylex();
    void yyerror( char *s );
    void install( char* symname );
    void contextcheck( char *symname );
    int errors;

%}

%union{
    char *id; /* identyfikator */
}

%start program
%token LET INTEGER IN
%token SKIP IF THEN ELSE FI END WHILE DO READ WRITE
%token ASSGNOP
%token NUMBER
%token <id> IDENTIFIER
%left '-' '+'
%left '*' '/'
%right '^'
%right '='
%nonassoc '<' '>'

%%

program: LET declarations IN commands END
;

declarations: /* empty */
| INTEGER id_seq IDENTIFIER '.'     { install( $3 ); }
;

id_seq: /* empty */
| id_seq IDENTIFIER ','             { install( $2 ); }
;

commands: /* empty */
| commands command ';'
;
command: SKIP
| READ IDENTIFIER                   { contextcheck( $2 ); }
| WRITE exp
| IDENTIFIER ASSGNOP exp            { contextcheck( $1 ); }
| IF exp THEN commands ELSE commands FI
| WHILE exp DO commands END
;

exp: NUMBER
| IDENTIFIER                        { contextcheck( $1 ); }
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
    // yydebug = 1;
    errors = 0;
    return yyparse();
}

void yyerror (char* str) /* Called by yyparse on error */
{
    printf("%s\n", str);
}

void install( char* symname )
{
    symrec *s;
    s = getsym (symname);
    if (s == 0)
        s = putsym (symname);
    else {
        errors++;
        printf( "%s is already defined\n", symname );
    }
}

void contextcheck( char *symname )
{
    if ( getsym( symname ) == 0 )
        printf( "%s is an undeclared identifier\n", symname );
}