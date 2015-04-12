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

/* STRING is a literal, with unescaped chars */
%token <word> WORD STRING
%token <word> BUILTIN
%token <number> CD NL BYE ALIAS UNALIAS SETENV PRINTENV UNSETENV

%%

commands:
       | commands command

command:
       NL
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
       |
       envcommands

alias:
       ALIAS
       {
           alias();
       }
       |
       ALIAS WORD WORD
       {
           aliasAdd(secondToLastWord, $3);
       }
       |
       UNALIAS WORD
       {
           unalias($2);
       }

envcommands:
       SETENV WORD WORD
       {
           
           ruthSetenv(secondToLastWord, $3);
       }
       |
       PRINTENV
       {
           
           ruthPrintenv();
       }
       |
       UNSETENV WORD
       {
           
           ruthUnsetenv($2);
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
       STRING
       {
            pushArg($1);
       }
       |
       args WORD
       {
           pushArg($2);
       }
       |
       args STRING
       {
           pushArg($2);
       }
%%
