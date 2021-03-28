%{
    #include <stdio.h>
    #include "multi.tab.h"
    int yylex();
%}
    
%%
[0-9]+          { yylval.INT = atoi(yytext);   return INT;   }
[0-9]+\.[0-9]*  { yylval.FLOAT = atof(yytext); return FLOAT; }
[ \t]           ;
\n              return '\n';
\+              return '+';
\*              return '*';
.               printf ("lexical error!\n");
%%

int yywrap() { return 1; }