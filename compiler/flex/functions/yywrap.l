%{
    #include <stdio.h>
    int yywrap();
    int yylex();
    int main();
%}
%%
%%
    /* wywolywana, jesli funkcja odczytujaca znaki ze strumienia zwrocila wartosc YY_NULL
    jesli zwraca 0 - skaner zaklada ze funkcja ustawila nowy plik do skanowania
                     skaner rozpoczyna skanowanie nowego pliku
    jesli zwraca 1 - skaner zaklda ze skanowanie zostalo zakonczone, konczy
                     dzialanie zwracajac 0 */
int yywrap() { return 1; }
int main() { return yylex(); }
