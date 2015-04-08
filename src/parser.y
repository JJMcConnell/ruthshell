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
%token <number> CD NL DOUBLE_QUOTE BYE

%%

commands:
       | commands command

command:
       NL
       |
       DOUBLE_QUOTE WORD DOUBLE_QUOTE
       |
       builtincmd NL
       |
       externalcmd NL

builtincmd:
       cd
       |
       bye
    
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

bye:
       BYE
       {
          return bye();
       }

externalcmd:
       WORD
       {
           runcmd($1);
       };

%%
