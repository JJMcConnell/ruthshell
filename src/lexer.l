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
\&                         return AMP;
alias                      return ALIAS;
\>                         return GT;
2\>                        return TWOGT;
2\>\&                      return TWOGTAND;
\>\>                       return GTGT;
\<                         return LT;
unalias                    moveTokensToYylval(yytext); return UNALIAS;
[a-zA-Z0-9\/\-\.*_]+       moveTokensToYylval(yytext); return WORD; /*Free this memory*/ 
\n                         printPrompt(); return NL; /* NL is newline */
[ \t]+                     ; /* do nothing */

\$\{                        return EVESTART;
\}                         return EVEEND; 

\".*\" {
    char buf[MAXSTRINGLEN];
    processStringLiteral(yytext, buf);
    moveTokensToYylval(buf);
    return STRING;
}

%%
