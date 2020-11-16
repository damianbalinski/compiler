// regula przetwarzania sklada sie z produkcji oraz operacji
// produkcja - notacja YACC
// operacja - instrukcja C, wykonywana w momencie dokonywania redukcji
              zgodnej z podana produkcja, kazda produkcja powinna miec
              akcje, jesli jej nie podano stosowana jest akcja domyslna
              $$ = $1

expr: expr ’+’ expr { $$ = $1 + $3; } ;

    // pojedyncza produkcja
E : T
  ;
    // wiele produkcji
E : E '+' T
  | T
  ;

    // produkcja pusta
E : E '+' T
  |
  ;

////////////////////////////////////
/*
 * results - nieterminal
 * components - terminale/nieterminale
 * action - wyrazenie w C wyliczajace wartosc semantyczna reguly
 */

// POJEDYNCZA REGULA
result: compotents... {action}
;

// WIELE REGUL
results:
  components1...
| components2...
...
;

// REGULA PUSTA (dopasowuje sie do pustego lancucha)
rule:
|
;

// REGULA PUSTA (jesli linia z %empty zawiara jakies skladowe
// zglaszany jest blad)
rule:
  %empty
;

// REKURENCJA LEWOSTRONNA (wydajniejsza)
expseq1:
  exp
| expseq1 ’,’ exp /* regula znajduje sie po lewej stronie */
;

// REKURENCJA PRAWOSTRONNA (moze powodowac przepelnienie stosu,
// przed wykonaniem reguly musi umiescic wszystkie skladowe na stosie)
expseq1:
  exp
| exp ’,’ expseq1 /* regula znajduje sie po prawej stronie */
;

// REKURENCJA POSREDNIA
expr:
  primary
| primary ’+’ primary
;
primary:
  constant
| ’(’ expr ’)’
;