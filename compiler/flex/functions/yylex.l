%{
    #include <stdio.h>
    int yywrap();
    int yylex();
    int main();
%}
%%
%%
    /* po wywolaniu rozpoczyna przetwarzanie znakow od miejsca gdzie ostatnio
    skonczyla w strumieniu yyin, przetwarza wejscie do napotkania konca pliku lub do napotkania
    instrukcji return w ktorejkolwiek z akcji, zwraca 0 po napotkaniu konca
    pliku */
    /* yylex() */
int yywrap() { return 1; }
int main() { return yylex(); }