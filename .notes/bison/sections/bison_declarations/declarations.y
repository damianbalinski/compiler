    /* KONFIGURACJA */
Zamiast parser LR, tworzy GLR, w przypadku niejednoznacznosci
tworzy równolegle wiele oddzielny parser dla kazdego przypadku.
Jesli nowo powstala galaz nie bedzie potem pasowala, zostaje
ona cicho usuwana.
%glr-parser   <BISON-GRAMMAR>
%expect-rr 1  <BISON-GRAMMAR>

    /* START */
%start program      /* okresla, ktora regula jest regula startowa programu. */
   
    /* UNIA */
%union {long n;tree t;  /* treeis defined inptypes.h.*/}

    /* TOKENY */
%token NUM FLOAT    /* tokeny bez okreslonej lacznosci ani priorytetu. */
%token <double> NUM /* tokeny z okreslonym typem wartosci semantycznej. */

%left '+' '-'       /* tokeny o lacznosci lewostronnej, im nizej */
%left '*' '/'       /* tym wiekszy priorytet, tokeny jednoznakowe */
                    /* nie muszo byc deklarowane w %token */
       
%right              /* tokeny o lacznosci prawostronnej, im nizej */
%right              /* tym wiekszy priorytet, tokeny jednoznakowe */
                    /* nie muszo byc deklarowane w %token */

%precedence NEG     /* token bez okreslonej lacznosci, zawarty na */
                    /* liscie tylko ze wzgledu na priorytet, im nizej */
                    /* na liscie, tym wiekszy priorytet */

    /* NIETERMINALE */
%nterm <double> exp /* deklaracja nieterminala, ktorego nie mozna */
                    /* zadeklarowac niejawnie za pomoca reguly */

%%
%%


3.7.12 Bison Declaration Summary
Here is a summary of the declarations used to define a grammar:

— Directive: %union
Declare the collection of data types that semantic values may have (see The Collection of Value Types).

— Directive: %token
Declare a terminal symbol (token type name) with no precedence or associativity specified (see Token Type Names).

— Directive: %right
Declare a terminal symbol (token type name) that is right-associative (see Operator Precedence).

— Directive: %left
Declare a terminal symbol (token type name) that is left-associative (see Operator Precedence).

— Directive: %nonassoc
Declare a terminal symbol (token type name) that is nonassociative (see Operator Precedence). Using it in a way that would be associative is a syntax error.

— Directive: %type
Declare the type of semantic values for a nonterminal symbol (see Nonterminal Symbols).

— Directive: %start
Specify the grammar's start symbol (see The Start-Symbol).

— Directive: %expect
Declare the expected number of shift-reduce conflicts (see Suppressing Conflict Warnings)