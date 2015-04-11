%{
#include <stdio.h>

#include "y.tab.h"
#include "ruthshell.h"
#include "util.h"

%}
%%

bye                        return BYE;
cd						   return CD; 
alias                      moveTokensToYylval(yytext); return ALIAS;
[a-zA-Z0-9\/\-\.*_]+       moveTokensToYylval(yytext); return WORD; /*Free this memory*/ 
\n                         printPrompt(); return NL; /* NL is newline */
[ \t]+                     ; /* do nothing */
\"					       return DOUBLE_QUOTE;

%%
