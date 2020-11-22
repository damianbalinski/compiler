%{
    #include "calculator.tab.h"
    int yylex();
%}
%option yylineno
%x LEXERR
%%
[0-9]+      { yylval = atoi( yytext ); return NUM; }
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
.           { BEGIN LEXERR; return LERROR; }  /* zjadamy bledna linijke */
<LEXERR>.   ;                                 
<LEXERR>\n  { BEGIN INITIAL;  return '\n'; }
%%

int yywrap() { return 1; }