%{
    #include <string.h>
    #include <stdlib.h>
    #include <stdio.h>
    void yyerror (char const* str);
    int yylex();
    int BRACES = 0;
%}
%token LEFT
%token RIGHT

%%
input:
  %empty
| input line
;

line:
 '\n'
| braces '\n'       { printf ("braces: %d\n", BRACES); BRACES=0; }
| error '\n'        { yyerrok; }
;

braces:
  LEFT braces RIGHT { ++BRACES; }
| LEFT RIGHT        { ++BRACES; }
;
%%

void yyerror (char const* str)
{
    fprintf (stderr, "%s\n", str);
}

int main()
{
    return yyparse();
}