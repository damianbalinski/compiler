%{
    #include "seq.tab.h"
    int yylex ();
%}
%%
[0-9]+      { yylval = atoi(yytext); return NUM; }
\(          return '(';
\)          return ')';
\,          return ',';
\n          return '\n';
[ \t]       ;
.           { printf ("lexical error"); }
%%

int yywrap() { return 1; }