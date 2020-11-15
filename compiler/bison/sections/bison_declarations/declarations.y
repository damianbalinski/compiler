%token NUM FLOAT    /* tokeny bez okreslonej lacznosci ani priorytetu. */

%left '+' '-'       /* tokeny o lacznosci lewostronnej, im nizej */
%left '*' '/'       /* tym wiekszy priorytet, tokeny jednoznakowe */
                    /* nie muszo byc deklarowane w %token */
       
%right              /* tokeny o lacznosci prawostronnej, im nizej */
%right              /* tym wiekszy priorytet, tokeny jednoznakowe */
                    /* nie muszo byc deklarowane w %token */

%precedence NEG     /* token bez okreslonej lacznosci, zawarty na */
                    /* liscie tylko ze wzgledu na priorytet, im nizej */
                    /* na liscie, tym wiekszy priorytet */
%%
%%