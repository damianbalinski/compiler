%{
    #define YYDEBUG 1

    #include <stdio.h>
    #include <stdlib.h>
    #include "debugger/debugger.h"
    #include "debugger/errors.h"
    #include "symbol_table/symbol_table.h"
    #include "registers/registers.h"
    #include "code_generator/instr_generator.h"

    extern int yylineno;
    extern char* yytext;
    int yylex();
    void yyerror( char *str );
%}

%code requires {
    #include "others/types.h"
}

%union{
    val_type val;        /* wartosc i rejestr */
    char *id;            /* identyfikator */
    int reg;
}

%start program
%nterm <reg> value
%nterm <reg> expression
%nterm <reg> identifier
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

declarations: declarations ',' PIDENTIFIER                  { put_variable($3); }
|  declarations ',' PIDENTIFIER '(' NUMBER ':' NUMBER ')'
|  PIDENTIFIER                                              { put_variable($1); }
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
|  value '+' value                   { $$ = reg_add($1, $3); }
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

value: NUMBER                        { $$ = get_const($1); }
|  identifier                        { $$ = $1; }
;

identifier: PIDENTIFIER              { $$ = get_variable($1); }
|  PIDENTIFIER '(' PIDENTIFIER ')'   { $$ = -1; }
|  PIDENTIFIER '(' NUMBER ')'        { $$ = -1; }
;

%%

int main( int argc, char** argv )
{
    // TEST
    // yydebug = 1;
    
    extern FILE *yyin;
    yyin = fopen(argv[1], "r");

    DBG_PARSER_BEGIN();
    yyparse();
    DBG_PARSER_END();
}

void yyerror (char* str)
{
    ERR_ADD();
    ERR_SYNTAX();
}
