%{
    #include <stdio.h>
    #include <stdlib.h>
    #include "symbol_table.c"
    #include "stack_machine.c"
    #include "code_generator.c"

    #define YYDEBUG 1

    // for labels if and while
    struct  lbs {
        int for_goto;
        int for_jmp_false;
    };

    int yylex();
    void yyerror( char *s );
    void install( char* symname );

    void contextcheck( enum code_ops operation, char *sym_name );

    struct lbs* newlblrec();

    // zmienne globalne
    int errors;
%}

%union{
    int intval;         /* wartosc int */
    char *id;           /* identyfikator */
    struct lbs* lbls;   /* adresy skokow (etykiety) */
}

%start program
%token <intval> NUMBER
%token <id> IDENTIFIER
%token <lbls> IF WHILE
%token LET INTEGER IN
%token SKIP THEN ELSE FI END DO READ WRITE
%token ASSGNOP
%left '-' '+'
%left '*' '/'
%right '^'
%right '='
%nonassoc '<' '>'

%%

program:    LET 
                declarations 
            IN      { gen_code( DATA, symtable->offset ); }
                commands
            END     { gen_code( HALT, 0 ); YYACCEPT;       }
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
| READ IDENTIFIER            { contextcheck( READ_INT, $2 ); }
| WRITE exp                  { gen_code( WRITE_INT, 0 );     }
| IDENTIFIER ASSGNOP exp     { contextcheck( STORE, $1 ); }

| IF exp                     { $1 = (struct lbs *) newlblrec();
                               $1->for_jmp_false = reserve_loc(); }
  THEN commands              { $1->for_goto = reserve_loc();      }
  ELSE                       { back_patch( $1->for_jmp_false, JMP_FALSE, gen_label() ); }
    commands
  FI                         { back_patch( $1->for_goto, GOTO, gen_label() ); }

| WHILE                      { $1 = (struct lbs *) newlblrec();
                               $1->for_goto = gen_label(); }
    exp                      { $1->for_jmp_false = reserve_loc(); }
  DO 
    commands
  END                        { gen_code( GOTO, $1->for_goto );
                               back_patch( $1->for_jmp_false, JMP_FALSE, gen_label() ); }
;

exp: NUMBER                  { gen_code( LD_INT, $1 );     }
| IDENTIFIER                 { contextcheck( LD_VAR, $1 ); }
| exp '<' exp                { gen_code( LT,   0 );        }
| exp '=' exp                { gen_code( EQ,   0 );        }
| exp '>' exp                { gen_code( GT,   0 );        }
| exp '+' exp                { gen_code( ADD,  0 );        }
| exp '-' exp                { gen_code( SUB,  0 );        }
| exp '*' exp                { gen_code( MULT, 0 );        }
| exp '/' exp                { gen_code( DIV,  0 );        }
| exp '^' exp                { gen_code( PWR,  0 );        }
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
    printf( "Parse Start\n");
    yyparse();
    printf( "Parse Completed\n");
    if (errors == 0) {
        print_code();
        fetch_execute_cycle();
    }
}

void yyerror (char* str) /* Called by yyparse on error */
{
    errors++;
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

void contextcheck( enum code_ops operation, char *sym_name )
{
    symrec *identifier;
    identifier = getsym( sym_name );
    if ( identifier == 0 ) {
        errors++;
        printf( "%s", sym_name );
        printf( "%s\n", " is an undeclared identifier"  );
    }
    else
        gen_code( operation, identifier->offset );
}

////////////////////////////////////////////////////
/* Allocate space for the labels */
struct lbs* newlblrec() {
    return  (struct lbs *) malloc(sizeof(struct lbs));
}