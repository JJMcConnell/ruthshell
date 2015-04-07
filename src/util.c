#include "util.h"
#include "ruthshell.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/* utils */
void printPrompt(void) {
    // check our PROMPT envar
    char* prompt = getenv("PROMPT");
    char buffer[MAXSTRINGLEN];
    *buffer = '\0';
    
    // if empty string
    if (prompt == NULL ||
        *prompt == '\0') {
        // set a default
        strcat(buffer, getenv("USER"));
        strcat(buffer, " $ ");
        prompt = buffer;
    }

    printf("%s", prompt);
}

