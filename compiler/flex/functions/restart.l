%{
    #include <stdio.h>
    int yywrap();
    int yylex();
%}
%%

%%
int yywrap() { return 1; }
int main() {
    yylex();
    FILE* file = fopen("/mnt/c/Users/gumis/source/repos/compiler/compiler/flex/test.txt", "r");
    yyrestart(file);
    yylex();

    return 0;
    }

    /* ponownie otwiera strumien file do przetwarzania, 
    nie resetuje stanu poczatkowego */
    /* yyrestart(file) */