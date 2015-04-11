#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "ruthshell.h"
#include "util.h"
#include "arglist.h"
#include "y.tab.h"

int main() {
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

/* need for flex and bison */
void yyerror(const char *str) {
    printf("last command: %s\n", yylval.word);
    fprintf(stderr, "error: %s\n", str);
}

int yywrap() {
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
    return EXITSUCCESS;   
}

int alias(void) {

        

}

int aliasAdd(char* name, char* word) {
    
}

int unalias(char* name) {

}

/* for external commands */
int runCmdAndFreeStrings(void) {
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
