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
%token <number> CD

%%

commands:
       | commands command

command:
       builtincmd        
       |
       externalcmd

builtincmd:
    cd
    
cd:
  CD  
    {
      printf("CD HOME");
      return 0;
    }
  |
  CD WORD
    {
      printf("CD %s", $2);
      return 0;
    }

externalcmd:
    WORD
    {
        runcmd($1);
    };

%%
