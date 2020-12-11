%{
    #define YYDEBUG 1

    #include <stdio.h>
    #include <stdlib.h>
    #include "debugger/debugger.h"
    #include "debugger/errors.h"
    #include "code_generator/instr_generator.h"
    #include "code_generator/code_generator.h"
    #include "code_generator/registers_machine.h"

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

%start program
%nterm <unit> value
%nterm <unit> valueloc
%nterm <unit> expression
%nterm <unit> ridentifier
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
program: DECLARE declarations T_BEGIN commands END { halt(); YYACCEPT; }
| T_BEGIN commands END                             { halt(); YYACCEPT; }
;

declarations: declarations ',' ID                  { add_variable($3);      }
|  declarations ',' ID '(' NUMBER ':' NUMBER ')'   { add_array($3, $5, $7); }
|  ID                                              { add_variable($1);      }
|  ID '(' NUMBER ':' NUMBER ')'                    { add_array($1, $3, $5); }
;

commands: commands command
|  command
;

command: lidentifier ASSIGN expression ';'              { assign($1, $3); }
|  IF condition THEN commands ELSE commands ENDIF
|  IF condition THEN commands ENDIF
|  WHILE condition DO commands ENDWHILE
|  REPEAT commands UNTIL condition ';'
|  FOR ID FROM value TO value DO commands ENDFOR
|  FOR ID FROM value DOWNTO value DO commands ENDFOR
|  READ lidentifier ';'                                 { read($2);       }
|  WRITE valueloc ';'                                   { write($2);      }
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

value: NUMBER                        { $$ = get_const($1);                    }
|  ridentifier                       { $$ = $1;                               }
;

valueloc: NUMBER
| ID                                 { $$ = get_variable($1,      LOCATION, INIT);   }
|  ID '(' ID ')'                     { $$ = get_array_var($1, $3, LOCATION, INIT);   }
|  ID '(' NUMBER ')'                 { $$ = get_array_num($1, $3, LOCATION, INIT);   }
;

ridentifier: ID                      { $$ = get_variable($1,      VALUE, INIT);      }
|  ID '(' ID ')'                     { $$ = get_array_var($1, $3, VALUE, INIT);      }
|  ID '(' NUMBER ')'                 { $$ = get_array_num($1, $3, VALUE, INIT);      }
;

lidentifier: ID                      { $$ = get_variable($1,      LOCATION, NOINIT); }
|  ID '(' ID ')'                     { $$ = get_array_var($1, $3, LOCATION, NOINIT); }
|  ID '(' NUMBER ')'                 { $$ = get_array_num($1, $3, LOCATION, NOINIT); }
%%

int main( int argc, char** argv )
{ 
    extern FILE *yyin;
    FILE* output;

    if (argc != 3) {
        ERR_BAD_CALL(argv[0]);
        ERR_ADD();
    }
    else if ((yyin = fopen(argv[1], "r")) == NULL) {
        ERR_BAD_FILENAME(argv[1]);
        ERR_ADD();
    }

    DBG_PARSER_BEGIN();
    reg_init();
    yyparse();
    DBG_PARSER_END();

    if ((output = fopen(argv[2], "w")) == NULL) {
        ERR_BAD_FILENAME(argv[2]);
        ERR_ADD();
    }

    code_print_all(output);
    return 0;
}

void yyerror (char* str)
{
    ERR_SYNTAX();
    ERR_ADD();
}
