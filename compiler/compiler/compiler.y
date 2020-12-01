%{
    #define YYDEBUG 1

    #include <stdio.h>
    #include <stdlib.h>
    #include "debugger/debugger.h"
    #include "errors/errors.h"

    extern int yylineno;
    extern char* yytext;
    int yylex();
    void yyerror( char *str );
%}

%union{
    long long val;       /* liczba */
    char *id;            /* identyfikator */
}

%start program
%token <val> NUMBER
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
program: DECLARE declarations T_BEGIN commands END
| T_BEGIN commands END
;

declarations: declarations ',' PIDENTIFIER
|  declarations ',' PIDENTIFIER '(' NUMBER ':' NUMBER ')'
|  PIDENTIFIER
|  PIDENTIFIER '(' NUMBER ':' NUMBER ')'
;

commands: commands command
|  command
;

command: identifier ASSIGN expression ';'
|  IF condition THEN commands ELSE commands ENDIF
|  IF condition THEN commands ENDIF
|  WHILE condition DO commands ENDWHILE
|  REPEAT commands UNTIL condition ';'
|  FOR PIDENTIFIER FROM value TO value DO commands ENDFOR
|  FOR PIDENTIFIER FROM value DOWNTO value DO commands ENDFOR
|  READ identifier ';'
|  WRITE value ';'
;

expression: value
|  value '+' value
|  value '-' value
|  value '*' value
|  value '/' value
|  value '%' value
;

condition: value EQ value
|  value NE value
|  value LT value
|  value GT value
|  value LE value
|  value GE value
;

value: NUMBER
|  identifier
;

identifier: PIDENTIFIER
|  PIDENTIFIER '(' PIDENTIFIER ')'
|  PIDENTIFIER '(' NUMBER ')'
;

%%

int main( int argc, char** argv )
{
    // TEST
    // yydebug = 1;

    // inicjalizacja
    ERR_INIT;

    extern FILE *yyin;
    yyin = fopen(argv[1], "r");

    PR_PARSE_BEGIN;
    yyparse();
    PR_PARSE_END;
}

void yyerror (char* str)
{
    ERR_ADD;
    fprintf(stderr, ERR_SYNTAX);
}
