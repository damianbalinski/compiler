%{
    #include "y.tab.h"
    int yylex();
%}
%%
[0-9]+      { printf( "ret NUM\n"); return NUM; }
[ \t]       ;
\(          return "(";
\)          return ")";
\,          return ",";
.           { printf("lexer_error"); }
%%