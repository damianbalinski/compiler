// TODO
%define api.token.prefix {TOK_}


// JEDNAKOWY TYP DLA WSZYSTKICH REGUL
%define api.value.type {double}
#define YYSTYPE double

// WIELE TYPOW
%union      // bison sam okresla unie dostepnych typow
-----------------------------
// zmienna specjalna unia informuje bisona, ze taki typow
// podczas  deklaracji tokenow sa prawdziwymy typami 
%define variableapi.value.type union
-----------------------------
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
