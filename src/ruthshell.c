#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#include "ruthshell.h"
#include "util.h"
#include "arglist.h"
#include "y.tab.h"

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
    // set all of the tab counts to 0
    aliasCount = 0;
}

void teardown() {

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

    if(chdir(path) == -1) {

    int value = errno;
    
    if (value == ENOENT){

        printf("Error: the file does not exist \n");
    }
    else if (value == EACCES){
        
        printf("Error: permission is denied for one of the components of the path \n");
    }
    else if (value == ENOTDIR){

        printf("Error: A component of the path is not a directory \n");
    }
    return value;

    }
}

int bye(void) {
    teardown();
    return EXITSUCCESS;   
}

void alias(void) {
    listAllAliases();
}

void aliasAdd(char* name, char* word) {
    addAlias(name, word);
}

void unalias(char* name) {
    removeAlias(name);
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

    if (subProc == -1) { // forking error!
        /* TODO: implement some better error handling with return vals */
        printf("Error: could not fork\n");
        return -1;
    }
    else if (subProc == 0) { // if child process
        // execute the command with argv
        // this will only truly exit if there is an error
        _exit(execvpe(cmd, argv, environ));
    }
    else { // if shell process
        // wait for the forked process to finish
        int status;
        waitpid(subProc, &status, 0);

        if (WIFEXITED(status)){

            int retVal = WEXITSTATUS(status);
            if (retVal != 0)
                            
                if(retVal == 255) {
                    printf("Error: command not found \n");
                }   
             
                else {
                    printf("Error: command returned %i\n", retVal);
                }
        // do some smart error handling with status
        }
    }

    popArgsFreeStrings(); // free argv
    return 0;
}
