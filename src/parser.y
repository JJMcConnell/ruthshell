%{
#include <stdio.h>
#include <string.h>

#include "ruthshell.h"
%}


%union {
    int integer;
    char* string;
    char* word;
}

%token <word> WORD
%token <word> BUILTIN
%token <number> CD NL

%%

commands:
       | commands command

command:
       NL               /* blank line does nothing */
       |
       builtincmd NL
       |
       externalcmd NL

builtincmd:
       cd
    
cd:
       CD
       {
         printf("CD HOME\n");
       }
       |
       CD WORD
       {
         printf("CD %s\n", $2);
       }

externalcmd:
       WORD
       {
           runcmd($1);
       };

%%
