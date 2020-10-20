%{
    #include <stdio.h>
    #include <stdbool.h>

    #define ERROR(X) printf("\n"X); return 1
    #define TYPE(X) COM_TYPE = X
    
    // BLEDY
    #define ERR_STRING "Blad: znak mowej linii w stringu\n"
    
    // TYPY KOMENTARZY
    #define DOC_TYPE true
    #define NDOC_TYPE false 

    /*
     DOC_MODE - tryb pracy lexera, true zachowuje komentarze dokumentujace
     COM_TYPE - typ komentarza, true oznacza komenarz dokumentujacy
     */
    bool DOC_MODE = false;
    int COM_TYPE = false;
    int yywrap();
    int yylex();
    void comment(const char* str);
%}
    /*
    STR - string,
    LCOM - komentarz jednolinijkowy
    MCOM - komentarz wielolinijkowy
    */
%x      STR
%x      LCOM
%x      MCOM

%%      
    /* STRING */
<INITIAL>\"     { printf( "(" ); BEGIN( STR ); }       /* poczatek str, tylko poza komentarzem */
<STR>\\\"       { printf( "c" ); }                     /* ignorowanie sekwencji \" */
<STR>\"         { printf( ")" ); BEGIN( INITIAL ); }   /* koniec str */
<STR>\\\n       { }                                    /* ignorowanie znaku nowej linii */
<STR>\n         { ERROR( ERR_STRING ); }               /* nieprawidlowy string */
<STR>.          { printf( "C" ); }                     /* w str, najmniejszy priorytet */

    /* SINGLE LINE COMMENTS */
<INITIAL>"//"   { printf( "[" ); comment( yytext ); TYPE( NDOC_TYPE ); BEGIN( LCOM ); }   /* poczatek komentarza jednolinijkowego */
<INITIAL>"///"  { printf( "{" ); comment( yytext ); TYPE( DOC_TYPE ); BEGIN( LCOM ); }    /* poczatek komentarza jednolinijkowego */
<LCOM>\\\n      { comment( yytext ); }                                                    /* znak ucieczki, zostajemy w komentarzu */
<LCOM>\n        { printf( "]" ); comment( yytext ); BEGIN(INITIAL); }                     /* koniec linii, konczymy komentarz jednolinijkowy */
<LCOM>.         { printf( "X" ); }                                                        /* jestesmy w komentarzu */


%%

/**
 * Jesli jestesmy w trybie dokumentowania oraz przetwarzamy
 * komentarz dokumentujacy, zawartosc jest przepisywana.
 * W przeciwnym wypadku komenarz jest ignorowany.
 */
void comment(const char* str) { printf( yytext ); }
int yywrap() { return 1; }
int main() { return yylex(); }
