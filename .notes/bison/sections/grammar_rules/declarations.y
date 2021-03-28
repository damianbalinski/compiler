%%
| ’-’ exp  %prec NEG    /* informuje, ze dana regula ma taki sam */
                        /* priorytet jak NEG */

stmt:
    expr ’;’  %dprec 1  /* w przypadku niejednoznacznosci pierwszenstwo */
|   decl      %dprec 2  /* ma decl */

%empty                  /* oznaczenie pustej reguly, rownowazne z */
                        /* pozostawieniem pustej linii */

%%
