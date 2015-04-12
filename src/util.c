#include "util.h"
#include "ruthshell.h"
#include "y.tab.h"

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

void strCopyToBuffer(char* buffer, char* str) {
    do
        *buffer++ = *str;
    while (*str++ != '\0');
}

void processStringLiteral(char* literal, char* buffer) {
    // trim off initial left quotes
    ++literal;

    while (*literal != '\0') {
        if (*literal == '\\')
            ++literal;
        *buffer++ = *literal++;
    }

    // trim final quotes
    *(--buffer) = '\0';
}

void moveTokensToYylval(char* yytext) {
    cleanStringBuffer(strBuffer);
    strCopyToBuffer(strBuffer, yytext);
    yylval.word = strBuffer;
}

void cleanStringBuffer(char* buffer) {
    *buffer = '\0';   
}
