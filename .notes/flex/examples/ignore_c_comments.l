%{
    #include <stdio.h>
    int yywrap();
    int yylex();
%}
%%
"/*"        {
            int c;

            for ( ; ; )
                {
                while ( (c = input()) != '*' &&
                        c != EOF )
                    ;    /* eat up text of comment */

                if ( c == '*' )
                    {
                    while ( (c = input()) == '*' )
                        ;
                    if ( c == '/' )
                        break;    /* found the end */
                    }

                if ( c == EOF )
                    {
                    error( "EOF in comment" );
                    break;
                    }
                }
            }
%%
int yywrap() { return 1; }
int main() { return yylex(); }
