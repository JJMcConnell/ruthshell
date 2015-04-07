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

%%

commands:
       | commands command

command:
       builtincmd        
       |
       externalcmd

builtincmd:
    BUILTIN WORD
    {
        printf("cd %s", $1);
    };

externalcmd:
    WORD
    {
        runcmd($1);
    };

%%
