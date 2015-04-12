#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "ruthshell.h"
#include "util.h"
#include "arglist.h"
#include "y.tab.h"

LinkedList* aliasList;

char strBuffer[MAXSTRINGLEN];
char secondToLastWord[MAXSTRINGLEN];

int main() {
    init();

    while (1) {
        printPrompt();
        int status = yyparse();

        if (status == EOLFOUND) {
            // only case where bye hasn't yet been called
            printf("\n");
            return bye();
        }
        else if (status == EXITSUCCESS) {
            return 0;
        }
    }
}

void init() {
    if (aliasList == NULL)
        aliasList = createNewLinkedList(DATAPAIR);
}

void teardown() {
    freeList(aliasList);
}

/* need for flex and bison */
void yyerror(const char *str) {
    fprintf(stderr, "\nargv:\n");
    char** cur = argv;
 
    while (*cur != NULL) {
        fprintf(stderr, "%s ", *cur++);
    }
    fprintf(stderr, "\n");

    printf("last command: %s\n", yylval.word);
    fprintf(stderr, "error: %s\n", str);

    // on syntax error, just in case, clear out argv
    if (streq("syntax error", str))
        popArgsFreeStrings();
    
}

int yywrap() {
    // scan forever
    return 1;
} 


/*** Shell Operations ***/
/* builtins */
int cdHome(void) {
    return cd(getenv("HOME"));
}

int cd(char* path) {
    return chdir(path);
}

int bye(void) {
    teardown();
    return EXITSUCCESS;   
}

void alias(void) {
    walkAndExecute(aliasList, printKeyData);
}

void aliasAdd(char* name, char* word) {
    Data d = { .key = name, .value = word };

    // see if this alias is already in the list
    LinkedListNode* curEntry = findNode(aliasList, &d);
    if (curEntry != NULL) {
        // we actually need new dynamic string copies
        curEntry->data.key = strdup(name);
        curEntry->data.value = strdup(word);
    }
    else {
        // this handles the memory for us
        push(aliasList, &d); 
    }
}

void unalias(char* name) {
    // find the data with key name
    LinkedListNode* cur = aliasList->head;

    while (cur != NULL) {
        if (streq(cur->data.key, name)) {
            popNode(aliasList, cur);
            break;
        }
        cur = cur->next;
    }
}

/* for external commands */
int runCmdAndFreeStrings(void) {
    if (handledCommandWithAlias(cmd)) {
        // if already handled, return
        popArgsFreeStrings();
        return 0;
    }

    // first create fork for new process
    pid_t subProc = fork();

    if (subProc == 0) { // if child process
        // execute the command with argv
        execvpe(cmd, argv, environ);
    }
    else { // if shell process
        // wait for the forked process to finish
        int status;
        waitpid(subProc, &status, 0);
    }

    popArgsFreeStrings(); // free argv
    return 0;
}
