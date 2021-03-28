%{
    #include <stdio.h>
    int yywrap();
    int yylex();
%}
%%
                            /* brak wzorca - przekopiowanie tokenu */
a           ;               /* brak akcji - pomijanie wzorca */
z           |               /* symbok | - taka sama akcja jak dla nastepnej reguly */
b           putchar( 'B' ); /* pojedyncza instrukcja */
c           {               /* blok {} - NIE moze zawierac { } */
                putchar( 'C' );
                putchar( 'C' ); 
            }
d           %{              /* blok %{ %} - moze zawierac { } */
                {
                    putchar( 'D' );
                    putchar( 'D' );
                }
            %}
%%
int yywrap() { return 1; }
int main() { return yylex(); }
