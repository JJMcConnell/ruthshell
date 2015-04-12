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
    char* word;
}

%token <word> WORD
%token <word> BUILTIN
%token <number> CD NL DOUBLE_QUOTE BYE ALIAS UNALIAS

%%

commands:
       | commands command

command:
       NL
       |
       DOUBLE_QUOTE WORD DOUBLE_QUOTE
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
       |
       alias

alias:
       ALIAS
       {
           alias();
       }
       |
       ALIAS WORD WORD
       {
           printf("got alias: key: %s; value: %s\n",
               secondToLastWord, $3);
           aliasAdd(secondToLastWord, $3);
       }
       |
       UNALIAS WORD
       {
           unalias($2);
       }

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
