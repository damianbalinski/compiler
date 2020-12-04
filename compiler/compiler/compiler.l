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
{DIGIT}+    { DBG_TOKEN("NUMBER");   yylval.val = atoll(yytext); return(NUMBER); }
":="        { DBG_TOKEN("ASSIGN");   return(ASSIGN);   }
"="         { DBG_TOKEN("EQ");       return(EQ);       }
"!="        { DBG_TOKEN("NE");       return(NE);       }
"<"         { DBG_TOKEN("LT");       return(LT);       }
"<="        { DBG_TOKEN("LE");       return(LE);       }
">"         { DBG_TOKEN("GT");       return(GT);       }
">="        { DBG_TOKEN("GE");       return(GE);       }
BEGIN       { DBG_TOKEN("T_BEGIN");  return(T_BEGIN);  }
DECLARE     { DBG_TOKEN("DECLARE");  return(DECLARE);  }
DO          { DBG_TOKEN("DO");       return(DO);       }
DOWNTO      { DBG_TOKEN("DOWNTO");   return(DOWNTO);   }
ELSE        { DBG_TOKEN("ELSE");     return(ELSE);     }
END         { DBG_TOKEN("END");      return(END);      }
ENDFOR      { DBG_TOKEN("ENDFOR");   return(ENDFOR);   }
ENDIF       { DBG_TOKEN("ENDIF");    return(ENDIF);    }
ENDWHILE    { DBG_TOKEN("ENDWHILE"); return(ENDWHILE); }
FOR         { DBG_TOKEN("FOR");      return(FOR);      }
FROM        { DBG_TOKEN("FROM");     return(FROM);     }
IF          { DBG_TOKEN("IF");       return(IF);       }
READ        { DBG_TOKEN("READ");     return(READ);     }
REPEAT      { DBG_TOKEN("REPEAT");   return(REPEAT);   }
THEN        { DBG_TOKEN("THEN");     return(THEN);     }
TO          { DBG_TOKEN("TO");       return(TO);       }
UNTIL       { DBG_TOKEN("UNTIL");    return(UNTIL);    }
WHILE       { DBG_TOKEN("WHILE");    return(WHILE);    }
WRITE       { DBG_TOKEN("WRITE");    return(WRITE);    }
{ID}        { DBG_TOKEN("PIDENTIFIER"); yylval.id = strdup( yytext); return(PIDENTIFIER); }
\[          { DBG_TOKEN("COMMENT_IN");  BEGIN COMMENT;  }
<COMMENT>\] { DBG_TOKEN("COMMENT_OUT"); BEGIN INITIAL; }
<COMMENT>.  ;
<COMMENT>\n ;
[ \t\n]+    ;
.           { DBG_TOKEN("OTHER");       return(yytext[0]);   }
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