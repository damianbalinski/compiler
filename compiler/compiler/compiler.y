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
    #include "others/cond.h"
}

%union{
    input_type val;      /* wartosc i rejestr */
    unit_type* unit;     /* pamiec i rejestr */
    char *id;            /* identyfikator */
    cond_type* cond;
}

//%glr-parser
%start program
%nterm <unit> value
%nterm <unit> valueloc
%nterm <unit> expression
%type <unit> condition
%nterm <unit> ridentifier
%nterm <unit> lidentifier
%token <val> NUMBER
%token <id> ID
%token DECLARE T_BEGIN END
%token <cond> IF WHILE REPEAT
%token THEN ELSE ENDIF
%token DO
%token ENDWHILE
%token UNTIL
%token FOR FROM TO ENDFOR DOWNTO
%token READ WRITE
%left '-' '+'                        /* operatory arytmetyczne1 */
%left '*' '/' '%'                    /* operatory arytmetyczne2 */
%nonassoc EQ NE LT LE GT GE          /* operatory porownania    */
%nonassoc ASSIGN                     /* operator przypisania    */

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

|   IF              {   $1 = cond_alloc();                  }
    condition       {   jump_true_false($1, $3, INIT);
                        jump_end($1, $3, INIT);             }
    THEN            {   $1->label_cmd = code_get_label();   }
    commands    
    ENDIF           {   $1->label_end = code_get_label();
                        jump_true_false($1, $3, FINISH);
                        jump_end($1, $3, FINISH);
                        DBG_JUMPS($1);
                        jumps_free($1, $3);                 }

|   WHILE           {   $1 = cond_alloc();                    
                        $1->label_cond = code_get_label();  }  
    condition       {   jump_true_false($1, $3, INIT);
                        jump_end($1, $3, INIT);             }
    DO              {   $1->label_cmd = code_get_label();   }
    commands        {   jump_cond($1, $3, INIT);            }
    ENDWHILE        {   $1->label_end = code_get_label();
                        jump_true_false($1, $3, FINISH);
                        jump_end($1, $3, FINISH);
                        jump_cond($1, $3, FINISH);
                        DBG_JUMPS($1);
                        jumps_free($1, $3);                 }
                    
|   REPEAT          {   $1 = cond_alloc();                 
                        $1->label_cmd = code_get_label();   }
    commands
    UNTIL
    condition       {   jump_true_false($1, $5, INIT);
                        jump_cmd($1, $5, INIT);             }
    ';'             {   $1->label_end = code_get_label();
                        jump_true_false($1, $5, FINISH);
                        jump_cmd($1, $5, FINISH);
                        DBG_JUMPS($1);
                        jumps_free($1, $5);                 }

|  FOR ID FROM value TO value DO commands ENDFOR
|  FOR ID FROM value DOWNTO value DO commands ENDFOR
|  READ lidentifier ';'                                 { read($2);       }
|  WRITE valueloc ';'                                   { write($2);      }
;

expression: value              { $$ = $1;          }
|  value '+' value             { $$ = sum($1, $3); }
|  value '-' value             { $$ = dif($1, $3); }
|  value '*' value             { $$ = mul($1, $3); }
|  value '/' value
|  value '%' value
;

condition: value EQ value            { $$ = eq_ne($1, $3, EQUAL);         }
|  value NE value                    { $$ = eq_ne($1, $3, NOT_EQUAL);     }
|  value LT value                    { $$ = lt_ge($1, $3, LESS);          }
|  value GT value                    { $$ = gt_le($1, $3, GREATER);       }
|  value LE value                    { $$ = gt_le($1, $3, LESS_EQUAL);    }
|  value GE value                    { $$ = lt_ge($1, $3, GREATER_EQUAL); }
;

value: NUMBER                        { $$ = get_const($1,         VALUE); }
|  ridentifier                       { $$ = $1;                           }
;

valueloc: NUMBER                     { $$ = get_const($1,         LOCATION);         }
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

/* Metoda startowa.
 * ERR1 - nieprawidlowa liczba argumentow
 * ERR2 - problem z otwarciem argv[1]
 * ERR3 - problem z otwarciem argv[2]
 */
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
