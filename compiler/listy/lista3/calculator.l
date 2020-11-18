%{
    #include "calculator.tab.h"
    int yylex ();
%}
%%
[0-9]+      { yylval = atoi(yytext); return NUM; }
\(          return '(';
\)          return ')';
\+          return '+';
\-          return '-';
\*          return '*';
\/          return '/';
\^          return '^';
\n          return '\n';
\\\n        ;
[ \t]       ;
^#.*\n      ;
.           { printf ("lexical error: %s\n", yytext); }

%%

int yywrap() { return 1; }