%{
    #include "braces.tab.h"
    int yylex();
%}
%%
\(      { return LEFT; }
\)      { return RIGHT; }
\n      { return '\n'; }
.       { printf("lexical error"); }
%%

int yywrap() { return 1; }