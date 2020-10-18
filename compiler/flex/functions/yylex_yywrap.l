%{
    #include <stdio.h>
    int yywrap();
    int yylex();
    int main();
%}
%%
%%
    /* po wywolaniu rozpoczyna przetwarzanie znakow od miejsca gdzie ostatnio
    skonczyla, przetwarza wejscie do napotkania konca pliku lub do napotkania
    instrukcji return w ktorejkolwiek z akcji, zwraca 0 po napotkaniu konca
    pliku */
    /* yylex() */

    /* wywolywana jednorazowo po przetworzeniu calego pliku.
    jesli zwraca 0 - skaner zaklada ze funkcja ustawila nowy plik do skanowania
                     skaner rozpoczyna skanowanie nowego pliku
    jesli zwraca 1 - skaner zaklda ze skanowanie zostalo zakonczone, konczy
                     dzialanie */
int yywrap()
{
    return 1;
}

    /* funkcja startowa, wywoluje yylex przetwarzajaca plik. */
int main() { return yylex(); }

    /** yymore() */