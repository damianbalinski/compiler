    /* KONFIGURACJA */
Zamiast parser LR, tworzy GLR, w przypadku niejednoznacznosci
tworzy równolegle wiele oddzielny parser dla kazdego przypadku.
Jesli nowo powstala galaz nie bedzie potem pasowala, zostaje
ona cicho usuwana.
%glr-parser   <BISON-GRAMMAR>
%expect-rr 1  <BISON-GRAMMAR>

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