%{
#include <stdio.h>
#include <string.h>

#include "ruthshell.h"
#include "util.h"
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
       NL
       |
       builtincmd NL
       |
       externalcmd NL

builtincmd:
       cd
    
cd:
       CD
       {
           cdHome();
       }
       |
       CD WORD
       {
           cd($2);
       }

externalcmd:
       WORD
       {
           runcmd($1);
       };

%%
