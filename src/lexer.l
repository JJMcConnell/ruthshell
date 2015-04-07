%{
#include <stdio.h>
#include <string.h>

#include "y.tab.h"
#include "ruthshell.h"
#include "util.h"

%}
%%

cd						   return CD; 
[a-zA-Z0-9\/\-\.*_]+       yylval.word = strdup(yytext); return WORD; /*Free this memory*/ 
\n                         printPrompt(); return NL; /* NL is newline */
[ \t]+                     ; /* do nothing */

%%
