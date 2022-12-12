%{
#include <stdio.h>
#include "arquivo_bison.tab.h"
#include <string.h>
%}

DIGIT [0-9]


%%
(" "|\t)
{DIGIT}+ {yylval = atoi(yytext); return NUM;}
\+ {return SOMA;}
\- {return SUB;}
\* {return MULT;}
\n {return 0;}
\) {return ')';}
\( {return '(';}
%%




