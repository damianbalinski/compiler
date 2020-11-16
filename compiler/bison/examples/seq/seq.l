%{
    #include "seq.tab.h"
    int yylex ();
%}
%%
[0-9]+      return NUM;
\(          return '(';
\)          return ')';
\,          return ',';
\n          return '\n';
[ \t]       ;
.           { printf ("lexical error"); }
%%

int yywrap() { return 1; }