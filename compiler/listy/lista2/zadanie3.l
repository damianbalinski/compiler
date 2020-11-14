%{
    #include <stdio.h>
    #include <stdbool.h>

    #define ERROR(X) printf("\n"X); return 1
    #define TYPE(X) COM_DOC = X
    
    // BLEDY
    #define ERR_STRING "Blad: znak mowej linii w stringu\n"
    
    // TYPY KOMENTARZY
    #define DOC_TYPE true
    #define NDOC_TYPE false 

    /*
     DOC_MODE - tryb pracy lexera, true zachowuje komentarze dokumentujace
     COM_DOC  - typ komentarza, true oznacza komenarz dokumentujacy
     */
    bool DOC_MODE = false;
    int COM_DOC = false;
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
<INITIAL>\"     { ECHO; BEGIN( STR ); }       /* poczatek str, tylko poza komentarzem */
<STR>\\\"       { ECHO; }                     /* ignorowanie sekwencji \" */
<STR>\"         { ECHO; BEGIN( INITIAL ); }   /* koniec str */
<STR>\\\n       { ECHO; }                     /* ignorowanie znaku nowej linii */
<STR>\n         { ERROR( ERR_STRING ); }      /* nieprawidlowy string */
<STR>.          { ECHO; }                     /* w str, najmniejszy priorytet */

    /* KOMENTARZE JEDNOLINIJKOWE */
<INITIAL>"//"   { TYPE( NDOC_TYPE ); comment( yytext ); BEGIN( LCOM ); }   /* poczatek komentarza jednolinijkowego */
<INITIAL>"///"  { TYPE( DOC_TYPE );  comment( yytext ); BEGIN( LCOM ); }   /* poczatek komentarza jednolinijkowego */
<INITIAL>"//!"  { TYPE( DOC_TYPE );  comment( yytext ); BEGIN( LCOM ); }   /* poczatek komentarza jednolinijkowego */
<LCOM>\\\n      { comment( yytext ); }                                     /* znak ucieczki, zostajemy w komentarzu */
<LCOM>\n        { ECHO; BEGIN(INITIAL); }                                  /* koniec linii, konczymy komentarz jednolinijkowy */
<LCOM>.         { comment( yytext ); }                                     /* jestesmy w komentarzu */

    /* KOMENTARZE WIELOLINIKJOWE */
<INITIAL>"/*"       { TYPE( NDOC_TYPE ); comment( yytext ); BEGIN( MCOM ); }    /* poczatek komentarza wielolinijkowego */  
<INITIAL>"/**"      { TYPE( DOC_TYPE ); comment( yytext ); BEGIN( MCOM ); }     /* poczatek komentarza wielolinijkowego */  
<INITIAL>"/*!"      { TYPE( DOC_TYPE ); comment( yytext ); BEGIN( MCOM ); }     /* poczatek komentarza wielolinijkowego */  
<MCOM>[^*\n]*       { comment( yytext ); }                                      /* jestesmy w komentarzu */
<MCOM>"*"+[^*/\n]*  { comment( yytext ); }                                      /* zostawiamy ostatnie *_/ */
<MCOM>\n            { comment( yytext ); }                                      /* nowa linia w komentarzu wielolinijkowym */
<MCOM>"*"+"/"       { comment( yytext ); BEGIN(INITIAL); };                     /* konczymy komentarz */
%%

/**
 * Jesli jestesmy w trybie dokumentowania oraz przetwarzamy
 * komentarz dokumentujacy, zawartosc jest przepisywana.
 * W przeciwnym wypadku komenarz jest ignorowany.
 */
void comment(const char* str)
{
    if (DOC_MODE && COM_DOC )
        printf( str );
}
int yywrap() { return 1; }
int main(int argc, char** argv)
{ 
    if (argc > 1 && strcmp(argv[1], "--doc") == 0) {
        DOC_MODE = true;
        printf("<<DOC MODE>>\n");
    }
    return yylex();
}
