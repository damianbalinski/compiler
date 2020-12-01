%{
    #include <stdio.h>
    #include <string.h>
    #include "compiler.tab.h"
    #include "debugger/debugger.h"

    int yywrap();
    int yylex();
%}

%option yylineno

DIGIT [0-9]
ID    [_a-z]+

%x      COMMENT

%%
{DIGIT}+    { PR_TOKEN("NUMBER");   yylval.num.val = atoll(yytext); return(NUMBER); }
":="        { PR_TOKEN("ASSIGN");   return(ASSIGN);   }
"="         { PR_TOKEN("EQ");       return(EQ);       }
"!="        { PR_TOKEN("NE");       return(NE);       }
"<"         { PR_TOKEN("LT");       return(LT);       }
"<="        { PR_TOKEN("LE");       return(LE);       }
">"         { PR_TOKEN("GT");       return(GT);       }
">="        { PR_TOKEN("GE");       return(GE);       }
BEGIN       { PR_TOKEN("T_BEGIN");  return(T_BEGIN);  }
DECLARE     { PR_TOKEN("DECLARE");  return(DECLARE);  }
DO          { PR_TOKEN("DO");       return(DO);       }
DOWNTO      { PR_TOKEN("DOWNTO");   return(DOWNTO);   }
ELSE        { PR_TOKEN("ELSE");     return(ELSE);     }
END         { PR_TOKEN("END");      return(END);      }
ENDFOR      { PR_TOKEN("ENDFOR");   return(ENDFOR);   }
ENDIF       { PR_TOKEN("ENDIF");    return(ENDIF);    }
ENDWHILE    { PR_TOKEN("ENDWHILE"); return(ENDWHILE); }
FOR         { PR_TOKEN("FOR");      return(FOR);      }
FROM        { PR_TOKEN("FROM");     return(FROM);     }
IF          { PR_TOKEN("IF");       return(IF);       }
READ        { PR_TOKEN("READ");     return(READ);     }
REPEAT      { PR_TOKEN("REPEAT");   return(REPEAT);   }
THEN        { PR_TOKEN("THEN");     return(THEN);     }
TO          { PR_TOKEN("TO");       return(TO);       }
UNTIL       { PR_TOKEN("UNTIL");    return(UNTIL);    }
WHILE       { PR_TOKEN("WHILE");    return(WHILE);    }
WRITE       { PR_TOKEN("WRITE");    return(WRITE);    }
{ID}        { PR_TOKEN("PIDENTIFIER"); yylval.id = strdup( yytext); return(PIDENTIFIER); }
\[          { PR_TOKEN("COMMENT_IN");  BEGIN COMMENT;  }
<COMMENT>\] { PR_TOKEN("COMMENT_OUT"); BEGIN INITIAL; }
<COMMENT>.  ;
<COMMENT>\n ;
[ \t\n]+    ;
.           { PR_TOKEN("OTHER");       return(yytext[0]);   }
%%

int yywrap() { 
    // TEST
    // return 0;

    // NON TEST
    return 1;
}

// TEST
// int main()
// {
//     while(1)
// 	    yylex();;
//     return 0;
// }