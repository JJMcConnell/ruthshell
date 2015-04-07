%{
#include <stdio.h>
#include <string.h>

#include "y.tab.h"
#include "ruthshell.h"

%}
%%

[a-zA-Z0-9\-\.*_]+       yylval.word = strdup(yytext); return WORD;

\n                       ; 
[ \t]+                   ; /* do nothing */

%%
