%{
    #include <stdio.h>
    #include "compiler.tab.h"
    #include "debugger/debugger.h"

    int yywrap();
    int yylex();
%}

DIGIT [0-9]
ID    [_a-z]+

%%
{DIGIT}+    { PR_TOKEN("NUMBER"); return(NUMBER); }
":="        { PR_TOKEN("ASSIGN"); return(ASSIGN); }
"="         { PR_TOKEN("EQ");     return(EQ);     }
"!="        { PR_TOKEN("NE");     return(NE);     }
"<"         { PR_TOKEN("LT");     return(LT);     }
"<="        { PR_TOKEN("LE");     return(LE);     }
">"         { PR_TOKEN("GT");     return(GT);     }
">="        { PR_TOKEN("GE");     return(GE);     }
BEGIN       { PR_TOKEN("T_BEGIN"); return(T_BEGIN); }
DECLARE     { PR_TOKEN("DECLARE"); return(DECLARE); }
DO          { PR_TOKEN("DO");      return(DO);      }
DOWNTO      { PR_TOKEN("DOWNTO");  return(DOWNTO);  }
ELSE        { PR_TOKEN("ELSE");    return(ELSE);    }
END         { PR_TOKEN("END");     return(END);     }
ENDFOR      { PR_TOKEN("ENDFOR");  return(ENDFOR);  }
ENDIF
ENDWHILE
FOR
FROM
IF
READ
REPEAT
THEN
TO
UNTIL
WHILE
WRITE


{ID}        { PR_TOKEN("PIDENTIFIER"); return(PIDENTIFIER); }
[ \t\n]+    ;
.           { PR_TOKEN("OTHER");       return(yytext[0]);   }
%%

int yywrap() { 
    // TEST
    return 0;

    // NON TEST
    // return 1;
}

// TEST
int main()
{
    while(1)
	    yylex();;
    return 0;
}