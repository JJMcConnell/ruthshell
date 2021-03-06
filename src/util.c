#include "util.h"
#include "ruthshell.h"
#include "y.tab.h"
#include "lex.yy.h"
#include "arglist.h"
#include "alias.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

int savedStdout;
int savedStderr;
int savedStdin;

/* utils */
void printPrompt(void) {
    // if not interactive, return
    if (!interactive)
        return;

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
   
        *buffer++ = *literal++;
    }

    // trim final quotes
    *(--buffer) = '\0';
}

void moveTokensToYylval(char* yytext) {
    // move old yylval to secondToLastWord
    cleanStringBuffer(secondToLastWord);
    strcpy(secondToLastWord, lastWord);

    // copy yytext to yylval
    cleanStringBuffer(lastWord);
    strcpy(lastWord, yytext);
    yylval.word = lastWord;
}

void cleanStringBuffer(char* buffer) {
    *buffer = '\0';
}

bool handledCommandWithAlias(char* cmd) {
    size_t i = 0;

    for (i = 0; i < aliasCount; ++i) {
        if (streq(aliastab[i].alias, cmd)) {
            // now feed the value and arguments through lex
            char buf[MAXSTRINGLEN];
            buf[0] = '\0';
            strcat(buf, aliastab[i].cmd);

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
    }
    return false; // no alias, unhandled
}

/* IO Redirection */
void redirectStdoutFile(char* fname, int mode) {
    int file = open(fname, mode, 0666);
    savedStdout = dup(STDOUT_FILENO);
    close(STDOUT_FILENO);
    dup2(file, STDOUT_FILENO);
    close(file);
}

void redirectStderrFile(char* fname, int mode) {
    int file = open(fname, mode, 0666);
    savedStderr = dup(STDERR_FILENO);
    close(STDERR_FILENO);
    dup2(file, STDERR_FILENO);
    close(file);
}

void redirectStderrStdout(void) {
    dup2(STDOUT_FILENO, STDERR_FILENO);
}

void redirectStdinFile(char* fname, int mode) {
    int file = open(fname, mode, 0666);
    savedStdin = dup(STDIN_FILENO);
    close(STDIN_FILENO);
    dup2(file, STDIN_FILENO);
    close(file);
}

void resetStdout(void) {
    dup2(savedStdout, STDOUT_FILENO);      
    close(savedStdout);
}

void resetStderr(void) {
    dup2(savedStderr, STDERR_FILENO);      
    close(savedStderr);
}

void resetStdin(void) {
    dup2(savedStdin, STDIN_FILENO);      
    close(savedStdin);
}
