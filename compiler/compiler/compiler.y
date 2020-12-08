%{
    #define YYDEBUG 1

    #include <stdio.h>
    #include <stdlib.h>
    #include "debugger/debugger.h"
    #include "debugger/errors.h"
    #include "code_generator/instr_generator.h"

    extern int yylineno;
    extern char* yytext;
    int yylex();
    void yyerror( char *str );
%}

%code requires {
    #include "others/types.h"
    #include "others/unit.h"
}

%union{
    input_type val;      /* wartosc i rejestr */
    unit_type* unit;     /* pamiec i rejestr */
    char *id;            /* identyfikator */
}

%destructor { unit_free($$); } unit
%start program
%nterm <unit> value
%nterm <unit> expression
%nterm <unit> identifier
%nterm <unit> lidentifier
%token <val> NUMBER
%token <id> ID
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

declarations: declarations ',' ID                  { add_variable($3);      }
|  declarations ',' ID '(' NUMBER ':' NUMBER ')'   { add_array($3, $5, $7); }
|  ID                                              { add_variable($1);      }
|  ID '(' NUMBER ':' NUMBER ')'                    { add_array($1, $3, $5); }
;

commands: commands command
|  command
;

command: lidentifier ASSIGN expression ';'         { }
|  IF condition THEN commands ELSE commands ENDIF
|  IF condition THEN commands ENDIF
|  WHILE condition DO commands ENDWHILE
|  REPEAT commands UNTIL condition ';'
|  FOR ID FROM value TO value DO commands ENDFOR
|  FOR ID FROM value DOWNTO value DO commands ENDFOR
|  READ identifier ';'
|  WRITE value ';'
;

expression: value
|  value '+' value                   { /* $$ = sum($1, $3); */ }
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
|  identifier                        {  }
;

identifier: ID                       { /* $$ = get_rvariable($1); */ }
|  ID '(' ID ')'
|  ID '(' NUMBER ')' 
;

lidentifier: ID                      { $$ = get_lvariable($1); }
|  ID '(' ID ')'
|  ID '(' NUMBER ')'                 { /*$$ = get_larray_num($1, $3); */ }
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
