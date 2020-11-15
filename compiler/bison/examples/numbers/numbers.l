%{
    #include <stdio.h>
    int yywrap();
    int yylex();
    #include "y.tab.h"
%}
%%
"+"     return '+';
"*"     return "*";
"("     return "(";
")"     return ")";
[0-9]+  return num;
[ \t]   ;
.       printf( "ERROR" );
