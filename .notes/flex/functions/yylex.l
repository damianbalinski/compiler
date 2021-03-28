%{
    #include <stdio.h>
    int yywrap();
    int yylex();
    int main();
%}
%%
%%
    /* po wywolaniu rozpoczyna przetwarzanie znakow od miejsca gdzie ostatnio
    skonczyla w strumieniu yyin, przetwarza wejscie do napotkania nastepnego
    tokena lub konca pliku, zwraca wartosc numeryczna znalezionego tokena lub
    0 po napotkaniu konca lub */

int yywrap() { return 1; }
int main() { return yylex(); }