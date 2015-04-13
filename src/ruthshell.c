#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>

#include "ruthshell.h"
#include "util.h"
#include "alias.h"
#include "variable.h"
#include "arglist.h"
#include "y.tab.h"

char lastWord[MAXSTRINGLEN];
char secondToLastWord[MAXSTRINGLEN];
int fdRight;
bool interactive;

int main() {
    init();

    if (signal(SIGINT, signal_handler) == SIG_ERR) {

        }

    printPrompt();
    while (1) {
        
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
    varCount = 0;
    savedStdout = STDOUT_FILENO;
    savedStderr = STDERR_FILENO;
    savedStdin = STDIN_FILENO;
    interactive = isatty(STDIN_FILENO) && isatty(STDOUT_FILENO);
}

void teardown() {

}

/* need for flex and bison */
void yyerror(const char *str) {
   /* fprintf(stderr, "\nargv:\n");
    char** cur = argv;
 
    while (*cur != NULL) {
        fprintf(stderr, "%s ", *cur++);
    }
    fprintf(stderr, "\n");

    printf("last command: %s\n", yylval.word);
*/
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
    int chdirStatus = chdir(path);

    if(chdirStatus == -1) {
        int value = errno;

        if (value == ENOENT)
            fprintf(stderr, "Error: the file does not exist \n");
        else if (value == EACCES)
            fprintf(stderr, "Error: permission is denied for one of the components of the path \n");
        else if (value == ENOTDIR)
            fprintf(stderr, "Error: A component of the path is not a directory \n");
    }

    return chdirStatus;
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

void ruthSetenv(char* variable, char* word){
    addVariable(variable, word);
}

void ruthPrintenv(void){
    listAllVariables();
}

void ruthUnsetenv(char* variable){
    removeVariable(variable);
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
        fprintf(stderr, "Error: could not fork\n");
        return -1;
    }
    else if (subProc == 0) { // if child process
        // execute the command with argv
        // this will only truly exit if there is an error
        _exit(execvp(cmd, argv));
    }
    else { // if shell process
        // wait for the forked process to finish
        int status;
        waitpid(subProc, &status, 0);

        if (WIFEXITED(status)) {
            int retVal = WEXITSTATUS(status);
            if (retVal != 0) {
                if(retVal == 255)
                    fprintf(stderr, "Error: command not found \n");
                else
                    fprintf(stderr, "Error: command returned %i\n", retVal);
            }
        }
    }

    popArgsFreeStrings(); // free argv
    return 0;
}

/* for external commands */
int runCmdAndFreeStringsBG(void) {
    if (handledCommandWithAlias(cmd)) {
        // if already handled, return
        popArgsFreeStrings();
        return 0;
    }
// first create fork for new process
    pid_t subProc = fork();

    if (subProc == -1) { // forking error!
        /* TODO: implement some better error handling with return vals */
        fprintf(stderr, "Error: could not fork\n");
        return -1;
    }
    else if (subProc == 0) { // if child process
        // execute the command with argv
        // this will only truly exit if there is an error
        _exit(execvp(cmd, argv));
    }
    /*else { // if shell process
        // wait for the forked process to finish
        int status;
        waitpid(subProc, &status, 0);

        if (WIFEXITED(status)) {
            int retVal = WEXITSTATUS(status);
            if (retVal != 0) {
                if(retVal == 255)
                    printf("Error: command not found \n");
                else
                    printf("Error: command returned %i\n", retVal);
            }
        }
    } */

    popArgsFreeStrings(); // free argv
    return 0;
}

void signal_handler(int signo) {

    if(signo == SIGINT) {
        //printf("recieved SIGINT\n");        
    }
    
}

int runPipedCmdAndFreeStringsLeft(void) {
    int filedes[2];
    pipe(filedes);

    fdRight = filedes[0];

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
        // redirect to pipe
        dup2(filedes[1], STDOUT_FILENO);
    
        // execute the command with argv
        // this will only truly exit if there is an error
        _exit(execvp(cmd, argv));
    }
    else { // if shell process
        // wait for the forked process to finish
        int status;
        waitpid(subProc, &status, 0);

        if (WIFEXITED(status)) {
            int retVal = WEXITSTATUS(status);
            if (retVal != 0) {
                if(retVal == 255)
                    printf("Error: command not found \n");
                else
                    printf("Error: command returned %i\n", retVal);
            }
        }
    }

    popArgsFreeStrings();

    return 0;
}

int runPipedCmdAndFreeStringsRight(void) {
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
        // redirect to pipe
        dup2(fdRight, STDIN_FILENO);
    
        // execute the command with argv
        // this will only truly exit if there is an error
        _exit(execvp(cmd, argv));
    }
    else { // if shell process
        // wait for the forked process to finish
        int status;
        waitpid(subProc, &status, 0);

        if (WIFEXITED(status)) {
            int retVal = WEXITSTATUS(status);
            if (retVal != 0) {
                if(retVal == 255)
                    printf("Error: command not found \n");
                else
                    printf("Error: command returned %i\n", retVal);
            }
        }
    }

    popArgsFreeStrings();
    return 0;
}
