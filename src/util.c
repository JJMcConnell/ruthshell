#include "util.h"
#include "ruthshell.h"
#include "y.tab.h"
#include "lex.yy.h"
#include "arglist.h"

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
    printf("%s\n", d->key);
    return 0; // don't break
}

bool handledCommandWithAlias(char* cmd) {
    LinkedListNode* cur = aliasList->head;

    while (cur != NULL) {
        //printf("cur = %p\n", cur);
        if (streq(cur->data.key, cmd)) {
            // now feed the value and arguments through lex
            char buf[MAXSTRINGLEN];
            buf[0] = '\0';
            strcat(buf, cur->data.value);

            char** cur = argv + 1; // skip argv[0] (invocation)
            while (*cur != NULL) {
                strcat(buf, " ");
                strcat(buf, *cur++);
            }
            strcat(buf, "\n"); // commands end with newline keypress

            // now clear out the old args
            popArgsFreeStrings();

            YY_BUFFER_STATE strScanner = yy_scan_string(buf);
            yyparse();

            YY_BUFFER_STATE stdinScanner = yy_create_buffer(stdin, YY_BUF_SIZE);
            yy_switch_to_buffer(stdinScanner);
            yy_delete_buffer(strScanner);

            return true; // yes, handled
        }

        cur = cur->next;
    }
    return false; // no alias, unhandled
}
