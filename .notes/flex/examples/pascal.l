/* scanner for a toy Pascal-like language */

%{
/* need this for the call to atof() below */
#include <math.h>
%}

DIGIT    [0-9]
ID       [a-z][a-z0-9]*

%%

{DIGIT}+    {
            printf( "integer: (%d)\n", atoi( yytext ) );
            }

{DIGIT}+"."{DIGIT}*        {
            printf( "float: (%g)\n", atof( yytext ) );
            }

if|then|begin|end|procedure|function    {
            printf( "keyword: (%s)\n", yytext );
            }

{ID}        printf( "identifier: (%s)\n", yytext );

"+"|"-"|"*"|"/"   {
            printf( "operator: %s\n", yytext );
            }

"{"[^{}\n]*"}"     /* eat up one-line comments */

[ \t\n]+          /* eat up whitespace */

.           printf( "unrecognized character: %s\n", yytext );

%%

int main( int argc, char **argv )
    {
    ++argv, --argc;  /* skip over program name */
    if ( argc > 0 )
            yyin = fopen( argv[0], "r" );
    else
            yyin = stdin;

    yylex();
}