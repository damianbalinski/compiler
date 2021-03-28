// regula przetwarzania sklada sie z produkcji oraz operacji
// produkcja - notacja YACC
// akcja     - wyrazenie w C wyliczajace wartosc semantyczna reguly,
//           - wykonywana w momencie przetwarzania produkcji,
//           - jesli nie podano stosowana jest akcja domyslna $$ = $1

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
