$n - wartosc semantyczna n-tego komponentu w regule, numerowanie od 1
$$ - wartosc semantyczna grupowanego wyrazenia
$<itype>n - wartosc unii dla podanego typu

@n - pozycja n-tego komponentu w regule, numerowanie od 1
     parser automatcznie przypisuje @$, biorac poczatek @1
     oraz koniec @n
@1 - pozycja lewego operandu
@3 - pozycja prawego operandu
@3.first_line   - poczatek bledu (wiersz)
@3.first_column - poczatek bledu (kolumna)
@3.last_line    - koniec bledu   (wiersz)
@3.last_column  - koniec bledu   (kolumna)

// AKCJA DOMYSLNA (jesli nie podano)
$$ = $1