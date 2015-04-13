%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

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
%token <number> CD NL BYE ALIAS UNALIAS GT LT SETENV PRINTENV UNSETENV
%token <number> GTGT LTLT TWOGT TWOGTAND

%type <word> file

%%
commands:
       |
       commands command

command:
       NL
       |
       cmd.builtin NL
       |
       cmd.external NL
       {
           runCmdAndFreeStrings();
       }
       |
       concreteCommands GT file NL
       {
           redirectStdoutFile($3, O_RDWR | O_CREAT | O_TRUNC);
           runCmdAndFreeStrings();
           resetStdout();
       }
       |
       concreteCommands GTGT file NL
       {
           redirectStdoutFile($3, O_RDWR | O_CREAT | O_APPEND);
           runCmdAndFreeStrings();
           resetStdout();
       }
       |
       concreteCommands TWOGT file NL
       {
           redirectStderrFile($3, O_RDWR | O_CREAT | O_APPEND);
           runCmdAndFreeStrings();
           resetStderr();
       }
       |
       concreteCommands TWOGTAND file NL
       {
           redirectStderrStdout();
           runCmdAndFreeStrings();
           resetStdout();
           resetStderr();
       }
       |
       concreteCommands LT file
       {
           redirectStdinFile($3, O_RDONLY);
           runCmdAndFreeStrings();
           resetStdin();
       }

concreteCommands:
       cmd.builtin
       |
       cmd.external

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

file:
       WORD
       {
           $$ = $1;
       }
       |
       STRING
       {
           $$ = $1;
       }

%%
