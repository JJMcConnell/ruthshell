#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "ruthshell.h"
#include "util.h"
#include "y.tab.h"

int main() {
    while (1) {
        printPrompt();
        int status = yyparse();
        printf("yyparse() has returned: %d\n", status);
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

/* for external commands */
int runcmd(char* cmd) {
    int retVal = system(cmd);

    return retVal;
}
