%{
    #include <stdio.h>
	#include <stdbool.h>
	#include <math.h>
	#define MAX 1024

	// ERRORS
	#define ERR_FULL_STACK "Blad: przekroczono maksymalny rozmiar stosu\n"
	#define ERR_ARGUMENTS "Blad: za malo argumentow\n"
	#define ERR_OPERATORS "Blad: za malo operatorow\n"
	#define ERR_CHARACTER(S) "Blad: nierozpoznany symbol [%s]\n", S
    
	// PROTOTYPY
	int yywrap();
    int yylex();
	void results();
	void reset();
	void push( int a );
	int pop();

	// ZMIENNE
	int N = 0;			// szczyt stosu
	int V = 0;			// wartosc wyrazenia
	int a, b;			// operandy
	int STACK[MAX];		// stos
	bool EMPTY = false;	// stan stosu (czy ostatnia operacja pop sie powiodla)

%}
INT				[-]?[0-9]+
BLANK			[ \t]
%%
{INT}			push(atoi(yytext));
\+				{ b=pop(); a=pop(); push( a+b ); }
\-				{ b=pop(); a=pop(); push( a-b ); }
\*				{ b=pop(); a=pop(); push( a*b ); }
\/				{ b=pop(); a=pop(); push( a/b ); }
\%				{ b=pop(); a=pop(); push( a%b ); }
\^				{ b=pop(); a=pop(); push( pow(a,b) ); }
{BLANK}*		;
\n				{ 	results();
					reset();
				}
.				{ 	
					printf( ERR_CHARACTER(yytext) );
					reset();
				}
%%

/* Zeruje stos */
void reset()
{
	N = 0;
	yyrestart(stdin);
}

/* Drukuje wynik */
void results()
{
	if ( N != 1)
		printf(ERR_OPERATORS);
	else
		printf("= %d\n", STACK[0]);
}

int yywrap() {

	return 0;
}

/* Dodaje a na szczyt stosu */
void push(int a)
{
	if(EMPTY) {
		/* ostatnia operacja pop nie powiadla sie */
		EMPTY = false;
		return;
	}
	if(N == MAX) {
		printf(ERR_FULL_STACK);
		reset();
		return;
	}
	STACK[N++] = a;
	EMPTY = false;
}

/* Pobiera numer ze szczytu stosu */
int pop()
{
	if(N == 0) {
		printf(ERR_ARGUMENTS);
		EMPTY=true;
		reset();
		return -1;
	}
	return STACK[--N];
}

int main()
{
	yylex();	
	return 0;
}
