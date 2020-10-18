%{
    #include <stdio.h>
    int yywrap();
    int yylex();
%}
%%
aaa         { REJECT; 
              printf( "(Ax3)" ); }
aa          { printf( "(Ax2)" ); }
a           { printf( "(Ax1)" ); }
%%
int yywrap() { return 1; }
int main() { return yylex(); }

/**
 * AKCJE
 * ;            - brak akcji, nie drukuje dopasowanego leksemu
 * ECHO;        - drukuje dopasowany leksem
 * BEGIN cond;   - zmienia stan na cond
 * REJECT;       - odrzuca opasowanie, dalszy kod akcji nie bedzie wykonany, 
                   szuka nastepnego najlepszego dopasowania
 */