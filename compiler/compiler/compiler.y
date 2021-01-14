%{
    #define YYDEBUG 1

    #include <cstdio>
    #include <cstdlib>
    #include "debugger/debugger.hpp"
    #include "debugger/errors.hpp"
    #include "code_generator/instr_generator.hpp"
    #include "code_generator/code_generator.hpp"
    #include "code_generator/registers_machine.hpp"
    #include "parse_tree/commands.hpp"

    extern int yylineno;
    extern char* yytext;
    extern int yylex(void);
    extern CommandVector* commands;
    void yyerror(char *str);
%}

%code requires {
    #include "others/types.hpp"
    #include "others/unit.hpp"
    #include "parse_tree/commands.hpp"
    #include "parse_tree/values.hpp"
    #include "parse_tree/conditions.hpp"
    #include "parse_tree/expressions.hpp"
}

%union{
    data_type input;         /* wartosc          */
    unit_type* unit;         /* pamiec i rejestr */
    char *id;                /* identyfikator    */
    bool type;               /* wartosc logiczna */
    AbstractCommand* cmd;    /* komenda          */
    CommandVector* vec;      /* wektor komend    */
    AbstractValue* val;      /* wartosc          */
    AbstractExpression* exp; /* wyrazenie        */
    AbstractCondition* con;  /* warunek          */
    
}

%start program
%type <val> value
%type <val> valueloc
%type <exp> expression
%type <con> condition
%type <val> ridentifier
%type <val> lidentifier
%type <cmd> command
%type <vec> commands
%token <input> NUMBER
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
program: DECLARE declarations T_BEGIN commands END { commands = $4; commands->push_back(new CHalt()); YYACCEPT; }
| T_BEGIN commands END                             { commands = $2; commands->push_back(new CHalt()); YYACCEPT; }
;

declarations: declarations ',' ID                  { add_variable($3);      }
|  declarations ',' ID '(' NUMBER ':' NUMBER ')'   { add_array($3, $5, $7); }
|  ID                                              { add_variable($1);      }
|  ID '(' NUMBER ':' NUMBER ')'                    { add_array($1, $3, $5); }
;

commands: commands command                         { $1->push_back($2);  $$ = $1;           }
|  command                                         { $$ = new CommandVector();
                                                     $$->push_back($1);                     }
;

command: lidentifier ASSIGN expression ';'           { $$ = new CAssign($1, $3);            }
| IF condition THEN commands ELSE commands ENDIF     { $$ = new CIfThenElse($2, $4, $6);    }
| IF condition THEN commands ENDIF                   { $$ = new CIfThen($2, $4);            }
| WHILE condition DO commands ENDWHILE               { $$ = new CWhile($2, $4);             }
| REPEAT commands UNTIL condition ';'                { $$ = new CRepeat($4, $2);            }
| FOR ID FROM value TO value DO commands ENDFOR      { $$ = new CForTo($2, $4, $6, $8);     }
| FOR ID FROM value DOWNTO value DO commands ENDFOR  { $$ = new CForDownto($2, $4, $6, $8); }
| READ lidentifier ';'                               { $$ = new CRead($2);                  }
| WRITE valueloc ';'                                 { $$ = new CWrite($2);                 }
;

expression: value              { $$ = new ExpressionBas($1);     }
|  value '+' value             { $$ = new ExpressionSum($1, $3); }
|  value '-' value             { $$ = new ExpressionDif($1, $3); }
|  value '*' value             { $$ = new ExpressionMul($1, $3); }
|  value '/' value             { $$ = new ExpressionDiv($1, $3); }
|  value '%' value             { $$ = new ExpressionMod($1, $3); }
;

condition: value EQ value      { $$ = new ConditionEQ($1, $3);   }
|  value NE value              { $$ = new ConditionNE($1, $3);   }
|  value LT value              { $$ = new ConditionLT($1, $3);   }
|  value GT value              { $$ = new ConditionGT($1, $3);   }
|  value LE value              { $$ = new ConditionLE($1, $3);   }
|  value GE value              { $$ = new ConditionGE($1, $3);   }
;

value: NUMBER                  { $$ = new VNum($1, VALUE);                     }
|  ridentifier                 { $$ = $1;                                      }
;

valueloc: NUMBER               { $$ = new VNum($1, LOCATION);                  }
|  ID                          { $$ = new VVar($1, LOCATION, INIT);            }
|  ID '(' ID ')'               { $$ = new VArrVar($1, $3, LOCATION, INIT);     }
|  ID '(' NUMBER ')'           { $$ = new VArrNum($1, $3, LOCATION, INIT);     }
;

ridentifier: ID                { $$ = new VVar($1, VALUE, INIT);               }
|  ID '(' ID ')'               { $$ = new VArrVar($1, $3, VALUE, INIT);        }
|  ID '(' NUMBER ')'           { $$ = new VArrNum($1, $3, VALUE, INIT);        }
;

lidentifier: ID                { $$ = new VVar($1, LOCATION, NOINIT);          }
|  ID '(' ID ')'               { $$ = new VArrVar($1, $3, LOCATION, NOINIT);   }
|  ID '(' NUMBER ')'           { $$ = new VArrNum($1, $3, LOCATION, NOINIT);   }
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

    // commands->print();
    commands->code();
    
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
