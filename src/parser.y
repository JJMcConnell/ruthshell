%{
#include <stdio.h>
#include <stdlib.h>
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
       cmd.builtin NL
       |
       cmd.external NL

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
       WORD
       {
            printf("got command, no args\n");
       }
       |
       WORD args
       {
            printf("got command with args!\n");
       }

args:
       WORD
       {
            printf("Got an arg\n");
       }
       |
       args WORD
       {
            printf("Got arg with more to follow\n");
       }

%%
