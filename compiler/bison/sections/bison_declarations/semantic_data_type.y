// TODO
%define api.token.prefix {TOK_}

// JEDNAKOWY TYP DLA WSZYSTKICH REGUL
%define api.value.type {double}
#define YYSTYPE double

// WIELE TYPOW
%union      // bison sam okresla unie dostepnych typow
-----------------------------
// zmienna specjalna unia informuje bisona, ze taki typow
// nazwy tokenow nazwanych (a nie tagi typow) sa skladowymi unii
// dostep do tokenow nienazwanych uzyskujemy poprzez rzutowanie
%define api.value.type union
-----------------------------
// tagi typow sa skladowymi unii
%define api.value.type {union MyUnion}
-----------------------------
// tagi typow sa skladowymi unii
#define YYSTYPE union

// TAKI TYPOW
// dla kazdego tokenu generuja odpowiednia nazwe typu
// umieszczana pod YYSTYPE
%token
%nterm
%type

%define api.value.type union
%token <int> INT "integer"
%token <int> 'n'
%nterm <int> expr
%token <char const *> ID "identifier"

// DOSTEP DO TYPU
// pola w strukturze sa nazywane tak samo jak tokeny
yylval.INT = 42;            // weglug id
return INT;
*((int*)&yylval) = 42;      // wedlug typu
