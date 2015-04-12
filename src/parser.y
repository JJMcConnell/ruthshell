%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ruthshell.h"
#include "util.h"
#include "arglist.h"
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
       {
            doubleQuote($2);
       }
       |
       cmd.builtin NL
       |
       cmd.external NL
       {
           runCmdAndFreeStrings();
       }

cmd.builtin:
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

cmd.external:
       execfile args
       |
       execfile

execfile:
      WORD
      {
          cmd = strdup($1);
          pushArg($1); // first arg is invocation
      }

args:
       WORD
       {
            pushArg($1);
       }
       |
       args WORD
       {
           pushArg($2);
       }

%%
