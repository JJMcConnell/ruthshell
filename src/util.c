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

void moveTokensToYylval(char* yytext) {
    // move old yylval to secondToLastWord
    cleanStringBuffer(secondToLastWord);
    strCopyToBuffer(secondToLastWord, strBuffer);

    // copy yytext to yylval
    cleanStringBuffer(strBuffer);
    strCopyToBuffer(strBuffer, yytext);
    yylval.word = strBuffer;
}

void cleanStringBuffer(char* buffer) {
    *buffer = '\0';   
}

int printStringData(Data* d) {
    printf("%s\n", d->s);
    return 0; // don't break
}

int printIntData(Data* d) {
    printf("%i\n", d->i);
    return 0; // don't break
}

int printKeyData(Data* d) {
    printf("key: %s; value: %s\n", d->key, d->value);
    return 0; // don't break
}
