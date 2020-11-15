%{
    #include "y.tab.h"
    int yylex();
%}
%%
"("     { printf( "L" ); return yytext[0]; }
\)      { printf( "R" ); return yytext[0]; }
.       { printf("lexer_error"); }
%%