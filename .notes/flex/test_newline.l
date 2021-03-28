%{
    #include <stdio.h>
    int yywrap();
    int yylex();
%}
%%
aaa     printf( "AAA" );
\n      printf( "." );

%%
int yywrap() { return 1; }
int main()
{
    printf( "<<START>>" );
    yylex(); 
    printf( "<<STOP>>" );
}
