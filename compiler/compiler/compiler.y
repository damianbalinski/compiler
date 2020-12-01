%{
    #define YYDEBUG 1

    #include <stdio.h>
    #include <stdlib.h>

    int yylex();
    void yyerror( char *str );
%}

%union{
    int val;             /* wartosc int */
    char *id;            /* identyfikator */
}

%start program
%token <intval> NUMBER
%token <id> PIDENTIFIER
%token DECLARE T_BEGIN END
%token IF THEN ELSE ENDIF
%token DO
%token WHILE ENDWHILE
%token REPEAT UNTIL
%token FOR FROM TO ENDFOR DOWNTO
%token READ WRITE
%left '-' '+'                        /* operatory arytmetyczne */
%left '*' '/' '%'
%nonassoc EQ NE LT LE GT GE          /* operatory porownania */
%nonassoc ASSIGN                     /* operator przypisania */

%%
program: DECLARE declarations
         T_BEGIN commands
         END
;

declarations: declarations ',' PIDENTIFIER
|  PIDENTIFIER
;

commands: commands command
|  command
;

command: identifier ASSIGN expression
;

expression: value
;

value: NUMBER
;

identifier: PIDENTIFIER
;

%%

int main( int argc, char *argv[] )
{
    // TEST
    // yydebug = 1;

    extern FILE *yyin;
    yyin = fopen( argv[0], "r" );
    printf( "Parse Start\n");
    yyparse();
    printf( "Parse Completed\n");
}

void yyerror (char* str)
{
    fprintf(stderr, str);
}
