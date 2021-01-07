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
    input_type val;      /* wartosc          */
    unit_type* unit;     /* pamiec i rejestr */
    char *id;            /* identyfikator    */
    bool type;           /* wartosc logiczna */
    cond_type* cond;     /* skoki warunkowe  */
}

%start program
%type <unit> value
%type <unit> valueloc
%type <unit> expression
%type <unit> condition
%type <unit> ridentifier
%type <unit> lidentifier
%type <type> to_downto else
%token <val> NUMBER
%token <id> ID
%token DECLARE T_BEGIN END
%token <cond> IF WHILE REPEAT FOR
%token THEN ELSE ENDIF
%token DO
%token ENDWHILE
%token UNTIL
%token FROM TO ENDFOR DOWNTO
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
    commands        {   $1->label_end = code_get_label();   }
    else            {   $1->label_else = code_get_label();  }
    ENDIF           {   jump_true_false($1, $3, FINISH);
                        jump_end($1, $3, FINISH);
                        jump_else($1, $9, FINISH);
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
                        $1->label_end = code_get_label();   }
    commands
    UNTIL
    condition       {   jump_true_false($1, $5, INIT);            }
    ';'             {   $1->label_cmd = code_get_label();
                        jump_true_false($1, $5, FINISH);
                        jump_end($1, $5, FINISH);
                        DBG_JUMPS($1);
                        jumps_free($1, $5);                 }

|   FOR             {   $1 = cond_alloc();                  }
    ID              {   $1->iter = add_iterator($3);        }
    FROM
    value
    to_downto
    value           {   $8 = for_init($1, $6, $8, $7);      }
    DO              {   $1->label_cond = code_get_label();
                        jump_true_false($1, $8, INIT);
                        jump_end($1, $8, INIT);        
                        $1->label_cmd = code_get_label();   }
    commands        {   for_step($1, $8, $7);
                        jump_cond($1, $8, INIT);            }
    ENDFOR          {   $1->label_end = code_get_label();
                        jump_true_false($1, $8, FINISH);
                        jump_end($1, $8, FINISH);
                        jump_cond($1, $8, FINISH);
                        for_free($1, $8);
                        remove_iterator($3);                }

|  READ lidentifier ';'        { read($2);          }
|  WRITE valueloc ';'          { write($2);         }
;

to_downto: TO                  { $$ = FOR_TO;       }
|  DOWNTO                      { $$ = FOR_DOWNTO;   }
;

else: %empty                   { $<cond>-7->label_end = code_get_label();
                                 $$ = IF_THEN;                             }
|  ELSE                        { jump_else($<cond>-7, IF_THEN_ELSE, INIT); 
                                 $<cond>-7->label_end = code_get_label();  }
   commands                    { $$ = IF_THEN_ELSE;                        }
;

expression: value              { $$ = $1;           }
|  value '+' value             { $$ = sum($1, $3);  }
|  value '-' value             { $$ = dif($1, $3);  }
|  value '*' value             { $$ = mul($1, $3);  }
|  value '/' value             { $$ = divs($1, $3); }
|  value '%' value             { $$ = mod($1, $3);  }
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
    DBG_REGISTER_PRINT();

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
