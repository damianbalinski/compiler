// DEKLARACJA %union
// okresla kolekcje dostepnych typow
// wielokrotne unie sa konkatenowane
%union {
    double val;
    symrec *tptr;
}

// DEKLARACJA union
union YYSTYPE
{
    double val;
    symrec *tptr;
};

// UZYCIE
%define api.value.type {union YYSTYPE}
%nterm <val> expr
%token <tptr> ID