%{
    #include <stdio.h>
    int yywrap();
    int yylex();
    int main();
%}
%%
%%
    /* po wywolaniu rozpoczyna przetwarzanie znakow od miejsca gdzie ostatnio
    skonczyla, przetwarza wejscie do napotkania konca pliku lub instrukcji return */
    /* yylex() */

    /* wywolywana jednorazowo po przetworzeniu calego pliku. */
int yywrap()
{
    return 1;
}

    /* funkcja startowa, wywoluje yylex przetwarzajaca plik. */
int main() { return yylex(); }

    /** yymore() */