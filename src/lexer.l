%{
#include <stdio.h>

#include "y.tab.h"
#include "ruthshell.h"
#include "util.h"

%}

%%
bye                        return BYE;
cd						   return CD; 
setenv                     return SETENV;
unsetenv                   return UNSETENV;
printenv                   return PRINTENV;
alias                      return 
\&                         return 
>                          return GT;
<                          return LT;
unalias                    moveTokensToYylval(yytext); return 
[a-zA-Z0-9\/\-\.*_]+       moveTokensToYylval(yytext); return WORD; /*Free this memory*/ 
\n                         printPrompt(); return NL; /* NL is newline */
[ \t]+                     ; /* do nothing */


\".*\" {
    char buf[MAXSTRINGLEN];
    processStringLiteral(yytext, buf);
    moveTokensToYylval(buf);
    return STRING;
}

%%
