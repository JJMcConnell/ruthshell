#include <stdlib.h>
#include <stdio.h>

#include "ruthshell.h"
#include "y.tab.h"

int main() {
    while (1) {
        int status = yyparse();
        printf("yyparse() has returned: %d", status);
    }


}

void yyerror(const char *str) {
    printf("last command: %s\n", yylval.word);
    fprintf(stderr, "error: %s\n", str);
}

int yywrap() {
    return 1;
} 

int runcmd(char* cmd) {
    int retVal = system(cmd);

    return retVal;
}
